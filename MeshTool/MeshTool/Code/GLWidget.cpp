#include "GLWidget.h"
#include "ShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cassert>
#include "Utility.h"
#include <QMouseEvent>

GLWidget::GLWidget(QWidget *parent)
	: QOpenGLWidget(parent),
	brightness(0.0f),
	camera(new Camera()),
	cameraController(camera, glm::vec3(0.0f), 1.0f),
	wireframe(false)
{
	setMouseTracking(true);
}

GLWidget::~GLWidget()
{
	makeCurrent();
}

void GLWidget::setBrightness(float _brightness)
{
	brightness = _brightness;
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

void GLWidget::centerCamera()
{
	cameraController.centerCamera();
}

void GLWidget::initializeGL()
{
	funcs = getGLFunctions();
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

	testShader = ShaderProgram::createShaderProgram("Resources/Shaders/test.vert", "Resources/Shaders/test.frag");
	gridShader = ShaderProgram::createShaderProgram("Resources/Shaders/grid.vert", "Resources/Shaders/grid.frag");

	uModelViewProjection.create(testShader);
	uModel.create(testShader);
	uCamPos.create(testShader);
	uLineMode.create(testShader);

	uModelViewProjectionG.create(gridShader);

	cameraController.update(glm::vec2(0.0f), 0.0f, false);
}

void GLWidget::paintGL()
{
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), width / float(height), 0.01f, 100.0f);


	funcs->glClearColor(0.0f, 1.0f * brightness, 0.0f, 1.0f);
	funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	if (mesh)
	{
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		glm::mat4 model = glm::rotate(glm::mat4(1.0f), time * glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));


		testShader->bind();

		uModelViewProjection.set(projection * camera->getViewMatrix());
		uModel.set(glm::mat4());
		uCamPos.set(camera->getPosition());

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
	}

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

	Utility::glErrorCheck();
}

void GLWidget::resizeGL(int _width, int _height)
{
	width = _width;
	height = _height;
}

void GLWidget::mouseMoveEvent(QMouseEvent * _event)
{
	Qt::MouseButtons buttons = _event->buttons();

	QPoint currentPosQ = _event->pos();
	glm::vec2 currentPos = glm::vec2(currentPosQ.x(), currentPosQ.y());
	static glm::vec2 previousPos;
	glm::vec2 delta = currentPos - previousPos;
	delta.y *= width / float(height);
	previousPos = currentPos;

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

void GLWidget::wheelEvent(QWheelEvent *_event)
{
	cameraController.update(glm::vec2(0.0f), _event->angleDelta().y(), false);
	update();
}
