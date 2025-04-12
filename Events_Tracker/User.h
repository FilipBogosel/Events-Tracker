#pragma once
#include <string>
#include "DynamicVector.h"
#include <vector>
class User
{
private:
	std::string name;
	std::string password;
	std::vector<Event> events_list;
public:
	//default constructor
	User();
	//user constructor with parameters
	User(std::string name, std::string password);
	//Copy constructor
	User(const User& u);
	//Assignment operator overloading
	void operator=(const User& u);
	//user destructor
	~User();
	//operator == overloading
	bool operator==(const User& u);
	//getters
	std::string get_name() const;
	std::string get_password() const;
	std::vector<Event> get_events_list() const;
	//add event to the list
	void add_event_to_user(const Event& e);
	//remove event from the list
	void remove_event_from_user(int position);


	
};

