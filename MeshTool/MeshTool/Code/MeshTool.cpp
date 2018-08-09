#include "MeshTool.h"
#include "OBJLoader.h"
#include <qfiledialog.h>
#include <thread>
#include <qtimer.h>
#include "Texture.h"

MeshTool::MeshTool(QWidget *parent)
	: QMainWindow(parent),
	loadingMesh(false)
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

void MeshTool::on_actionToggleRenderMode_toggled(bool _enabled)
{
	openGLWidget->toggleRenderMode(_enabled);
	openGLWidget->update();
}

void MeshTool::on_albedoRedSpinBox_valueChanged(double _value)
{
	if (openGLWidget->material)
	{
		glm::vec4 albedo = openGLWidget->material->getAlbedo();
		albedo.r = _value;
		openGLWidget->material->setAlbedo(albedo);
		openGLWidget->update();
	}
	
}

void MeshTool::on_albedoGreenSpinBox_valueChanged(double _value)
{
	if (openGLWidget->material)
	{
		glm::vec4 albedo = openGLWidget->material->getAlbedo();
		albedo.g = _value;
		openGLWidget->material->setAlbedo(albedo);
		openGLWidget->update();
	}
}

void MeshTool::on_albedoBlueSpinBox_valueChanged(double _value)
{
	if (openGLWidget->material)
	{
		glm::vec4 albedo = openGLWidget->material->getAlbedo();
		albedo.b = _value;
		openGLWidget->material->setAlbedo(albedo);
		openGLWidget->update();
	}
}

void MeshTool::on_metallicSpinBox_valueChanged(double _value)
{
	if (openGLWidget->material)
	{
		openGLWidget->material->setMetallic(_value);
		openGLWidget->update();
	}
}

void MeshTool::on_roughnessSpinBox_valueChanged(double _value)
{
	if (openGLWidget->material)
	{
		openGLWidget->material->setRoughness(_value);
		openGLWidget->update();
	}
}

void MeshTool::on_emissiveRedSpinBox_valueChanged(double _value)
{
	if (openGLWidget->material)
	{
		glm::vec3 emissive = openGLWidget->material->getEmissive();
		emissive.r = _value;
		openGLWidget->material->setEmissive(emissive);
		openGLWidget->update();
	}
}

void MeshTool::on_emissiveGreenSpinBox_valueChanged(double _value)
{
	if (openGLWidget->material)
	{
		glm::vec3 emissive = openGLWidget->material->getEmissive();
		emissive.g = _value;
		openGLWidget->material->setEmissive(emissive);
		openGLWidget->update();
	}
}

void MeshTool::on_emissiveBlueSpinBox_valueChanged(double _value)
{
	if (openGLWidget->material)
	{
		glm::vec3 emissive = openGLWidget->material->getEmissive();
		emissive.b = _value;
		openGLWidget->material->setEmissive(emissive);
		openGLWidget->update();
	}
}

void MeshTool::on_albedoTextureButton_clicked()
{
	// get file path
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Texture File"), "",
		tr("DirectDrawSurface (*.dds);;PNG (*.png)"));

	if (!fileName.isEmpty())
	{
		openGLWidget->material->setAlbedoMap(Texture::createTexture(fileName.toLatin1().data()));
		albedoTextureLineEdit->setText(fileName);
	}
	else
	{
		openGLWidget->material->setAlbedoMap(nullptr);
		albedoTextureLineEdit->clear();
	}
	openGLWidget->update();
}

void MeshTool::on_normalTextureButton_clicked()
{
	// get file path
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Texture File"), "",
		tr("DirectDrawSurface (*.dds);;PNG (*.png)"));

	if (!fileName.isEmpty())
	{
		openGLWidget->material->setNormalMap(Texture::createTexture(fileName.toLatin1().data()));
		normalTextureLineEdit->setText(fileName);
	}
	else
	{
		openGLWidget->material->setNormalMap(nullptr);
		normalTextureLineEdit->clear();
	}
	openGLWidget->update();
}

void MeshTool::on_metallicTextureButton_clicked()
{
	// get file path
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Texture File"), "",
		tr("DirectDrawSurface (*.dds);;PNG (*.png)"));

	if (!fileName.isEmpty())
	{
		openGLWidget->material->setMetallicMap(Texture::createTexture(fileName.toLatin1().data()));
		metallicTextureLineEdit->setText(fileName);
	}
	else
	{
		openGLWidget->material->setMetallicMap(nullptr);
		metallicTextureLineEdit->clear();
	}
	openGLWidget->update();
}

void MeshTool::on_roughnessTextureButton_clicked()
{
	// get file path
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Texture File"), "",
		tr("DirectDrawSurface (*.dds);;PNG (*.png)"));

	if (!fileName.isEmpty())
	{
		openGLWidget->material->setRoughnessMap(Texture::createTexture(fileName.toLatin1().data()));
		roughnessTextureLineEdit->setText(fileName);
	}
	else
	{
		openGLWidget->material->setRoughnessMap(nullptr);
		roughnessTextureLineEdit->clear();
	}
	openGLWidget->update();
}

void MeshTool::on_aoTextureButton_clicked()
{
	// get file path
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Texture File"), "",
		tr("DirectDrawSurface (*.dds);;PNG (*.png)"));

	if (!fileName.isEmpty())
	{
		openGLWidget->material->setAoMap(Texture::createTexture(fileName.toLatin1().data()));
		aoTextureLineEdit->setText(fileName);
	}
	else
	{
		openGLWidget->material->setAoMap(nullptr);
		aoTextureLineEdit->clear();
	}
	openGLWidget->update();
}

void MeshTool::on_emissiveTextureButton_clicked()
{
	// get file path
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Texture File"), "",
		tr("DirectDrawSurface (*.dds);;PNG (*.png)"));

	if (!fileName.isEmpty())
	{
		openGLWidget->material->setEmissiveMap(Texture::createTexture(fileName.toLatin1().data()));
		emissiveTextureLineEdit->setText(fileName);
	}
	else
	{
		openGLWidget->material->setEmissiveMap(nullptr);
		emissiveTextureLineEdit->clear();
	}
	openGLWidget->update();
}

void MeshTool::on_displacementTextureButton_clicked()
{
	// get file path
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Texture File"), "",
		tr("DirectDrawSurface (*.dds);;PNG (*.png)"));

	if (!fileName.isEmpty())
	{
		openGLWidget->material->setDisplacementMap(Texture::createTexture(fileName.toLatin1().data()));
		displacementTextureLineEdit->setText(fileName);
	}
	else
	{
		openGLWidget->material->setDisplacementMap(nullptr);
		displacementTextureLineEdit->clear();
	}
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

				if (meshTool->openGLWidget->material)
				{
					meshTool->openGLWidget->material->setAlbedo(glm::vec4(meshTool->albedoRedSpinBox->value(), meshTool->albedoGreenSpinBox->value(), meshTool->albedoBlueSpinBox->value(), 1.0));
					meshTool->openGLWidget->material->setMetallic(meshTool->metallicSpinBox->value());
					meshTool->openGLWidget->material->setRoughness(meshTool->roughnessSpinBox->value());
					meshTool->openGLWidget->material->setEmissive(glm::vec3(meshTool->emissiveRedSpinBox->value(), meshTool->emissiveGreenSpinBox->value(), meshTool->emissiveBlueSpinBox->value()));
				}

				meshTool->openGLWidget->update();

				// acquire lock to signal that mesh loading is done
				std::lock_guard<std::mutex> lockReset(meshTool->loadingMeshMutex);
				meshTool->loadingMesh = false;
			});
		});
		meshLoadThread.detach();
	}
}
