#include <iostream>
#include "Event.h"
#include "EventsRepository.h"
#include <cassert>
#include "Service.h"
#include "User.h"
#include "UserRepository.h"
#include <vector>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS

// Event tests
void test_default_constructor() {
    Event e;
    assert(e.get_title() == "");
    assert(e.get_description() == "");
    assert(e.get_link_to_event() == "");
    assert(e.get_number_of_participants() == 0);
    assert(e.get_date_time() == std::chrono::system_clock::time_point());
}

void test_parameters_constructor() {
    Event e{ "title", "description", "link", std::chrono::system_clock::time_point(), 10 };
    assert(e.get_title() == "title");
    assert(e.get_description() == "description");
    assert(e.get_link_to_event() == "link");
    assert(e.get_number_of_participants() == 10);
    assert(e.get_date_time() == std::chrono::system_clock::time_point());
}

void test_copy_constructor() {
    Event e{ "title", "description", "link", std::chrono::system_clock::time_point(), 10 };
    Event e2{ e };
    assert(e2.get_title() == "title");
    assert(e2.get_description() == "description");
    assert(e2.get_link_to_event() == "link");
    assert(e2.get_number_of_participants() == 10);
    assert(e2.get_date_time() == std::chrono::system_clock::time_point());
}

void test_destructor() {
    Event* e = new Event{ "title", "description", "link", std::chrono::system_clock::time_point(), 10 };
    delete e;
}

void test_assignment_operator() {
    Event e{ "title", "description", "link", std::chrono::system_clock::time_point(), 10 };
    Event e2;
    e2 = e;
    assert(e2.get_title() == "title");
    assert(e2.get_description() == "description");
    assert(e2.get_link_to_event() == "link");
    assert(e2.get_number_of_participants() == 10);
    assert(e2.get_date_time() == std::chrono::system_clock::time_point());
}

void test_comparison_operator() {
    Event e{ "title", "description", "link", std::chrono::system_clock::time_point(), 10 };
    Event e2{ "title", "description", "link", std::chrono::system_clock::time_point(), 10 };
    assert(e == e2);
}

void test_setters() {
    Event e;
    e.set_title("title");
    e.set_description("description");
    e.set_link_to_event("link");
    e.set_number_of_participants(10);
    e.set_date_time(std::chrono::system_clock::time_point());
    assert(e.get_title() == "title");
    assert(e.get_description() == "description");
    assert(e.get_link_to_event() == "link");
    assert(e.get_number_of_participants() == 10);
    assert(e.get_date_time() == std::chrono::system_clock::time_point());
}

void test_getters() {
    Event e{ "title", "description", "link", std::chrono::system_clock::time_point(), 10 };
    assert(e.get_title() == "title");
    assert(e.get_description() == "description");
    assert(e.get_link_to_event() == "link");
    assert(e.get_number_of_participants() == 10);
    assert(e.get_date_time() == std::chrono::system_clock::time_point());
}

void test_all_for_event() {
    test_default_constructor();
    test_parameters_constructor();
    test_copy_constructor();
    test_destructor();
    test_assignment_operator();
    test_comparison_operator();
    test_setters();
    test_getters();
}

// std::vector tests
void test_vector_operations() {
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    assert(vec.size() == 2);
    assert(vec[0] == 10);
    assert(vec[1] == 20);

    vec.erase(vec.begin() + 1);
    assert(vec.size() == 1);
    assert(vec[0] == 10);

    vec.clear();
    assert(vec.empty());
}

void test_vector_with_events() {
    std::vector<Event> vec;
    Event e1{ "title1", "description1", "link1", std::chrono::system_clock::time_point(), 10 };
    Event e2{ "title2", "description2", "link2", std::chrono::system_clock::time_point(), 20 };
    vec.push_back(e1);
    vec.push_back(e2);
    assert(vec.size() == 2);
    assert(vec[0] == e1);
    assert(vec[1] == e2);

    vec.pop_back();
    assert(vec.size() == 1);
    assert(vec[0] == e1);
}

void test_all_for_vector() {
    test_vector_operations();
    test_vector_with_events();
}

// EventsRepo tests
void test_get_events_list() {
    EventsRepo repo;
    Event e{ "title", "description", "link", std::chrono::system_clock::time_point(), 10 };
    repo.add_event(e);
    assert(repo.get_events_list()[0] == e);
}

void test_get_events_number() {
    EventsRepo repo;
    Event e{ "title", "description", "link", std::chrono::system_clock::time_point(), 10 };
    repo.add_event(e);
    assert(repo.get_events_list().size() == 1);
}

void test_add_event() {
    EventsRepo repo;
    Event e{ "title", "description", "link", std::chrono::system_clock::time_point(), 10 };
    repo.add_event(e);
    assert(repo.get_events_list().size() == 1);
    assert(repo.get_events_list()[0] == e);
}

void test_remove_event_position() {
    EventsRepo repo;
    Event e{ "title", "description", "link", std::chrono::system_clock::time_point(), 10 };
    repo.add_event(e);
    repo.remove_event_position(0);
    assert(repo.get_events_list().empty());
}

void test_update_event_at_position() {
    EventsRepo repo;
    Event e{ "title", "description", "link", std::chrono::system_clock::time_point(), 10 };
    repo.add_event(e);
    Event e2{ "title2", "description2", "link2", std::chrono::system_clock::time_point(), 20 };
    repo.update_event_at_position(0, e2);
    assert(repo.get_events_list()[0] == e2);
}

void test_all_for_events_repo() {
    test_get_events_list();
    test_get_events_number();
    test_add_event();
    test_remove_event_position();
    test_update_event_at_position();
}

// Service tests
void test_add_to_events_repository() {
    Service s;
    Event e{ "title", "description", "link", std::chrono::system_clock::time_point(), 10 };
    s.add_to_events_repository(e);
    assert(s.get_events_list().size() == 1);
    assert(s.get_events_list()[0] == e);
}

void test_remove_from_events_repository() {
    Service s;
    Event e{ "title", "description", "link", std::chrono::system_clock::time_point(), 10 };
    s.add_to_events_repository(e);
    s.remove_from_events_repository(0);
    assert(s.get_events_list().empty());
}

void test_all_for_service() {
    test_add_to_events_repository();
    test_remove_from_events_repository();
}

// User tests
void test_add_event_to_user() {
    User u{ "name", "password" };
    Event e{ "title", "description", "link", std::chrono::system_clock::time_point(), 10 };
    u.add_event_to_user(e);
    assert(u.get_events_list().size() == 1);
    assert(u.get_events_list()[0] == e);
}

void test_remove_event_from_user() {
    User u{ "name", "password" };
    Event e{ "title", "description", "link", std::chrono::system_clock::time_point(), 10 };
    u.add_event_to_user(e);
    u.remove_event_from_user(0);
    assert(u.get_events_list().empty());
}

void test_all_for_user() {
    test_add_event_to_user();
    test_remove_event_from_user();
}

// Main test runner
//int main() {
//    test_all_for_event();
//    std::cout << "Event tests passed!\n";
//    test_all_for_vector();
//    std::cout << "std::vector tests passed!\n";
//    test_all_for_events_repo();
//    std::cout << "EventsRepo tests passed!\n";
//    test_all_for_service();
//    std::cout << "Service tests passed!\n";
//    test_all_for_user();
//    std::cout << "User tests passed!\n";
//    std::cout << "All tests passed!!!\n";
//    return 0;
//}
