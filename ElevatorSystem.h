/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : ElevatorSystem.h

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

#ifndef __ELEV_SYSTEM__
#define __ELEV_SYSTEM__

#include<iostream>
#include<vector>

#include "Event.h"
#include "Elevator.h"
#include "Timer.h"
#include "EventQueue.h"
#include "matrix.cpp"


using namespace std;

class ElevatorSystem
{
	private:
		vector<Elevator> elevators;												// Stores the elevators in the form of a vector
		int number;																// Stores the number of elevators
		int floors;																// Stores the number of floors
		matrix<Customer> allCustomers;											// Stores the customers on all floors
	
	public:
		
		EventQueue upcomingEvents;
		
		ElevatorSystem(int no_elevators = 1, int no_floors = 1, float speed = 1);	// Default constructor
		
		int FindBestElevator(Task task);										// Finds the best elevator for a call task
		double FindBestTime(Task task);											// Finds the estimated time of best elevator
		double FindTime(int e, Task task);										// Finds estimated time of task
		void showSystem();														// Shows the status of all elevators
		Task& giveTask(int e, Task t);											// Gives a task to a particular elevator
		void doTask(int e);														// Processes the task of a particular elevator
		void update(Timer t);													// Updates the current time for all elevators
		Event& giveEvent(Event ev);												// Creates an event for the event list
		void addCustomer(int floor, Customer cus);								// Adds a customer to the elevator system
		void removeCustomer(int floor, Customer cus);							// Removes a customer from the elevator system
		void printMetrics();													// Prints the performance metrics
		void printStatus();														// Prints the status log
};

#endif

