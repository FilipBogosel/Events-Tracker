#include "Service.h"
#include <ctime>
#include <algorithm>

void Service::add_to_events_repository(const Event& e)
{
	this->events_repository.add_event(e);
}

void Service::remove_from_events_repository(int position)
{
	this->events_repository.remove_event_position(position);
}

void Service::update_event_at_position(int position, Event new_event)
{
	this->events_repository.update_event_at_position(position, new_event);
}

std::vector<Event> Service::get_events_list() const
{
	return this->events_repository.get_events_list();
}

void Service::initialise_repo_with_10()
{
	this->events_repository.initialise_repo_with_10();
}

void Service::add_to_users_repository(const User& u)
{
	this->users_repository.add_user(u);
}

std::vector<User> Service::get_users_list() const
{
	return this->users_repository.get_users_list();
}

void Service::initialise_users_repo_with_10()
{
	this->users_repository.initialise_repo_with_10();
}

void Service::save_users_to_file(const std::string& filename)
{
	this->users_repository.save_to_file(filename);
}

void Service::load_users_from_file(const std::string& filename)
{
	this->users_repository.load_from_file(filename);
}

bool Service::is_already_user(const User& u)
{
	return this->users_repository.is_already_user(u);
}

void Service::add_event_to_watchlist(const Event& e, int user_position)
{
	for (int i = 0; i < this->events_repository.get_events_list().size(); i++) {
		if(this->events_repository.get_events_list()[i] == e)
			this->events_repository.get_events_list()[i].set_number_of_participants(this->events_repository.get_events_list()[i].get_number_of_participants() + 1);
	}
	this->users_repository.add_event_to_watchlist(e, user_position);
}

void Service::remove_event_from_watchlist(int user_position, int event_position)
{
	for (int i = 0; i < this->events_repository.get_events_list().size(); i++)
		if (this->events_repository.get_events_list()[i] == this->users_repository.get_users_list()[user_position].get_events_list()[event_position]) {
			this->events_repository.get_events_list()[i].set_number_of_participants(this->events_repository.get_events_list()[i].get_number_of_participants() - 1);
			break;
		}
	this->users_repository.remove_event_from_watchlist(user_position, event_position);
	
}

std::vector<Event> Service::get_watchlist_for_user(int user_position)
{
	return this->users_repository.get_users_list()[user_position].get_events_list();
}

std::vector<Event> Service::get_events_for_month(int month)
{
	std::vector<Event> events = this->events_repository.get_events_list();
	std::vector<Event> events_for_month;
	tm timeinfo;
	for (const auto& event : events) {
		time_t tt = std::chrono::system_clock::to_time_t(event.get_date_time());
		localtime_s(&timeinfo, &tt);
		if (timeinfo.tm_mon + 1 == month)
			events_for_month.push_back(event);
	}
	return events_for_month;
	
}

std::vector<Event> Service::sort_events(std::vector<Event> events)
{
	std::sort(events.begin(), events.end(), [](const Event& e1, const Event& e2) {
		return e1.get_date_time() < e2.get_date_time();
		});
	return events;
}

int Service::get_user_position(const User& u)
{
	for (int i = 0; i < this->users_repository.get_users_number(); i++)
		if (this->users_repository.get_users_list()[i] == u)
			return i;
	return -1;
}

void Service::save_repo_to_file(const std::string& filename)
{
	this->events_repository.save_to_file(filename);
}

void Service::load_repo_from_file(const std::string& filename)
{
	this->events_repository.load_from_file(filename);
}

void Service::save_events_list_to_file(const std::string& filename, const User& user)
{
	if (filename.find(".html") != std::string::npos) {
		this->events_list = new EventsListHTML(filename);
	}
	else {
		this->events_list = new EventsListCSV(filename);
	}
	this->events_list->set_list(this->users_repository.get_users_list()[this->get_user_position(user)]);
	this->events_list->write_to_file();
	delete this->events_list;
	this->events_list = nullptr;
}

