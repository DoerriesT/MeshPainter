/********************************************************************************
** Form generated from reading UI file 'MeshPainter.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESHPAINTER_H
#define UI_MESHPAINTER_H

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

class Ui_MeshPainter
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
    QAction *actionClearActive;
    QAction *actionSetEmissiveColor;
    QAction *actionClearAll;
    QAction *actionOpenAlbedoTexture;
    QAction *actionOpenMetallicTexture;
    QAction *actionOpenRoughnessTexture;
    QAction *actionOpenAmbientOcclusionTexture;
    QAction *actionOpenEmissiveTexture;
    QAction *actionOpenDisplacementTexture;
    QAction *actionSaveAllTextures;
    QAction *actionSaveAlbedoTexture;
    QAction *actionSaveMetallicTexture;
    QAction *actionSaveRoughnessTexture;
    QAction *actionSaveAmbientOcclusionTexture;
    QAction *actionSaveEmissiveTexture;
    QAction *actionSaveDisplacementTexture;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    GLWidget *openGLWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOpenTexture;
    QMenu *menuSaveTexture;
    QMenu *menuView;
    QMenu *menuEdit;
    QMenu *menuActiveTexture;

    void setupUi(QMainWindow *MeshPainter)
    {
        if (MeshPainter->objectName().isEmpty())
            MeshPainter->setObjectName(QStringLiteral("MeshPainter"));
        MeshPainter->resize(912, 768);
        actionOpen = new QAction(MeshPainter);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionToggleWireframe = new QAction(MeshPainter);
        actionToggleWireframe->setObjectName(QStringLiteral("actionToggleWireframe"));
        actionToggleWireframe->setCheckable(true);
        actionCenterCamera = new QAction(MeshPainter);
        actionCenterCamera->setObjectName(QStringLiteral("actionCenterCamera"));
        actionRenderView = new QAction(MeshPainter);
        actionRenderView->setObjectName(QStringLiteral("actionRenderView"));
        actionRenderView->setCheckable(true);
        actionRenderView->setChecked(true);
        actionToggleCameraMode = new QAction(MeshPainter);
        actionToggleCameraMode->setObjectName(QStringLiteral("actionToggleCameraMode"));
        actionToggleCameraMode->setCheckable(true);
        actionUvView = new QAction(MeshPainter);
        actionUvView->setObjectName(QStringLiteral("actionUvView"));
        actionUvView->setCheckable(true);
        action3dView = new QAction(MeshPainter);
        action3dView->setObjectName(QStringLiteral("action3dView"));
        action3dView->setCheckable(true);
        actionDefaultView = new QAction(MeshPainter);
        actionDefaultView->setObjectName(QStringLiteral("actionDefaultView"));
        actionDefaultView->setCheckable(true);
        actionDefaultView->setChecked(false);
        actionTextureView = new QAction(MeshPainter);
        actionTextureView->setObjectName(QStringLiteral("actionTextureView"));
        actionTextureView->setCheckable(true);
        actionSetStrokeWidth = new QAction(MeshPainter);
        actionSetStrokeWidth->setObjectName(QStringLiteral("actionSetStrokeWidth"));
        actionSet_Color = new QAction(MeshPainter);
        actionSet_Color->setObjectName(QStringLiteral("actionSet_Color"));
        actionSet_Clear_Color = new QAction(MeshPainter);
        actionSet_Clear_Color->setObjectName(QStringLiteral("actionSet_Clear_Color"));
        actionSet_Clear_Color_2 = new QAction(MeshPainter);
        actionSet_Clear_Color_2->setObjectName(QStringLiteral("actionSet_Clear_Color_2"));
        actionAlbedoSetColor = new QAction(MeshPainter);
        actionAlbedoSetColor->setObjectName(QStringLiteral("actionAlbedoSetColor"));
        actionClear = new QAction(MeshPainter);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        actionSet_Resolution = new QAction(MeshPainter);
        actionSet_Resolution->setObjectName(QStringLiteral("actionSet_Resolution"));
        actionSet_Clear_Color_3 = new QAction(MeshPainter);
        actionSet_Clear_Color_3->setObjectName(QStringLiteral("actionSet_Clear_Color_3"));
        actionMetallicSetValue = new QAction(MeshPainter);
        actionMetallicSetValue->setObjectName(QStringLiteral("actionMetallicSetValue"));
        actionClear_2 = new QAction(MeshPainter);
        actionClear_2->setObjectName(QStringLiteral("actionClear_2"));
        actionSet_Resolution_2 = new QAction(MeshPainter);
        actionSet_Resolution_2->setObjectName(QStringLiteral("actionSet_Resolution_2"));
        actionSet_Clear_Color_4 = new QAction(MeshPainter);
        actionSet_Clear_Color_4->setObjectName(QStringLiteral("actionSet_Clear_Color_4"));
        actionRoughnessSetValue = new QAction(MeshPainter);
        actionRoughnessSetValue->setObjectName(QStringLiteral("actionRoughnessSetValue"));
        actionSet_Resolution_3 = new QAction(MeshPainter);
        actionSet_Resolution_3->setObjectName(QStringLiteral("actionSet_Resolution_3"));
        actionClear_3 = new QAction(MeshPainter);
        actionClear_3->setObjectName(QStringLiteral("actionClear_3"));
        actionSet_Clear_Color_5 = new QAction(MeshPainter);
        actionSet_Clear_Color_5->setObjectName(QStringLiteral("actionSet_Clear_Color_5"));
        actionAmbientOcclusionSet = new QAction(MeshPainter);
        actionAmbientOcclusionSet->setObjectName(QStringLiteral("actionAmbientOcclusionSet"));
        actionSet_Resolution_4 = new QAction(MeshPainter);
        actionSet_Resolution_4->setObjectName(QStringLiteral("actionSet_Resolution_4"));
        actionClear_4 = new QAction(MeshPainter);
        actionClear_4->setObjectName(QStringLiteral("actionClear_4"));
        actionSet_Clear_Color_6 = new QAction(MeshPainter);
        actionSet_Clear_Color_6->setObjectName(QStringLiteral("actionSet_Clear_Color_6"));
        actionSet_Color_6 = new QAction(MeshPainter);
        actionSet_Color_6->setObjectName(QStringLiteral("actionSet_Color_6"));
        actionSet_Resolution_5 = new QAction(MeshPainter);
        actionSet_Resolution_5->setObjectName(QStringLiteral("actionSet_Resolution_5"));
        actionClear_5 = new QAction(MeshPainter);
        actionClear_5->setObjectName(QStringLiteral("actionClear_5"));
        actionSet_Clear_Color_7 = new QAction(MeshPainter);
        actionSet_Clear_Color_7->setObjectName(QStringLiteral("actionSet_Clear_Color_7"));
        actionSet_Color_7 = new QAction(MeshPainter);
        actionSet_Color_7->setObjectName(QStringLiteral("actionSet_Color_7"));
        actionSet_Resolution_6 = new QAction(MeshPainter);
        actionSet_Resolution_6->setObjectName(QStringLiteral("actionSet_Resolution_6"));
        actionClear_6 = new QAction(MeshPainter);
        actionClear_6->setObjectName(QStringLiteral("actionClear_6"));
        actionEmissiveSetEmissiveColor = new QAction(MeshPainter);
        actionEmissiveSetEmissiveColor->setObjectName(QStringLiteral("actionEmissiveSetEmissiveColor"));
        actionAlbedoDeleteTexture = new QAction(MeshPainter);
        actionAlbedoDeleteTexture->setObjectName(QStringLiteral("actionAlbedoDeleteTexture"));
        actionAlbedoAddTexture = new QAction(MeshPainter);
        actionAlbedoAddTexture->setObjectName(QStringLiteral("actionAlbedoAddTexture"));
        actionMetallicAddTexture = new QAction(MeshPainter);
        actionMetallicAddTexture->setObjectName(QStringLiteral("actionMetallicAddTexture"));
        actionMetallicDeleteTexture = new QAction(MeshPainter);
        actionMetallicDeleteTexture->setObjectName(QStringLiteral("actionMetallicDeleteTexture"));
        actionRoughnessAddTexture = new QAction(MeshPainter);
        actionRoughnessAddTexture->setObjectName(QStringLiteral("actionRoughnessAddTexture"));
        actionRoughnessDeleteTexture = new QAction(MeshPainter);
        actionRoughnessDeleteTexture->setObjectName(QStringLiteral("actionRoughnessDeleteTexture"));
        actionAmbientOcclusionAddTexture = new QAction(MeshPainter);
        actionAmbientOcclusionAddTexture->setObjectName(QStringLiteral("actionAmbientOcclusionAddTexture"));
        actionAmbientOcclusionDeleteTexture = new QAction(MeshPainter);
        actionAmbientOcclusionDeleteTexture->setObjectName(QStringLiteral("actionAmbientOcclusionDeleteTexture"));
        actionEmissiveAddTexture = new QAction(MeshPainter);
        actionEmissiveAddTexture->setObjectName(QStringLiteral("actionEmissiveAddTexture"));
        actionEmissiveDeleteTexture = new QAction(MeshPainter);
        actionEmissiveDeleteTexture->setObjectName(QStringLiteral("actionEmissiveDeleteTexture"));
        actionDisplacementAddTexture = new QAction(MeshPainter);
        actionDisplacementAddTexture->setObjectName(QStringLiteral("actionDisplacementAddTexture"));
        actionDisplacementDeleteTexture = new QAction(MeshPainter);
        actionDisplacementDeleteTexture->setObjectName(QStringLiteral("actionDisplacementDeleteTexture"));
        actionMake_Current = new QAction(MeshPainter);
        actionMake_Current->setObjectName(QStringLiteral("actionMake_Current"));
        actionMake_Current_2 = new QAction(MeshPainter);
        actionMake_Current_2->setObjectName(QStringLiteral("actionMake_Current_2"));
        actionMake_Current_3 = new QAction(MeshPainter);
        actionMake_Current_3->setObjectName(QStringLiteral("actionMake_Current_3"));
        actionMake_Current_4 = new QAction(MeshPainter);
        actionMake_Current_4->setObjectName(QStringLiteral("actionMake_Current_4"));
        actionMake_Current_5 = new QAction(MeshPainter);
        actionMake_Current_5->setObjectName(QStringLiteral("actionMake_Current_5"));
        actionMake_Current_6 = new QAction(MeshPainter);
        actionMake_Current_6->setObjectName(QStringLiteral("actionMake_Current_6"));
        actionActivateAlbedoTexture = new QAction(MeshPainter);
        actionActivateAlbedoTexture->setObjectName(QStringLiteral("actionActivateAlbedoTexture"));
        actionActivateAlbedoTexture->setCheckable(true);
        actionActivateAlbedoTexture->setChecked(true);
        actionActivateMetallicTexture = new QAction(MeshPainter);
        actionActivateMetallicTexture->setObjectName(QStringLiteral("actionActivateMetallicTexture"));
        actionActivateMetallicTexture->setCheckable(true);
        actionActivateRoughnessTexture = new QAction(MeshPainter);
        actionActivateRoughnessTexture->setObjectName(QStringLiteral("actionActivateRoughnessTexture"));
        actionActivateRoughnessTexture->setCheckable(true);
        actionActivateAmbientOcclusionTexture = new QAction(MeshPainter);
        actionActivateAmbientOcclusionTexture->setObjectName(QStringLiteral("actionActivateAmbientOcclusionTexture"));
        actionActivateAmbientOcclusionTexture->setCheckable(true);
        actionActivateEmissiveTexture = new QAction(MeshPainter);
        actionActivateEmissiveTexture->setObjectName(QStringLiteral("actionActivateEmissiveTexture"));
        actionActivateEmissiveTexture->setCheckable(true);
        actionActivateDisplacementTexture = new QAction(MeshPainter);
        actionActivateDisplacementTexture->setObjectName(QStringLiteral("actionActivateDisplacementTexture"));
        actionActivateDisplacementTexture->setCheckable(true);
        actionActivateDisplacementTexture->setChecked(false);
        actionSetPaint = new QAction(MeshPainter);
        actionSetPaint->setObjectName(QStringLiteral("actionSetPaint"));
        actionClearActive = new QAction(MeshPainter);
        actionClearActive->setObjectName(QStringLiteral("actionClearActive"));
        actionSetEmissiveColor = new QAction(MeshPainter);
        actionSetEmissiveColor->setObjectName(QStringLiteral("actionSetEmissiveColor"));
        actionClearAll = new QAction(MeshPainter);
        actionClearAll->setObjectName(QStringLiteral("actionClearAll"));
        actionOpenAlbedoTexture = new QAction(MeshPainter);
        actionOpenAlbedoTexture->setObjectName(QStringLiteral("actionOpenAlbedoTexture"));
        actionOpenMetallicTexture = new QAction(MeshPainter);
        actionOpenMetallicTexture->setObjectName(QStringLiteral("actionOpenMetallicTexture"));
        actionOpenRoughnessTexture = new QAction(MeshPainter);
        actionOpenRoughnessTexture->setObjectName(QStringLiteral("actionOpenRoughnessTexture"));
        actionOpenAmbientOcclusionTexture = new QAction(MeshPainter);
        actionOpenAmbientOcclusionTexture->setObjectName(QStringLiteral("actionOpenAmbientOcclusionTexture"));
        actionOpenEmissiveTexture = new QAction(MeshPainter);
        actionOpenEmissiveTexture->setObjectName(QStringLiteral("actionOpenEmissiveTexture"));
        actionOpenDisplacementTexture = new QAction(MeshPainter);
        actionOpenDisplacementTexture->setObjectName(QStringLiteral("actionOpenDisplacementTexture"));
        actionSaveAllTextures = new QAction(MeshPainter);
        actionSaveAllTextures->setObjectName(QStringLiteral("actionSaveAllTextures"));
        actionSaveAlbedoTexture = new QAction(MeshPainter);
        actionSaveAlbedoTexture->setObjectName(QStringLiteral("actionSaveAlbedoTexture"));
        actionSaveMetallicTexture = new QAction(MeshPainter);
        actionSaveMetallicTexture->setObjectName(QStringLiteral("actionSaveMetallicTexture"));
        actionSaveRoughnessTexture = new QAction(MeshPainter);
        actionSaveRoughnessTexture->setObjectName(QStringLiteral("actionSaveRoughnessTexture"));
        actionSaveAmbientOcclusionTexture = new QAction(MeshPainter);
        actionSaveAmbientOcclusionTexture->setObjectName(QStringLiteral("actionSaveAmbientOcclusionTexture"));
        actionSaveEmissiveTexture = new QAction(MeshPainter);
        actionSaveEmissiveTexture->setObjectName(QStringLiteral("actionSaveEmissiveTexture"));
        actionSaveDisplacementTexture = new QAction(MeshPainter);
        actionSaveDisplacementTexture->setObjectName(QStringLiteral("actionSaveDisplacementTexture"));
        centralWidget = new QWidget(MeshPainter);
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

        MeshPainter->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MeshPainter);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 912, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuOpenTexture = new QMenu(menuFile);
        menuOpenTexture->setObjectName(QStringLiteral("menuOpenTexture"));
        menuSaveTexture = new QMenu(menuFile);
        menuSaveTexture->setObjectName(QStringLiteral("menuSaveTexture"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuActiveTexture = new QMenu(menuEdit);
        menuActiveTexture->setObjectName(QStringLiteral("menuActiveTexture"));
        MeshPainter->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(menuOpenTexture->menuAction());
        menuFile->addAction(menuSaveTexture->menuAction());
        menuFile->addAction(actionSaveAllTextures);
        menuOpenTexture->addAction(actionOpenAlbedoTexture);
        menuOpenTexture->addAction(actionOpenMetallicTexture);
        menuOpenTexture->addAction(actionOpenRoughnessTexture);
        menuOpenTexture->addAction(actionOpenAmbientOcclusionTexture);
        menuOpenTexture->addAction(actionOpenEmissiveTexture);
        menuOpenTexture->addAction(actionOpenDisplacementTexture);
        menuSaveTexture->addAction(actionSaveAlbedoTexture);
        menuSaveTexture->addAction(actionSaveMetallicTexture);
        menuSaveTexture->addAction(actionSaveRoughnessTexture);
        menuSaveTexture->addAction(actionSaveAmbientOcclusionTexture);
        menuSaveTexture->addAction(actionSaveEmissiveTexture);
        menuSaveTexture->addAction(actionSaveDisplacementTexture);
        menuView->addAction(actionCenterCamera);
        menuView->addAction(actionToggleWireframe);
        menuView->addSeparator();
        menuView->addAction(actionDefaultView);
        menuView->addAction(actionTextureView);
        menuView->addAction(actionRenderView);
        menuView->addAction(actionUvView);
        menuEdit->addAction(menuActiveTexture->menuAction());
        menuEdit->addSeparator();
        menuEdit->addAction(actionSetStrokeWidth);
        menuEdit->addAction(actionSetPaint);
        menuEdit->addAction(actionClearActive);
        menuEdit->addAction(actionClearAll);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSetEmissiveColor);
        menuActiveTexture->addAction(actionActivateAlbedoTexture);
        menuActiveTexture->addAction(actionActivateMetallicTexture);
        menuActiveTexture->addAction(actionActivateRoughnessTexture);
        menuActiveTexture->addAction(actionActivateAmbientOcclusionTexture);
        menuActiveTexture->addAction(actionActivateEmissiveTexture);
        menuActiveTexture->addAction(actionActivateDisplacementTexture);

        retranslateUi(MeshPainter);

        QMetaObject::connectSlotsByName(MeshPainter);
    } // setupUi

    void retranslateUi(QMainWindow *MeshPainter)
    {
        MeshPainter->setWindowTitle(QApplication::translate("MeshPainter", "MeshPainter", nullptr));
        actionOpen->setText(QApplication::translate("MeshPainter", "Open Model", nullptr));
        actionToggleWireframe->setText(QApplication::translate("MeshPainter", "Toggle Wireframe", nullptr));
        actionCenterCamera->setText(QApplication::translate("MeshPainter", "Center Camera", nullptr));
        actionRenderView->setText(QApplication::translate("MeshPainter", "Render View", nullptr));
        actionToggleCameraMode->setText(QApplication::translate("MeshPainter", "Toggle Camera Mode", nullptr));
        actionUvView->setText(QApplication::translate("MeshPainter", "UV View", nullptr));
        action3dView->setText(QApplication::translate("MeshPainter", "3D View", nullptr));
        actionDefaultView->setText(QApplication::translate("MeshPainter", "Basic View", nullptr));
        actionTextureView->setText(QApplication::translate("MeshPainter", "Texture View", nullptr));
        actionSetStrokeWidth->setText(QApplication::translate("MeshPainter", "Set Stroke Width", nullptr));
        actionSet_Color->setText(QApplication::translate("MeshPainter", "Set Color", nullptr));
        actionSet_Clear_Color->setText(QApplication::translate("MeshPainter", "Set Clear Color", nullptr));
        actionSet_Clear_Color_2->setText(QApplication::translate("MeshPainter", "Set Clear Color", nullptr));
        actionAlbedoSetColor->setText(QApplication::translate("MeshPainter", "Set Color", nullptr));
        actionClear->setText(QApplication::translate("MeshPainter", "Clear Texture", nullptr));
        actionSet_Resolution->setText(QApplication::translate("MeshPainter", "Set Resolution", nullptr));
        actionSet_Clear_Color_3->setText(QApplication::translate("MeshPainter", "Set Clear Value", nullptr));
        actionMetallicSetValue->setText(QApplication::translate("MeshPainter", "Set Value", nullptr));
        actionClear_2->setText(QApplication::translate("MeshPainter", "Clear Texture", nullptr));
        actionSet_Resolution_2->setText(QApplication::translate("MeshPainter", "Set Resolution", nullptr));
        actionSet_Clear_Color_4->setText(QApplication::translate("MeshPainter", "Set Clear Value", nullptr));
        actionRoughnessSetValue->setText(QApplication::translate("MeshPainter", "Set Value", nullptr));
        actionSet_Resolution_3->setText(QApplication::translate("MeshPainter", "Set Resolution", nullptr));
        actionClear_3->setText(QApplication::translate("MeshPainter", "Clear Texture", nullptr));
        actionSet_Clear_Color_5->setText(QApplication::translate("MeshPainter", "Set Clear Value", nullptr));
        actionAmbientOcclusionSet->setText(QApplication::translate("MeshPainter", "Set Value", nullptr));
        actionSet_Resolution_4->setText(QApplication::translate("MeshPainter", "Set Resolution", nullptr));
        actionClear_4->setText(QApplication::translate("MeshPainter", "Clear Texture", nullptr));
        actionSet_Clear_Color_6->setText(QApplication::translate("MeshPainter", "Set Clear Color", nullptr));
        actionSet_Color_6->setText(QApplication::translate("MeshPainter", "Set Color", nullptr));
        actionSet_Resolution_5->setText(QApplication::translate("MeshPainter", "Set Resolution", nullptr));
        actionClear_5->setText(QApplication::translate("MeshPainter", "Clear", nullptr));
        actionSet_Clear_Color_7->setText(QApplication::translate("MeshPainter", "Set Clear Color", nullptr));
        actionSet_Color_7->setText(QApplication::translate("MeshPainter", "Set Color", nullptr));
        actionSet_Resolution_6->setText(QApplication::translate("MeshPainter", "Set Resolution", nullptr));
        actionClear_6->setText(QApplication::translate("MeshPainter", "Clear", nullptr));
        actionEmissiveSetEmissiveColor->setText(QApplication::translate("MeshPainter", "Set Emissive Color", nullptr));
        actionAlbedoDeleteTexture->setText(QApplication::translate("MeshPainter", "Delete Texture", nullptr));
        actionAlbedoAddTexture->setText(QApplication::translate("MeshPainter", "Add Texture", nullptr));
        actionMetallicAddTexture->setText(QApplication::translate("MeshPainter", "Add Texture", nullptr));
        actionMetallicDeleteTexture->setText(QApplication::translate("MeshPainter", "Delete Texture", nullptr));
        actionRoughnessAddTexture->setText(QApplication::translate("MeshPainter", "Add Texture", nullptr));
        actionRoughnessDeleteTexture->setText(QApplication::translate("MeshPainter", "Delete Texture", nullptr));
        actionAmbientOcclusionAddTexture->setText(QApplication::translate("MeshPainter", "Add Texture", nullptr));
        actionAmbientOcclusionDeleteTexture->setText(QApplication::translate("MeshPainter", "Delete Texture", nullptr));
        actionEmissiveAddTexture->setText(QApplication::translate("MeshPainter", "Add Texture", nullptr));
        actionEmissiveDeleteTexture->setText(QApplication::translate("MeshPainter", "Delete Texture", nullptr));
        actionDisplacementAddTexture->setText(QApplication::translate("MeshPainter", "Add Texture", nullptr));
        actionDisplacementDeleteTexture->setText(QApplication::translate("MeshPainter", "Delete Texture", nullptr));
        actionMake_Current->setText(QApplication::translate("MeshPainter", "Make Current", nullptr));
        actionMake_Current_2->setText(QApplication::translate("MeshPainter", "Make Current", nullptr));
        actionMake_Current_3->setText(QApplication::translate("MeshPainter", "Make Current", nullptr));
        actionMake_Current_4->setText(QApplication::translate("MeshPainter", "Make Current", nullptr));
        actionMake_Current_5->setText(QApplication::translate("MeshPainter", "Make Current", nullptr));
        actionMake_Current_6->setText(QApplication::translate("MeshPainter", "Make Current", nullptr));
        actionActivateAlbedoTexture->setText(QApplication::translate("MeshPainter", "Albedo Texture", nullptr));
        actionActivateMetallicTexture->setText(QApplication::translate("MeshPainter", "Metallic Texture", nullptr));
        actionActivateRoughnessTexture->setText(QApplication::translate("MeshPainter", "Roughness Texture", nullptr));
        actionActivateAmbientOcclusionTexture->setText(QApplication::translate("MeshPainter", "Ambient Occlusion Texture", nullptr));
        actionActivateEmissiveTexture->setText(QApplication::translate("MeshPainter", "Emissive Texture", nullptr));
        actionActivateDisplacementTexture->setText(QApplication::translate("MeshPainter", "Displacement Texture", nullptr));
        actionSetPaint->setText(QApplication::translate("MeshPainter", "Set Paint", nullptr));
        actionClearActive->setText(QApplication::translate("MeshPainter", "Clear Active Texture", nullptr));
        actionSetEmissiveColor->setText(QApplication::translate("MeshPainter", "Set Emissive Color", nullptr));
        actionClearAll->setText(QApplication::translate("MeshPainter", "Clear All Textures", nullptr));
        actionOpenAlbedoTexture->setText(QApplication::translate("MeshPainter", "Albedo", nullptr));
        actionOpenMetallicTexture->setText(QApplication::translate("MeshPainter", "Metallic", nullptr));
        actionOpenRoughnessTexture->setText(QApplication::translate("MeshPainter", "Roughness", nullptr));
        actionOpenAmbientOcclusionTexture->setText(QApplication::translate("MeshPainter", "Ambient Occlusion", nullptr));
        actionOpenEmissiveTexture->setText(QApplication::translate("MeshPainter", "Emissive", nullptr));
        actionOpenDisplacementTexture->setText(QApplication::translate("MeshPainter", "Displacement", nullptr));
        actionSaveAllTextures->setText(QApplication::translate("MeshPainter", "Save All Textures", nullptr));
        actionSaveAlbedoTexture->setText(QApplication::translate("MeshPainter", "Albedo", nullptr));
        actionSaveMetallicTexture->setText(QApplication::translate("MeshPainter", "Metallic", nullptr));
        actionSaveRoughnessTexture->setText(QApplication::translate("MeshPainter", "Roughness", nullptr));
        actionSaveAmbientOcclusionTexture->setText(QApplication::translate("MeshPainter", "Ambient Occlusion", nullptr));
        actionSaveEmissiveTexture->setText(QApplication::translate("MeshPainter", "Emissive", nullptr));
        actionSaveDisplacementTexture->setText(QApplication::translate("MeshPainter", "Displacement", nullptr));
        menuFile->setTitle(QApplication::translate("MeshPainter", "File", nullptr));
        menuOpenTexture->setTitle(QApplication::translate("MeshPainter", "Open Texture", nullptr));
        menuSaveTexture->setTitle(QApplication::translate("MeshPainter", "Save Texture", nullptr));
        menuView->setTitle(QApplication::translate("MeshPainter", "View", nullptr));
        menuEdit->setTitle(QApplication::translate("MeshPainter", "Edit", nullptr));
        menuActiveTexture->setTitle(QApplication::translate("MeshPainter", "Active Texture", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MeshPainter: public Ui_MeshPainter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHPAINTER_H
