#include "Events_Tracker_QT.h"
#include <QFile>


Events_Tracker_QT::Events_Tracker_QT(QWidget *parent): QMainWindow(parent)
{
    // Initialize the service pointer
    this->service = new Service();
    
    ui.setupUi(this);
	// Set the window title
	setWindowTitle("Events Tracker");
	// Set the window icon
	setWindowIcon(QIcon("C:\\Users\\Filip\\Documents\\Desktop\\Important Images\\Igh0zt-Ios7-Style-Metro-Ui-MetroUI-Apps-Calendar.512.png"));
	// create elements in the window, the current window beeing the window where user chooses between user and admin mode
	// We'll have a button for user mode and a button for admin mode and one for exit

	//Create a label that tells the user to choose between user and admin mode
	QLabel* label = new QLabel("Choose between user and admin mode", this);
	// Create the user mode button
	QPushButton* userModeButton = new QPushButton("User Mode", this);
	// Create admin mode button
	QPushButton* adminModeButton = new QPushButton("Admin Mode", this);
	//Create exit button
	QPushButton* exitButton = new QPushButton("Exit", this);
	//Create layout
	QVBoxLayout* layout = new QVBoxLayout();
	QVBoxLayout* buttonLayout = new QVBoxLayout();
	// Set the layout for the central widget
	QWidget* centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);
	centralWidget->setLayout(layout);
	// Add everything to the layout
	layout->addWidget(label);
	buttonLayout->addWidget(userModeButton);
	buttonLayout->addWidget(adminModeButton);
	buttonLayout->addWidget(exitButton);
	layout->addLayout(buttonLayout);
	// I want the label to be centered, bold and a lot bigger
	label->setAlignment(Qt::AlignCenter);
	buttonLayout->setAlignment(Qt::AlignCenter);
	label->setStyleSheet("font-size: 24px; font-weight: bold;");
	// Set the button size
	userModeButton->setFixedSize(200, 50);
	adminModeButton->setFixedSize(200, 50);
	exitButton->setFixedSize(200, 50);
	// Set the button style
	userModeButton->setStyleSheet(
		"QPushButton {"
		"background-color: black; "
		"color: white; "
		"font-size: 18px; "
		"font-weight: bold; "
		"border-radius: 5px; "
		"border: none; "
		"padding: 5px; "
		"}"
		"QPushButton:hover {"
		"background-color: #1C5E32; "
		"}"
	);

	// Admin Mode Button - A professional deep purple
	adminModeButton->setStyleSheet(
		"QPushButton {"
		"background-color: black; "
		"color: white; "
		"font-size: 18px; "
		"font-weight: bold; "
		"border-radius: 5px; "
		"border: none; "
		"padding: 5px; "
		"}"
		"QPushButton:hover {"
		"background-color: #443C70; "
		"}"
	);

	// Exit Button - Keeping the refined red with red hover
	exitButton->setStyleSheet(
		"QPushButton {"
		"background-color: black; "
		"color: white; "
		"font-size: 18px; "
		"font-weight: bold; "
		"border-radius: 5px; "
		"border: none; "
		"padding: 5px; "
		"}"
		"QPushButton:hover {"
		"background-color: #BC2649; "
		"}"
	);


	// Set the layout to be centered
	layout->setAlignment(Qt::AlignCenter);
	// Set the spacing between the elements
	layout->setSpacing(20);
	buttonLayout->setSpacing(20);

	

	// Connect the buttons to the slots
	connect(adminModeButton, &QPushButton::clicked, this, [this]() {
		// Create the admin window
		Admin_Window* adminWindow = new Admin_Window(this, this->service);
		adminWindow->show();
		// Hide the current window
		this->hide();
		});
	connect(exitButton, &QPushButton::clicked, this, &QWidget::close);

	connect(userModeButton, &QPushButton::clicked, this, [this]() {
		// Create the user window
		LoginUser* userWindow = new LoginUser(this, this->service);
		userWindow->show();
		// Hide the current window
		this->hide();
		});

}

Events_Tracker_QT::~Events_Tracker_QT()
{
    delete service;
}
