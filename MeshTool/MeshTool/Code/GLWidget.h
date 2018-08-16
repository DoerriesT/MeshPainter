#pragma once
#include <QOpenGLWidget>
#include <memory>
#include "Uniform.h"
#include "Mesh.h"
#include "ArcBallCameraController.h"
#include "Material.h"

enum class ViewMode
{
	DEFAULT, RENDER, UV
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
	void centerCamera();
	Material *material;

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int _width, int _height) override;
	void mouseMoveEvent(QMouseEvent *_event) override;
	void mousePressEvent(QMouseEvent *_event) override;
	void wheelEvent(QWheelEvent *_event) override;

private:
	QOpenGLFunctions_3_3_Core * funcs;

	int width;
	int height;
	bool wireframe;
	ViewMode viewMode;

	std::shared_ptr<Camera> camera;
	ArcBallCameraController cameraController;

	std::shared_ptr<GLMesh> mesh;

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
	GLuint paintTexture;

	glm::vec3 paintColor;
	glm::vec2 mouseCoord;
	bool restart;
	bool paint;

	std::shared_ptr<ShaderProgram> testShader;
	std::shared_ptr<ShaderProgram> gridShader;
	std::shared_ptr<ShaderProgram> uvShader;
	std::shared_ptr<ShaderProgram> renderShader;
	std::shared_ptr<ShaderProgram> paintShader;
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

	Uniform<glm::mat4> uModelViewProjectionG = Uniform<glm::mat4>("uModelViewProjection");

	Uniform<glm::mat4> uTransformationP = Uniform<glm::mat4>("uTransformation");
	Uniform<glm::vec3> uColorP = Uniform<glm::vec3>("uColor");

	void createAttachments(int _width, int _height);
};
