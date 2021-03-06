#include "MeshPainter.h"
#include "OBJLoader.h"
#include <qfiledialog.h>
#include <thread>
#include <qtimer.h>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>

MeshPainter::MeshPainter(QWidget *parent)
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

MeshPainter::~MeshPainter()
{
}

void MeshPainter::on_actionCenterCamera_triggered()
{
	openGLWidget->centerCamera();
	openGLWidget->update();
}

void MeshPainter::on_actionToggleWireframe_toggled(bool _enabled)
{
	openGLWidget->toggleWireframe(_enabled);
	openGLWidget->update();
}

void MeshPainter::on_actionDefaultView_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setViewMode(ViewMode::DEFAULT);
		openGLWidget->update();
	}
}

void MeshPainter::on_actionTextureView_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setViewMode(ViewMode::TEXTURE);
		openGLWidget->update();
	}
}

void MeshPainter::on_actionRenderView_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setViewMode(ViewMode::RENDER);
		openGLWidget->update();
	}
}

void MeshPainter::on_actionUvView_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setViewMode(ViewMode::UV);
		openGLWidget->update();
	}
}

void MeshPainter::on_actionOpenAlbedoTexture_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Albedo Texture"), "", tr("PNG (*.png);;DirectDrawSurface (*.dds)"));
	if (!fileName.isEmpty())
	{
		openGLWidget->setTexture(fileName.toLatin1().data(), TextureMode::ALBEDO);
		openGLWidget->update();
	}
}

void MeshPainter::on_actionOpenMetallicTexture_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Albedo Texture"), "", tr("PNG (*.png);;DirectDrawSurface (*.dds)"));
	if (!fileName.isEmpty())
	{
		openGLWidget->setTexture(fileName.toLatin1().data(), TextureMode::METALLIC);
		openGLWidget->update();
	}
}

void MeshPainter::on_actionOpenRoughnessTexture_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Roughness Texture"), "", tr("PNG (*.png);;DirectDrawSurface (*.dds)"));
	if (!fileName.isEmpty())
	{
		openGLWidget->setTexture(fileName.toLatin1().data(), TextureMode::ROUGHNESS);
		openGLWidget->update();
	}
}

void MeshPainter::on_actionOpenAmbientOcclusionTexture_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Ambient Occlusion Texture"), "", tr("PNG (*.png);;DirectDrawSurface (*.dds)"));
	if (!fileName.isEmpty())
	{
		openGLWidget->setTexture(fileName.toLatin1().data(), TextureMode::AMBIENT_OCCLUSION);
		openGLWidget->update();
	}
}

void MeshPainter::on_actionOpenEmissiveTexture_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Emissive Texture"), "", tr("PNG (*.png);;DirectDrawSurface (*.dds)"));
	if (!fileName.isEmpty())
	{
		openGLWidget->setTexture(fileName.toLatin1().data(), TextureMode::EMISSIVE);
		openGLWidget->update();
	}
}

void MeshPainter::on_actionOpenDisplacementTexture_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Displacement Texture"), "", tr("PNG (*.png);;DirectDrawSurface (*.dds)"));
	if (!fileName.isEmpty())
	{
		openGLWidget->setTexture(fileName.toLatin1().data(), TextureMode::DISPLACEMENT);
		openGLWidget->update();
	}
}

void MeshPainter::on_actionSaveAlbedoTexture_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Albedo Texture"), "", tr("PNG (*.png)"));
	if (!fileName.isEmpty())
	{
		openGLWidget->saveTexture(fileName.toLatin1().data(), TextureMode::ALBEDO);
	}
}

void MeshPainter::on_actionSaveMetallicTexture_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Metallic Texture"), "", tr("PNG (*.png)"));
	if (!fileName.isEmpty())
	{
		openGLWidget->saveTexture(fileName.toLatin1().data(), TextureMode::METALLIC);
	}
}

void MeshPainter::on_actionSaveRoughnessTexture_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Roughness Texture"), "", tr("PNG (*.png)"));
	if (!fileName.isEmpty())
	{
		openGLWidget->saveTexture(fileName.toLatin1().data(), TextureMode::ROUGHNESS);
	}
}

void MeshPainter::on_actionSaveAmbientOcclusionTexture_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Ambient Occlusion Texture"), "", tr("PNG (*.png)"));
	if (!fileName.isEmpty())
	{
		openGLWidget->saveTexture(fileName.toLatin1().data(), TextureMode::AMBIENT_OCCLUSION);
	}
}

void MeshPainter::on_actionSaveEmissiveTexture_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Emissive Texture"), "", tr("PNG (*.png)"));
	if (!fileName.isEmpty())
	{
		openGLWidget->saveTexture(fileName.toLatin1().data(), TextureMode::EMISSIVE);
	}
}

void MeshPainter::on_actionSaveDisplacementTexture_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Displacement Texture"), "", tr("PNG (*.png)"));
	if (!fileName.isEmpty())
	{
		openGLWidget->saveTexture(fileName.toLatin1().data(), TextureMode::DISPLACEMENT);
	}
}

void MeshPainter::on_actionSaveAllTextures_triggered()
{
	QString directoryName = QFileDialog::getExistingDirectory(this, tr("Save All Textures"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!directoryName.isEmpty())
	{
		openGLWidget->saveAllTextures(directoryName.toLatin1().data());
	}
}

void MeshPainter::on_actionActivateAlbedoTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::ALBEDO);
		openGLWidget->update();
	}
}

void MeshPainter::on_actionActivateMetallicTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::METALLIC);
		openGLWidget->update();
	}
}

void MeshPainter::on_actionActivateRoughnessTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::ROUGHNESS);
		openGLWidget->update();
	}
}

void MeshPainter::on_actionActivateAmbientOcclusionTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::AMBIENT_OCCLUSION);
		openGLWidget->update();
	}
}

void MeshPainter::on_actionActivateEmissiveTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::EMISSIVE);
		openGLWidget->update();
	}
}

void MeshPainter::on_actionActivateDisplacementTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::DISPLACEMENT);
		openGLWidget->update();
	}
}

void MeshPainter::on_actionSetStrokeWidth_triggered()
{
	double result = QInputDialog::getDouble(this, tr("Set Stroke Width"), tr("Set Stroke Width"), openGLWidget->getStrokeWidth(), 1.0, 50.0);
	openGLWidget->setStrokeWidth(float(result));
	openGLWidget->update();
}

void MeshPainter::on_actionSetPaint_triggered()
{
	glm::vec3 prevColor = openGLWidget->getPaintColor() * 255.0f; // QColor uses 0 - 255
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

void MeshPainter::on_actionClearActive_triggered()
{
	QMessageBox msgBox;
	msgBox.setWindowTitle("Clear Active Texture");
	msgBox.setText("Are you sure you want to clear the active texture?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Yes);

	if (msgBox.exec() == QMessageBox::Yes)
	{
		QColorDialog colorDialog(this);
		colorDialog.setWindowTitle("Set Clear Color");
		if (colorDialog.exec())
		{
			double r, g, b;
			colorDialog.currentColor().getRgbF(&r, &g, &b);
			openGLWidget->clearActiveTexture({ r, g, b });
			openGLWidget->update();
		}
	}
}

void MeshPainter::on_actionClearAll_triggered()
{
	QMessageBox msgBox;
	msgBox.setWindowTitle("Clear All Textures");
	msgBox.setText("Are you sure you want to clear all textures and reset them to default values?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Yes);

	if (msgBox.exec() == QMessageBox::Yes)
	{
		openGLWidget->clearAllTextures();
		openGLWidget->update();
	}
}

void MeshPainter::on_actionSetEmissiveColor_triggered()
{
	glm::vec3 prevColor = openGLWidget->getMaterial()->getEmissive() * 255.0f;
	QColorDialog colorDialog({ int(prevColor.r), int(prevColor.g), int(prevColor.b) }, this);
	if (colorDialog.exec())
	{
		QColor qcolor = colorDialog.currentColor();
		double r, g, b;
		qcolor.getRgbF(&r, &g, &b);
		openGLWidget->getMaterial()->setEmissive({ r, g, b });
		openGLWidget->update();
	}
}

void MeshPainter::on_actionOpen_triggered()
{
	// get file path
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Mesh File"), "", tr("Wavefront OBJ File (*.obj)"));

	// get lock on bool to check if there is already a loading operation going on
	std::lock_guard<std::mutex> lockCheck(loadingMeshMutex);

	// only continue if a file was selected and we are not already loading a mesh
	if (!fileName.isEmpty() && !loadingMesh)
	{
		// set flag that a mesh loading operation is going on
		loadingMesh = true;
		MeshPainter *meshTool = this;

		QMessageBox::information(this, "Loading Model", "The model is being loaded in the background. This may take a while.");

		// start thread to load mesh
		std::thread meshLoadThread([fileName, meshTool]()
		{
			// in order to use QTimer::singleShot, we need a QEventLoop
			QEventLoop loop;
			Q_UNUSED(loop)

			OBJLoader::Error loadError;
			// allocate on heap to avoid unnecessary copy when posting to gui thread
			IndexedMesh *indexedMesh =  new IndexedMesh(OBJLoader::loadOBJ(fileName.toLatin1().data(), loadError));

			// execture on gui thread
			QTimer::singleShot(0, qApp, [indexedMesh, meshTool, loadError]()
			{
				if (loadError != OBJLoader::Error::SUCCESS)
				{
					QMessageBox::critical(meshTool, "Model Loading Failed!", "Loading the Model has failed.");

					// acquire lock to signal that mesh loading is done
					std::lock_guard<std::mutex> lockReset(meshTool->loadingMeshMutex);
					meshTool->loadingMesh = false;
					return;
				}

				// create GLMesh
				meshTool->openGLWidget->setMesh(*indexedMesh);
				// the GLMesh created in GLWidget holds a copy of indexedMesh, so delete this instance
				delete indexedMesh;

				// reset material textures
				meshTool->openGLWidget->clearAllTextures();
				meshTool->openGLWidget->update();

				// acquire lock to signal that mesh loading is done
				std::lock_guard<std::mutex> lockReset(meshTool->loadingMeshMutex);
				meshTool->loadingMesh = false;
			});
		});
		meshLoadThread.detach();
	}
}
