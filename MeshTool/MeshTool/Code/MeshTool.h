#pragma once

#include <QtWidgets/QWidget>
#include "ui_MeshTool.h"

class MeshTool : public QWidget
{
	Q_OBJECT

public:
	MeshTool(QWidget *parent = Q_NULLPTR);

private:
	Ui::MeshToolClass ui;

private slots:
	void on_brightnessSlider_sliderMoved(int _val);
	void on_pushButton_clicked();
};
