/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : Elevator.h

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

#ifndef __ELEVATOR__
#define __ELEVATOR__

#include<iostream>
#include<string>
#include<vector>
#include "Task.h"
#include "Timer.h"
#include "Customer.h"

#ifndef __STATUSCODES__
#define __STATUSCODES__

#define BUSY 0x8057
#define IDLE 0x1D1E

#endif

using namespace std;


class Elevator
{	
	
	private:
		int id;						// Id of the elevator
		float position;				// Stores the current position of the elevator
		Task processingTask;		// Stores the task which the elevator is currently performing
		unsigned int status;		// Has the status of the elevator BUSY or IDLE (as defined above)
		unsigned int direction; 	// Stores which direction it is currently moving - UP or DOWN. IDLE if the Elevator is IDLE.
		vector<Task> tasks;			// Stores the task list of each elevator
		float staticTime;			// Time taken to cross 1 floor
		double currentTime;			// Current time synchronized everywhere
		double idleTime;			// Stores the time for which elevator was idle
		vector<Customer> customers;	// Stores the list of customers in the elevator
		double avgWaitingTime;
		double totWaitingTime;
		double totReachingTime;
		double avgReachingTime;
		int customerServed;
		int customerIn;
		
	public:
		Elevator(unsigned long int el_id = 0, string el_name = "", float pos = 0, float time = 1); 	// Elevator constructor
		
		int getId();								// Returns elevator id
		float getPosition() const;					// Returns the current position of the elevator
		unsigned int getDirection() const; 			// Returns which direction it is currently moving - UP or DOWN. IDLE if the Elevator is IDLE.
		unsigned int getStatus() const;				// Return the current status of the Elevator - IDLE if there are no tasks in the task queue BUSY otherwise
		const Task& getProcessingTask() const;		// Returns the task the elevator is currently performing
		
		Task& addTask(Task& task, int flag);		// Add the Task task to the task Queue and return a constant refernce to the added Task. 
		const Task& processNextTask();				// Starts the execution of the next task and removes it from the task list.
		void removeTask(Task& t);					// Remove the Task t from the Task queue.
		float getFinishTime(Task& task);			// Get the estimated time to complete all the task in the queue (Will not be the actual time - this is just what the ElevatorSystem uses to decide the tasks)
		
		void showStatus();							// Displays all tasks of the elevator
		void update(Timer time);					// Updates the position,time,etc. of the elevator
		void addCustomer(Customer cus);				// Adds a customer to the customers vector
		void removeCustomer(Customer* cus);			// Removes a customer from the customers vector
		void updateAvg(double time);				// Updates the average time
		double updateTasks(Task task);				// Increases the timestamps of tasks
		double getTime();							// Returns current time
		
		double getAvgWaitingTime();					// Returns the average waiting time of customers of this elevator
		double getIdleTime();						// Returns idle time of the elevator
		void printStatus();							// Prints the status of elevator
		void updateReach(Customer* cus);			// Updates average reaching time
		double getAvgReachingTime();				// Returns average reaching time
};

#endif

