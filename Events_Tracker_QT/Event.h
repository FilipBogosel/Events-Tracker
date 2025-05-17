#pragma once
#include <chrono>
#include <string>
#include <ostream>
#include <istream>
class Event
{
private:
	std::string title, description, link_to_event; 
	std::chrono::system_clock::time_point date_time;
	int number_of_participants;
public:
	//Default constructor
	Event();
	//Constructor with parameters
	Event(const std::string& title, const std::string& description, const std::string& link_to_event,
		const std::chrono::system_clock::time_point& date_time, int number_of_participants);
	//Destructor
	~Event();
	//Copy constructor
	Event(const Event& e);


	//Getters for private fields-read only
	std::string get_title() const { return this->title; }
	std::string get_description() const { return this->description; }
	std::string get_link_to_event() const { return this->link_to_event; }
	std::chrono::system_clock::time_point get_date_time() const { return this->date_time; }
	int get_number_of_participants() const { return this->number_of_participants; }

	//Setters for private fields-write only
	void set_title(std::string title);
	void set_description(std::string description);
	void set_link_to_event(std::string link_to_event);
	void set_date_time(std::chrono::system_clock::time_point date_time);
	void set_number_of_participants(int number_of_participants);

	//Assignment operator
	Event& operator=(const Event& e);
	//Comparison operator
	bool operator==(const Event& e);
	//Get date_time as string
	std::string get_date_time_as_string() const;

	//Get a time point from a string
	std::chrono::system_clock::time_point string_to_time_point(std::string date_time);

	friend std::ostream& operator<<(std::ostream& os, const Event& event);
	friend std::istream& operator>>(std::istream& is, Event& event);

	std::string to_string() const;	
};

