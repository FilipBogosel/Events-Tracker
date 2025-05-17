#pragma once
#include "User.h"
#include <vector>

class UserRepo
{
private:
	std::vector<User> users_list;
public:
	//Adds an user to the list
	void add_user(const User& u);
	//Initialises the repo with 10 users
	void initialise_repo_with_10();
	//Returns the list of users
	std::vector<User> get_users_list() const;
	//Returns the number of users
	int get_users_number() const;
	//Function that saves the users list to a file
	void save_to_file(const std::string &file_name);
	//Function that loads the users list from a file
	void load_from_file(std::string file_name);
	//Function that tells if a user is in the list
	bool is_already_user(const User& u);
	//Function that adds an event to the user's watchlist
	void add_event_to_watchlist(const Event& e, int user_position);
	//Function that removes an event from the user's watchlist
	void remove_event_from_watchlist(int user_position, int event_position);

};

