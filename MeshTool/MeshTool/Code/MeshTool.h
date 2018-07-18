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

private slots:
	void on_actionOpen_triggered();
	void on_actionCenterCamera_triggered();
	void on_actionToggleWireframe_toggled(bool _enabled);
};
