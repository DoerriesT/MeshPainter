#include "MeshTool.h"
#include "OBJLoader.h"
#include <qfiledialog.h>
#include <thread>
#include <qtimer.h>
#include <QStandardItemModel>
#include "Texture.h"
#include "HalfEdgeMesh.h"

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
	textureModeGroup->addAction(actionAlbedoTexture);
	textureModeGroup->addAction(actionMetallicTexture);
	textureModeGroup->addAction(actionRoughnessTexture);
	textureModeGroup->addAction(actionAmbientOcclusionTexture);
	textureModeGroup->addAction(actionEmissiveTexture);
	textureModeGroup->addAction(actionDisplacementTexture);

	materialItemModel = new QStandardItemModel();
	QStandardItem *parentItem = ((QStandardItemModel *)materialItemModel)->invisibleRootItem();
	for (int i = 0; i < 4; ++i) 
	{
		QStandardItem *item = new QStandardItem(QString("item %0").arg(i));
		parentItem->appendRow(item);
		//parentItem = item;
	}
	treeViewMaterial->setModel(materialItemModel);
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

void MeshTool::on_actionAlbedoTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::ALBEDO);
		openGLWidget->update();
	}
}

void MeshTool::on_actionMetallicTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::METALLIC);
		openGLWidget->update();
	}
}

void MeshTool::on_actionRoughnessTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::ROUGHNESS);
		openGLWidget->update();
	}
}

void MeshTool::on_actionAmbientOcclusionTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::AMBIENT_OCCLUSION);
		openGLWidget->update();
	}
}

void MeshTool::on_actionEmissiveTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::EMISSIVE);
		openGLWidget->update();
	}
}

void MeshTool::on_actionDisplacementTexture_toggled(bool _enabled)
{
	if (_enabled)
	{
		openGLWidget->setTextureMode(TextureMode::DISPLACEMENT);
		openGLWidget->update();
	}
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
