#include "User.h"

User::User()
{
	this->name = "";
	this->password = "";
	this->events_list = std::vector<Event>();
}

User::User(std::string name, std::string password)
{
	this->name = name;
	this->password = password;
	this->events_list = std::vector<Event>();
}

User::User(const User& u)
{
	this->name = u.name;
	this->password = u.password;
	this->events_list = u.events_list;
}

void User::operator=(const User& u)
{
	this->name = u.name;
	this->password = u.password;
	this->events_list = u.events_list;
}

User::~User()
{
}

bool User::operator==(const User& u)
{
	if (this->name == u.name) return true;
}

std::string User::get_name() const
{
	return this->name;
}

std::string User::get_password() const
{
	return this->password;
}

std::vector<Event> User::get_events_list() const
{
	return this->events_list;
}

void User::add_event_to_user(const Event& e)
{
	this->events_list.push_back(e);
}

void User::remove_event_from_user(int position)
{
	if (position < 0 || position > this->events_list.size()) {
		return; 
	}
	this->events_list.erase(this->events_list.begin()+position);
}
