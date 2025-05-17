#pragma once
#include < QtWidgets/QMainWindow>
#include <QPushButton>
#include <QIcon>
#include <QLabel>
#include <QLayout>	
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include "Service.h"

class LoginUser : public QMainWindow
{
	Q_OBJECT
public:
	LoginUser(QWidget* parent = nullptr, Service *service = nullptr);
	~LoginUser();
	QWidget* parent;
private:
	Service *service;
	QLineEdit* username;
	QLineEdit* password;
	QPushButton* signInButton;
	QPushButton* signUpButton;
	QPushButton* exitButton;
	void signInPressed();
	void signUpPressed();
	
};

