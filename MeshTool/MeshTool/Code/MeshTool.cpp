#include "MeshTool.h"
#include "OBJLoader.h"

MeshTool::MeshTool(QWidget *parent)
	: QMainWindow(parent)
{
	setupUi(this);
}

MeshTool::~MeshTool()
{
}

void MeshTool::on_actionCenterCamera_triggered()
{
	openGLWidget->centerCamera();
	openGLWidget->update();
}

void MeshTool::on_actionToggleWireframe_toggled(bool _enabled)
{
	openGLWidget->toggleWireframe(_enabled);
	openGLWidget->update();
}

void MeshTool::on_actionOpen_triggered()
{
	static bool loaded = false;

	if (!loaded)
	{
		IndexedMesh indexedMesh = OBJLoader::loadOBJ("Resources/Models/teapot.obj");

		openGLWidget->setMesh(indexedMesh);
		openGLWidget->update();

		loaded = true;
	}
}
