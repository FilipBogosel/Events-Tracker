#include "LoginUser.h"
#include <QMessageBox>
#include "User.h"
#include "User_Window.h"
LoginUser::LoginUser(QWidget* parent, Service *service)
{
	this->parent = parent;
	this->service = service;
	service->load_users_from_file("users.txt");
	setWindowTitle("Login User");
	setWindowIcon(QIcon("C:\\Users\\Filip\\Documents\\Desktop\\Important Images\\Igh0zt-Ios7-Style-Metro-Ui-MetroUI-Apps-Calendar.512.png"));
	// Create the username and password fields
	username = new QLineEdit(this);
	password = new QLineEdit(this);
	password->setEchoMode(QLineEdit::Password);
	// Create the login and exit buttons
	signInButton = new QPushButton("Login", this);
	exitButton = new QPushButton("Exit", this);
	signUpButton = new QPushButton("Sign Up", this);
	// Set the layout for the central widget
	QVBoxLayout* layout = new QVBoxLayout();
	QFormLayout* formLayout = new QFormLayout();
	formLayout->addRow("Username:", username);
	formLayout->addRow("Password:", password);
	layout->addLayout(formLayout);
	layout->addWidget(signInButton);
	layout->addWidget(signUpButton);
	layout->addWidget(exitButton);
	QWidget* centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);
	centralWidget->setLayout(layout);
	//this->setFixedSize(300, 200);

	connect(signInButton, &QPushButton::clicked, this, &LoginUser::signInPressed);
	connect(signUpButton, &QPushButton::clicked, this, &LoginUser::signUpPressed);
	connect(exitButton, &QPushButton::clicked, this, [this]() {
		this->close();
		this->parent->show();
		});

}

LoginUser::~LoginUser()
{
}

void LoginUser::signInPressed()
{
	// Get the username and password from the fields
	std::string user = username->text().toStdString();
	std::string pass = password->text().toStdString();
	// Check if the user is in the repository
	User us = User(user, pass);
	if (service->is_already_user(us))
	{
		// Create the user window
		QMessageBox::information(this, "Success", "Login successful");
		
		User_Window* userWindow = new User_Window(this,service->get_user_position(us), service);
		userWindow->setWindowTitle("User Window");
		setWindowIcon(QIcon("C:\\Users\\Filip\\Documents\\Desktop\\Important Images\\Igh0zt-Ios7-Style-Metro-Ui-MetroUI-Apps-Calendar.512.png"));
		service->save_users_to_file("users.txt");
		userWindow->show();	
		this->hide();
	}
	else
	{
		QMessageBox::warning(this, "Error", "Invalid username or password");
	}


}

void LoginUser::signUpPressed()
{
	// Get the username and password from the fields
	std::string user = username->text().toStdString();
	std::string pass = password->text().toStdString();
	// Check if the user is in the repository
	User us = User(user, pass);
	if (service->is_already_user(us))
	{
		QMessageBox::warning(this, "Error", "User already exists");
	}
	else
	{
		service->add_to_users_repository(us);
		QMessageBox::information(this, "Success", "User created successfully");
		// Create the user window
		service->save_users_to_file("users.txt");
		User_Window* userWindow = new User_Window(this, service->get_user_position(us),service);
		userWindow->setWindowTitle("User Window");
		setWindowIcon(QIcon("C:\\Users\\Filip\\Documents\\Desktop\\Important Images\\Igh0zt-Ios7-Style-Metro-Ui-MetroUI-Apps-Calendar.512.png"));
		
		userWindow->show();
		this->hide();
	}

}
