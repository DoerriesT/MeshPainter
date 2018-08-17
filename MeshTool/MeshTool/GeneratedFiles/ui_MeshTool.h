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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTreeView>
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
    QAction *actionAlbedoTexture;
    QAction *actionMetallicTexture;
    QAction *actionRoughnessTexture;
    QAction *actionAmbientOcclusionTexture;
    QAction *actionEmissiveTexture;
    QAction *actionDisplacementTexture;
    QAction *actionTextureView;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QTreeView *treeViewModel;
    QTreeView *treeViewMaterial;
    GLWidget *openGLWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuEdit;

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
        actionAlbedoTexture = new QAction(MeshTool);
        actionAlbedoTexture->setObjectName(QStringLiteral("actionAlbedoTexture"));
        actionAlbedoTexture->setCheckable(true);
        actionAlbedoTexture->setChecked(true);
        actionMetallicTexture = new QAction(MeshTool);
        actionMetallicTexture->setObjectName(QStringLiteral("actionMetallicTexture"));
        actionMetallicTexture->setCheckable(true);
        actionRoughnessTexture = new QAction(MeshTool);
        actionRoughnessTexture->setObjectName(QStringLiteral("actionRoughnessTexture"));
        actionRoughnessTexture->setCheckable(true);
        actionAmbientOcclusionTexture = new QAction(MeshTool);
        actionAmbientOcclusionTexture->setObjectName(QStringLiteral("actionAmbientOcclusionTexture"));
        actionAmbientOcclusionTexture->setCheckable(true);
        actionEmissiveTexture = new QAction(MeshTool);
        actionEmissiveTexture->setObjectName(QStringLiteral("actionEmissiveTexture"));
        actionEmissiveTexture->setCheckable(true);
        actionDisplacementTexture = new QAction(MeshTool);
        actionDisplacementTexture->setObjectName(QStringLiteral("actionDisplacementTexture"));
        actionDisplacementTexture->setCheckable(true);
        actionTextureView = new QAction(MeshTool);
        actionTextureView->setObjectName(QStringLiteral("actionTextureView"));
        actionTextureView->setCheckable(true);
        centralWidget = new QWidget(MeshTool);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        treeViewModel = new QTreeView(centralWidget);
        treeViewModel->setObjectName(QStringLiteral("treeViewModel"));

        verticalLayout->addWidget(treeViewModel);

        treeViewMaterial = new QTreeView(centralWidget);
        treeViewMaterial->setObjectName(QStringLiteral("treeViewMaterial"));

        verticalLayout->addWidget(treeViewMaterial);


        horizontalLayout->addLayout(verticalLayout);

        openGLWidget = new GLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(openGLWidget);

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
        menuEdit->addAction(actionAlbedoTexture);
        menuEdit->addAction(actionMetallicTexture);
        menuEdit->addAction(actionRoughnessTexture);
        menuEdit->addAction(actionAmbientOcclusionTexture);
        menuEdit->addAction(actionEmissiveTexture);
        menuEdit->addAction(actionDisplacementTexture);

        retranslateUi(MeshTool);

        QMetaObject::connectSlotsByName(MeshTool);
    } // setupUi

    void retranslateUi(QMainWindow *MeshTool)
    {
        MeshTool->setWindowTitle(QApplication::translate("MeshTool", "MeshTool", nullptr));
        actionOpen->setText(QApplication::translate("MeshTool", "Open", nullptr));
        actionToggleWireframe->setText(QApplication::translate("MeshTool", "Toggle Wireframe", nullptr));
        actionCenterCamera->setText(QApplication::translate("MeshTool", "Center Camera", nullptr));
        actionRenderView->setText(QApplication::translate("MeshTool", "Render View", nullptr));
        actionToggleCameraMode->setText(QApplication::translate("MeshTool", "Toggle Camera Mode", nullptr));
        actionUvView->setText(QApplication::translate("MeshTool", "UV View", nullptr));
        action3dView->setText(QApplication::translate("MeshTool", "3D View", nullptr));
        actionDefaultView->setText(QApplication::translate("MeshTool", "Default View", nullptr));
        actionAlbedoTexture->setText(QApplication::translate("MeshTool", "Albedo Texture", nullptr));
        actionMetallicTexture->setText(QApplication::translate("MeshTool", "Metallic Texture", nullptr));
        actionRoughnessTexture->setText(QApplication::translate("MeshTool", "Roughness Texture", nullptr));
        actionAmbientOcclusionTexture->setText(QApplication::translate("MeshTool", "Ambient Occlusion Texture", nullptr));
        actionEmissiveTexture->setText(QApplication::translate("MeshTool", "Emissive Texture", nullptr));
        actionDisplacementTexture->setText(QApplication::translate("MeshTool", "Displacement Texture", nullptr));
        actionTextureView->setText(QApplication::translate("MeshTool", "Texture View", nullptr));
        menuFile->setTitle(QApplication::translate("MeshTool", "File", nullptr));
        menuView->setTitle(QApplication::translate("MeshTool", "View", nullptr));
        menuEdit->setTitle(QApplication::translate("MeshTool", "Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MeshTool: public Ui_MeshTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHTOOL_H
