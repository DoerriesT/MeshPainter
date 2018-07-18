#include "MeshTool.h"
#include "OBJLoader.h"
#include <qfiledialog.h>

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
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Mesh File"), "",
		tr("Wavefront OBJ File (*.obj)"));

	if (!fileName.isEmpty())
	{
		IndexedMesh indexedMesh = OBJLoader::loadOBJ(fileName.toLatin1().data());

		openGLWidget->setMesh(indexedMesh);
		openGLWidget->update();
	}
}
