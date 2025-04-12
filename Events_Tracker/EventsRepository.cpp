#include "EventsRepository.h"
#include <fstream>
#include <exception>

void EventsRepo::add_event(const Event& e)
{
	if (this->is_in_list(e)) return;
	this->events_list.push_back(e);
	return;
}

void EventsRepo::remove_event_position(int position)
{
	if (position<0 || position>this->get_events_number()) return;
	this->events_list.erase(this->events_list.begin() + position);
}

void EventsRepo::update_event_at_position(int position, Event e)
{
	if (position<0 || position>this->get_events_number()) return;
	this->events_list[position] = e;
}

void EventsRepo::initialise_repo_with_10()
{
	//initialise  time1 with 22.03.2025 12:00
	std::tm time1 = {};
	time1.tm_year = 2025 - 1900;
	time1.tm_mon = 3 - 1;
	time1.tm_mday = 22;
	time1.tm_hour = 12;
	time1.tm_min = 0;
	std::tm time2 = time1;
	time2.tm_mday = 23;
	std::tm time3 = time1;
	time3.tm_mday = 24;
	std::tm time4 = time1;
	time4.tm_mday = 25;
	std::tm time5 = time1;
	time5.tm_mday = 26;
	std::tm time6 = time1;
	time6.tm_mday = 27;
	std::tm time7 = time1;
	time7.tm_mday = 28;
	std::tm time8 = time1;
	time8.tm_mday = 29;
	std::tm time9 = time1;
	time9.tm_mday = 30;
	std::tm time10 = time1;
	time10.tm_mday = 31;
	std::chrono::system_clock::time_point date_time1 = std::chrono::system_clock::from_time_t(std::mktime(&time1));
	std::chrono::system_clock::time_point date_time2 = std::chrono::system_clock::from_time_t(std::mktime(&time2));
	std::chrono::system_clock::time_point date_time3 = std::chrono::system_clock::from_time_t(std::mktime(&time3));
	std::chrono::system_clock::time_point date_time4 = std::chrono::system_clock::from_time_t(std::mktime(&time4));
	std::chrono::system_clock::time_point date_time5 = std::chrono::system_clock::from_time_t(std::mktime(&time5));
	std::chrono::system_clock::time_point date_time6 = std::chrono::system_clock::from_time_t(std::mktime(&time6));
	std::chrono::system_clock::time_point date_time7 = std::chrono::system_clock::from_time_t(std::mktime(&time7));
	std::chrono::system_clock::time_point date_time8 = std::chrono::system_clock::from_time_t(std::mktime(&time8));
	std::chrono::system_clock::time_point date_time9 = std::chrono::system_clock::from_time_t(std::mktime(&time9));
	std::chrono::system_clock::time_point date_time10 = std::chrono::system_clock::from_time_t(std::mktime(&time10));
	this->add_event(Event("Conference", "Taking place in Cluj-Napoca for students","https://conference.com", date_time1, 100));
	this->add_event(Event("Workshop", "Taking place in Cluj-Napoca for students", "http://workshop.com", date_time2, 50));
	this->add_event(Event("Seminar", "Taking place in Cluj-Napoca for students", "http://seminar.com", date_time3, 200));
	this->add_event(Event("Course", "Taking place in Cluj-Napoca for students", "http://course.com", date_time4, 150));
	this->add_event(Event("Concert", "Concert of Smiley in Cluj-Napoca", "http://concert.com", date_time5, 1000));
	this->add_event(Event("Festival", "Festival of music Cluj-Napoca", "http://festival.com", date_time6, 5000));
	this->add_event(Event("Exhibition", "Exhibition of paintings at the art museum Cluj-Napoca", "http://exhibition.com", date_time7, 300));
	this->add_event(Event("Show", "Show of magic city center Cluj-Napoca", "http://show.com", date_time8, 100));
	this->add_event(Event("Cinema", "Cinema for students city center Cluj-Napoca", "http://cinema.com", date_time9, 200));
	this->add_event(Event("Theatre", "The best theatre group is coming in Cluj", "http://theatre.com", date_time10, 300));
}

std::vector<Event> EventsRepo::get_events_list() const
{
	return this->events_list;
}

int EventsRepo::get_events_number() const
{
	return this->events_list.size();
}

bool EventsRepo::is_in_list(const Event& e)
{
	for (const auto& event : this->events_list) {
		if(event.get_title() == e.get_title()) {
			return true;
		}
	}
	return false;
}

void EventsRepo::save_to_file(const std::string& file_name)
{
	std::ofstream file(file_name);

	if (!file.is_open()) {
		throw std::exception("Couldn't open the file!");
	}

	file << this->events_list.size() << "\n";

	for (const auto& event : this->events_list) {
		file << event << "\n";
	}
	file.close();
}

void EventsRepo::load_from_file(const std::string& file_name)
{
	std::ifstream file(file_name);
	if (!file.is_open()) {
		throw std::exception("Couldn't open the file!");
	}

	this->events_list.clear();
	
	int no_events;
	file >> no_events;
	file.ignore();// for skipping the newline

	for (int i = 0; i < no_events; i++) {
		Event e;
		file >> e;
		this->add_event(e);
		file.get();
	}

	file.close();
}
