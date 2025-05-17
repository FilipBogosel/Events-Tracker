#pragma once
#include <vector>
#include "Event.h"
#include "User.h"
class EventsList
{
protected:
	std::vector<Event> events_list;
	std::string file_name;

public:
	virtual void write_to_file() = 0;
	virtual ~EventsList() {}
	//virtual std::vector<Event> get_events() = 0;
	virtual void set_list(const User& user) = 0;
};