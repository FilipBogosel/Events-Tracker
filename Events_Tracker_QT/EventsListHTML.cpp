#include "EventsListHTML.h"

EventsListHTML::EventsListHTML(const std::string& file_name)
{
	this->file_name = file_name;
}

void EventsListHTML::write_to_file()
{
	std::ofstream file(file_name);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file " + file_name);
	}
	file << "<!DOCTYPE html>\n";
	file << "<html>\n";
	file << "<head>\n";
	file << "\t<title>Events List</title>\n";
	file << "</head>\n";
	file << "<body>\n";
	file << "<table border=\"1\">\n";
	file << "\t<tr>\n";
	file << "\t\t<td>Title</td>\n";
	file << "\t\t<td>Description</td>\n";
	file << "\t\t<td>Link</td>\n";
	file << "\t\t<td>Date and time</td>\n";
	file << "\t\t<td>Number of participants</td>\n";
	file << "\t</tr>\n";
	for (const auto& event : events_list)
	{
		file << "\t<tr>\n";
		file << "\t\t<td>" << event.get_title() << "</td>\n";
		file << "\t\t<td>" << event.get_description() << "</td>\n";
		file << "\t\t<td><a href=\"" << event.get_link_to_event() << "\" > Link</a></td>\n";
		file << "\t\t<td>" << event.get_date_time_as_string() << "</td>\n";
		file << "\t\t<td>" << event.get_number_of_participants() << "</td>\n";
		file << "\t</tr>\n";
	}
	file << "</table>\n";
	file << "</body>\n";
	file << "</html>\n";
}

void EventsListHTML::set_list(const User& user)
{
	this->events_list = user.get_events_list();
}
