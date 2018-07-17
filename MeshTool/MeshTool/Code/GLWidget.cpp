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
	cameraController(camera, glm::vec3(0.0f), 1.0f)
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
	mesh = GLMesh::createMesh(_mesh);
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
	
	testShader = ShaderProgram::createShaderProgram("Resources/Shaders/test.vert", "Resources/Shaders/test.frag");
	uModelViewProjection.create(testShader);
	uModel.create(testShader);
	uCamPos.create(testShader);
	uLineMode.create(testShader);

	cameraController.update(glm::vec2(0.0f), 0.0f, false);
}

void GLWidget::paintGL()
{
	funcs->glClearColor(0.0f, 1.0f * brightness, 0.0f, 1.0f);
	funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	if (mesh)
	{
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		glm::mat4 model = glm::rotate(glm::mat4(1.0f), time * glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), width/float(height), 0.01f, 100.0f);

		testShader->bind();

		uModelViewProjection.set(projection * camera->getViewMatrix());
		uModel.set(glm::mat4());
		uCamPos.set(camera->getPosition());

		mesh->enableVertexAttribArrays();
		uLineMode.set(false);
		mesh->render();
		//funcs->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//uLineMode.set(true);
		//mesh->render();
		//funcs->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
