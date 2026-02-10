# Person List Manager
A C++ program for managing a list of people. You can add, view, sort, search, delete, save to file, and load from file.

## Features

- Add person(s) with:
  - First name
  - Last name
  - Signature (`yyyxxx` format, lowercase only)
  - Height in meters
- Print the full list of people
- Sort the list by:
  - Last name (case-insensitive)
  - Signature
  - Height
  - Random order
- Search for a person by their signature
- Delete a person from the list by signature
- Save the list to a file
- Load the list from a file
- Paginated output (20 people per page)
- Simple yes/no prompts and menu navigation

## How to Compile

Use a C++ compiler that supports C++11 or later:
```bash
g++ -std=c++11 -o person_manager main.cpp project.cpp
```

## How to Run
```bash
./person_manager
```

## File Format
When saving to a file, each person's data is stored on a line separated by |:
```bash
FirstName|LastName|signature|height
```

