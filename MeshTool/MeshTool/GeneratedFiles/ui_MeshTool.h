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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MeshTool
{
public:
    QAction *actionOpen;
    QAction *actionToggleWireframe;
    QAction *actionCenterCamera;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    GLWidget *openGLWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;

    void setupUi(QMainWindow *MeshTool)
    {
        if (MeshTool->objectName().isEmpty())
            MeshTool->setObjectName(QStringLiteral("MeshTool"));
        MeshTool->resize(825, 604);
        actionOpen = new QAction(MeshTool);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionToggleWireframe = new QAction(MeshTool);
        actionToggleWireframe->setObjectName(QStringLiteral("actionToggleWireframe"));
        actionToggleWireframe->setCheckable(true);
        actionCenterCamera = new QAction(MeshTool);
        actionCenterCamera->setObjectName(QStringLiteral("actionCenterCamera"));
        centralWidget = new QWidget(MeshTool);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        openGLWidget = new GLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

        gridLayout->addWidget(openGLWidget, 0, 0, 1, 1);

        MeshTool->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MeshTool);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 825, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MeshTool->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuFile->addAction(actionOpen);
        menuView->addAction(actionToggleWireframe);
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
        menuFile->setTitle(QApplication::translate("MeshTool", "File", nullptr));
        menuView->setTitle(QApplication::translate("MeshTool", "View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MeshTool: public Ui_MeshTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHTOOL_H
