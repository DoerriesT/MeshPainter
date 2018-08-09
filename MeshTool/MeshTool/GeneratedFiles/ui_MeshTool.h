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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MeshTool
{
public:
    QAction *actionOpen;
    QAction *actionToggleWireframe;
    QAction *actionCenterCamera;
    QAction *actionToggleRenderMode;
    QAction *actionToggleCameraMode;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    GLWidget *openGLWidget;
    QGridLayout *gridLayout;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *albedoRedSpinBox;
    QDoubleSpinBox *albedoGreenSpinBox;
    QDoubleSpinBox *albedoBlueSpinBox;
    QLabel *label_10;
    QDoubleSpinBox *metallicSpinBox;
    QLabel *label_11;
    QDoubleSpinBox *roughnessSpinBox;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_2;
    QDoubleSpinBox *emissiveRedSpinBox;
    QDoubleSpinBox *emissiveGreenSpinBox;
    QDoubleSpinBox *emissiveBlueSpinBox;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *albedoTextureLineEdit;
    QPushButton *albedoTextureButton;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *normalTextureLineEdit;
    QPushButton *normalTextureButton;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *metallicTextureLineEdit;
    QPushButton *metallicTextureButton;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *roughnessTextureLineEdit;
    QPushButton *roughnessTextureButton;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *aoTextureLineEdit;
    QPushButton *aoTextureButton;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *emissiveTextureLineEdit;
    QPushButton *emissiveTextureButton;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_9;
    QLineEdit *displacementTextureLineEdit;
    QPushButton *displacementTextureButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;

    void setupUi(QMainWindow *MeshTool)
    {
        if (MeshTool->objectName().isEmpty())
            MeshTool->setObjectName(QStringLiteral("MeshTool"));
        MeshTool->resize(912, 768);
        actionOpen = new QAction(MeshTool);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionToggleWireframe = new QAction(MeshTool);
        actionToggleWireframe->setObjectName(QStringLiteral("actionToggleWireframe"));
        actionToggleWireframe->setCheckable(true);
        actionCenterCamera = new QAction(MeshTool);
        actionCenterCamera->setObjectName(QStringLiteral("actionCenterCamera"));
        actionToggleRenderMode = new QAction(MeshTool);
        actionToggleRenderMode->setObjectName(QStringLiteral("actionToggleRenderMode"));
        actionToggleRenderMode->setCheckable(true);
        actionToggleCameraMode = new QAction(MeshTool);
        actionToggleCameraMode->setObjectName(QStringLiteral("actionToggleCameraMode"));
        actionToggleCameraMode->setCheckable(true);
        centralWidget = new QWidget(MeshTool);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        openGLWidget = new GLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

        verticalLayout->addWidget(openGLWidget);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        albedoRedSpinBox = new QDoubleSpinBox(centralWidget);
        albedoRedSpinBox->setObjectName(QStringLiteral("albedoRedSpinBox"));
        albedoRedSpinBox->setMaximum(1);
        albedoRedSpinBox->setSingleStep(0.1);
        albedoRedSpinBox->setValue(1);

        horizontalLayout->addWidget(albedoRedSpinBox);

        albedoGreenSpinBox = new QDoubleSpinBox(centralWidget);
        albedoGreenSpinBox->setObjectName(QStringLiteral("albedoGreenSpinBox"));
        albedoGreenSpinBox->setMaximum(1);
        albedoGreenSpinBox->setSingleStep(0.1);
        albedoGreenSpinBox->setValue(1);

        horizontalLayout->addWidget(albedoGreenSpinBox);

        albedoBlueSpinBox = new QDoubleSpinBox(centralWidget);
        albedoBlueSpinBox->setObjectName(QStringLiteral("albedoBlueSpinBox"));
        albedoBlueSpinBox->setMaximum(1);
        albedoBlueSpinBox->setSingleStep(0.1);
        albedoBlueSpinBox->setValue(1);

        horizontalLayout->addWidget(albedoBlueSpinBox);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 1, 0, 1, 1);

        metallicSpinBox = new QDoubleSpinBox(centralWidget);
        metallicSpinBox->setObjectName(QStringLiteral("metallicSpinBox"));
        metallicSpinBox->setMaximum(1);
        metallicSpinBox->setSingleStep(0.1);

        gridLayout->addWidget(metallicSpinBox, 1, 1, 1, 1);

        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 2, 0, 1, 1);

        roughnessSpinBox = new QDoubleSpinBox(centralWidget);
        roughnessSpinBox->setObjectName(QStringLiteral("roughnessSpinBox"));
        roughnessSpinBox->setMaximum(1);
        roughnessSpinBox->setSingleStep(0.1);
        roughnessSpinBox->setValue(1);

        gridLayout->addWidget(roughnessSpinBox, 2, 1, 1, 1);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 3, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        emissiveRedSpinBox = new QDoubleSpinBox(centralWidget);
        emissiveRedSpinBox->setObjectName(QStringLiteral("emissiveRedSpinBox"));
        emissiveRedSpinBox->setSingleStep(0.1);

        horizontalLayout_2->addWidget(emissiveRedSpinBox);

        emissiveGreenSpinBox = new QDoubleSpinBox(centralWidget);
        emissiveGreenSpinBox->setObjectName(QStringLiteral("emissiveGreenSpinBox"));
        emissiveGreenSpinBox->setSingleStep(0.1);

        horizontalLayout_2->addWidget(emissiveGreenSpinBox);

        emissiveBlueSpinBox = new QDoubleSpinBox(centralWidget);
        emissiveBlueSpinBox->setObjectName(QStringLiteral("emissiveBlueSpinBox"));
        emissiveBlueSpinBox->setSingleStep(0.1);

        horizontalLayout_2->addWidget(emissiveBlueSpinBox);


        gridLayout->addLayout(horizontalLayout_2, 3, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 4, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        albedoTextureLineEdit = new QLineEdit(centralWidget);
        albedoTextureLineEdit->setObjectName(QStringLiteral("albedoTextureLineEdit"));
        albedoTextureLineEdit->setReadOnly(true);

        horizontalLayout_3->addWidget(albedoTextureLineEdit);

        albedoTextureButton = new QPushButton(centralWidget);
        albedoTextureButton->setObjectName(QStringLiteral("albedoTextureButton"));

        horizontalLayout_3->addWidget(albedoTextureButton);


        gridLayout->addLayout(horizontalLayout_3, 4, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 5, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        normalTextureLineEdit = new QLineEdit(centralWidget);
        normalTextureLineEdit->setObjectName(QStringLiteral("normalTextureLineEdit"));
        normalTextureLineEdit->setReadOnly(true);

        horizontalLayout_4->addWidget(normalTextureLineEdit);

        normalTextureButton = new QPushButton(centralWidget);
        normalTextureButton->setObjectName(QStringLiteral("normalTextureButton"));

        horizontalLayout_4->addWidget(normalTextureButton);


        gridLayout->addLayout(horizontalLayout_4, 5, 1, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 6, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        metallicTextureLineEdit = new QLineEdit(centralWidget);
        metallicTextureLineEdit->setObjectName(QStringLiteral("metallicTextureLineEdit"));
        metallicTextureLineEdit->setReadOnly(true);

        horizontalLayout_5->addWidget(metallicTextureLineEdit);

        metallicTextureButton = new QPushButton(centralWidget);
        metallicTextureButton->setObjectName(QStringLiteral("metallicTextureButton"));

        horizontalLayout_5->addWidget(metallicTextureButton);


        gridLayout->addLayout(horizontalLayout_5, 6, 1, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 7, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        roughnessTextureLineEdit = new QLineEdit(centralWidget);
        roughnessTextureLineEdit->setObjectName(QStringLiteral("roughnessTextureLineEdit"));
        roughnessTextureLineEdit->setReadOnly(true);

        horizontalLayout_6->addWidget(roughnessTextureLineEdit);

        roughnessTextureButton = new QPushButton(centralWidget);
        roughnessTextureButton->setObjectName(QStringLiteral("roughnessTextureButton"));

        horizontalLayout_6->addWidget(roughnessTextureButton);


        gridLayout->addLayout(horizontalLayout_6, 7, 1, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 8, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        aoTextureLineEdit = new QLineEdit(centralWidget);
        aoTextureLineEdit->setObjectName(QStringLiteral("aoTextureLineEdit"));
        aoTextureLineEdit->setReadOnly(true);

        horizontalLayout_7->addWidget(aoTextureLineEdit);

        aoTextureButton = new QPushButton(centralWidget);
        aoTextureButton->setObjectName(QStringLiteral("aoTextureButton"));

        horizontalLayout_7->addWidget(aoTextureButton);


        gridLayout->addLayout(horizontalLayout_7, 8, 1, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 9, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        emissiveTextureLineEdit = new QLineEdit(centralWidget);
        emissiveTextureLineEdit->setObjectName(QStringLiteral("emissiveTextureLineEdit"));
        emissiveTextureLineEdit->setReadOnly(true);

        horizontalLayout_8->addWidget(emissiveTextureLineEdit);

        emissiveTextureButton = new QPushButton(centralWidget);
        emissiveTextureButton->setObjectName(QStringLiteral("emissiveTextureButton"));

        horizontalLayout_8->addWidget(emissiveTextureButton);


        gridLayout->addLayout(horizontalLayout_8, 9, 1, 1, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 10, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        displacementTextureLineEdit = new QLineEdit(centralWidget);
        displacementTextureLineEdit->setObjectName(QStringLiteral("displacementTextureLineEdit"));
        displacementTextureLineEdit->setReadOnly(true);

        horizontalLayout_9->addWidget(displacementTextureLineEdit);

        displacementTextureButton = new QPushButton(centralWidget);
        displacementTextureButton->setObjectName(QStringLiteral("displacementTextureButton"));

        horizontalLayout_9->addWidget(displacementTextureButton);


        gridLayout->addLayout(horizontalLayout_9, 10, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        MeshTool->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MeshTool);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 912, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MeshTool->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuFile->addAction(actionOpen);
        menuView->addAction(actionToggleWireframe);
        menuView->addAction(actionToggleRenderMode);
        menuView->addAction(actionCenterCamera);

        retranslateUi(MeshTool);

        QMetaObject::connectSlotsByName(MeshTool);
    } // setupUi

    void retranslateUi(QMainWindow *MeshTool)
    {
        MeshTool->setWindowTitle(QApplication::translate("MeshTool", "MeshTool", nullptr));
        actionOpen->setText(QApplication::translate("MeshTool", "Open", nullptr));
        actionToggleWireframe->setText(QApplication::translate("MeshTool", "Toggle Wireframe", nullptr));
        actionCenterCamera->setText(QApplication::translate("MeshTool", "Center Camera", nullptr));
        actionToggleRenderMode->setText(QApplication::translate("MeshTool", "Toggle Render Mode", nullptr));
        actionToggleCameraMode->setText(QApplication::translate("MeshTool", "Toggle Camera Mode", nullptr));
        label_8->setText(QApplication::translate("MeshTool", "Albedo", nullptr));
        label_10->setText(QApplication::translate("MeshTool", "Metallic", nullptr));
        label_11->setText(QApplication::translate("MeshTool", "Roughness", nullptr));
        label_9->setText(QApplication::translate("MeshTool", "Emissive Color", nullptr));
        label->setText(QApplication::translate("MeshTool", "Albedo Texture", nullptr));
        albedoTextureLineEdit->setPlaceholderText(QApplication::translate("MeshTool", "Texture Path", nullptr));
        albedoTextureButton->setText(QApplication::translate("MeshTool", "Select", nullptr));
        label_2->setText(QApplication::translate("MeshTool", "Normal Texture", nullptr));
        normalTextureLineEdit->setPlaceholderText(QApplication::translate("MeshTool", "Texture Path", nullptr));
        normalTextureButton->setText(QApplication::translate("MeshTool", "Select", nullptr));
        label_3->setText(QApplication::translate("MeshTool", "Metallic Texture", nullptr));
        metallicTextureLineEdit->setPlaceholderText(QApplication::translate("MeshTool", "Texture Path", nullptr));
        metallicTextureButton->setText(QApplication::translate("MeshTool", "Select", nullptr));
        label_4->setText(QApplication::translate("MeshTool", "Roughness Texture", nullptr));
        roughnessTextureLineEdit->setPlaceholderText(QApplication::translate("MeshTool", "Texture Path", nullptr));
        roughnessTextureButton->setText(QApplication::translate("MeshTool", "Select", nullptr));
        label_5->setText(QApplication::translate("MeshTool", "Ambient Occlusion Texture", nullptr));
        aoTextureLineEdit->setPlaceholderText(QApplication::translate("MeshTool", "Texture Path", nullptr));
        aoTextureButton->setText(QApplication::translate("MeshTool", "Select", nullptr));
        label_6->setText(QApplication::translate("MeshTool", "Emissive Texture", nullptr));
        emissiveTextureLineEdit->setPlaceholderText(QApplication::translate("MeshTool", "Texture Path", nullptr));
        emissiveTextureButton->setText(QApplication::translate("MeshTool", "Select", nullptr));
        label_7->setText(QApplication::translate("MeshTool", "Displacement Texture", nullptr));
        displacementTextureLineEdit->setPlaceholderText(QApplication::translate("MeshTool", "Texture Path", nullptr));
        displacementTextureButton->setText(QApplication::translate("MeshTool", "Select", nullptr));
        menuFile->setTitle(QApplication::translate("MeshTool", "File", nullptr));
        menuView->setTitle(QApplication::translate("MeshTool", "View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MeshTool: public Ui_MeshTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHTOOL_H
