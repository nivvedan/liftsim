/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : Customer.h

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



File Created on : Wednesday, November 2, 2011.
Last modified on : Tuesday, 15 November, 2011.

*/

#ifndef __CUSTOMER__
#define __CUSTOMER__

#include<iostream>
#include<string>
#include<vector>


#ifndef __TASKTYPES__
#define __TASKTYPES__

#define DEFAULT 0xDEFA	// This is the default task that the constructor initializes to.
#define CALL 0xCA11		// This task type is generated when a customer on a floor calls an elevator.
#define GO 0x0060		// This task type is generated when a customer presses a button on the elevator.
#define UP 0x0900
#define DOWN 0xD047

#endif

using namespace std;

class Customer {
	
	private:
		unsigned long int id;			// Customer ID
		string name;					// Customer Name
		double timestamp;				// Customer timestamp
		
		int atFloor;					// Arrival floor of customer
		int toFloor;					// Departure floor of customer
		int goes;						// Direction of call of elevator
		
	public:
		Customer(unsigned long int cus_id = 0, string cus_name = "", double t = 0, int max_floors = 100, bool sane = true);
																				// Constructor
		unsigned long int getId() const;										// Returns customer ID
		unsigned long int setId(unsigned long int newId);						// Sets customer ID
		
		string getName() const;													// Returns customer name
		string setName(string newname);											// Sets customer name
		
		double getTime() const;													// Returns customer timestamp
		int getAt() const;														// Returns arrival floor
		int getTo() const;														// Returns departure floor
		int getDir() const;
		
		bool operator ==(Customer* cust);										// As usual
		bool operator ==(Customer cust);										// As usual
		const Customer& operator =(const Customer& cust);						// As usual
		bool operator ==(vector<Customer>::iterator it);						// As usual
	};

#endif

