#include "EventsListCSV.h"

EventsListCSV::EventsListCSV(const std::string& file_name) : file_name{file_name} {}

void EventsListCSV::write_to_file()
{
	std::ofstream file(file_name);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file " + file_name);
	}
	for (const auto& event : events_list)
	{
		file << event.get_title() << ',' << event.get_description() << ',' << event.get_link_to_event()
			<< ',' << event.get_date_time_as_string() << ',' << event.get_number_of_participants() << "\n";
	}
	file.close();
}

void EventsListCSV::set_list(const User& user)
{
	events_list = user.get_events_list();
}
