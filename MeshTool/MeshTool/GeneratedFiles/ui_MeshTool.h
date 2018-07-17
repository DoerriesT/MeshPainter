/********************************************************************************
** Form generated from reading UI file 'MeshTool.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESHTOOL_H
#define UI_MESHTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MeshToolClass
{
public:
    QGridLayout *gridLayout;
    QSlider *brightnessSlider;
    GLWidget *openGLWidget;
    QPushButton *pushButton;

    void setupUi(QWidget *MeshToolClass)
    {
        if (MeshToolClass->objectName().isEmpty())
            MeshToolClass->setObjectName(QStringLiteral("MeshToolClass"));
        MeshToolClass->resize(942, 702);
        gridLayout = new QGridLayout(MeshToolClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        brightnessSlider = new QSlider(MeshToolClass);
        brightnessSlider->setObjectName(QStringLiteral("brightnessSlider"));
        brightnessSlider->setMaximum(100);
        brightnessSlider->setOrientation(Qt::Vertical);
        brightnessSlider->setInvertedAppearance(false);

        gridLayout->addWidget(brightnessSlider, 0, 0, 1, 1);

        openGLWidget = new GLWidget(MeshToolClass);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);

        gridLayout->addWidget(openGLWidget, 0, 1, 2, 1);

        pushButton = new QPushButton(MeshToolClass);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);


        retranslateUi(MeshToolClass);

        QMetaObject::connectSlotsByName(MeshToolClass);
    } // setupUi

    void retranslateUi(QWidget *MeshToolClass)
    {
        MeshToolClass->setWindowTitle(QApplication::translate("MeshToolClass", "MeshTool", nullptr));
        pushButton->setText(QApplication::translate("MeshToolClass", "Load Model", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MeshToolClass: public Ui_MeshToolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHTOOL_H
