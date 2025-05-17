#pragma once
#include "EventsRepository.h"
#include "UserRepository.h"
#include <vector>
#include "EventsListCSV.h"
#include "EventsListHTML.h"
#include "EventsList.h"
#include <memory>

class Service
{
private:
	EventsRepo events_repository;
	UserRepo users_repository;
	EventsList* events_list;


public:
	//Function for adding an event to the events repo
	void add_to_events_repository(const Event& e);
	//Function for removing an event from the events repo
	void remove_from_events_repository(int position);
	//Function for updating an event from the events repo
	void update_event_at_position(int position, Event new_event);
	//Function for getting the list of events from the events repo
	std::vector<Event> get_events_list() const;
	//Function that initialises the events repo with 10 events
	void initialise_repo_with_10();
	//Function for adding an user to the users repo
	void add_to_users_repository(const User& u);
	//Function for getting the list of users from the users repo
	std::vector<User> get_users_list() const;
	//Function that initialises the users repo with 10 users
	void initialise_users_repo_with_10();
	//Function that saves the users list to a file
	void save_users_to_file(const std::string& filename);
	//Function that loads the users list from a file
	void load_users_from_file(const std::string& filename);
	//Function that tells if a user is in the list
	bool is_already_user(const User& u);
	//Function that adds an event to the user's watchlist
	void add_event_to_watchlist(const Event& e, int user_position);
	//Function that removes an event from a certain user's watchlist
	void remove_event_from_watchlist(int user_position, int event_position);
	//Function that returns the events in the user's watchlist
	std::vector<Event> get_watchlist_for_user(int user_position);
	//Function that returns the events from a certain month
	std::vector<Event> get_events_for_month(int month);
	//Function that sorts a given list of events
	std::vector<Event> sort_events(std::vector<Event> events);
	//Function that retruns the position of the user in the users list
	int get_user_position(const User& u);
	//Function that saves the repository to a given file
	void save_repo_to_file(const std::string& filename);
	//Function that loads the repository from a given file
	void load_repo_from_file(const std::string& filename);
	//Function that saves the current event list to a file
	void save_events_list_to_file(const std::string& filename, const User& user);





	
};

