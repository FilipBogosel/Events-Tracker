/********************************************************************************
** Form generated from reading UI file 'Events_Tracker_QT.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVENTS_TRACKER_QT_H
#define UI_EVENTS_TRACKER_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Events_Tracker_QTClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Events_Tracker_QTClass)
    {
        if (Events_Tracker_QTClass->objectName().isEmpty())
            Events_Tracker_QTClass->setObjectName("Events_Tracker_QTClass");
        Events_Tracker_QTClass->resize(600, 400);
        menuBar = new QMenuBar(Events_Tracker_QTClass);
        menuBar->setObjectName("menuBar");
        Events_Tracker_QTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Events_Tracker_QTClass);
        mainToolBar->setObjectName("mainToolBar");
        Events_Tracker_QTClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Events_Tracker_QTClass);
        centralWidget->setObjectName("centralWidget");
        Events_Tracker_QTClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Events_Tracker_QTClass);
        statusBar->setObjectName("statusBar");
        Events_Tracker_QTClass->setStatusBar(statusBar);

        retranslateUi(Events_Tracker_QTClass);

        QMetaObject::connectSlotsByName(Events_Tracker_QTClass);
    } // setupUi

    void retranslateUi(QMainWindow *Events_Tracker_QTClass)
    {
        Events_Tracker_QTClass->setWindowTitle(QCoreApplication::translate("Events_Tracker_QTClass", "Events_Tracker_QT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Events_Tracker_QTClass: public Ui_Events_Tracker_QTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVENTS_TRACKER_QT_H
