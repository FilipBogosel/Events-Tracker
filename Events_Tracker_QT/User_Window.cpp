#include "User_Window.h"
#include <vector>
#include <Event.h>
#include <QStandardItemModel>
#include <QMessageBox>
#include <sstream>

User_Window::User_Window(QWidget* parent, int user_position, Service* service) : QMainWindow(parent)
{
    this->parent = parent;
    this->user_position = user_position;
    this->service = service;
    
    // Initialize window properties
    setupWindowProperties();

    // Create layouts
    QHBoxLayout* mainLayout = createMainLayout();

    // Set the layout for the central widget
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);
    
    // Connect signals to slots
    connectButtons();
}

User_Window::~User_Window()
{
}

void User_Window::setupWindowProperties()
{
    setWindowTitle("User Window");
    setWindowIcon(QIcon("C:\\Users\\Filip\\Documents\\Desktop\\Important Images\\Igh0zt-Ios7-Style-Metro-Ui-MetroUI-Apps-Calendar.512.png"));
}

QHBoxLayout* User_Window::createMainLayout()
{
    // Create main layout
    QHBoxLayout* mainLayout = new QHBoxLayout();

    // Create left side (playlist) layout
    QVBoxLayout* playlistLayout = createPlaylistLayout();

    // Create add button
    addButton = new QPushButton("<", this);
    addButton->setStyleSheet("background-color: #2A7E43; color: white;");

    // Create right side (controls) layout
    QVBoxLayout* controlsLayout = createControlsLayout();

    // Add both main sections to main layout
    mainLayout->addLayout(playlistLayout);
    mainLayout->addWidget(addButton);
    mainLayout->addLayout(controlsLayout);

    return mainLayout;
}

QVBoxLayout* User_Window::createPlaylistLayout()
{
    QVBoxLayout* playlistLayout = new QVBoxLayout();

    // Title label
    QLabel* playlistLabel = new QLabel("My Events", this);
    playlistLabel->setAlignment(Qt::AlignCenter);
    playlistLabel->setStyleSheet("font-weight: bold; font-size: 16px;");

    // Create playlist view
    playlist = populate_playlist();

    // Add to layout
    playlistLayout->addWidget(playlistLabel);
    playlistLayout->addWidget(playlist);
    QHBoxLayout* playlistOptions = new QHBoxLayout();
    this->fileType = new QComboBox;
	fileType->addItem("CSV");
	fileType->addItem("HTML");
    this->openPlaylist = new QPushButton("Open", this);
    deleteButton = new QPushButton("Delete Event", this);
    playlistOptions->addWidget(openPlaylist);
    playlistOptions->addWidget(fileType);
    playlistOptions->addWidget(deleteButton);

	playlistLayout->addLayout(playlistOptions);
    return playlistLayout;
}

QVBoxLayout* User_Window::createControlsLayout()
{
    QVBoxLayout* controlsLayout = new QVBoxLayout();

    // Title label
    QLabel* availableLabel = new QLabel("Available Events", this);
    availableLabel->setAlignment(Qt::AlignCenter);
    availableLabel->setStyleSheet("font-weight: bold; font-size: 16px;");

    // Available events list
    availableEvents = new QStackedWidget(this);
    availableEvents->setMinimumHeight(200);
    //Initialise event cards
    initializeEvents();

    // Create buttons layout
    QGridLayout* buttonsLayout = createButtonsLayout();

    // Add widgets to controls layout
    controlsLayout->addWidget(availableLabel);
    controlsLayout->addWidget(availableEvents);
    controlsLayout->addLayout(buttonsLayout);

    return controlsLayout;
}

QGridLayout* User_Window::createButtonsLayout()
{
    QGridLayout* buttonsLayout = new QGridLayout();

    // Create buttons
    exitButton = new QPushButton("Exit", this);
    nextButton = new QPushButton("Next", this);
    previousButton = new QPushButton("Previous", this);

    // Style buttons
    styleButtons();

    // Add buttons to layout
    buttonsLayout->addWidget(previousButton, 0, 0);
    buttonsLayout->addWidget(nextButton, 0, 3);
    //buttonsLayout->addWidget(deleteButton, 1, 1);
    buttonsLayout->addWidget(exitButton, 1, 3);

    return buttonsLayout;
}

void User_Window::styleButtons()
{
    addButton->setStyleSheet("background-color: #2A7E43; color: white;");
    deleteButton->setStyleSheet("background-color: #D8315B; color: white;");
    exitButton->setStyleSheet("background-color: #495057; color: white;");
	exitButton->setFixedHeight(40);
    nextButton->setStyleSheet("background-color: #3A86FF; color: white;");
    previousButton->setStyleSheet("background-color: #3A86FF; color: white;");
}

void User_Window::connectButtons()
{
    connect(playlist, &QListView::doubleClicked, this, [this]() {
        std::stringstream ss;
        QModelIndex index = playlist->currentIndex();
        int row = index.row();
        ss << service->get_watchlist_for_user(user_position)[row];
        std::string event_string = ss.str();
        QString event_details = QString::fromStdString(event_string);
        QMessageBox::information(this, "Event Details", event_details);
        });
    connect(exitButton, &QPushButton::clicked, this, [this]() {
        service->save_users_to_file("users.txt");
        this->close();
        this->parent->show();
    });
    
    connect(deleteButton, &QPushButton::clicked, this, [this]() {
        QModelIndex index = playlist->currentIndex();
        int row = index.row();

        // Check if a row is selected
        if (!index.isValid()) {
            QMessageBox::warning(this, "Warning", "Please select an event to delete.");
            return;
        }

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirm Delete",
            "Are you sure you want to delete this event?",
            QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            service->remove_event_from_watchlist(user_position, row);
            this->refreshPlaylistView();
        }
    });
    //Connect next and previous
    connect(nextButton, &QPushButton::clicked, this, [this]() {
        navigateEvents(1);
        });

    connect(previousButton, &QPushButton::clicked, this, [this]() {
        navigateEvents(-1);
        });

    connect(addButton, &QPushButton::clicked, this, [this]() {
		Event event = events[currentEventIndex];
		service->add_event_to_watchlist(event, user_position);
		refreshPlaylistView();
		});
    connect(openPlaylist, &QPushButton::clicked, this, [this]() {

		std::string file_type = fileType->currentText().toStdString();
		if (file_type == "CSV") {
            service->save_events_list_to_file("events.csv", service->get_users_list()[user_position]);
			std::string command = "start excel.exe events.csv";
			system(command.c_str());
		}
		else if (file_type == "HTML") {
			service->save_events_list_to_file("events.html", service->get_users_list()[user_position]);
			std::string command = "rundll32 url.dll, FileProtocolHandler events.html";
            system(command.c_str());
		}
		
     });
    
}

QWidget* User_Window::createEventCard(const Event& event)
{
    // Create a frame to hold event details
    QFrame* card = new QFrame(this);
    card->setFrameShape(QFrame::Box);
    card->setStyleSheet("background-color: #080612; border-radius: 8px;");

    QVBoxLayout* layout = new QVBoxLayout(card);
    // Event title
    QLabel* titleLabel = new QLabel(QString::fromStdString(event.get_title()), this);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 16px; color: white;");
    titleLabel->setAlignment(Qt::AlignCenter);

    // Event description
    QLabel* descLabel = new QLabel(QString::fromStdString(event.get_description()), this);
    descLabel->setWordWrap(true);
    descLabel->setStyleSheet("color: white;");

    // Event date
    QLabel* dateLabel = new QLabel(QString::fromStdString(event.get_date_time_as_string()), this);
    dateLabel->setStyleSheet("font-style: italic; color: white;");

    // Event link
    QLabel* linkLabel = new QLabel(QString::fromStdString("Link: " + event.get_link_to_event()), this);
    linkLabel->setStyleSheet("color: #0d6efd;");
    linkLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    linkLabel->setOpenExternalLinks(true);

    // Event participants
    QLabel* participantsLabel = new QLabel(QString("Participants: %1").arg(event.get_number_of_participants()), this);
    participantsLabel->setStyleSheet("color: white;");

    // Add all labels to layout
    layout->addWidget(titleLabel);
    layout->addWidget(descLabel);
    layout->addWidget(dateLabel);
    layout->addWidget(linkLabel);
    layout->addWidget(participantsLabel);

    return card;
}

void User_Window::navigateEvents(int direction)
{
    int newIndex = currentEventIndex + direction;

    if (newIndex < 0) {
        newIndex = this->events.size();
    }
    else if (newIndex > this->events.size()) {
        newIndex = 0;
    }

    currentEventIndex = newIndex;
    availableEvents->setCurrentIndex(currentEventIndex);
}

void User_Window::initializeEvents()
{
    this->service->load_repo_from_file("events.txt");
    this->events = service->get_events_list();
    currentEventIndex = 0;

    for (const auto& event : events) {
        QWidget* card = createEventCard(event);
        availableEvents->addWidget(card);
    }

    availableEvents->setCurrentIndex(0);
}

QListView* User_Window::populate_playlist()
{
    service->load_users_from_file("users.txt");
    QListView* listView = new QListView(this);
    std::vector<Event> playlist = service->get_watchlist_for_user(user_position);
    QStandardItemModel* model = new QStandardItemModel(this);

    // Populate the model with the events
    for (const auto& event : playlist)
    {
        QString displayText = QString::fromStdString(event.get_title() + " - " + event.get_date_time_as_string());
        QStandardItem* item = new QStandardItem(displayText);
        model->appendRow(item);
    }

    // Set the model for the list view
    listView->setModel(model);
    listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listView->setSelectionMode(QAbstractItemView::SingleSelection);

    return listView;
}

void User_Window::refreshPlaylistView()
{
    // Refresh the playlist view
    QStandardItemModel* model = new QStandardItemModel(this);
    std::vector<Event> userPlaylist = service->get_watchlist_for_user(user_position);
    
    for (const auto& event : userPlaylist)
    {
        QString displayText = QString::fromStdString(event.get_title() + " - " + event.get_date_time_as_string());
        QStandardItem* item = new QStandardItem(displayText);
        model->appendRow(item);
    }
    
    playlist->setModel(model);
}
