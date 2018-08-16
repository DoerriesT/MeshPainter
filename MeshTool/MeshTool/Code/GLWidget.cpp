#include "GLWidget.h"
#include "ShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cassert>
#include "Utility.h"
#include <QMouseEvent>
#include "Texture.h"
#include <iostream>

GLWidget::GLWidget(QWidget *parent)
	: QOpenGLWidget(parent),
	camera(new Camera()),
	cameraController(camera, glm::vec3(0.0f), 1.0f),
	wireframe(false),
	paint(false),
	restart(true),
	viewMode(ViewMode::DEFAULT)
{
	setMouseTracking(true);
}

GLWidget::~GLWidget()
{
	// member data destructors have gl objects, so make the context current
	makeCurrent();
	delete material;
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

void GLWidget::centerCamera()
{
	cameraController.centerCamera();
}

void GLWidget::initializeGL()
{
	funcs = getGLFunctions();

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

	// quad
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

	struct GridVertex
	{
		glm::vec3 position;
		glm::vec3 color;
	};

	// create grid
	{
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

		Utility::glErrorCheck();
	}

	// create axes
	{
		float arrow = 0.05f;

		GridVertex axisVertices[] =
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
		funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GridVertex), (void*)0);

		// vertex color
		funcs->glEnableVertexAttribArray(1);
		funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GridVertex), (void*)offsetof(GridVertex, color));

		funcs->glBindVertexArray(0);

		Utility::glErrorCheck();
	}

	testShader = ShaderProgram::createShaderProgram("Resources/Shaders/default.vert", "Resources/Shaders/default.frag");
	gridShader = ShaderProgram::createShaderProgram("Resources/Shaders/grid.vert", "Resources/Shaders/grid.frag");
	uvShader = ShaderProgram::createShaderProgram("Resources/Shaders/uvView.vert", "Resources/Shaders/uvView.frag");
	paintShader = ShaderProgram::createShaderProgram("Resources/Shaders/paint.vert", "Resources/Shaders/paint.frag");
	renderShader = ShaderProgram::createShaderProgram("Resources/Shaders/render.vert", "Resources/Shaders/render.frag");

	uModelViewProjection.create(testShader);
	uModel.create(testShader);
	uCamPos.create(testShader);
	uLineMode.create(testShader);
	uLightDir.create(testShader);

	uModelViewProjectionG.create(gridShader);

	uModelViewProjectionMatrixR.create(renderShader);
	uModelMatrixR.create(renderShader);
	uAtlasDataR.create(renderShader);
	uMaterialR.create(renderShader);
	uLightColorR.create(renderShader);
	uLightDirectionR.create(renderShader);
	uCamPosR.create(renderShader);

	uTransformationP.create(paintShader);
	uColorP.create(paintShader);

	funcs->glGenFramebuffers(1, &fbo);
	funcs->glGenFramebuffers(1, &paintFbo);

	createAttachments(1, 1);

	cameraController.update(glm::vec2(0.0f), 0.0f, false);

	material = new Material(glm::vec4(0.0, 0.0, 0.0, 1.0));

	irradianceTexture = Texture::createTexture("Resources/Textures/irradiance.dds");
	reflectanceTexture = Texture::createTexture("Resources/Textures/reflectance.dds");
	brdfLUT = Texture::createTexture("Resources/Textures/brdf.dds");

	funcs->glActiveTexture(GL_TEXTURE7);
	funcs->glBindTexture(irradianceTexture->getTarget(), irradianceTexture->getId());
	funcs->glActiveTexture(GL_TEXTURE8);
	funcs->glBindTexture(reflectanceTexture->getTarget(), reflectanceTexture->getId());
	funcs->glActiveTexture(GL_TEXTURE9);
	funcs->glBindTexture(GL_TEXTURE_2D, brdfLUT->getId());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	funcs->glGenTextures(1, &paintTexture);
	funcs->glBindTexture(GL_TEXTURE_2D, paintTexture);
	funcs->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1024, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void GLWidget::paintGL()
{
	funcs->glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	if (paint)
	{
		paint = false;

		static glm::vec2 prevMouseCoord = mouseCoord;

		if (restart)
		{
			restart = false;
			prevMouseCoord = mouseCoord;
		}

		std::vector<glm::vec4> coords;
		
		unsigned int pointCount = glm::round(glm::distance(mouseCoord, prevMouseCoord));

		funcs->glReadBuffer(GL_COLOR_ATTACHMENT1);
		for (unsigned int i = 0; i < pointCount; ++i)
		{
			glm::vec2 coord = glm::mix(prevMouseCoord, mouseCoord, float(i) / pointCount);
			glm::vec4 data;
			funcs->glReadPixels(GLint(coord.x), height - GLint(coord.y), 1, 1, GL_RGBA, GL_FLOAT, &data);
			coords.push_back(data);
		}

		prevMouseCoord = mouseCoord;

		paintShader->bind();
		float strokeWidth = 10.0f;
		uColorP.set(paintColor);

		funcs->glBindFramebuffer(GL_FRAMEBUFFER, paintFbo);
		funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, paintTexture, 0);

		funcs->glViewport(0, 0, 1024, 1024);

		funcs->glEnable(GL_BLEND);
		funcs->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		funcs->glBindVertexArray(quadVAO);
		funcs->glEnableVertexAttribArray(0);

		for (glm::vec4 &data : coords)
		{
			// valid paint coord
			if (data.b > 0)
			{
				glm::vec2 paintCoord(data.x, 1.0f - data.y);

				glm::mat4 transform = glm::translate(glm::mat4(), glm::vec3(paintCoord * 2.0f - 1.0f, 0.0f)) * glm::scale(glm::mat4(), glm::vec3((1.0f / 1024.0f) * strokeWidth, (1.0f / 1024.0f) * strokeWidth, 1.0f));

				uTransformationP.set(transform);
				funcs->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
			}
		}
		

		funcs->glDisable(GL_BLEND);
		funcs->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		funcs->glViewport(0, 0, width, height);
	}

	const GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	funcs->glDrawBuffers(2, drawBuffers);
	funcs->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	Utility::glErrorCheck();

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), width / float(height), 0.01f, 10000.0f);

	if (mesh)
	{
		switch (viewMode)
		{
		case ViewMode::DEFAULT:
		{
			testShader->bind();

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
		case ViewMode::RENDER:
		{
			renderShader->bind();

			uModelViewProjectionMatrixR.set(projection * camera->getViewMatrix());
			uModelMatrixR.set(glm::mat4());
			uAtlasDataR.set(glm::vec4(1.0f, 1.0f, 0.0f, 0.0f));
			uMaterialR.set(material);
			uLightColorR.set(glm::vec3(1.0f));
			uLightDirectionR.set(glm::normalize(glm::vec3(1.0f, 1.0f, -1.0f)));
			uCamPosR.set(camera->getPosition());

			material->bindTextures();

			funcs->glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, paintTexture);

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
		case ViewMode::UV:
		{
			uvShader->bind();
			mesh->enableVertexAttribArrays();
			funcs->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			mesh->render();
			funcs->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		}
	}

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

			funcs->glDisable(GL_DEPTH_TEST);
			funcs->glDepthMask(GL_FALSE);

			funcs->glDrawArrays(GL_LINES, 0, 30);

			funcs->glEnable(GL_DEPTH_TEST);
			funcs->glDepthMask(GL_TRUE);
		}
	}
	Utility::glErrorCheck();
	funcs->glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
	funcs->glReadBuffer(GL_COLOR_ATTACHMENT0);
	funcs->glBindFramebuffer(GL_DRAW_FRAMEBUFFER, defaultFramebufferObject());
	//funcs->glDrawBuffer(GL_BACK);
	
	Utility::glErrorCheck();

	funcs->glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	Utility::glErrorCheck();
}

void GLWidget::resizeGL(int _width, int _height)
{
	width = _width;
	height = _height;
	createAttachments(width, height);
}

void GLWidget::mouseMoveEvent(QMouseEvent * _event)
{
	Qt::MouseButtons buttons = _event->buttons();

	QPoint currentPosQ = _event->pos();
	glm::vec2 currentPos = glm::vec2(currentPosQ.x(), currentPosQ.y());
	static glm::vec2 prevPos;
	glm::vec2 delta = currentPos - prevPos;
	delta.y *= width / float(height);
	prevPos = currentPos;

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
	if (buttons.testFlag(Qt::LeftButton))
	{
		paint = true;
		mouseCoord = currentPos;
		paintColor = glm::vec3(1.0, 0.0, 0.0);
		update();
	}
}

void GLWidget::mousePressEvent(QMouseEvent * _event)
{
	Qt::MouseButtons buttons = _event->buttons();
	QPoint currentPosQ = _event->pos();

	static int c = 0;
	glm::vec3 colors[] = { {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f} };

	if (buttons.testFlag(Qt::LeftButton) && !buttons.testFlag(Qt::RightButton))
	{
		restart = true;
		paint = true;
		mouseCoord = glm::vec2(currentPosQ.x(), currentPosQ.y());
		paintColor = colors[c++ % 3];
		update();
	}
}

void GLWidget::wheelEvent(QWheelEvent *_event)
{
	cameraController.update(glm::vec2(0.0f), _event->angleDelta().y(), false);
	update();
}

void GLWidget::createAttachments(int _width, int _height)
{
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

	Utility::glErrorCheck();

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
		std::cout << "FBO not complete! " << std::endl;
	}

	funcs->glBindFramebuffer(GL_FRAMEBUFFER, 0);

	Utility::glErrorCheck();
}
