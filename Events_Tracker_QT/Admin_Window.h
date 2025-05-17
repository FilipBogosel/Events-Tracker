#pragma once
#include <QtWidgets/QMainWindow>
#include <QListView>
#include <QStandardItemModel>
#include "Service.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "Event.h"
#include <vector>
#include <string>
#include <sstream>
#include <QMessageBox>
class Admin_Window : public QMainWindow
{
	Q_OBJECT
public:
	Admin_Window(QWidget* parent = nullptr, Service *service=nullptr);
	~Admin_Window();
private:
	QListView* eventsListView;
	QListView* populate_events_list();
	void style_buttons(QPushButton* addButton, QPushButton* deleteButton, QPushButton* updateButton, QPushButton* exitButton);
	Service *service;
	QPushButton* addButton;
	QPushButton* deleteButton ;
	QPushButton* updateButton;
	QPushButton* exitButton;
	QLineEdit* event_name;
	QLineEdit* event_description;
	QLineEdit* event_date;
	QLineEdit* event_participants;
	QLineEdit* event_link;
	void setupWindowProperties();
	QHBoxLayout* createMainLayout();
	QVBoxLayout* createListViewLayout();
	QVBoxLayout* createOptionsLayout();
	QVBoxLayout* createEventDetailsLayout();
	QVBoxLayout* createButtonsLayout();
	void setupEventDetailsDisplay();
	QVBoxLayout* buttonsLayout;
	void connectButtons();
	QWidget* par;
	void refreshListView();
};

