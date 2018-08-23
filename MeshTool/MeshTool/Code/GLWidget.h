#pragma once
#include <QOpenGLWidget>
#include <memory>
#include "Uniform.h"
#include "Mesh.h"
#include "ArcBallCameraController.h"
#include "Material.h"

enum class ViewMode
{
	DEFAULT, TEXTURE, RENDER, UV
};

enum class TextureMode
{
	ALBEDO, METALLIC, ROUGHNESS, AMBIENT_OCCLUSION, EMISSIVE, DISPLACEMENT
};

class ShaderProgram;

class GLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent);
	~GLWidget();

	void setMesh(const IndexedMesh &_mesh);
	void toggleWireframe(bool _enabled);
	void setViewMode(ViewMode _viewMode);
	void setTextureMode(TextureMode _textureMode);
	void setPaintColor(const glm::vec3 &_paintColor);
	void setStrokeWidth(float _strokeWidth);
	void setTexture(const std::string &_filepath, TextureMode _textureType);
	void clearActiveTexture(const glm::vec3 &_clearColor);
	void clearAllTextures();
	void centerCamera();
	void saveTexture(const std::string &_filepath, TextureMode _textureType);
	void saveAllTextures(const std::string &_filepath);
	float getStrokeWidth() const;
	glm::vec3 getPaintColor() const;
	Material *getMaterial();

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int _width, int _height) override;
	void mouseMoveEvent(QMouseEvent *_event) override;
	void mousePressEvent(QMouseEvent *_event) override;
	void wheelEvent(QWheelEvent *_event) override;

private:
	QOpenGLFunctions_3_3_Core *funcs;

	int width;
	int height;
	bool wireframe;
	ViewMode viewMode;
	TextureMode textureMode;

	std::shared_ptr<Camera> camera;
	ArcBallCameraController cameraController;

	std::shared_ptr<GLMesh> mesh;
	Material *material;

	GLuint gridVAO;
	GLuint gridVBO;
	GLuint axisVAO;
	GLuint axisVBO;
	GLuint triangleVAO;
	GLuint triangleVBO;
	GLuint quadVAO;
	GLuint quadVBO;
	GLuint quadEBO;

	GLuint fbo;
	GLuint colorTexture;
	GLuint uvTexture;
	GLuint depthTexture;

	GLuint paintFbo;

	GLuint paintTextureWidth;
	GLuint paintTextureHeight;
	glm::vec3 paintColor;
	glm::vec2 mouseCoord;
	glm::vec2 prevMouseCoord;
	float strokeWidth;
	bool restart;
	float uvZoom;
	glm::vec2 uvTranslate;

	std::shared_ptr<ShaderProgram> defaultShader;
	std::shared_ptr<ShaderProgram> gridShader;
	std::shared_ptr<ShaderProgram> uvShader;
	std::shared_ptr<ShaderProgram> renderShader;
	std::shared_ptr<ShaderProgram> paintShader;
	std::shared_ptr<ShaderProgram> textureShader;
	std::shared_ptr<ShaderProgram> blitShader;

	std::shared_ptr<Texture> irradianceTexture;
	std::shared_ptr<Texture> reflectanceTexture;
	std::shared_ptr<Texture> brdfLUT;

	Uniform<glm::mat4> uModelViewProjection = Uniform<glm::mat4>("uModelViewProjection");
	Uniform<glm::mat4> uModel = Uniform<glm::mat4>("uModel");
	Uniform<glm::vec3> uCamPos = Uniform<glm::vec3>("uCamPos");
	Uniform<glm::vec3> uLightDir = Uniform<glm::vec3>("uLightDir");
	Uniform<GLboolean> uLineMode = Uniform<GLboolean>("uLineMode");

	Uniform<glm::mat4> uModelViewProjectionMatrixR = Uniform<glm::mat4>("uModelViewProjectionMatrix");
	Uniform<glm::mat4> uModelMatrixR = Uniform<glm::mat4>("uModelMatrix");
	Uniform<glm::vec4> uAtlasDataR = Uniform<glm::vec4>("uAtlasData"); // x = 1/cols, y = 1/rows, z = texOffsetX, w = texOffsetY
	UniformMaterial uMaterialR = UniformMaterial("uMaterial");
	Uniform<glm::vec3> uLightColorR = Uniform<glm::vec3>("uLightColor");
	Uniform<glm::vec3> uLightDirectionR = Uniform<glm::vec3>("uLightDirection");
	Uniform<glm::vec3> uCamPosR = Uniform<glm::vec3>("uCamPos");
	Uniform<GLint> albedoMapR = Uniform<GLint>("albedoMap");
	Uniform<GLint> metallicMapR = Uniform<GLint>("metallicMap");
	Uniform<GLint> roughnessMapR = Uniform<GLint>("roughnessMap");
	Uniform<GLint> aoMapR = Uniform<GLint>("aoMap");
	Uniform<GLint> emissiveMapR = Uniform<GLint>("emissiveMap");
	Uniform<GLint> uDisplacementMapR = Uniform<GLint>("uDisplacementMap");
	Uniform<GLint> uIrradianceMapR = Uniform<GLint>("uIrradianceMap");
	Uniform<GLint> uPrefilterMapR = Uniform<GLint>("uPrefilterMap");
	Uniform<GLint> uBrdfLUTR = Uniform<GLint>("uBrdfLUT");

	Uniform<glm::mat4> uModelViewProjectionG = Uniform<glm::mat4>("uModelViewProjection");

	Uniform<glm::mat4> uTransformationP = Uniform<glm::mat4>("uTransformation");
	Uniform<glm::vec3> uColorP = Uniform<glm::vec3>("uColor");

	Uniform<glm::mat4> uModelViewProjectionT = Uniform<glm::mat4>("uModelViewProjection");
	Uniform<GLint> uTextureT = Uniform<GLint>("uTexture");

	Uniform<GLboolean> uGridModeU = Uniform<GLboolean>("uGridMode");
	Uniform<glm::mat3> uTransformationU = Uniform<glm::mat3>("uTransformation");
	Uniform<GLint> uTextureU = Uniform<GLint>("uTexture");

	Uniform<GLint> uSourceTextureB = Uniform<GLint>("uSourceTexture");

	void createAttachments(int _width, int _height);
	std::shared_ptr<Texture> createTexture(int _width, int _height);
	GLuint getPaintTexture(TextureMode _textureMode);
	void paint();
};
