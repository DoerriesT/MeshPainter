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

private slots:
	void on_actionOpen_triggered();
	void on_actionCenterCamera_triggered();
	void on_actionToggleWireframe_toggled(bool _enabled);
	void on_actionDefaultView_toggled(bool _enabled);
	void on_actionRenderView_toggled(bool _enabled);
	void on_actionUvView_toggled(bool _enabled);
	void on_albedoRedSpinBox_valueChanged(double _value);
	void on_albedoGreenSpinBox_valueChanged(double _value);
	void on_albedoBlueSpinBox_valueChanged(double _value);
	void on_metallicSpinBox_valueChanged(double _value);
	void on_roughnessSpinBox_valueChanged(double _value);
	void on_emissiveRedSpinBox_valueChanged(double _value);
	void on_emissiveGreenSpinBox_valueChanged(double _value);
	void on_emissiveBlueSpinBox_valueChanged(double _value);
	void on_albedoTextureButton_clicked();
	void on_normalTextureButton_clicked();
	void on_metallicTextureButton_clicked();
	void on_roughnessTextureButton_clicked();
	void on_aoTextureButton_clicked();
	void on_emissiveTextureButton_clicked();
	void on_displacementTextureButton_clicked();
};
