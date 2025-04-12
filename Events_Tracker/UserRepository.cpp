#include "UserRepository.h"
#include <fstream>
#include <iostream>

void UserRepo::add_user(const User& u)
{
	this->users_list.push_back(u);
}

void UserRepo::initialise_repo_with_10()
{
	User u1{ "user1", "password1" };
	User u2{ "user2", "password2" };
	User u3{ "user3", "password3" };
	User u4{ "user4", "password4" };
	User u5{ "user5", "password5" };
	User u6{ "user6", "password6" };
	User u7{ "user7", "password7" };
	User u8{ "user8", "password8" };
	User u9{ "user9", "password9" };
	User u10{ "user10", "password10" };
	this->add_user(u1);
	this->add_user(u2);
	this->add_user(u3);
	this->add_user(u4);
	this->add_user(u5);
	this->add_user(u6);
	this->add_user(u7);
	this->add_user(u8);
	this->add_user(u9);
	this->add_user(u10);
}

std::vector<User> UserRepo::get_users_list() const
{
	return this->users_list;
}

int UserRepo::get_users_number() const
{
	return this->get_users_list().size();
}

void UserRepo::save_to_file(const std::string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Unable to open file for writing");
	}

	for (int i = 0; i < this->users_list.size(); ++i) {
		User user = this->get_users_list()[i];
		file << user.get_name() << "\n";
		file << user.get_password() << "\n";
		file << user.get_events_list().size() << "\n";
		for (int j = 0; j < user.get_events_list().size(); ++j) {
			Event event = user.get_events_list()[j];
			file << event.get_title() << "\n";
			file << event.get_description() << "\n";
			file << event.get_link_to_event() << "\n";
			file << event.get_date_time_as_string() << "\n";
			file << event.get_number_of_participants() << "\n";
		}
	}
	file.close();
}


void UserRepo::load_from_file(std::string file_name)
{
	std::ifstream file(file_name);
	if (!file.is_open())
		throw std::invalid_argument("The file could not be opened!");
	std::string name, password, title, description, link, date_time, line;
	int  events_number;
	while (file >> name >> password >> events_number) {
		User u{ name, password };
		file.get();
		for (const auto& event : u.get_events_list()) {
			std::getline(file, line); // title
			std::string title = line;
			std::getline(file, line); // description
			std::string description = line;
			std::getline(file, line); // link
			std::string link = line;
			std::getline(file, line); // date_time
			std::string date_time = line;
			std::getline(file, line); // number_of_participants
			int number_of_participants = std::stoi(line);
			Event e0;
			std::chrono::system_clock::time_point date_time_tp = e0.string_to_time_point(date_time);
			Event e{ title, description, link, date_time_tp, number_of_participants };
			u.add_event_to_user(e);
		}
		this->add_user(u);
	}
	file.close();
}

bool UserRepo::is_already_user(const User& u)
{
	for (const auto& user : this->users_list) {
		if (user.get_name() == u.get_name() && user.get_password() == u.get_password()) {
			return true;
		}
	}
	return false;
}

void UserRepo::add_event_to_watchlist(const Event& e, int user_position)
{
	this->users_list[user_position].add_event_to_user(e);
}

void UserRepo::remove_event_from_watchlist(int user_position, int event_position)
{
	this->users_list[user_position].remove_event_from_user(event_position);
}
