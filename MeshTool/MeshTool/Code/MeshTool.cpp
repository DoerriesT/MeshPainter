#include "MeshTool.h"
#include "Mesh.h"
#include "OBJLoader.h"

MeshTool::MeshTool(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void MeshTool::on_brightnessSlider_sliderMoved(int _val)
{
	printf("%d\n", _val);
	ui.openGLWidget->setBrightness(_val / 100.0f);
	ui.openGLWidget->update();
}

void MeshTool::on_pushButton_clicked()
{
	static bool loaded = false;

	if (!loaded)
	{
		IndexedMesh indexedMesh = OBJLoader::loadOBJ("Resources/Models/dragon.obj");

		ui.openGLWidget->setMesh(indexedMesh);
		ui.openGLWidget->update();

		loaded = true;
	}
}
