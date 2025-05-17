#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Events_Tracker_QT.h"
#include "Admin_Window.h"
#include <QPushButton>
#include <QIcon>
#include <QLabel>
#include <QLayout>
#include <QVBoxLayout>
#include <QListView>
#include "LoginUser.h"


class Events_Tracker_QT : public QMainWindow
{
    Q_OBJECT

public:
	Service *service;
    Events_Tracker_QT(QWidget *parent = nullptr);
    ~Events_Tracker_QT();

private:
    Ui::Events_Tracker_QTClass ui;

};
