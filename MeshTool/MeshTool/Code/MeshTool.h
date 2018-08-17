#pragma once
#include <QMainWindow>
#include "ui_MeshTool.h"
#include <mutex>

class MeshTool : public QMainWindow, public Ui::MeshTool
{
	Q_OBJECT

public:
	MeshTool(QWidget *parent = Q_NULLPTR);
	~MeshTool();

private:
	std::mutex loadingMeshMutex;
	bool loadingMesh;
	QActionGroup *viewModeGroup;
	QActionGroup *textureModeGroup;
	QAbstractItemModel *materialItemModel;

private slots:
	void on_actionOpen_triggered();
	void on_actionCenterCamera_triggered();
	void on_actionToggleWireframe_toggled(bool _enabled);
	void on_actionDefaultView_toggled(bool _enabled);
	void on_actionTextureView_toggled(bool _enabled);
	void on_actionRenderView_toggled(bool _enabled);
	void on_actionUvView_toggled(bool _enabled);
	void on_actionAlbedoTexture_toggled(bool _enabled);
	void on_actionMetallicTexture_toggled(bool _enabled);
	void on_actionRoughnessTexture_toggled(bool _enabled);
	void on_actionAmbientOcclusionTexture_toggled(bool _enabled);
	void on_actionEmissiveTexture_toggled(bool _enabled);
	void on_actionDisplacementTexture_toggled(bool _enabled);
};
