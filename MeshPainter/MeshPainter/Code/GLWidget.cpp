#include "GLWidget.h"
#include "ShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cassert>
#include "Utility.h"
#include <QMouseEvent>
#include "Texture.h"
#include <thread>
#define STBI_MSC_SECURE_CRT
#include <stb_image_write.h>
#include <qmessagebox.h>

GLWidget::GLWidget(QWidget *parent)
	: QOpenGLWidget(parent),
	camera(new Camera()),
	cameraController(camera, glm::vec3(0.0f), 5.0f),
	wireframe(false),
	restart(true),
	strokeWidth(15.0f),
	viewMode(ViewMode::RENDER),
	textureMode(TextureMode::ALBEDO),
	paintTextureWidth(2048),
	paintTextureHeight(2048),
	uvZoom(1.0f),
	uvTranslate(0.0f, 1.0)
{
	setMouseTracking(true);
}

GLWidget::~GLWidget()
{
	// member data destructors have gl objects, so make the context current
	makeCurrent();
}

void GLWidget::setMesh(const IndexedMesh &_mesh)
{
	makeCurrent();

	// free this mesh before allocating storage for the new mesh
	mesh.reset();

	mesh = GLMesh::createMesh(_mesh);
}

void GLWidget::toggleWireframe(bool _enabled)
{
	wireframe = _enabled;
}

void GLWidget::setViewMode(ViewMode _viewMode)
{
	viewMode = _viewMode;
}

void GLWidget::setTextureMode(TextureMode _textureMode)
{
	textureMode = _textureMode;
}

void GLWidget::setPaintColor(const glm::vec3 &_paintColor)
{
	paintColor = _paintColor;
}

void GLWidget::setStrokeWidth(float _strokeWidth)
{
	strokeWidth = _strokeWidth;
}

void GLWidget::setTexture(const std::string & _filepath, TextureMode _textureType)
{
	makeCurrent();

	std::shared_ptr<Texture> tex = Texture::createTexture(_filepath, true);

	// we only use 2d textures
	if (tex->getTarget() != GL_TEXTURE_2D)
	{
		QMessageBox::critical(this, "Unsupported Texture Type", "The texture you tried to load is not supported as it is not 2D.");
		return;
	}

	// bind paint fbo and bind the requested texture as attachment
	funcs->glBindFramebuffer(GL_FRAMEBUFFER, paintFbo);
	funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, getPaintTexture(_textureType), 0);
	funcs->glViewport(0, 0, paintTextureWidth, paintTextureHeight);

	blitShader->bind();
	uSourceTextureB.set(15);

	// bind triangle mesh for fullscreen pass
	funcs->glBindVertexArray(triangleVAO);
	funcs->glEnableVertexAttribArray(0);

	// set user selected texture as source texture for blit shader
	funcs->glActiveTexture(GL_TEXTURE15);
	funcs->glBindTexture(GL_TEXTURE_2D, tex->getId());

	// fullscreen pass
	funcs->glDrawArrays(GL_TRIANGLES, 0, 3);

	// rebind default fbo
	funcs->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void GLWidget::clearActiveTexture(const glm::vec3 &_clearColor)
{
	makeCurrent();

	funcs->glBindFramebuffer(GL_FRAMEBUFFER, paintFbo);
	funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, getPaintTexture(textureMode), 0);
	funcs->glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, 1.0f);
	funcs->glClear(GL_COLOR_BUFFER_BIT);
	funcs->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void GLWidget::clearAllTextures()
{
	makeCurrent();

	funcs->glBindFramebuffer(GL_FRAMEBUFFER, paintFbo);

	// albedo
	{
		funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, material.getAlbedoMap()->getId(), 0);
		funcs->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		funcs->glClear(GL_COLOR_BUFFER_BIT);
	}

	// metallic
	{
		funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, material.getMetallicMap()->getId(), 0);
		funcs->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		funcs->glClear(GL_COLOR_BUFFER_BIT);
	}

	// roughness
	{
		funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, material.getRoughnessMap()->getId(), 0);
		funcs->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		funcs->glClear(GL_COLOR_BUFFER_BIT);
	}

	// ao
	{
		funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, material.getAoMap()->getId(), 0);
		funcs->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		funcs->glClear(GL_COLOR_BUFFER_BIT);
	}

	// emissive
	{
		funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, material.getEmissiveMap()->getId(), 0);
		funcs->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		funcs->glClear(GL_COLOR_BUFFER_BIT);
	}

	// displacement
	{
		funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, material.getDisplacementMap()->getId(), 0);
		funcs->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		funcs->glClear(GL_COLOR_BUFFER_BIT);
	}

	funcs->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void GLWidget::centerCamera()
{
	cameraController.centerCamera();
}

void GLWidget::saveTexture(const std::string &_filepath, TextureMode _textureType)
{
	makeCurrent();

	std::unique_ptr<unsigned char[]> textureData = std::make_unique<unsigned char[]>(paintTextureWidth * paintTextureHeight * 4);

	funcs->glActiveTexture(GL_TEXTURE0);
	funcs->glBindTexture(GL_TEXTURE_2D, getPaintTexture(_textureType));

	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.get());

	// save in seperate thread so that the main window does not get blocked
	std::thread t([textureData = std::move(textureData), _filepath, this]()
	{
		stbi_flip_vertically_on_write(false);
		stbi_write_png(_filepath.c_str(), paintTextureWidth, paintTextureHeight, 4, textureData.get(), 0);
	});
	t.detach();
}

void GLWidget::saveAllTextures(const std::string &_filepath)
{
	std::string formattedTime = Utility::getFormatedTime();

	saveTexture(_filepath + "/" + formattedTime + "_albedo.png", TextureMode::ALBEDO);
	saveTexture(_filepath + "/" + formattedTime + "_metallic.png", TextureMode::METALLIC);
	saveTexture(_filepath + "/" + formattedTime + "_roughness.png", TextureMode::ROUGHNESS);
	saveTexture(_filepath + "/" + formattedTime + "_ambient_occlusion.png", TextureMode::AMBIENT_OCCLUSION);
	saveTexture(_filepath + "/" + formattedTime + "_emissive.png", TextureMode::EMISSIVE);
	saveTexture(_filepath + "/" + formattedTime + "_displacement.png", TextureMode::DISPLACEMENT);
}

float GLWidget::getStrokeWidth() const
{
	return strokeWidth;
}

glm::vec3 GLWidget::getPaintColor() const
{
	return paintColor;
}

Material *GLWidget::getMaterial()
{
	return &material;
}

void GLWidget::initializeGL()
{
	// get gl functions
	funcs = getGLFunctions();

	// setup state
	{
		funcs->glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		funcs->glEnable(GL_DEPTH_TEST);
		funcs->glDepthFunc(GL_LEQUAL);

		funcs->glDisable(GL_STENCIL_TEST);
		funcs->glStencilFunc(GL_ALWAYS, 1, 0xFF);
		funcs->glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

		funcs->glDisable(GL_CULL_FACE);

		funcs->glDisable(GL_BLEND);

		funcs->glLineWidth(1.0f);
		funcs->glEnable(GL_LINE_SMOOTH);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	// create quad mesh for painting
	{
		glm::vec3 positions[] =
		{
			{-0.5f, -0.5f, 0.0f},
			{0.5f, -0.5f, 0.0f},
			{-0.5f, 0.5f, 0.0f},
			{0.5f, 0.5f, 0.0f}
		};

		uint32_t indices[] =
		{
			0, 1, 2, 2, 1, 3
		};

		// create buffers/arrays
		funcs->glGenVertexArrays(1, &quadVAO);
		funcs->glGenBuffers(1, &quadVBO);
		funcs->glGenBuffers(1, &quadEBO);
		funcs->glBindVertexArray(quadVAO);
		funcs->glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		funcs->glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
		funcs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
		funcs->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// vertex positions
		funcs->glEnableVertexAttribArray(0);
		funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

		funcs->glBindVertexArray(0);
	}

	// create triangle mesh for fullscreen rendering (copy imported texture to paint texture)
	{
		glm::vec3 positions[] =
		{
			{ -1.0f, -1.0f, 0.0f },
			{ 3.0f, -1.0f, 0.0f },
			{ -1.0f, 3.0f, 0.0f }
		};

		// create buffers/arrays
		funcs->glGenVertexArrays(1, &triangleVAO);
		funcs->glGenBuffers(1, &triangleVBO);
		funcs->glBindVertexArray(triangleVAO);
		funcs->glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
		funcs->glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

		// vertex positions
		funcs->glEnableVertexAttribArray(0);
		funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

		funcs->glBindVertexArray(0);
	}

	// create grid mesh
	{
		struct GridVertex
		{
			glm::vec3 position;
			glm::vec3 color;
		};

		GridVertex gridVertices[44];

		for (unsigned int i = 0; i < 11; ++i)
		{
			float xPos = (i - 5.0f);
			gridVertices[i * 2] = { glm::vec3(xPos, 0.0f, -5.0f) * 0.1f, (i == 5) ? glm::vec3(0.0f, 0.0f, 1.0f) : glm::vec3(0.2) };
			gridVertices[i * 2 + 1] = { glm::vec3(xPos, 0.0f, 5.0f) * 0.1f, (i == 5) ? glm::vec3(0.0f, 0.0f, 1.0f) : glm::vec3(0.2) };
		}

		for (unsigned int i = 0; i < 11; ++i)
		{
			float yPos = (i - 5.0f);
			gridVertices[22 + i * 2] = { glm::vec3(-5.0f, 0.0f, yPos) * 0.1f, (i == 5) ? glm::vec3(1.0f, 0.0f, 0.0f) : glm::vec3(0.2) };
			gridVertices[22 + i * 2 + 1] = { glm::vec3(5.0f, 0.0f, yPos) * 0.1f, (i == 5) ? glm::vec3(1.0f, 0.0f, 0.0f) : glm::vec3(0.2) };
		}

		// create buffers/arrays
		funcs->glGenVertexArrays(1, &gridVAO);
		funcs->glGenBuffers(1, &gridVBO);
		funcs->glBindVertexArray(gridVAO);
		funcs->glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
		funcs->glBufferData(GL_ARRAY_BUFFER, sizeof(gridVertices), gridVertices, GL_STATIC_DRAW);

		// vertex positions
		funcs->glEnableVertexAttribArray(0);
		funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GridVertex), (void*)0);

		// vertex color
		funcs->glEnableVertexAttribArray(1);
		funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GridVertex), (void*)offsetof(GridVertex, color));

		funcs->glBindVertexArray(0);
	}

	// create axes mesh
	{
		struct AxisVertex
		{
			glm::vec3 position;
			glm::vec3 color;
		};

		const float arrow = 0.05f;

		AxisVertex axisVertices[] =
		{
			// x axis

			{ glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
			{ glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) },

			// arrow
			{ glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
			{ glm::vec3(1.0f - 3.0f * arrow, arrow, arrow), glm::vec3(1.0f, 0.0f, 0.0f) },

			{ glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
			{ glm::vec3(1.0f - 3.0f * arrow, -arrow, arrow), glm::vec3(1.0f, 0.0f, 0.0f) },

			{ glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
			{ glm::vec3(1.0f - 3.0f * arrow, arrow, -arrow), glm::vec3(1.0f, 0.0f, 0.0f) },

			{ glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
			{ glm::vec3(1.0f - 3.0f * arrow, -arrow, -arrow), glm::vec3(1.0f, 0.0f, 0.0f) },

			// y axis

			{ glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
			{ glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) },

			// arrow
			{ glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
			{ glm::vec3(arrow, 1.0f - 3.0f * arrow, arrow), glm::vec3(0.0f, 1.0f, 0.0f) },

			{ glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
			{ glm::vec3(-arrow,1.0f - 3.0f * arrow, arrow), glm::vec3(0.0f, 1.0f, 0.0f) },

			{ glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
			{ glm::vec3(arrow, 1.0f - 3.0f * arrow, -arrow), glm::vec3(0.0f, 1.0f, 0.0f) },

			{ glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
			{ glm::vec3(-arrow, 1.0f - 3.0f * arrow, -arrow), glm::vec3(0.0f, 1.0f, 0.0f) },


			// z axis

			{ glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
			{ glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },

			// arrow
			{ glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
			{ glm::vec3(arrow, arrow, 1.0f - 3.0f * arrow), glm::vec3(0.0f, 0.0f, 1.0f) },

			{ glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
			{ glm::vec3(-arrow, arrow,1.0f - 3.0f * arrow), glm::vec3(0.0f, 0.0f, 1.0f) },

			{ glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
			{ glm::vec3(arrow, -arrow, 1.0f - 3.0f * arrow), glm::vec3(0.0f, 0.0f, 1.0f) },

			{ glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
			{ glm::vec3(-arrow, -arrow, 1.0f - 3.0f * arrow), glm::vec3(0.0f, 0.0f, 1.0f) },

		};

		// create buffers/arrays
		funcs->glGenVertexArrays(1, &axisVAO);
		funcs->glGenBuffers(1, &axisVBO);
		funcs->glBindVertexArray(axisVAO);
		funcs->glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
		funcs->glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);

		// vertex positions
		funcs->glEnableVertexAttribArray(0);
		funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AxisVertex), (void*)0);

		// vertex color
		funcs->glEnableVertexAttribArray(1);
		funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(AxisVertex), (void*)offsetof(AxisVertex, color));

		funcs->glBindVertexArray(0);
	}

	// create shaders
	{
		defaultShader = ShaderProgram::createShaderProgram("Resources/Shaders/default.vert", "Resources/Shaders/default.frag");
		gridShader = ShaderProgram::createShaderProgram("Resources/Shaders/grid.vert", "Resources/Shaders/grid.frag");
		uvShader = ShaderProgram::createShaderProgram("Resources/Shaders/uvView.vert", "Resources/Shaders/uvView.frag");
		paintShader = ShaderProgram::createShaderProgram("Resources/Shaders/paint.vert", "Resources/Shaders/paint.frag");
		renderShader = ShaderProgram::createShaderProgram("Resources/Shaders/render.vert", "Resources/Shaders/render.frag");
		textureShader = ShaderProgram::createShaderProgram("Resources/Shaders/texture.vert", "Resources/Shaders/texture.frag");
		blitShader = ShaderProgram::createShaderProgram("Resources/Shaders/blit.vert", "Resources/Shaders/blit.frag");
	}

	// create uniforms
	{
		// default view mode shader
		uModelViewProjection.create(defaultShader);
		uModel.create(defaultShader);
		uCamPos.create(defaultShader);
		uLineMode.create(defaultShader);
		uLightDir.create(defaultShader);

		// grid shader
		uModelViewProjectionG.create(gridShader);

		// render view mode shader
		uModelViewProjectionMatrixR.create(renderShader);
		uModelMatrixR.create(renderShader);
		uAtlasDataR.create(renderShader);
		uMaterialR.create(renderShader);
		uLightColorR.create(renderShader);
		uLightDirectionR.create(renderShader);
		uCamPosR.create(renderShader);
		albedoMapR.create(renderShader);
		metallicMapR.create(renderShader);
		roughnessMapR.create(renderShader);
		aoMapR.create(renderShader);
		emissiveMapR.create(renderShader);
		uDisplacementMapR.create(renderShader);
		uIrradianceMapR.create(renderShader);
		uPrefilterMapR.create(renderShader);
		uBrdfLUTR.create(renderShader);

		// paint shader
		uTransformationP.create(paintShader);
		uColorP.create(paintShader);

		// texture view mode shader
		uModelViewProjectionT.create(textureShader);
		uTextureT.create(textureShader);

		// uv view mode shader
		uGridModeU.create(uvShader);
		uTransformationU.create(uvShader);
		uTextureU.create(uvShader);

		// blit shader
		uSourceTextureB.create(blitShader);
	}

	// create fbos
	{
		funcs->glGenFramebuffers(1, &fbo);
		funcs->glGenFramebuffers(1, &paintFbo);
	}

	// create dummy attachments. at this point we dont yet know the widget resolution
	createAttachments(1, 1);

	// initialize the camera controller
	cameraController.update(glm::vec2(0.0f), 0.0f, false);

	// create textures for render view mode image based lighting
	irradianceTexture = Texture::createTexture("Resources/Textures/irradiance.dds");
	reflectanceTexture = Texture::createTexture("Resources/Textures/reflectance.dds");
	brdfLUT = Texture::createTexture("Resources/Textures/brdf.dds");

	// bind IBL textures
	{
		funcs->glActiveTexture(GL_TEXTURE7);
		funcs->glBindTexture(irradianceTexture->getTarget(), irradianceTexture->getId());
		funcs->glActiveTexture(GL_TEXTURE8);
		funcs->glBindTexture(reflectanceTexture->getTarget(), reflectanceTexture->getId());
		funcs->glActiveTexture(GL_TEXTURE9);
		funcs->glBindTexture(GL_TEXTURE_2D, brdfLUT->getId());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	// create and initialize paint textures
	{
		material.setAlbedoMap(createTexture(paintTextureWidth, paintTextureHeight));
		material.setMetallicMap(createTexture(paintTextureWidth, paintTextureHeight));
		material.setRoughnessMap(createTexture(paintTextureWidth, paintTextureHeight));
		material.setAoMap(createTexture(paintTextureWidth, paintTextureHeight));
		material.setEmissiveMap(createTexture(paintTextureWidth, paintTextureHeight));
		material.setDisplacementMap(createTexture(paintTextureWidth, paintTextureHeight));

		clearAllTextures();
	}

	Utility::glErrorCheck();
}

void GLWidget::paintGL()
{
	// bind offscreen fbo
	funcs->glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// clear attachments
	const GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	funcs->glDrawBuffers(2, drawBuffers);
	funcs->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// calculate projection matrix
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), width / float(height), 0.01f, 10000.0f);

	// if there is a mesh loaded, render it according to the currently selected view mode
	if (mesh)
	{
		switch (viewMode)
		{

			// the default view mode displays the mesh with some basic lighting and without textures.
			// if wireframe is enabled, a wireframe will be drawn over the mesh
		case ViewMode::DEFAULT:
		{
			defaultShader->bind();

			uModelViewProjection.set(projection * camera->getViewMatrix());
			uModel.set(glm::mat4());
			uCamPos.set(camera->getPosition());
			uLightDir.set(-camera->getForwardDirection());

			mesh->enableVertexAttribArrays();
			uLineMode.set(false);
			mesh->render();

			if (wireframe)
			{
				funcs->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				uLineMode.set(true);
				mesh->render();
				funcs->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			break;
		}

		// texture view mode displays the mesh without lighting. the currently active texture is
		// applied.
		case ViewMode::TEXTURE:
		{
			textureShader->bind();

			uModelViewProjectionT.set(projection * camera->getViewMatrix());
			uTextureT.set(0);

			funcs->glActiveTexture(GL_TEXTURE0);
			funcs->glBindTexture(GL_TEXTURE_2D, getPaintTexture(textureMode));

			mesh->enableVertexAttribArrays();
			mesh->render();
			break;
		}

		// the render view mode draws the mesh with physically- and image based lighting using all textures
		case ViewMode::RENDER:
		{
			renderShader->bind();

			uModelViewProjectionMatrixR.set(projection * camera->getViewMatrix());
			uModelMatrixR.set(glm::mat4());
			uAtlasDataR.set(glm::vec4(1.0f, 1.0f, 0.0f, 0.0f));
			uMaterialR.set(&material);
			uLightColorR.set(glm::vec3(1.0f));
			uLightDirectionR.set(glm::normalize(glm::vec3(1.0f, 1.0f, -1.0f)));
			uCamPosR.set(camera->getPosition());
			albedoMapR.set(0);
			metallicMapR.set(2);
			roughnessMapR.set(3);
			aoMapR.set(4);
			emissiveMapR.set(5);
			uDisplacementMapR.set(6);
			uIrradianceMapR.set(7);
			uPrefilterMapR.set(8);
			uBrdfLUTR.set(9);

			material.bindTextures();

			funcs->glActiveTexture(GL_TEXTURE7);
			funcs->glBindTexture(irradianceTexture->getTarget(), irradianceTexture->getId());
			funcs->glActiveTexture(GL_TEXTURE8);
			funcs->glBindTexture(reflectanceTexture->getTarget(), reflectanceTexture->getId());
			funcs->glActiveTexture(GL_TEXTURE9);
			funcs->glBindTexture(GL_TEXTURE_2D, brdfLUT->getId());

			mesh->enableVertexAttribArrays();
			mesh->render();
			break;
		}

		// the uv view mode displays the uv layout of the mesh using the currently active texture.
		// wireframe mode can be optionally enabled in this view mode
		case ViewMode::UV:
		{
			uvShader->bind();

			funcs->glActiveTexture(GL_TEXTURE0);
			funcs->glBindTexture(GL_TEXTURE_2D, getPaintTexture(textureMode));

			mesh->enableVertexAttribArrays();

			glm::mat3 scale =
			{
				uvZoom, 0.0f, 0.0f,
				0.0f, uvZoom, 0.0f,
				0.0f, 0.0f, 1.0f
			};

			glm::mat3 translate =
			{
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				uvTranslate.x, 1.0 - uvTranslate.y, 1.0f
			};

			uTransformationU.set(translate * scale);
			uTextureU.set(0);

			uGridModeU.set(false);
			mesh->render();
			uGridModeU.set(true);
			if (wireframe)
			{
				funcs->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				mesh->render();
				funcs->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}
		}
	}

	// except for uv view mode grid and axes are always drawn
	if (viewMode != ViewMode::UV)
	{
		// draw grid and axes
		{
			gridShader->bind();

			uModelViewProjectionG.set(projection * camera->getViewMatrix());

			funcs->glBindVertexArray(gridVAO);
			funcs->glEnableVertexAttribArray(0);
			funcs->glEnableVertexAttribArray(1);

			funcs->glDrawArrays(GL_LINES, 0, 44);

			uModelViewProjectionG.set(glm::translate(glm::mat4(), glm::vec3(-0.8f, -0.8f, 0.0f)) * projection * glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -1.0f)) * glm::mat4(glm::mat3(camera->getViewMatrix())) * glm::scale(glm::mat4(), glm::vec3(0.05f)));

			funcs->glBindVertexArray(axisVAO);
			funcs->glEnableVertexAttribArray(0);
			funcs->glEnableVertexAttribArray(1);

			funcs->glClear(GL_DEPTH_BUFFER_BIT);

			funcs->glDrawArrays(GL_LINES, 0, 30);
		}
	}

	// blit from offscreen fbo to default frame buffer
	{
		funcs->glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
		funcs->glReadBuffer(GL_COLOR_ATTACHMENT0);
		funcs->glBindFramebuffer(GL_DRAW_FRAMEBUFFER, defaultFramebufferObject());
		//funcs->glDrawBuffer(GL_BACK);

		funcs->glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	}

	Utility::glErrorCheck();
}

void GLWidget::resizeGL(int _width, int _height)
{
	// the widget was resized, destroy and recreate all attachments
	width = _width;
	height = _height;
	createAttachments(width, height);
}

void GLWidget::mouseMoveEvent(QMouseEvent * _event)
{
	Qt::MouseButtons buttons = _event->buttons();

	QPoint currentPosQ = _event->pos();
	glm::vec2 currentPos = glm::vec2(currentPosQ.x(), currentPosQ.y());
	// delta to last mouse position
	glm::vec2 delta = currentPos - mouseCoord;
	// correct for aspect ratio to make camera movement equally fast in all directions
	delta.y *= width / float(height);
	mouseCoord = currentPos;

	// if we are not in uv view mode, use mouse input to move the camera
	if (viewMode != ViewMode::UV)
	{
		if (buttons.testFlag(Qt::RightButton))
		{
			cameraController.update(delta, 0.0f, false);
			update();
		}
		if (buttons.testFlag(Qt::MiddleButton))
		{
			cameraController.update(delta, 0.0f, true);
			update();
		}
	}
	// if in uv view mode adjust uv map translation
	else
	{
		if (buttons.testFlag(Qt::RightButton))
		{
			uvTranslate += delta / float(width);
			update();
		}
	}

	// in any case, if the left mouse button was pressed, paint into the currently active texture
	if (buttons.testFlag(Qt::LeftButton))
	{
		paint();
		update();
	}
}

void GLWidget::mousePressEvent(QMouseEvent * _event)
{
	Qt::MouseButtons buttons = _event->buttons();
	QPoint currentPosQ = _event->pos();
	mouseCoord = glm::vec2(currentPosQ.x(), currentPosQ.y());

	// if lest mouse button was pressed, restart mouse position and paint
	if (buttons.testFlag(Qt::LeftButton))
	{
		restart = true;
		paint();
		update();
	}
}

void GLWidget::wheelEvent(QWheelEvent *_event)
{
	// if not in uv view mode update camera controller
	if (viewMode != ViewMode::UV)
	{
		cameraController.update(glm::vec2(0.0f), _event->angleDelta().y(), false);
		update();
	}
	// if in uv view mode update zoom
	else
	{
		const float SCROLL_DELTA_MULT = 0.001f;
		uvZoom += _event->angleDelta().y() * SCROLL_DELTA_MULT;
		update();
	}
}

void GLWidget::createAttachments(int _width, int _height)
{
	// this is safe since deleting a 0 value is defined as no-op
	funcs->glDeleteTextures(1, &colorTexture);
	funcs->glDeleteTextures(2, &uvTexture);

	funcs->glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	funcs->glGenTextures(1, &colorTexture);
	funcs->glBindTexture(GL_TEXTURE_2D, colorTexture);
	funcs->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

	funcs->glGenTextures(1, &uvTexture);
	funcs->glBindTexture(GL_TEXTURE_2D, uvTexture);
	funcs->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, _width, _height, 0, GL_RGBA, GL_FLOAT, NULL);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, uvTexture, 0);

	funcs->glGenTextures(1, &depthTexture);
	funcs->glBindTexture(GL_TEXTURE_2D, depthTexture);
	funcs->glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, _width, _height, 0, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, NULL);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	funcs->glDrawBuffers(sizeof(drawBuffers) / sizeof(GLenum), drawBuffers);

	if (funcs->glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		QMessageBox::critical(this, "Failed to initialize Framebuffer", "The framebuffer could not be successfully initialized. The program will now terminate.");
		exit(EXIT_FAILURE);
	}

	funcs->glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// create a texture for painting
std::shared_ptr<Texture> GLWidget::createTexture(int _width, int _height)
{
	GLuint tex;
	funcs->glGenTextures(1, &tex);
	funcs->glBindTexture(GL_TEXTURE_2D, tex);
	funcs->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	return Texture::createTexture(tex, GL_TEXTURE_2D);
}

// return the id of texture of the given texture type
GLuint GLWidget::getPaintTexture(TextureMode _textureMode)
{
	switch (_textureMode)
	{
	case TextureMode::ALBEDO:
	{
		return  material.getAlbedoMap()->getId();
	}
	case TextureMode::METALLIC:
	{
		return  material.getMetallicMap()->getId();
	}
	case TextureMode::ROUGHNESS:
	{
		return  material.getRoughnessMap()->getId();
	}
	case TextureMode::AMBIENT_OCCLUSION:
	{
		return  material.getAoMap()->getId();
	}
	case TextureMode::EMISSIVE:
	{
		return  material.getEmissiveMap()->getId();
	}
	case TextureMode::DISPLACEMENT:
	{
		return  material.getDisplacementMap()->getId();
	}
	}
	return 0;
}

// paint a line from the previous mouse coordinate to the current into the currently active texture
void GLWidget::paint()
{
	// make the opengl context current
	makeCurrent();

	// bind the offscreen fbo and set read buffer to texture coordinate attachment
	funcs->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	funcs->glReadBuffer(GL_COLOR_ATTACHMENT1);

	// we may need to restart the line
	if (restart)
	{
		restart = false;
		prevMouseCoord = mouseCoord;
	}

	// determine the amount of points to draw into the texture
	unsigned int pointCount = glm::ceil(glm::distance(mouseCoord, prevMouseCoord));

	glm::vec2 textureSize(paintTextureWidth, paintTextureHeight);

	// read all texture coordinates on the line
	std::vector<glm::vec2> coords;
	for (unsigned int i = 0; i < pointCount; ++i)
	{
		glm::vec2 coord = glm::mix(prevMouseCoord, mouseCoord, float(i) / pointCount);
		glm::vec4 data;
		funcs->glReadPixels(GLint(coord.x), height - GLint(coord.y), 1, 1, GL_RGBA, GL_FLOAT, &data);

		// a coordinate is only valid if marked by the fragment shader in the previous draw pass
		if (data.b > 0)
		{
			// if there is a previous texcoord available, try to fill in missing points. this trick is
			// unfortunately barely better than not doing it at all, showing the limits of this technique
			//if (!coords.empty())
			//{
			//	glm::vec2 previousCoord(coords.back());
			//	glm::vec2 currentCoord(data);
			//
			//	const float densityMult = 2.0f;
			//	unsigned int fillCount = glm::ceil(glm::distance(currentCoord * textureSize, previousCoord * textureSize)) * densityMult;
			//
			//	for (unsigned int j = 1; j < fillCount; ++j)
			//	{
			//		coords.push_back(glm::mix(previousCoord, currentCoord, float(j) / fillCount));
			//	}
			//}
			coords.push_back(data);
		}
	}

	prevMouseCoord = mouseCoord;

	// bind paint shader
	paintShader->bind();
	// if we are in albedo or emissive mode, use the user selected color, else convert it to grayscale
	uColorP.set((textureMode == TextureMode::ALBEDO || textureMode == TextureMode::EMISSIVE) ? paintColor : glm::vec3(glm::dot(paintColor, { 0.2126f, 0.7152f, 0.0722f })));

	// bind the paint fbo and the current texture
	funcs->glBindFramebuffer(GL_FRAMEBUFFER, paintFbo);
	funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, getPaintTexture(textureMode), 0);

	// set view port
	funcs->glViewport(0, 0, paintTextureWidth, paintTextureHeight);

	// setup blend state
	funcs->glEnable(GL_BLEND);
	funcs->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// bind quad mesh for painting points into the texture
	funcs->glBindVertexArray(quadVAO);
	funcs->glEnableVertexAttribArray(0);

	// iterate over all texture coordinates and draw a point
	for (glm::vec2 &paintCoord : coords)
	{
		glm::mat4 transform = glm::translate(glm::mat4(), glm::vec3(paintCoord * 2.0f - 1.0f, 0.0f))
			* glm::scale(glm::mat4(), glm::vec3((1.0f / paintTextureWidth) * strokeWidth, (1.0f / paintTextureHeight) * strokeWidth, 1.0f));

		uTransformationP.set(transform);

		funcs->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	}

	// reset state to default
	funcs->glDisable(GL_BLEND);
	funcs->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	funcs->glViewport(0, 0, width, height);
}
