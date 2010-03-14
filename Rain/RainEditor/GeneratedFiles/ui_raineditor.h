/********************************************************************************
** Form generated from reading UI file 'raineditor.ui'
**
** Created: Thu Mar 11 21:30:37 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RAINEDITOR_H
#define UI_RAINEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RainEditorClass
{
public:
    QAction *action_Exit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *engineLayout;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *propPanelDock;
    QWidget *dockWidgetContents_3;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *propLayout;

    void setupUi(QMainWindow *RainEditorClass)
    {
        if (RainEditorClass->objectName().isEmpty())
            RainEditorClass->setObjectName(QString::fromUtf8("RainEditorClass"));
        RainEditorClass->resize(796, 535);
        action_Exit = new QAction(RainEditorClass);
        action_Exit->setObjectName(QString::fromUtf8("action_Exit"));
        centralWidget = new QWidget(RainEditorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        engineLayout = new QHBoxLayout();
        engineLayout->setSpacing(6);
        engineLayout->setObjectName(QString::fromUtf8("engineLayout"));

        horizontalLayout->addLayout(engineLayout);

        RainEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RainEditorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 796, 19));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        RainEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RainEditorClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        RainEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RainEditorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        RainEditorClass->setStatusBar(statusBar);
        propPanelDock = new QDockWidget(RainEditorClass);
        propPanelDock->setObjectName(QString::fromUtf8("propPanelDock"));
        propPanelDock->setMinimumSize(QSize(232, 40));
        propPanelDock->setMaximumSize(QSize(232, 524287));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        horizontalLayout_3 = new QHBoxLayout(dockWidgetContents_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        propLayout = new QHBoxLayout();
        propLayout->setSpacing(6);
        propLayout->setObjectName(QString::fromUtf8("propLayout"));

        horizontalLayout_3->addLayout(propLayout);

        propPanelDock->setWidget(dockWidgetContents_3);
        RainEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), propPanelDock);

        menuBar->addAction(menu_File->menuAction());
        menu_File->addAction(action_Exit);

        retranslateUi(RainEditorClass);
        QObject::connect(action_Exit, SIGNAL(triggered()), RainEditorClass, SLOT(close()));

        QMetaObject::connectSlotsByName(RainEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *RainEditorClass)
    {
        RainEditorClass->setWindowTitle(QApplication::translate("RainEditorClass", "Rain Editor", 0, QApplication::UnicodeUTF8));
        action_Exit->setText(QApplication::translate("RainEditorClass", "&Exit", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("RainEditorClass", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RainEditorClass: public Ui_RainEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RAINEDITOR_H
