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

private slots:

	// file
	void on_actionOpen_triggered();
	
	// edit
	void on_actionActivateAlbedoTexture_toggled(bool _enabled);
	void on_actionActivateMetallicTexture_toggled(bool _enabled);
	void on_actionActivateRoughnessTexture_toggled(bool _enabled);
	void on_actionActivateAmbientOcclusionTexture_toggled(bool _enabled);
	void on_actionActivateEmissiveTexture_toggled(bool _enabled);
	void on_actionActivateDisplacementTexture_toggled(bool _enabled);

	void on_actionSetStrokeWidth_triggered();
	void on_actionSetPaint_triggered();
	void on_actionClearActive_triggered();
	void on_actionClearAll_triggered();
	void on_actionSetEmissiveColor_triggered();

	// view
	void on_actionCenterCamera_triggered();
	void on_actionToggleWireframe_toggled(bool _enabled);
	void on_actionDefaultView_toggled(bool _enabled);
	void on_actionTextureView_toggled(bool _enabled);
	void on_actionRenderView_toggled(bool _enabled);
	void on_actionUvView_toggled(bool _enabled);
};
