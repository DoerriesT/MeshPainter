#version 330 core

const float PI = 3.14159265359;
const int ALBEDO = 1;
const int NORMAL = 2;
const int METALLIC = 4;
const int ROUGHNESS = 8;
const int AO = 16;
const int EMISSIVE = 32;
const int DISPLACEMENT = 64;

const float EXPOSURE = 16.0;

layout(location = 0) out vec4 oFragColor;
layout(location = 1) out vec4 oUv;

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vWorldPos;

struct Material
{
    vec4 albedo;
    float metallic;
    float roughness;
	vec3 emissive;
    int mapBitField;
};

layout(binding = 0) uniform sampler2D albedoMap;
layout(binding = 1) uniform sampler2D normalMap;
layout(binding = 2) uniform sampler2D metallicMap;
layout(binding = 3) uniform sampler2D roughnessMap;
layout(binding = 4) uniform sampler2D aoMap;
layout(binding = 5) uniform sampler2D emissiveMap;
layout(binding = 6) uniform sampler2D uDisplacementMap;
layout(binding = 7) uniform samplerCube uIrradianceMap;
layout(binding = 8) uniform samplerCube uPrefilterMap;
layout(binding = 9) uniform sampler2D uBrdfLUT;

uniform Material uMaterial;
uniform vec3 uLightColor;
uniform vec3 uLightDirection;
uniform vec3 uCamPos;

const float A = 0.15; // shoulder strength
const float B = 0.50; // linear strength
const float C = 0.10; // linear angle
const float D = 0.20; // toe strength
const float E = 0.02; // toe numerator
const float F = 0.30; // toe denominator
const vec3 W = vec3(11.2); // linear white point value

vec3 uncharted2Tonemap(vec3 x)
{
   return ((x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F))-E/F;
}

// based on http://www.thetenthplanet.de/archives/1180
mat3 calculateTBN( vec3 N, vec3 p, vec2 uv )
{
    // get edge vectors of the pixel triangle
    vec3 dp1 = dFdx( p );
    vec3 dp2 = dFdy( p );
    vec2 duv1 = dFdx( uv );
    vec2 duv2 = dFdy( uv );
 
    // solve the linear system
    vec3 dp2perp = cross( dp2, N );
    vec3 dp1perp = cross( N, dp1 );
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;
 
    // construct a scale-invariant frame 
    float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
    return mat3( T * invmax, B * invmax, N );
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a2 = roughness*roughness;
    a2 *= a2;
    float NdotH2 = max(dot(N, H), 0.0);
    NdotH2 *= NdotH2;

    float nom   = a2;
    float denom = NdotH2 * (a2 - 1.0) + 1.0;

    denom = PI * denom * denom;

    return nom / max(denom, 0.0000001);
}

float GeometrySmith(float NdotV, float NdotL, float roughness)
{
	float r = (roughness + 1.0);
    float k = (r*r) / 8.0;
    float ggx2 =  NdotV / max(NdotV * (1.0 - k) + k, 0.0000001);
    float ggx1 = NdotL / max(NdotL * (1.0 - k) + k, 0.0000001);

    return ggx1 * ggx2;
}


vec3 fresnelSchlick(float HdotV, vec3 F0)
{
	float power = (-5.55473 * HdotV - 6.98316) * HdotV;
	return F0 + (1.0 - F0) * pow(2.0, power);
}

vec3 fresnelSchlickRoughness(float HdotV, vec3 F0, float roughness)
{
	float power = (-5.55473 * HdotV - 6.98316) * HdotV;
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(2.0, power);
}

void main()
{
	vec2 texCoord = vTexCoord;
	oUv = vec4(vTexCoord, 1.0, 1.0);

	vec3 N = normalize(vNormal);
	mat3 TBN = calculateTBN(N, vWorldPos, texCoord);

	if((uMaterial.mapBitField & DISPLACEMENT) == DISPLACEMENT)
	{
		const float heightScale = 0.05;
	
		const float minLayers = 8.0;
		const float maxLayers = 32.0;

		vec3 viewDir = normalize(uCamPos - vWorldPos) * TBN;
		float numLayers = mix(maxLayers, minLayers, abs(viewDir.z));

		// the amount to shift the texture coordinates per layer (from vector P)
		vec2 P = viewDir.xy * heightScale; 

		float layerDepth = 1.0 / numLayers;
		vec2 deltaTexCoord = P / numLayers;
	
		// get initial values
		vec2  currentTexCoord  = texCoord;
		float currentDepthMapValue = texture(uDisplacementMap, texCoord).r;
		float previousDepthMapValue = 0.0;
		float currentLayerDepth = 0.0;
		  
		while(currentLayerDepth < currentDepthMapValue)
		{
		    currentTexCoord -= deltaTexCoord;
	
			previousDepthMapValue = currentDepthMapValue;
		    currentDepthMapValue = texture(uDisplacementMap, currentTexCoord).r;  
	
		    currentLayerDepth += layerDepth;  
		}
		
		// get depth after and before collision for linear interpolation
		float afterDepth  = currentDepthMapValue - currentLayerDepth;
		float beforeDepth = previousDepthMapValue - currentLayerDepth + layerDepth;
		 
		// interpolation of texture coordinates
		float weight = afterDepth / (afterDepth - beforeDepth);
		texCoord = mix(currentTexCoord, currentTexCoord + deltaTexCoord, weight);
	}

    vec4 albedo;
    if((uMaterial.mapBitField & ALBEDO) == ALBEDO)
    {
		albedo = texture(albedoMap, texCoord).rgba; 
        albedo.rgb = pow(albedo.rgb, vec3(2.2));
    }
    else
    {
        albedo = uMaterial.albedo;
    }

    if((uMaterial.mapBitField & NORMAL) == NORMAL)
    {
        vec3 tangentSpaceNormal = texture(normalMap, texCoord).xyz * 2.0 - 1.0;
        N = normalize(TBN * tangentSpaceNormal);
    }

    float metallic;
    if((uMaterial.mapBitField & METALLIC) == METALLIC)
    {
        metallic  = texture(metallicMap, texCoord).r;
    }
    else
    {
        metallic = uMaterial.metallic;
    }

    float roughness;
    if((uMaterial.mapBitField & ROUGHNESS) == ROUGHNESS)
    {
        roughness = texture(roughnessMap, texCoord).r;
    }
    else
    {
        roughness = uMaterial.roughness;
    }

    float ao;
    if((uMaterial.mapBitField & AO) == AO)
    {
        ao = texture(aoMap, texCoord).r;
    }
    else
    {
        ao = 1.0;
    }

	vec3 emissive;
	if((uMaterial.mapBitField & EMISSIVE) != 0)
    {
        emissive = uMaterial.emissive * texture(emissiveMap, texCoord).rgb;
    }
    else
    {
        emissive = uMaterial.emissive;
    }
	
	vec3 V = normalize(uCamPos - vWorldPos.xyz);
	float NdotV = max(dot(N, V), 0.0);
	vec3 F0 = mix(vec3(0.04), albedo.rgb, metallic);
	

	vec3 L = normalize(uLightDirection);
	vec3 H = normalize(V + L);
	float NdotL = max(dot(N, L), 0.0);

	// Cook-Torrance BRDF
	float NDF = DistributionGGX(N, H, roughness);
	float G = GeometrySmith(NdotV, NdotL, roughness);
	vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

	vec3 nominator = NDF * G * F;
	float denominator = max(4 * NdotV * NdotL, 0.0000001);

	vec3 specular = nominator / denominator;

	// because of energy conversion kD and kS must add up to 1.0
	vec3 kD = vec3(1.0) - F;
	// multiply kD by the inverse metalness so if a material is metallic, it has no diffuse lighting (and otherwise a blend)
	kD *= 1.0 - metallic;
			
	vec3 directionalLightContribution = vec3((kD * albedo.rgb / PI + specular) * uLightColor * NdotL);
				
	// ambient lighting using IBL
	vec3 kS = fresnelSchlickRoughness(NdotV, F0,roughness);
	kD = 1.0 - kS;
	kD *= 1.0 - metallic;
    
	vec3 irradiance = texture(uIrradianceMap, N).rgb;
	vec3 diffuse = irradiance * albedo.rgb;
    
	// sample both the pre-filter map and the BRDF lut and combine them together as per the Split-Sum approximation to get the IBL specular part.
	const float MAX_REFLECTION_LOD = 4.0;
	vec3 prefilteredColor = textureLod(uPrefilterMap, reflect(-V, N), roughness * MAX_REFLECTION_LOD).rgb;

	vec2 brdf  = textureLod(uBrdfLUT, vec2(NdotV, roughness), 0.0).rg;
	specular = prefilteredColor * (kS * brdf.x + brdf.y);
				
	vec3 ambientLightContribution = vec3((kD * diffuse + specular) * ao);

	oFragColor = vec4(directionalLightContribution + ambientLightContribution + emissive, albedo.a);
	
	oFragColor.rgb = uncharted2Tonemap(oFragColor.rgb * 8.0);
	vec3 whiteScale = 1.0/uncharted2Tonemap(W);
	oFragColor.rgb *= whiteScale;
	
    // gamma correct
    oFragColor.rgb = pow(oFragColor.rgb, vec3(1.0/2.2));
}