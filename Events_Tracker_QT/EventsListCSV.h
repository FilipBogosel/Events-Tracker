#pragma once
#include "EventsList.h"
#include <fstream>
#include "User.h"
class EventsListCSV :  public EventsList
{
protected:
	std::string file_name;
	std::vector<Event> events_list;

public:
	//Constructor 
	EventsListCSV(const std::string& file_name);
	//save in csv
	void write_to_file() override;
	//sets the events list to be the same as the current user's list
	void set_list(const User& user) override;
};

