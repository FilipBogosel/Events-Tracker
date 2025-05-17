#pragma once
#include <QtWidgets/QMainWindow>
#include <QListView>
#include <QPushButton>
#include <QIcon>
#include <QLabel>
#include "Service.h"
#include "User.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QGridLayout>
#include <QStackedWidget>
#include <QComboBox>

class User_Window : public QMainWindow
{
	Q_OBJECT
public:
	User_Window(QWidget* parent = nullptr, int user_position = -1, Service *service = nullptr);
	~User_Window();
private:
	// UI setup methods
	void setupWindowProperties();
	QHBoxLayout* createMainLayout();
	QVBoxLayout* createPlaylistLayout();
	QVBoxLayout* createControlsLayout();
	QGridLayout* createButtonsLayout();
	void styleButtons();
	void connectButtons();
	
	// Data methods
	QWidget* createEventCard(const Event& event);
	void navigateEvents(int direction);
	void initializeEvents();
	QListView* populate_playlist();
	void refreshPlaylistView();

	
	// Member variables
	QWidget* parent;
	Service* service;
	int user_position;
	int currentEventIndex;
	std::vector<Event> events;
	
	// UI elements
	QListView* playlist;
	QStackedWidget* availableEvents;
	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* updateButton;
	QPushButton* exitButton;
	QPushButton* nextButton;
	QPushButton* previousButton;
	QPushButton* openPlaylist;
	QComboBox* fileType;
	
	// Form fields
	QLineEdit* event_name;
	QLineEdit* event_description;
	QLineEdit* event_date;
	QLineEdit* event_participants;
	QLineEdit* event_link;
};

