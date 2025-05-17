# Event Management System

## Project Description
A C++ application for managing events and user watchlists, featuring:  
- **Administrator Mode**: Manage events (add/remove/update)  
- **User Mode**: Browse events, maintain personal watchlist, and get event reminders  
- File persistence for events and users  
- Unit tests for core components  

## Key Features
### 🛠 Administrator Functions
- Add/remove/update events  
- View all events  
- Persistent storage in `events.txt`  
- Initialization with sample events  

### 👥 User Functions
- Secure sign up/login system  
- Browse events by month  
- Add/remove events to watchlist  
- Automatic web link opening for events  
- Watchlist persistence in `users.txt`  
- Chronological event sorting  

## Prerequisites
- Windows OS (uses Windows API for link handling)  
- C++17 compatible compiler (GCC/MinGW recommended)  

## Installation
1. Clone repository:
```bash
git clone https://github.com/yourusername/event-manager.git
cd event-manager
```
## Main menu:
```
Log as administrator or user? 1. Administrator 2. User 0. Exit
```
## Administrator Commands
```
1. Display watchlist
2. Browse events by month
3. Remove from watchlist
0. Exit
```

## User features
```
1. Display watchlist
2. Browse events by month
3. Remove from watchlist
0. Exit
```
