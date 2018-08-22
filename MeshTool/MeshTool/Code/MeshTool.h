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
	void on_actionOpenAlbedoTexture_triggered();
	void on_actionOpenMetallicTexture_triggered();
	void on_actionOpenRoughnessTexture_triggered();
	void on_actionOpenAmbientOcclusionTexture_triggered();
	void on_actionOpenEmissiveTexture_triggered();
	void on_actionOpenDisplacementTexture_triggered();
	void on_actionSaveAlbedoTexture_triggered();
	void on_actionSaveMetallicTexture_triggered();
	void on_actionSaveRoughnessTexture_triggered();
	void on_actionSaveAmbientOcclusionTexture_triggered();
	void on_actionSaveEmissiveTexture_triggered();
	void on_actionSaveDisplacementTexture_triggered();
	void on_actionSaveAllTextures_triggered();
	
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
