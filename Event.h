/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : Event.h

Copyright (C) 2011 Nivvedan, Ankush Das

    liftsim is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    liftsim is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with liftsim.  If not, see <http://www.gnu.org/licenses/>.
    
    
Authors:

Nivvedan
nivvedan@iitb.ac.in

Ankush Das
ankushdas@iitb.ac.in



File Created on : Wednesday, October 12, 2011.
Last modified on : Tuesday, 15 November, 2011.

*/


#ifndef __EVENT__
#define __EVENT__

#include<iostream>
#include<string>
#include<vector>
#include "Customer.h"
#include "Object.h"

#ifndef __EVENTTYPES__
#define __EVENTTYPES__

#define DEFAULT 0xDEFA			// This is the default task that the constructor initializes to.
#define CUST_CALL 0xCA11		// This event type is generated when a customer on a floor calls an elevator.
#define CUST_GO 0x0060			// This event type is generated when a customer presses a button on the elevator.
#define ENTER 0xE12E			// Customer entering the elevator
#define LEAVE 0x1EA2			// Customer leaving the elevator

#endif


using namespace std;

class Event {
	
	private:
		unsigned long int id;
		string name;
		int floor;								// The floor number pressed on the elevator or the floor on which the call button is pressed.
		unsigned int direction;					// Stores the direction if a call button is pressed, otherwise DEFAULT
		unsigned int type;						// Stores the type of the Task - CALL or GO or ENTER of LEAVE
		double timestamp;						// Time at which the task occurs
		Customer* cus;							// The customer to which the event is associated
		int elevator;							// Elevator number associated with the event
	
	public:
		Event(unsigned long int ev_id = 0, string ev_name = "", unsigned int ev_type = DEFAULT, unsigned int ev_direction = DEFAULT, int ev_destination = DEFAULT, double time = 0, Customer* ev_cus = NULL, int ev_el = 0);			// The constructor for the event
		Event(const Event& event);															// Copy constructor for the event
		
		int getFloor() const;								// Returns the destination floor number of the event
		unsigned int getDirection() const; 					// Returns the direction variable
		
		unsigned long int getId() const;					// Event ID
		unsigned long int setId(unsigned long int newId);	// Sets the event ID
		
		string getName() const;								// Returns event name
		string setName(string newName);						// Gives a name to the event
		
		unsigned int getType() const;						// Returns the type of the event
		double getTime() const;								// Returns the timestamp of the event
		Customer* getCustomer() const;						// Returns pointer to the customer to which event is associated
		int getElevator() const;							// Returns the elevator number associated to the event
		
		bool operator ==(Event& a);							// Function which checks whether two events are equal or not
		bool operator !=(Event& a);							// As usual
		Event operator =(const Event& a);					// As usual
		bool operator !=(vector<Event>::iterator it);		// As usual
		bool operator ==(vector<Event>::iterator it);		// As usual
		Event operator =(vector<Event>::iterator it);		// As usual
		bool operator >(Event& a);							// For the priority queue
		bool operator <(Event& a);							// For the priority queue
		bool operator >=(Event& a);							// For the priority queue
		bool operator <=(Event& a);							// For the priority queue
		
		void increaseTime(double val);						// Increasing the timestamp
		void process();										// Justs prints stuff on the screen
		void show();										// Shows the event
};

#endif

