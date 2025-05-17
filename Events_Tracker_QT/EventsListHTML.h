#pragma once
#include "EventsList.h"
#include <fstream> 
#include "User.h"
class EventsListHTML : public EventsList
{
protected:
	std::string file_name;
	std::vector<Event> events_list;
public:
	//Constructor 
	EventsListHTML(const std::string& file_name);
	//save in html file
	void write_to_file() override;
	//sets the events list to be the same as the current user's list
	void set_list(const User& user) override;
};

