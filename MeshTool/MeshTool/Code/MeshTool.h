#pragma once

#include <QMainWindow>
#include "ui_MeshTool.h"

class MeshTool : public QMainWindow, public Ui::MeshTool
{
	Q_OBJECT

public:
	MeshTool(QWidget *parent = Q_NULLPTR);
	~MeshTool();

private slots:
	void on_actionOpen_triggered();
	void on_actionCenterCamera_triggered();
	void on_actionToggleWireframe_toggled(bool _enabled);
};
