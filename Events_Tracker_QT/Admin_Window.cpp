#include "Admin_Window.h"
#include <QFormLayout>
#include <QMessageBox>

Admin_Window::Admin_Window(QWidget* parent, Service *service)
{
    this->par = parent;
    // Initialize window properties
    setupWindowProperties();

    // Load data from repository
    /*service.initialise_repo_with_10();
	service.save_repo_to_file("events.txt");*/
	this->service = service;
    service->load_repo_from_file("events.txt");

    // Create layouts
    QHBoxLayout* mainLayout = createMainLayout();

    // Set the layout for the central widget
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);
}

Admin_Window::~Admin_Window()
{
}

void Admin_Window::setupWindowProperties()
{
    setWindowTitle("Admin Window");
    setWindowIcon(QIcon("C:\\Users\\Filip\\Documents\\Desktop\\Important Images\\Igh0zt-Ios7-Style-Metro-Ui-MetroUI-Apps-Calendar.512.png"));
}

QHBoxLayout* Admin_Window::createMainLayout()
{
    // Create main layout
    QHBoxLayout* mainLayout = new QHBoxLayout();

    // Create left side (list view) layout
    QVBoxLayout* listViewLayout = createListViewLayout();

    // Create right side (options) layout
    QVBoxLayout* optionsLayout = createOptionsLayout();

    // Add both main sections to main layout
    mainLayout->addLayout(listViewLayout);
    mainLayout->addLayout(optionsLayout);

    return mainLayout;
}

QVBoxLayout* Admin_Window::createListViewLayout()
{
    QVBoxLayout* listViewLayout = new QVBoxLayout();

    // Title label
    QLabel* eventsListLabel = new QLabel("Events List", this);
    eventsListLabel->setStyleSheet("font-weight: bold; font-size: 16px;");

    // Create list view with events - store in member variable
    eventsListView = populate_events_list(); // Use member variable

    // Setup event details display on double-click
    setupEventDetailsDisplay();

    // Add widgets to layout
    listViewLayout->addWidget(eventsListLabel);
    listViewLayout->addWidget(eventsListView);

    return listViewLayout;
}


QVBoxLayout* Admin_Window::createOptionsLayout()
{
    QVBoxLayout* optionsLayout = new QVBoxLayout();

    // Create form for event details
    QVBoxLayout* eventDetailsLayout = createEventDetailsLayout();

    // Create buttons layout
    QVBoxLayout* buttonsLayout = createButtonsLayout();

    // Add layouts to options layout
    optionsLayout->addLayout(eventDetailsLayout);
    optionsLayout->addLayout(buttonsLayout);

    return optionsLayout;
}

QVBoxLayout* Admin_Window::createEventDetailsLayout()
{
    QVBoxLayout* eventDetailsLayout = new QVBoxLayout();

    // Create form layout
    QFormLayout* formLayout = new QFormLayout();

    // Create labels
    QLabel* eventNameLabel = new QLabel("Event Name:", this);
    QLabel* eventDescriptionLabel = new QLabel("Event Description:", this);
    QLabel* eventDateLabel = new QLabel("Event Date:", this);
    QLabel* eventParticipantsLabel = new QLabel("Event Participants:", this);
    QLabel* eventLinkLabel = new QLabel("Event Link:", this);

    // Create input fields
    event_name = new QLineEdit(this);
    event_description = new QLineEdit(this);
    event_date = new QLineEdit(this);
    event_participants = new QLineEdit(this);
    event_link = new QLineEdit(this);

    // Add rows to form layout
    formLayout->addRow(eventNameLabel, event_name);
    formLayout->addRow(eventDescriptionLabel, event_description);
    formLayout->addRow(eventLinkLabel, event_link);
    formLayout->addRow(eventDateLabel, event_date);
    formLayout->addRow(eventParticipantsLabel, event_participants);

    // Add form layout to details layout
    eventDetailsLayout->addLayout(formLayout);

    return eventDetailsLayout;
}

QVBoxLayout* Admin_Window::createButtonsLayout()
{
    buttonsLayout = new QVBoxLayout();

    // Create buttons
    addButton = new QPushButton("Add Event", this);
    deleteButton = new QPushButton("Delete Event", this);
    updateButton = new QPushButton("Update Event", this);
    exitButton = new QPushButton("Exit", this);

    // Style the buttons
    style_buttons(addButton, deleteButton, updateButton, exitButton);
    connectButtons();//connect the buttons to their specific fuunction
    // Add buttons to layout
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(deleteButton);
    buttonsLayout->addWidget(updateButton);
    buttonsLayout->addWidget(exitButton);

    return buttonsLayout;
}

void Admin_Window::setupEventDetailsDisplay()
{
    connect(eventsListView, &QListView::doubleClicked, this, [this]() {
        std::stringstream ss;
        QModelIndex index = eventsListView->currentIndex();
        int row = index.row();
        ss << service->get_events_list()[row];
        std::string event_string = ss.str();
        QString event_details = QString::fromStdString(event_string);
        QMessageBox::information(this, "Event Details", event_details);
        });

    
}

void Admin_Window::connectButtons()
{
    connect(this->deleteButton, &QPushButton::clicked, this, [this]() {
        QModelIndex index = eventsListView->currentIndex();
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
            service->remove_from_events_repository(row);
			this->refreshListView();
        }
        });
    connect(this->exitButton, &QPushButton::clicked, this, [this] {
		service->save_repo_to_file("events.txt");
        this->close();
        this->par->show();
    });
    connect(this->addButton, &QPushButton::clicked, this, [this]() {
        Event e;
        std::string name = this->event_name->text().toStdString();
        std::string description = this->event_description->text().toStdString();
        std::string date = this->event_date->text().toStdString();
        std::chrono::system_clock::time_point date_tp = e.string_to_time_point(date);
        std::string link = this->event_link->text().toStdString();
        int number_of_participants = stoi(this->event_participants->text().toStdString());
        Event ev = Event(name, description, link, date_tp, number_of_participants);
        service->add_to_events_repository(ev);
        this->refreshListView();
		// Clear the input fields
		event_name->clear();
		event_description->clear();
		event_date->clear();
		event_participants->clear();
		event_link->clear();
    });
    connect(this->updateButton, &QPushButton::clicked, this, [this]() {
        QModelIndex ind = eventsListView->currentIndex();
        int pos = ind.row();
        Event e;
        std::string name = this->event_name->text().toStdString();
        std::string description = this->event_description->text().toStdString();
        std::string date = this->event_date->text().toStdString();
        std::chrono::system_clock::time_point date_tp = e.string_to_time_point(date);
        std::string link = this->event_link->text().toStdString();
        int number_of_participants = stoi(this->event_participants->text().toStdString());
        Event ev = Event(name, description, link, date_tp, number_of_participants);
        service->update_event_at_position(pos, ev); \
        refreshListView();
        event_name->clear();
        event_description->clear();
        event_date->clear();
        event_participants->clear();
        event_link->clear();

    });
}

void Admin_Window::refreshListView()
{
    // Refresh the list view properly
    QStandardItemModel* model = new QStandardItemModel(this);
    std::vector<Event> events = service->get_events_list();
    for (const auto& event : events) {
        QStandardItem* item = new QStandardItem(QString::fromStdString(event.to_string()));
        model->appendRow(item);
    }
    eventsListView->setModel(model);
}

QListView* Admin_Window::populate_events_list()
{
    QListView* listView = new QListView(this);
    QStandardItemModel* model = new QStandardItemModel(this);
    //Get events
    std::vector<Event> events = service->get_events_list();
    // Populate the model with the events
    for (const auto& event : events)
    {
        QStandardItem* item = new QStandardItem(QString::fromStdString(event.to_string()));
        model->appendRow(item);
    }
    listView->setModel(model);
    // Set the view to be read only
    listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // Set the view to be single selection
    listView->setSelectionMode(QAbstractItemView::SingleSelection);
    return listView;
}

void Admin_Window::style_buttons(QPushButton* addButton, QPushButton* deleteButton, QPushButton* updateButton, QPushButton* exitButton)
{
    deleteButton->setStyleSheet(
        "QPushButton {"
        "background-color: black; "
        "color: white; "
        "font-size: 14px; "
        "font-weight: bold; "
        "border-radius: 5px; "
        "padding: 10px; "
        "margin: 5px; "
        "}"
        "QPushButton:hover {"
        "background-color: #BC2649; "
        "}"
    );

    exitButton->setStyleSheet(
        "QPushButton {"
        "background-color: black; "
        "color: white; "
        "font-size: 14px; "
        "font-weight: bold; "
        "border-radius: 5px; "
        "padding: 10px; "
        "margin: 5px; "
        "}"
        "QPushButton:hover {"
        "background-color: #343A40; "
        "}"
    );
    addButton->setStyleSheet(
        "QPushButton {"
        "background-color: black; "
        "color: white; "
        "font-size: 14px; "
        "font-weight: bold; "
        "border-radius: 5px; "
        "padding: 10px; "
        "margin: 5px; "
        "}"
        "QPushButton:hover {"
        "background-color: #1C5E32; "
        "}"
    );

    updateButton->setStyleSheet(
        "QPushButton {"
        "background-color: black; "
        "color: white; "
        "font-size: 14px; "
        "font-weight: bold; "
        "border-radius: 5px; "
        "padding: 10px; "
        "margin: 5px; "
        "}"
        "QPushButton:hover {"
        "background-color: #443C70; "
        "}"
    );
}