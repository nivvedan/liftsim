/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : Task.h

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

#ifndef __TASK__
#define __TASK__

#include<iostream>
#include<string>
#include<vector>
#include "Event.h"

#define DEBUG false
#ifndef __TASKTYPES__
#define __TASKTYPES__

#define DEFAULT 0xDEFA	// This is the default task that the constructor initializes to.
#define CALL 0xCA11		// This task type is generated when a customer on a floor calls an elevator.
#define GO 0x0060		// This task type is generated when a customer presses a button on the elevator.
#define UP 0x0900
#define DOWN 0xD047

#endif

using namespace std;

class Task {
	
	private:
		int destination;		// The floor number pressed on the elevator or the floor on which the call button is pressed.
		unsigned int direction;	// Stores the direction if a call button is pressed, otherwise DEFAULT
		unsigned int type;		// Stores the type of the Task - CALL or GO
		double timestamp;		// Time at which the task occurs
		//vector<Event*> associatedEvents;
	
	public:
		Task(unsigned long int task_id = 0, string task_name = "", unsigned int task_type = DEFAULT, unsigned int task_direction = DEFAULT, int task_destination = DEFAULT, double time = 0);				// The constructor for the Task
		Task(const Task& task);								// Copy constructor for the Task
		
		int getDest() const;								// Returns the destination floor number of the Task
		unsigned int getDirection() const; 					// Returns the direction variable
		unsigned int getType() const;						// Returns the type of the Task
		double getTime() const;								// Returns the timestamp of the task
		
		bool operator ==(Task& a);							// Function which checks whether two Tasks are equal or not
		bool operator !=(Task& a);							// As usual
		Task operator =(const Task& a);						// As usual
		bool operator !=(vector<Task>::iterator it);		// As usual
		bool operator ==(vector<Task>::iterator it);		// As usual
		Task operator =(vector<Task>::iterator it);			// As usual
		/*
		------------------ OLD CODE (DIFEERENT IMPLEMENTATION) ---------------------
		void addEvent(Event* ev);
		void increaseTimeStamp(double val);
		void showEvents();
		void clearEvents();
		*/
};

#endif

