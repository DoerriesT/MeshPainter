#pragma once
#include <QOpenGLWidget>
#include <memory>
#include "Uniform.h"
#include "Mesh.h"
#include "ArcBallCameraController.h"

class ShaderProgram;

class GLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent);
	~GLWidget();

	void setBrightness(float _brightness);
	void setMesh(const IndexedMesh &_mesh);
	void toggleWireframe(bool _enabled);
	void centerCamera();

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int _width, int _height) override;
	void mouseMoveEvent(QMouseEvent *_event) override;
	void wheelEvent(QWheelEvent *_event) override;

private:
	QOpenGLFunctions_3_3_Core * funcs;

	float brightness;
	int width;
	int height;
	bool wireframe;

	std::shared_ptr<Camera> camera;
	ArcBallCameraController cameraController;

	std::shared_ptr<GLMesh> mesh;

	GLuint gridVAO;
	GLuint gridVBO;
	GLuint axisVAO;
	GLuint axisVBO;

	std::shared_ptr<ShaderProgram> testShader;
	std::shared_ptr<ShaderProgram> gridShader;

	Uniform<glm::mat4> uModelViewProjection = Uniform<glm::mat4>("uModelViewProjection");
	Uniform<glm::mat4> uModel = Uniform<glm::mat4>("uModel");
	Uniform<glm::vec3> uCamPos = Uniform<glm::vec3>("uCamPos");
	Uniform<GLboolean> uLineMode = Uniform<GLboolean>("uLineMode");

	Uniform<glm::mat4> uModelViewProjectionG = Uniform<glm::mat4>("uModelViewProjection");
};
