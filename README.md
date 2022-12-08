# OpenFlights-CS225-FinalProject
![Graph](graph.png?raw=true "Full Map")
# Installation for sudo command in linux distribution:

Ubuntu:

	apt install sudo

# Installation Instructions (for graphviz):

Graphviz is a package used to create a .PNG file with a printed graph of all airports. You need to install graphviz to view the created images.

MacOS:

    Install Homebrew: https://brew.sh
    Install graphviz: https://graphviz.org/download/

Windows and Linux: 

    Install graphviz: https://graphviz.org/download/

# Program Organization: 

  Data files: ../OpenFlights-CS225-FinalProject/data
  
    Sample Data: ../OpenFlights-CS225-FinalProject/data/sample
    
    Actual Data: ../OpenFlights-CS225-FinalProject/data/raw

  Function Declarations: ../OpenFlights-CS225-FinalProject/data/includes
  
    Project functions:  ../OpenFlights-CS225-FinalProject/data/includes/project.h
    
    Test functions: ./OpenFlights-CS225-FinalProject/data/includes/test.h

  Function Definitions: ../OpenFlights-CS225-FinalProject/data/src
  
    Project functions:  ../OpenFlights-CS225-FinalProject/data/includes/project.cpp
    
    Main function: ./OpenFlights-CS225-FinalProject/data/includes/main.cpp

  Test Suites: ../OpenFlights-CS225-FinalProject/data/tests/tests.cpp

# Changing Dataset of Airports:

All datasets should be added to the data folder (“../OpenFlights-CS225-FinalProject/data”). In the main.cpp file, there are two functions getRoutesPath() (returns the relative path as a string of the routes data) and getAirportsPath() (returns the relative path as a string of the airports data). These functions should be changed with the relative path of the files the user wants to parse and use for the program. The return string for each function should be written as: 

    ../OpenFlights-CS225-FinalProject/relative path 

# Changing Output of Generated Images:

Users can not select an output location. All graphical .png images are saved in the “../OpenFlights-CS225” root directory. The file should be found underneath the tests folder.

# Commands to run code: 

	  cd ../OpenFlights-CS225-FinalProject
	  make - compiles the main.cpp and test.cpp files
	  make exec - compiles the main.cpp file
	  make tests - compiles the test.cpp
	  ./bin/exec - runs the main.cpp file 
	  ./bin/tests - runs the test.cpp file 

*To reproduce and run test cases, users should type “make tests” in the terminal followed by 

    ./bin/tests
    
to run tests.

*To run the program, users should type “make exec” in the terminal followed by 
    
    ./bin/exec 

to the program.

# Execution Instructions: 

Follow instructions displayed on the console. When inputting airport codes, users can type the four-digit code or ICAO code of the airport in lowercase or uppercase. To find an airport’s ICAO code, we suggest using the following website: https://www.world-airport-codes.com. If a certain code is not available in the data set an error message will appear and we ask if you please enter a new code.


# Team Contract

## Communication

**Team Meetings**

The group will meet every Friday in the afternoon at a time that suits every person. If we can't find a suitable time, we will work out a time in the evening. Thr group will meet once a week, and each meeting should last atleast an hour. We will be making use of Github, VS Code, and Google Docs. Our Google Doc will keep track of team notes.

**Assistance**

We will be using Discord for team communication, and each member should reply with 2 days of receiving a text.

**Respect**

We'll assign every team member critical tasks for the week, so they have sufficient work to do and are involved in team discussions. To ensure that there is mutual respect, we will take conflicting decisions by majority.

## Collaboration

**Work Distribution**

Each week, we will assign a particular task to each member, and we will commuicate on discord or during the weekly meetings to deal with any unforeseen issues.

**Time Commitment**

Each member will do at least 3 hours of work each week, apart from the weekly meetings. There are no prior time commitments that need to be accounted for. It is the team’s responsibility to make sure that each member's work is delivered by the end of the week. If a team member is not completing their tasks even after repeated requests, they will be required to explain their circumstances. Based on their explanation further actions, such as alerting a staff member, may be taken.

**Conflict Resolution**

In case of any conflicts or disagreements between the group, we will vote by majority and take the final decision. We agree that the team will be respectful and make the right decisions.

## Signatures

Aryan Malhotra - aryanm8

Aamir Hafiz - ahafi2

Alexis Serrano - aserr3

Lorenzo Bujalil Silva - lorenzo9
