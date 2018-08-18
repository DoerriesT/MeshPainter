#include "MeshTool.h"
#include "OBJLoader.h"
#include <qfiledialog.h>
#include <thread>
#include <qtimer.h>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>
#include "Texture.h"
#include "HalfEdgeMesh.h"

float test;

MeshTool::MeshTool(QWidget *parent)
	: QMainWindow(parent),
	loadingMesh(false)
{
	setupUi(this);
	viewModeGroup = new QActionGroup(this);
	viewModeGroup->addAction(actionDefaultView);
	viewModeGroup->addAction(actionTextureView);
	viewModeGroup->addAction(actionRenderView);
	viewModeGroup->addAction(actionUvView);

	textureModeGroup = new QActionGroup(this);
	textureModeGroup->addAction(actionActivateAlbedoTexture);
	textureModeGroup->addAction(actionActivateMetallicTexture);
	textureModeGroup->addAction(actionActivateRoughnessTexture);
	textureModeGroup->addAction(actionActivateAmbientOcclusionTexture);
	textureModeGroup->addAction(actionActivateEmissiveTexture);
	textureModeGroup->addAction(actionActivateDisplacementTexture);
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

void MeshTool::on_actionDefaultView_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setViewMode(ViewMode::DEFAULT);
		openGLWidget->update();
	}
}

void MeshTool::on_actionTextureView_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setViewMode(ViewMode::TEXTURE);
		openGLWidget->update();
	}
}

void MeshTool::on_actionRenderView_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setViewMode(ViewMode::RENDER);
		openGLWidget->update();
	}
}

void MeshTool::on_actionUvView_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setViewMode(ViewMode::UV);
		openGLWidget->update();
	}
}

void MeshTool::on_actionActivateAlbedoTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::ALBEDO);
		openGLWidget->update();
	}
}

void MeshTool::on_actionActivateMetallicTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::METALLIC);
		openGLWidget->update();
	}
}

void MeshTool::on_actionActivateRoughnessTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::ROUGHNESS);
		openGLWidget->update();
	}
}

void MeshTool::on_actionActivateAmbientOcclusionTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::AMBIENT_OCCLUSION);
		openGLWidget->update();
	}
}

void MeshTool::on_actionActivateEmissiveTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::EMISSIVE);
		openGLWidget->update();
	}
}

void MeshTool::on_actionActivateDisplacementTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::DISPLACEMENT);
		openGLWidget->update();
	}
}

void MeshTool::on_actionAlbedoSetColor_triggered()
{
	glm::vec3 prevColor = glm::vec3(openGLWidget->material->getAlbedo()) * 255.0f;
	QColorDialog colorDialog({ int(prevColor.r), int(prevColor.g), int(prevColor.b) }, this);
	if (colorDialog.exec())
	{
		QColor qcolor = colorDialog.currentColor();
		double r, g, b;
		qcolor.getRgbF(&r, &g, &b);
		openGLWidget->material->setAlbedo({ r, g, b, 1.0 });
		openGLWidget->update();
	}
}

void MeshTool::on_actionAlbedoAddTexture_triggered()
{
	if (openGLWidget->material->getAlbedoMap())
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Add Texture");
		msgBox.setText("There is already an albedo texture.");
		msgBox.exec();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Add Texture");
		msgBox.setText("Add albedo texture?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Yes);

		if (msgBox.exec() == QMessageBox::Yes)
		{
			openGLWidget->addTexture(TextureMode::ALBEDO);
			openGLWidget->update();
		}
	}
}

void MeshTool::on_actionAlbedoDeleteTexture_triggered()
{
	if (openGLWidget->material->getAlbedoMap())
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Delete Texture");
		msgBox.setText("Are you sure you want to delete the albedo texture?");
		msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Yes);

		if (msgBox.exec() == QMessageBox::Yes)
		{
			openGLWidget->material->setAlbedoMap(nullptr);
			openGLWidget->update();
		}
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Delete Texture");
		msgBox.setText("No Texture to delete.");
		msgBox.exec();
	}
}

void MeshTool::on_actionMetallicSetValue_triggered()
{
	double result = QInputDialog::getDouble(this, tr("Set Metallic"), tr("Set Metallic"), openGLWidget->material->getMetallic(), 0.0, 1.0);
	openGLWidget->material->setMetallic(float(result));
	openGLWidget->update();
}

void MeshTool::on_actionMetallicAddTexture_triggered()
{
	if (openGLWidget->material->getMetallicMap())
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Add Texture");
		msgBox.setText("There is already a metallic texture.");
		msgBox.exec();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Add Texture");
		msgBox.setText("Add metallic texture?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Yes);

		if (msgBox.exec() == QMessageBox::Yes)
		{
			openGLWidget->addTexture(TextureMode::METALLIC);
			openGLWidget->update();
		}
	}
}

void MeshTool::on_actionMetallicDeleteTexture_triggered()
{
	if (openGLWidget->material->getMetallicMap())
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Delete Texture");
		msgBox.setText("Are you sure you want to delete the metallic texture?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Yes);

		if (msgBox.exec() == QMessageBox::Yes)
		{
			openGLWidget->material->setMetallicMap(nullptr);
			openGLWidget->update();
		}
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Delete Texture");
		msgBox.setText("No Texture to delete.");
		msgBox.exec();
	}
}

void MeshTool::on_actionRoughnessSetValue_triggered()
{
	double result = QInputDialog::getDouble(this, tr("Set Roughness"), tr("Set Roughness"), openGLWidget->material->getRoughness(), 0.0, 1.0);
	openGLWidget->material->setRoughness(float(result));
	openGLWidget->update();
}

void MeshTool::on_actionRoughnessAddTexture_triggered()
{
	if (openGLWidget->material->getRoughnessMap())
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Add Texture");
		msgBox.setText("There is already a roughness texture.");
		msgBox.exec();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Add Texture");
		msgBox.setText("Add roughness texture?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Yes);

		if (msgBox.exec() == QMessageBox::Yes)
		{
			openGLWidget->addTexture(TextureMode::ROUGHNESS);
			openGLWidget->update();
		}
	}
}

void MeshTool::on_actionRoughnessDeleteTexture_triggered()
{
	if (openGLWidget->material->getRoughnessMap())
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Delete Texture");
		msgBox.setText("Are you sure you want to delete the roughness texture?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Yes);

		if (msgBox.exec() == QMessageBox::Yes)
		{
			openGLWidget->material->setRoughnessMap(nullptr);
			openGLWidget->update();
		}
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Delete Texture");
		msgBox.setText("No Texture to delete.");
		msgBox.exec();
	}
}

void MeshTool::on_actionAmbientOcclusionAddTexture_triggered()
{
	if (openGLWidget->material->getAoMap())
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Add Texture");
		msgBox.setText("There is already an ambient occlusion texture.");
		msgBox.exec();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Add Texture");
		msgBox.setText("Add ambient occlusion texture?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Yes);

		if (msgBox.exec() == QMessageBox::Yes)
		{
			openGLWidget->addTexture(TextureMode::AMBIENT_OCCLUSION);
			openGLWidget->update();
		}
	}
}

void MeshTool::on_actionAmbientOcclusionDeleteTexture_triggered()
{
	if (openGLWidget->material->getAoMap())
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Delete Texture");
		msgBox.setText("Are you sure you want to delete the ambient occlusion texture?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Yes);

		if (msgBox.exec() == QMessageBox::Yes)
		{
			openGLWidget->material->setAoMap(nullptr);
			openGLWidget->update();
		}
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Delete Texture");
		msgBox.setText("No Texture to delete.");
		msgBox.exec();
	}
}

void MeshTool::on_actionEmissiveSetEmissiveColor_triggered()
{
	glm::vec3 prevColor = glm::vec3(openGLWidget->material->getEmissive()) * 255.0f;
	QColorDialog colorDialog({ int(prevColor.r), int(prevColor.g), int(prevColor.b) }, this);
	if (colorDialog.exec())
	{
		QColor qcolor = colorDialog.currentColor();
		double r, g, b;
		qcolor.getRgbF(&r, &g, &b);
		openGLWidget->material->setEmissive({ r, g, b });
		openGLWidget->update();
	}
}

void MeshTool::on_actionEmissiveAddTexture_triggered()
{
	if (openGLWidget->material->getEmissiveMap())
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Add Texture");
		msgBox.setText("There is already an emissive texture.");
		msgBox.exec();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Add Texture");
		msgBox.setText("Add emissive texture?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Yes);

		if (msgBox.exec() == QMessageBox::Yes)
		{
			openGLWidget->addTexture(TextureMode::EMISSIVE);
			openGLWidget->update();
		}
	}
}

void MeshTool::on_actionEmissiveDeleteTexture_triggered()
{
	if (openGLWidget->material->getEmissiveMap())
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Delete Texture");
		msgBox.setText("Are you sure you want to delete the emissive texture?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Yes);

		if (msgBox.exec() == QMessageBox::Yes)
		{
			openGLWidget->material->setEmissiveMap(nullptr);
			openGLWidget->update();
		}
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Delete Texture");
		msgBox.setText("No Texture to delete.");
		msgBox.exec();
	}
}

void MeshTool::on_actionDisplacementAddTexture_triggered()
{
	if (openGLWidget->material->getDisplacementMap())
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Add Texture");
		msgBox.setText("There is already a displacement texture.");
		msgBox.exec();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Add Texture");
		msgBox.setText("Add displacement texture?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Yes);

		if (msgBox.exec() == QMessageBox::Yes)
		{
			openGLWidget->addTexture(TextureMode::DISPLACEMENT);
			openGLWidget->update();
		}
	}
}

void MeshTool::on_actionDisplacementDeleteTexture_triggered()
{
	if (openGLWidget->material->getDisplacementMap())
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Delete Texture");
		msgBox.setText("Are you sure you want to delete the displacement texture?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Yes);

		if (msgBox.exec() == QMessageBox::Yes)
		{
			openGLWidget->material->setDisplacementMap(nullptr);
			openGLWidget->update();
		}
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Delete Texture");
		msgBox.setText("No Texture to delete.");
		msgBox.exec();
	}
}

void MeshTool::on_actionSetStrokeWidth_triggered()
{
	double result = QInputDialog::getDouble(this, tr("Set Stroke Width"), tr("Set Stroke Width"), openGLWidget->getStrokeWidth(), 1.0, 50.0);
	openGLWidget->setStrokeWidth(float(result));
	openGLWidget->update();
}

void MeshTool::on_actionSetPaint_triggered()
{
	glm::vec3 prevColor = openGLWidget->getPaintColor() * 255.0f;
	QColorDialog colorDialog({ int(prevColor.r), int(prevColor.g), int(prevColor.b )}, this);
	if (colorDialog.exec())
	{
		QColor qcolor = colorDialog.currentColor();
		double r, g, b;
		qcolor.getRgbF(&r, &g, &b);
		openGLWidget->setPaintColor({r, g, b});
		openGLWidget->update();
	}
}

void MeshTool::on_actionFill_triggered()
{
	openGLWidget->fillActiveTexture();
	openGLWidget->update();
}

void MeshTool::on_actionOpen_triggered()
{
	// get file path
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Mesh File"), "",
		tr("Wavefront OBJ File (*.obj)"));

	// get lock on bool to check if there is already a loading operation going on
	std::lock_guard<std::mutex> lockCheck(loadingMeshMutex);

	// only continue if a file was selected and we are not already loading a mesh
	if (!fileName.isEmpty() && !loadingMesh)
	{
		// set flag that a mesh loading operation is going on
		loadingMesh = true;
		MeshTool *meshTool = this;

		// start thread to load mesh
		std::thread meshLoadThread([fileName, meshTool]()
		{
			// in order to use QTimer::singleShot, we need a QEventLoop
			QEventLoop loop;
			Q_UNUSED(loop)

			// allocate on heap to avoid unnecessary copy when posting to gui thread
			IndexedMesh *indexedMesh =  new IndexedMesh(OBJLoader::loadOBJ(fileName.toLatin1().data()));

			// execture on gui thread
			QTimer::singleShot(0, qApp, [indexedMesh, meshTool]()
			{
				// create GLMesh
				meshTool->openGLWidget->setMesh(*indexedMesh);
				// the GLMesh created in GLWidget holds a copy of indexedMesh, so delete this instance
				delete indexedMesh;

				meshTool->openGLWidget->update();

				// acquire lock to signal that mesh loading is done
				std::lock_guard<std::mutex> lockReset(meshTool->loadingMeshMutex);
				meshTool->loadingMesh = false;
			});
		});
		meshLoadThread.detach();
	}
}
