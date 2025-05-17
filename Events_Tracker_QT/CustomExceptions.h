#pragma once
#include <string>
#include <exception>
#include <stdexcept>

class ValidationException : std::exception
{
private:
	std::string message;
public:
	ValidationException(std::string msg) : message{ msg } {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};

class InvalidInputException : public ValidationException
{
public:
	InvalidInputException(const std::string& msg) : ValidationException("Invalid input: " + msg) {}
};

class EventNotFoundException : public ValidationException
{
public:
	EventNotFoundException(const std::string& msg = "Event not found: ") : ValidationException(msg) {}
};

class UserNotFoundException : public ValidationException
{
public:
	UserNotFoundException(const std::string& msg = "User not found: ") : ValidationException(msg) {}
};

class DuplicateEventException : public ValidationException
{
public:
	DuplicateEventException(const std::string& msg = "Duplicate event: ") : ValidationException(msg) {}
};

class InvalidPositionException : public ValidationException
{
public:
	InvalidPositionException(const std::string& msg = "Invalid position: ") : ValidationException(msg) {}
};
