# Events Tracker QT

A cross‑platform desktop application built with Qt for managing, organizing, and visualizing personal or team events and reminders. 

## Features

- **Add / Edit / Delete Events**  
  Create new events with title, description, date, time and optional reminders.
- **Calendar View**  
  Month‑by‑month calendar interface for quick navigation and overview.
- **List & Detail View**  
  Scrollable list of upcoming events with full detail panels.
- **Search & Filter**  
  Quickly find events by keyword, date range, or category.
- **Notifications**  
  Optional pop‑up reminders at configurable intervals before each event.
- **Import / Export**  
  Save or load events to/from CSV for backup or integration with other tools.
- **Persistent Storage**  
  Uses a lightweight SQLite database under the hood; no external dependencies.

## Getting Started

### Prerequisites

- **Qt 5.12+** (or Qt 6.x)  
- **C++17** compiler (e.g. GCC, Clang, MSVC)  
- **CMake 3.14+**  

### Installation

1. **Clone the repository**  
   ```bash
   git clone https://github.com/your‑username/events‑tracker‑qt.git
   cd events‑tracker‑qt
2. **Build with CMake**
    ```bash
    mkdir build && cd build
    cmake .. 
    cmake --build .
3. **Run the app**
   ```bash
   ./EventsTracker
