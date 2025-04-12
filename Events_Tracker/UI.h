#pragma once
#include "Service.h"
#include <iostream>
class UI
{
private:
	Service service;
	//print the menu
	void print_administrator_menu();
	//print the user menu
	void print_user_menu();
	//dysplays all the events
	void display_events();
	//Administrator mode handler
	void administrator_mode_handler();
	//Reads an Event from console
	Event read_event();
	//Converts a string to a time_point
	std::chrono::system_clock::time_point string_to_time_point(std::string date_time);
	//User mode handler
	void user_mode_handler();
	//Function that prints a single event
	void print_event(Event e);
	//Function that handles the sequrntial display of events, one by one
	void handle_events_by_month(User user);
public:
	
	//run the app
	void run();

};

