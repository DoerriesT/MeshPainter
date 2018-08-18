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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
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
    QAction *actionRenderView;
    QAction *actionToggleCameraMode;
    QAction *actionUvView;
    QAction *action3dView;
    QAction *actionDefaultView;
    QAction *actionTextureView;
    QAction *actionSetStrokeWidth;
    QAction *actionSet_Color;
    QAction *actionSet_Clear_Color;
    QAction *actionSet_Clear_Color_2;
    QAction *actionAlbedoSetColor;
    QAction *actionClear;
    QAction *actionSet_Resolution;
    QAction *actionSet_Clear_Color_3;
    QAction *actionMetallicSetValue;
    QAction *actionClear_2;
    QAction *actionSet_Resolution_2;
    QAction *actionSet_Clear_Color_4;
    QAction *actionRoughnessSetValue;
    QAction *actionSet_Resolution_3;
    QAction *actionClear_3;
    QAction *actionSet_Clear_Color_5;
    QAction *actionAmbientOcclusionSet;
    QAction *actionSet_Resolution_4;
    QAction *actionClear_4;
    QAction *actionSet_Clear_Color_6;
    QAction *actionSet_Color_6;
    QAction *actionSet_Resolution_5;
    QAction *actionClear_5;
    QAction *actionSet_Clear_Color_7;
    QAction *actionSet_Color_7;
    QAction *actionSet_Resolution_6;
    QAction *actionClear_6;
    QAction *actionEmissiveSetEmissiveColor;
    QAction *actionAlbedoDeleteTexture;
    QAction *actionAlbedoAddTexture;
    QAction *actionMetallicAddTexture;
    QAction *actionMetallicDeleteTexture;
    QAction *actionRoughnessAddTexture;
    QAction *actionRoughnessDeleteTexture;
    QAction *actionAmbientOcclusionAddTexture;
    QAction *actionAmbientOcclusionDeleteTexture;
    QAction *actionEmissiveAddTexture;
    QAction *actionEmissiveDeleteTexture;
    QAction *actionDisplacementAddTexture;
    QAction *actionDisplacementDeleteTexture;
    QAction *actionMake_Current;
    QAction *actionMake_Current_2;
    QAction *actionMake_Current_3;
    QAction *actionMake_Current_4;
    QAction *actionMake_Current_5;
    QAction *actionMake_Current_6;
    QAction *actionActivateAlbedoTexture;
    QAction *actionActivateMetallicTexture;
    QAction *actionActivateRoughnessTexture;
    QAction *actionActivateAmbientOcclusionTexture;
    QAction *actionActivateEmissiveTexture;
    QAction *actionActivateDisplacementTexture;
    QAction *actionSetPaint;
    QAction *actionFill;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    GLWidget *openGLWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuEdit;
    QMenu *menuAlbedo;
    QMenu *menuMetallic;
    QMenu *menuRoughness;
    QMenu *menuAmbientOcclusion;
    QMenu *menuEmissive;
    QMenu *menuDisplacement;
    QMenu *menuActiveTexture;

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
        actionRenderView = new QAction(MeshTool);
        actionRenderView->setObjectName(QStringLiteral("actionRenderView"));
        actionRenderView->setCheckable(true);
        actionToggleCameraMode = new QAction(MeshTool);
        actionToggleCameraMode->setObjectName(QStringLiteral("actionToggleCameraMode"));
        actionToggleCameraMode->setCheckable(true);
        actionUvView = new QAction(MeshTool);
        actionUvView->setObjectName(QStringLiteral("actionUvView"));
        actionUvView->setCheckable(true);
        action3dView = new QAction(MeshTool);
        action3dView->setObjectName(QStringLiteral("action3dView"));
        action3dView->setCheckable(true);
        actionDefaultView = new QAction(MeshTool);
        actionDefaultView->setObjectName(QStringLiteral("actionDefaultView"));
        actionDefaultView->setCheckable(true);
        actionDefaultView->setChecked(true);
        actionTextureView = new QAction(MeshTool);
        actionTextureView->setObjectName(QStringLiteral("actionTextureView"));
        actionTextureView->setCheckable(true);
        actionSetStrokeWidth = new QAction(MeshTool);
        actionSetStrokeWidth->setObjectName(QStringLiteral("actionSetStrokeWidth"));
        actionSet_Color = new QAction(MeshTool);
        actionSet_Color->setObjectName(QStringLiteral("actionSet_Color"));
        actionSet_Clear_Color = new QAction(MeshTool);
        actionSet_Clear_Color->setObjectName(QStringLiteral("actionSet_Clear_Color"));
        actionSet_Clear_Color_2 = new QAction(MeshTool);
        actionSet_Clear_Color_2->setObjectName(QStringLiteral("actionSet_Clear_Color_2"));
        actionAlbedoSetColor = new QAction(MeshTool);
        actionAlbedoSetColor->setObjectName(QStringLiteral("actionAlbedoSetColor"));
        actionClear = new QAction(MeshTool);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        actionSet_Resolution = new QAction(MeshTool);
        actionSet_Resolution->setObjectName(QStringLiteral("actionSet_Resolution"));
        actionSet_Clear_Color_3 = new QAction(MeshTool);
        actionSet_Clear_Color_3->setObjectName(QStringLiteral("actionSet_Clear_Color_3"));
        actionMetallicSetValue = new QAction(MeshTool);
        actionMetallicSetValue->setObjectName(QStringLiteral("actionMetallicSetValue"));
        actionClear_2 = new QAction(MeshTool);
        actionClear_2->setObjectName(QStringLiteral("actionClear_2"));
        actionSet_Resolution_2 = new QAction(MeshTool);
        actionSet_Resolution_2->setObjectName(QStringLiteral("actionSet_Resolution_2"));
        actionSet_Clear_Color_4 = new QAction(MeshTool);
        actionSet_Clear_Color_4->setObjectName(QStringLiteral("actionSet_Clear_Color_4"));
        actionRoughnessSetValue = new QAction(MeshTool);
        actionRoughnessSetValue->setObjectName(QStringLiteral("actionRoughnessSetValue"));
        actionSet_Resolution_3 = new QAction(MeshTool);
        actionSet_Resolution_3->setObjectName(QStringLiteral("actionSet_Resolution_3"));
        actionClear_3 = new QAction(MeshTool);
        actionClear_3->setObjectName(QStringLiteral("actionClear_3"));
        actionSet_Clear_Color_5 = new QAction(MeshTool);
        actionSet_Clear_Color_5->setObjectName(QStringLiteral("actionSet_Clear_Color_5"));
        actionAmbientOcclusionSet = new QAction(MeshTool);
        actionAmbientOcclusionSet->setObjectName(QStringLiteral("actionAmbientOcclusionSet"));
        actionSet_Resolution_4 = new QAction(MeshTool);
        actionSet_Resolution_4->setObjectName(QStringLiteral("actionSet_Resolution_4"));
        actionClear_4 = new QAction(MeshTool);
        actionClear_4->setObjectName(QStringLiteral("actionClear_4"));
        actionSet_Clear_Color_6 = new QAction(MeshTool);
        actionSet_Clear_Color_6->setObjectName(QStringLiteral("actionSet_Clear_Color_6"));
        actionSet_Color_6 = new QAction(MeshTool);
        actionSet_Color_6->setObjectName(QStringLiteral("actionSet_Color_6"));
        actionSet_Resolution_5 = new QAction(MeshTool);
        actionSet_Resolution_5->setObjectName(QStringLiteral("actionSet_Resolution_5"));
        actionClear_5 = new QAction(MeshTool);
        actionClear_5->setObjectName(QStringLiteral("actionClear_5"));
        actionSet_Clear_Color_7 = new QAction(MeshTool);
        actionSet_Clear_Color_7->setObjectName(QStringLiteral("actionSet_Clear_Color_7"));
        actionSet_Color_7 = new QAction(MeshTool);
        actionSet_Color_7->setObjectName(QStringLiteral("actionSet_Color_7"));
        actionSet_Resolution_6 = new QAction(MeshTool);
        actionSet_Resolution_6->setObjectName(QStringLiteral("actionSet_Resolution_6"));
        actionClear_6 = new QAction(MeshTool);
        actionClear_6->setObjectName(QStringLiteral("actionClear_6"));
        actionEmissiveSetEmissiveColor = new QAction(MeshTool);
        actionEmissiveSetEmissiveColor->setObjectName(QStringLiteral("actionEmissiveSetEmissiveColor"));
        actionAlbedoDeleteTexture = new QAction(MeshTool);
        actionAlbedoDeleteTexture->setObjectName(QStringLiteral("actionAlbedoDeleteTexture"));
        actionAlbedoAddTexture = new QAction(MeshTool);
        actionAlbedoAddTexture->setObjectName(QStringLiteral("actionAlbedoAddTexture"));
        actionMetallicAddTexture = new QAction(MeshTool);
        actionMetallicAddTexture->setObjectName(QStringLiteral("actionMetallicAddTexture"));
        actionMetallicDeleteTexture = new QAction(MeshTool);
        actionMetallicDeleteTexture->setObjectName(QStringLiteral("actionMetallicDeleteTexture"));
        actionRoughnessAddTexture = new QAction(MeshTool);
        actionRoughnessAddTexture->setObjectName(QStringLiteral("actionRoughnessAddTexture"));
        actionRoughnessDeleteTexture = new QAction(MeshTool);
        actionRoughnessDeleteTexture->setObjectName(QStringLiteral("actionRoughnessDeleteTexture"));
        actionAmbientOcclusionAddTexture = new QAction(MeshTool);
        actionAmbientOcclusionAddTexture->setObjectName(QStringLiteral("actionAmbientOcclusionAddTexture"));
        actionAmbientOcclusionDeleteTexture = new QAction(MeshTool);
        actionAmbientOcclusionDeleteTexture->setObjectName(QStringLiteral("actionAmbientOcclusionDeleteTexture"));
        actionEmissiveAddTexture = new QAction(MeshTool);
        actionEmissiveAddTexture->setObjectName(QStringLiteral("actionEmissiveAddTexture"));
        actionEmissiveDeleteTexture = new QAction(MeshTool);
        actionEmissiveDeleteTexture->setObjectName(QStringLiteral("actionEmissiveDeleteTexture"));
        actionDisplacementAddTexture = new QAction(MeshTool);
        actionDisplacementAddTexture->setObjectName(QStringLiteral("actionDisplacementAddTexture"));
        actionDisplacementDeleteTexture = new QAction(MeshTool);
        actionDisplacementDeleteTexture->setObjectName(QStringLiteral("actionDisplacementDeleteTexture"));
        actionMake_Current = new QAction(MeshTool);
        actionMake_Current->setObjectName(QStringLiteral("actionMake_Current"));
        actionMake_Current_2 = new QAction(MeshTool);
        actionMake_Current_2->setObjectName(QStringLiteral("actionMake_Current_2"));
        actionMake_Current_3 = new QAction(MeshTool);
        actionMake_Current_3->setObjectName(QStringLiteral("actionMake_Current_3"));
        actionMake_Current_4 = new QAction(MeshTool);
        actionMake_Current_4->setObjectName(QStringLiteral("actionMake_Current_4"));
        actionMake_Current_5 = new QAction(MeshTool);
        actionMake_Current_5->setObjectName(QStringLiteral("actionMake_Current_5"));
        actionMake_Current_6 = new QAction(MeshTool);
        actionMake_Current_6->setObjectName(QStringLiteral("actionMake_Current_6"));
        actionActivateAlbedoTexture = new QAction(MeshTool);
        actionActivateAlbedoTexture->setObjectName(QStringLiteral("actionActivateAlbedoTexture"));
        actionActivateAlbedoTexture->setCheckable(true);
        actionActivateAlbedoTexture->setChecked(true);
        actionActivateMetallicTexture = new QAction(MeshTool);
        actionActivateMetallicTexture->setObjectName(QStringLiteral("actionActivateMetallicTexture"));
        actionActivateMetallicTexture->setCheckable(true);
        actionActivateRoughnessTexture = new QAction(MeshTool);
        actionActivateRoughnessTexture->setObjectName(QStringLiteral("actionActivateRoughnessTexture"));
        actionActivateRoughnessTexture->setCheckable(true);
        actionActivateAmbientOcclusionTexture = new QAction(MeshTool);
        actionActivateAmbientOcclusionTexture->setObjectName(QStringLiteral("actionActivateAmbientOcclusionTexture"));
        actionActivateAmbientOcclusionTexture->setCheckable(true);
        actionActivateEmissiveTexture = new QAction(MeshTool);
        actionActivateEmissiveTexture->setObjectName(QStringLiteral("actionActivateEmissiveTexture"));
        actionActivateEmissiveTexture->setCheckable(true);
        actionActivateDisplacementTexture = new QAction(MeshTool);
        actionActivateDisplacementTexture->setObjectName(QStringLiteral("actionActivateDisplacementTexture"));
        actionActivateDisplacementTexture->setCheckable(true);
        actionActivateDisplacementTexture->setChecked(false);
        actionSetPaint = new QAction(MeshTool);
        actionSetPaint->setObjectName(QStringLiteral("actionSetPaint"));
        actionFill = new QAction(MeshTool);
        actionFill->setObjectName(QStringLiteral("actionFill"));
        centralWidget = new QWidget(MeshTool);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        openGLWidget = new GLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(openGLWidget);

        MeshTool->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MeshTool);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 912, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuAlbedo = new QMenu(menuEdit);
        menuAlbedo->setObjectName(QStringLiteral("menuAlbedo"));
        menuMetallic = new QMenu(menuEdit);
        menuMetallic->setObjectName(QStringLiteral("menuMetallic"));
        menuRoughness = new QMenu(menuEdit);
        menuRoughness->setObjectName(QStringLiteral("menuRoughness"));
        menuAmbientOcclusion = new QMenu(menuEdit);
        menuAmbientOcclusion->setObjectName(QStringLiteral("menuAmbientOcclusion"));
        menuEmissive = new QMenu(menuEdit);
        menuEmissive->setObjectName(QStringLiteral("menuEmissive"));
        menuDisplacement = new QMenu(menuEdit);
        menuDisplacement->setObjectName(QStringLiteral("menuDisplacement"));
        menuActiveTexture = new QMenu(menuEdit);
        menuActiveTexture->setObjectName(QStringLiteral("menuActiveTexture"));
        MeshTool->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuFile->addAction(actionOpen);
        menuView->addAction(actionCenterCamera);
        menuView->addAction(actionToggleWireframe);
        menuView->addSeparator();
        menuView->addAction(actionDefaultView);
        menuView->addAction(actionTextureView);
        menuView->addAction(actionRenderView);
        menuView->addAction(actionUvView);
        menuEdit->addAction(menuActiveTexture->menuAction());
        menuEdit->addSeparator();
        menuEdit->addAction(menuAlbedo->menuAction());
        menuEdit->addAction(menuMetallic->menuAction());
        menuEdit->addAction(menuRoughness->menuAction());
        menuEdit->addAction(menuAmbientOcclusion->menuAction());
        menuEdit->addAction(menuEmissive->menuAction());
        menuEdit->addAction(menuDisplacement->menuAction());
        menuEdit->addSeparator();
        menuEdit->addAction(actionSetStrokeWidth);
        menuEdit->addAction(actionSetPaint);
        menuEdit->addAction(actionFill);
        menuAlbedo->addAction(actionAlbedoSetColor);
        menuAlbedo->addSeparator();
        menuAlbedo->addAction(actionAlbedoAddTexture);
        menuAlbedo->addAction(actionAlbedoDeleteTexture);
        menuMetallic->addAction(actionMetallicSetValue);
        menuMetallic->addSeparator();
        menuMetallic->addAction(actionMetallicAddTexture);
        menuMetallic->addAction(actionMetallicDeleteTexture);
        menuRoughness->addAction(actionRoughnessSetValue);
        menuRoughness->addSeparator();
        menuRoughness->addAction(actionRoughnessAddTexture);
        menuRoughness->addAction(actionRoughnessDeleteTexture);
        menuAmbientOcclusion->addAction(actionAmbientOcclusionAddTexture);
        menuAmbientOcclusion->addAction(actionAmbientOcclusionDeleteTexture);
        menuEmissive->addAction(actionEmissiveSetEmissiveColor);
        menuEmissive->addSeparator();
        menuEmissive->addAction(actionEmissiveAddTexture);
        menuEmissive->addAction(actionEmissiveDeleteTexture);
        menuDisplacement->addAction(actionDisplacementAddTexture);
        menuDisplacement->addAction(actionDisplacementDeleteTexture);
        menuActiveTexture->addAction(actionActivateAlbedoTexture);
        menuActiveTexture->addAction(actionActivateMetallicTexture);
        menuActiveTexture->addAction(actionActivateRoughnessTexture);
        menuActiveTexture->addAction(actionActivateAmbientOcclusionTexture);
        menuActiveTexture->addAction(actionActivateEmissiveTexture);
        menuActiveTexture->addAction(actionActivateDisplacementTexture);

        retranslateUi(MeshTool);

        QMetaObject::connectSlotsByName(MeshTool);
    } // setupUi

    void retranslateUi(QMainWindow *MeshTool)
    {
        MeshTool->setWindowTitle(QApplication::translate("MeshTool", "MeshTool", nullptr));
        actionOpen->setText(QApplication::translate("MeshTool", "Open Model", nullptr));
        actionToggleWireframe->setText(QApplication::translate("MeshTool", "Toggle Wireframe", nullptr));
        actionCenterCamera->setText(QApplication::translate("MeshTool", "Center Camera", nullptr));
        actionRenderView->setText(QApplication::translate("MeshTool", "Render View", nullptr));
        actionToggleCameraMode->setText(QApplication::translate("MeshTool", "Toggle Camera Mode", nullptr));
        actionUvView->setText(QApplication::translate("MeshTool", "UV View", nullptr));
        action3dView->setText(QApplication::translate("MeshTool", "3D View", nullptr));
        actionDefaultView->setText(QApplication::translate("MeshTool", "Default View", nullptr));
        actionTextureView->setText(QApplication::translate("MeshTool", "Texture View", nullptr));
        actionSetStrokeWidth->setText(QApplication::translate("MeshTool", "Set Stroke Width", nullptr));
        actionSet_Color->setText(QApplication::translate("MeshTool", "Set Color", nullptr));
        actionSet_Clear_Color->setText(QApplication::translate("MeshTool", "Set Clear Color", nullptr));
        actionSet_Clear_Color_2->setText(QApplication::translate("MeshTool", "Set Clear Color", nullptr));
        actionAlbedoSetColor->setText(QApplication::translate("MeshTool", "Set Color", nullptr));
        actionClear->setText(QApplication::translate("MeshTool", "Clear Texture", nullptr));
        actionSet_Resolution->setText(QApplication::translate("MeshTool", "Set Resolution", nullptr));
        actionSet_Clear_Color_3->setText(QApplication::translate("MeshTool", "Set Clear Value", nullptr));
        actionMetallicSetValue->setText(QApplication::translate("MeshTool", "Set Value", nullptr));
        actionClear_2->setText(QApplication::translate("MeshTool", "Clear Texture", nullptr));
        actionSet_Resolution_2->setText(QApplication::translate("MeshTool", "Set Resolution", nullptr));
        actionSet_Clear_Color_4->setText(QApplication::translate("MeshTool", "Set Clear Value", nullptr));
        actionRoughnessSetValue->setText(QApplication::translate("MeshTool", "Set Value", nullptr));
        actionSet_Resolution_3->setText(QApplication::translate("MeshTool", "Set Resolution", nullptr));
        actionClear_3->setText(QApplication::translate("MeshTool", "Clear Texture", nullptr));
        actionSet_Clear_Color_5->setText(QApplication::translate("MeshTool", "Set Clear Value", nullptr));
        actionAmbientOcclusionSet->setText(QApplication::translate("MeshTool", "Set Value", nullptr));
        actionSet_Resolution_4->setText(QApplication::translate("MeshTool", "Set Resolution", nullptr));
        actionClear_4->setText(QApplication::translate("MeshTool", "Clear Texture", nullptr));
        actionSet_Clear_Color_6->setText(QApplication::translate("MeshTool", "Set Clear Color", nullptr));
        actionSet_Color_6->setText(QApplication::translate("MeshTool", "Set Color", nullptr));
        actionSet_Resolution_5->setText(QApplication::translate("MeshTool", "Set Resolution", nullptr));
        actionClear_5->setText(QApplication::translate("MeshTool", "Clear", nullptr));
        actionSet_Clear_Color_7->setText(QApplication::translate("MeshTool", "Set Clear Color", nullptr));
        actionSet_Color_7->setText(QApplication::translate("MeshTool", "Set Color", nullptr));
        actionSet_Resolution_6->setText(QApplication::translate("MeshTool", "Set Resolution", nullptr));
        actionClear_6->setText(QApplication::translate("MeshTool", "Clear", nullptr));
        actionEmissiveSetEmissiveColor->setText(QApplication::translate("MeshTool", "Set Emissive Color", nullptr));
        actionAlbedoDeleteTexture->setText(QApplication::translate("MeshTool", "Delete Texture", nullptr));
        actionAlbedoAddTexture->setText(QApplication::translate("MeshTool", "Add Texture", nullptr));
        actionMetallicAddTexture->setText(QApplication::translate("MeshTool", "Add Texture", nullptr));
        actionMetallicDeleteTexture->setText(QApplication::translate("MeshTool", "Delete Texture", nullptr));
        actionRoughnessAddTexture->setText(QApplication::translate("MeshTool", "Add Texture", nullptr));
        actionRoughnessDeleteTexture->setText(QApplication::translate("MeshTool", "Delete Texture", nullptr));
        actionAmbientOcclusionAddTexture->setText(QApplication::translate("MeshTool", "Add Texture", nullptr));
        actionAmbientOcclusionDeleteTexture->setText(QApplication::translate("MeshTool", "Delete Texture", nullptr));
        actionEmissiveAddTexture->setText(QApplication::translate("MeshTool", "Add Texture", nullptr));
        actionEmissiveDeleteTexture->setText(QApplication::translate("MeshTool", "Delete Texture", nullptr));
        actionDisplacementAddTexture->setText(QApplication::translate("MeshTool", "Add Texture", nullptr));
        actionDisplacementDeleteTexture->setText(QApplication::translate("MeshTool", "Delete Texture", nullptr));
        actionMake_Current->setText(QApplication::translate("MeshTool", "Make Current", nullptr));
        actionMake_Current_2->setText(QApplication::translate("MeshTool", "Make Current", nullptr));
        actionMake_Current_3->setText(QApplication::translate("MeshTool", "Make Current", nullptr));
        actionMake_Current_4->setText(QApplication::translate("MeshTool", "Make Current", nullptr));
        actionMake_Current_5->setText(QApplication::translate("MeshTool", "Make Current", nullptr));
        actionMake_Current_6->setText(QApplication::translate("MeshTool", "Make Current", nullptr));
        actionActivateAlbedoTexture->setText(QApplication::translate("MeshTool", "Albedo Texture", nullptr));
        actionActivateMetallicTexture->setText(QApplication::translate("MeshTool", "Metallic Texture", nullptr));
        actionActivateRoughnessTexture->setText(QApplication::translate("MeshTool", "Roughness Texture", nullptr));
        actionActivateAmbientOcclusionTexture->setText(QApplication::translate("MeshTool", "Ambient Occlusion Texture", nullptr));
        actionActivateEmissiveTexture->setText(QApplication::translate("MeshTool", "Emissive Texture", nullptr));
        actionActivateDisplacementTexture->setText(QApplication::translate("MeshTool", "Displacement Texture", nullptr));
        actionSetPaint->setText(QApplication::translate("MeshTool", "Set Paint", nullptr));
        actionFill->setText(QApplication::translate("MeshTool", "Fill", nullptr));
        menuFile->setTitle(QApplication::translate("MeshTool", "File", nullptr));
        menuView->setTitle(QApplication::translate("MeshTool", "View", nullptr));
        menuEdit->setTitle(QApplication::translate("MeshTool", "Edit", nullptr));
        menuAlbedo->setTitle(QApplication::translate("MeshTool", "Albedo", nullptr));
        menuMetallic->setTitle(QApplication::translate("MeshTool", "Metallic", nullptr));
        menuRoughness->setTitle(QApplication::translate("MeshTool", "Roughness", nullptr));
        menuAmbientOcclusion->setTitle(QApplication::translate("MeshTool", "Ambient Occlusion", nullptr));
        menuEmissive->setTitle(QApplication::translate("MeshTool", "Emissive", nullptr));
        menuDisplacement->setTitle(QApplication::translate("MeshTool", "Displacement", nullptr));
        menuActiveTexture->setTitle(QApplication::translate("MeshTool", "Active Texture", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MeshTool: public Ui_MeshTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHTOOL_H
