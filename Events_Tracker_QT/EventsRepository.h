#pragma once
#include "Event.h"
#include <vector>
#include <ctime>
class EventsRepo
{
private:
	std::vector<Event> events_list;
public:
	//Adds the event to the end 
	void add_event(const Event& e);
	//Removes the event from given position
	void remove_event_position(int position);
	//Update event at given position
	void update_event_at_position(int position, Event new_event);
	//Initialises the repo with 10 events
	void initialise_repo_with_10();
	//Returns the list of events
	std::vector<Event> get_events_list() const;
	//Returns the number of events
	int get_events_number() const;

	void save_to_file(const std::string& file_name);
	void load_from_file(const std::string& file_name);
private:
	//Verifies if the event is already in the list
	bool is_in_list(const Event& e);


};

