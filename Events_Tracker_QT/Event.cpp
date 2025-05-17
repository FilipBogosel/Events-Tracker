#include <stdexcept>
#include "Event.h"
#include <sstream>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
//default constructor
Event::Event() 
{
	this->title = "";
	this->description = "";
	this->link_to_event = "";
	this->date_time = chrono::system_clock::time_point();
	this->number_of_participants = 0;
}
//param constructor
Event::Event(const string& title, const string& description, const string& link_to_event,
	const chrono::system_clock::time_point& date_time, int number_of_participants) : title{ title }, description{ description }, link_to_event{ link_to_event },
	date_time{ date_time }, number_of_participants{ number_of_participants }
{
}
//destructor
Event::~Event() {
}
//copy constructor
Event::Event(const Event& e)
{
	this->title = e.title;
	this->description = e.description;
	this->link_to_event = e.link_to_event;
	this->date_time = e.date_time;
	this->number_of_participants = e.number_of_participants;
}

Event& Event::operator=(const Event& e)
{
	this->title = e.title;
	this->description = e.description;
	this->link_to_event = e.link_to_event;
	this->date_time = e.date_time;
	this->number_of_participants = e.number_of_participants;
	return *this;
}

bool Event::operator==(const Event& e)
{
	return this->title == e.title && this->description == e.description && this->link_to_event == e.link_to_event && this->date_time == e.date_time && this->number_of_participants == e.number_of_participants;
}

std::string Event::get_date_time_as_string() const
{
	std::chrono::system_clock::time_point date_time = this->get_date_time();
	std::time_t date_time_t = std::chrono::system_clock::to_time_t(date_time);
	std::tm tm;

	// Use localtime_s for thread safety
	if (localtime_s(&tm, &date_time_t) != 0) {
		throw std::runtime_error("Failed to convert time_t to tm");
	}

	std::string day_string = (tm.tm_mday < 10 ? "0" : "") + std::to_string(tm.tm_mday);
	std::string month_string = (tm.tm_mon + 1 < 10 ? "0" : "") + std::to_string(tm.tm_mon + 1);
	std::string year_string = std::to_string(tm.tm_year + 1900);
	std::string hour_string = std::to_string(tm.tm_hour);
	if (hour_string.size() == 1)
		hour_string = "0" + hour_string;
	std::string minute_string = (tm.tm_min < 10 ? "0" : "") + std::to_string(tm.tm_min);

	std::string final_date_time_string = day_string + "." + month_string + "." + year_string + " " + hour_string + ":" + minute_string;
	return final_date_time_string;
}



void Event::set_title(string title) {
	this->title = title;
}

void Event::set_description(string description) {
	this->description = description;
}

void Event::set_link_to_event(string link) {
	this->link_to_event = link;
}

void Event::set_date_time(chrono::system_clock::time_point date) {
	this->date_time = date;
}

void Event::set_number_of_participants(int no_part) {
	this->number_of_participants = no_part;
}

chrono::system_clock::time_point Event::string_to_time_point(string date_time) {
	tm tm;
	int year, month, day, hour, minute;
	day = stoi(date_time.substr(0, 2));
	month = stoi(date_time.substr(3, 2));
	year = stoi(date_time.substr(6, 4));
	hour = stoi(date_time.substr(11, 2));
	minute = stoi(date_time.substr(14, 2));
	tm.tm_year = year - 1900;
	tm.tm_mon = month - 1;
	tm.tm_mday = day;
	tm.tm_hour = hour;
	tm.tm_min = minute;
	tm.tm_sec = 0;
	time_t time = mktime(&tm);
	return chrono::system_clock::from_time_t(time);


}

std::string Event::to_string() const
{
	stringstream ss;
	ss << this->title << "\n";
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Event& event)
{
	os << event.title << "\n";
	os << event.description << "\n";
	os << event.link_to_event << "\n";
	os << event.get_date_time_as_string() << "\n";
	os << event.number_of_participants << "\n";
	return os;
}

std::istream& operator>>(std::istream& is, Event& event)
{
	std::string title, description, date, link;
	int participants;
	getline(is, title);
	getline(is, description);
	getline(is, link);
	getline(is, date);
	is >> participants;
	is.ignore();// for the newline character

	event.set_title(title);
	event.set_description(description);
	event.set_link_to_event(link);
	event.set_date_time(event.string_to_time_point(date));
	event.set_number_of_participants(participants);

	return is;
}
