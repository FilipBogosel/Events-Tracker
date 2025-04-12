#include "UI.h"
#include <iostream>
#include "Event.h"
#define NOMINMAX
#include <windows.h>
#include <shellapi.h>
#include <limits>



using namespace std;

void UI::print_administrator_menu()
{
	cout << "1. Add event\n";
	cout << "2. Remove event\n";
	cout << "3. Update event\n";
	cout << "4. Display events\n";
	cout << "0. Exit\n";
}

void UI::print_user_menu()
{
	cout << "1. Dysplay events in your watchlist\n";
	cout << "2. Display one by one the events in the database for a given month(or all if no given month)\n";
	cout << "3. Remove event from watchlist\n";
	cout << "0. Exit\n";
}


void UI::user_mode_handler() {
	while (true) {
		cout << "1. Sign in\n";
		cout << "2. Sign up\n";
		cout << "0. Exit\n";
		cout << "Your choice: \n";
		int option1;
		string name, password;
		cin >> option1;
		if (option1 == 2) {

			cout << "Name: ";
			cin >> name;
			cout << "Password: ";
			cin >> password;
			User user{ name, password };
			if (this->service.is_already_user(user)) {
				cout << "User already exists!\n";
				continue;
			}
			this->service.add_to_users_repository(user);
		}
		else if (option1 == 1) {
			cout << "Name: ";
			cin >> name;
			cout << "Password: ";
			cin >> password;
			User user{ name, password };
			if (!this->service.is_already_user(user)) {
				cout << "User does not exist!\n";
				continue;
			}
		}
		else if (option1 == 0) return;
		else {
			cout << "Invalid choice!\n";
			continue;
		}
		while (true) {
			system("pause");
			system("cls");
			print_user_menu();
			int option2;
			cout << "Your choice: \n";
			cin >> option2;
			if (option2 == 1) {
				int user_position = this->service.get_user_position(User{ name, password });
				std::vector<Event> watchlist = this->service.get_watchlist_for_user(user_position);
				for (int i = 0; i < watchlist.size(); i++) {
					cout << "Event " << i + 1 << "\n";
					print_event(watchlist[i]);
				}
			}
			else if (option2 == 2) {
				User user{ name, password };
				handle_events_by_month(user);
			}
			else if (option2 == 3) {
				int user_position = this->service.get_user_position(User{ name, password });
				int pos = 0;
				cout << "Position: ";
				cin >> pos;
				cout << "\n";
				service.remove_event_from_watchlist(user_position, 0);
			}
			else if (option2 == 0) return;
			else {
				cout << "Invalid choice!\n";
			}
		}
	}

}

void UI::print_event(Event e)
{
	cout << "Title: " << e.get_title() << "\n";
	cout << "Description: " << e.get_description() << "\n";
	cout << "Link: " << e.get_link_to_event() << "\n";
	cout << "Number of participants: " << e.get_number_of_participants() << "\n";
	cout << "Date and time: " << e.get_date_time_as_string() << "\n";
	cout << "\n";
}

void UI::handle_events_by_month(User user)
{
	int i = 0;
	std::vector<Event> events;
	cout << "Do you want to sort events by month?(Y/N)\n";
	char opt;
	cin >> opt;
	if (opt == 'N' || opt == 'n') {
		events = this->service.get_events_list();
		events = this->service.sort_events(events);
	}
	else if (opt == 'Y' || opt == 'y') {
		int month;
		cout << "Give month: ";
		cin >> month;
		cout << "\n";
		events = this->service.get_events_for_month(month);
		events = this->service.sort_events(events);
	}
	else {
		cout << "Invalid option!\n";
		return;
	}

	while (true) {
		print_event(events[i]);
		string link = "rundll32 url.dll, FileProtocolHandler " + events[i].get_link_to_event();
		system(link.c_str());
		cout << "Do you want to add this event to your watchlist? (0/1)\n";
		int add_option;
		cin >> add_option;
		if (add_option == 1) {
			this->service.add_event_to_watchlist(events[i], service.get_user_position(user));
			cout << "Event added to watchlist!\n";
		}
		cout << "Press 0 to exit or any other key to continue\n";
		char continue_option;
		cin >> continue_option;
		if (continue_option == '0') break;
		i++;
		if (i == events.size()) {
			i = 0;
		}
	}
}


void UI::run()
{
	//service.initialise_repo_with_10();
	//service.initialise_users_repo_with_10();
	//service.save_users_to_file("users.txt");
	//service.save_repo_to_file("events.txt");
	this->service.load_users_from_file("users.txt");
	this->service.load_repo_from_file("events.txt");
	int option;
	while (true) {
		cout << "Log as administrator or user? 1.Administrator 2.User 0.Exit\n";
		try {
			cin >> option;
			if (cin.fail()) {
				throw invalid_argument("Please input a number!");
			}
			if (option == 1) {
				cout << "Password: \n";
				string password;
				cin >> password;
				if (password != "1234") {
					cout << "Invalid password!\n";
					continue;
				}
				this->administrator_mode_handler();
			}
			else if (option == 2) {
				user_mode_handler();

			}
			else if (option == 0)
			{
				service.save_users_to_file("users.txt");
				service.save_repo_to_file("events.txt");
				return;
			}
			else cout << "Invalid choice!\n";
		}
		catch (exception& e) {
			cout << e.what() << "\n";
			cin.clear(); // Clear the error state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
		}
	}

	
	
}

void UI::display_events()
{
	vector<Event> events = this->service.get_events_list();
	for (int i = 0; i < events.size(); i++) {
		cout << "Event " << i + 1 << "\n";
		cout << "Title: " << events[i].get_title() << "\n";
		cout << "Description: " << events[i].get_description() << "\n";
		cout << "Link: " << events[i].get_link_to_event() << "\n";
		cout << "Number of participants: " << events[i].get_number_of_participants() << "\n";
		cout << "Date and time: " << events[i].get_date_time_as_string() << "\n";
		cout << "\n";
	}
	return;
}



Event UI::read_event() {
	cout << "Title: ";
	string title;
	cin >> title;
	cout << "\nDescription: ";
	string description;
	cin >> description;
	cout << "\nLink: ";
	string link;
	cin >> link;
	cout << "\nNumber of participants: ";
	int number_of_participants;
	cin >> number_of_participants;
	if (cin.fail()) {
		throw invalid_argument("Please input a number!\n");
	}
	bool valid_date = false;
	string date_time;
	cin.ignore();
	while (!valid_date) {
		cout << "\nDate and time(DD.MM.YYYY HH:MM): ";
		getline(cin, date_time);
		if (date_time.size() != 16) {
			cout << "Invalid date and time!\n";
			continue;
		}
		cout << "\n";
		valid_date = true;

	}
	
	chrono::system_clock::time_point date_time_tp = string_to_time_point(date_time);
	Event e{ title, description, link, date_time_tp, number_of_participants };
	return e;

}

void UI::administrator_mode_handler()
{
	while (true) {
		system("pause");
		int choice;
		system("cls");
		this->print_administrator_menu();
		cout << "Your choice: \n";
		try {
			cin >> choice;
			if (cin.fail()) {
				throw invalid_argument("Invalid input! Please enter a number.");
			}

			if (choice == 1) {
				Event e = this->read_event();
				if (e.get_title() == "") return;
				int initial_size = this->service.get_events_list().size();
				this->service.add_to_events_repository(e);
				int after_size = this->service.get_events_list().size();
				if (initial_size == after_size) {
					cout << "Event already in the list!\n";
					continue;
				}
				cout << "Event added!\n";
			}
			else if (choice == 2) {
				cout << "Position: ";
				int position;
				cin >> position;
				if (cin.fail() || position < 0 || position >= this->service.get_events_list().size()) {
					throw invalid_argument("Invalid position!");
				}
				cout << "\n";
				this->service.remove_from_events_repository(position);
				cout << "Event removed!\n";
			}
			else if (choice == 3) {
				cout << "Position: ";
				int position;
				cin >> position;
				if (cin.fail() || position < 0 || position >= this->service.get_events_list().size()) {
					throw invalid_argument("Invalid position!");
				}
				Event e = this->read_event();
				if (e.get_title() == "") return;
				this->service.update_event_at_position(position, e);
				cout << "Event updated!\n";
			}
			else if (choice == 4) {
				this->display_events();
			}
			else if (choice == 0) return;
			else {
				throw invalid_argument("Invalid choice!");
			}
		}
		catch (const invalid_argument& e) {
			cout << e.what() << "\n";
			cin.clear(); // Clear the error state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
		}
	}
}

chrono::system_clock::time_point UI::string_to_time_point(string date_time) {
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