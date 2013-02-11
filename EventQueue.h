/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : EventQueue.h

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

#ifndef __EVENTQUEUE__
#define __EVENTQUEUE__

#include<iostream>
#include<string>
#include<list>

#include "Customer.h"
#include "Event.h"

using namespace std;

class EventQueue {

	private:
		list<Event> theQueue;
	
	public:
		double getMinTime();
		const Event& next();
		Event pop();
		int size() const;
		bool empty() const;		
		
		const Event& findById(unsigned long int ev_id);
		Event deleteById(unsigned long int ev_id);
		
		const Event& push(Event& e);
		void increaseTime(int el_no, double inc_val, double lim);
	};
		
#endif

