/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : Event.cpp

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


#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>

#include "Event.h"

using namespace std;

Event::Event(unsigned long int ev_id, string ev_name, unsigned int ev_type, unsigned int ev_direction, int ev_floor, double time, Customer* ev_cus, int ev_el)
{
	id = ev_id;
	if (ev_name == "") name = "Un-named Event";
	else name = ev_name;
	
	floor = ev_floor;
	direction = ev_direction;
	type = ev_type;
	timestamp = time;
	cus = ev_cus;
	elevator = ev_el;
	
}

Event::Event(const Event& event)
{
	id = event.id;
	name = event.name;
	floor = event.floor;
	direction = event.direction;
	type = event.type;
	timestamp = event.timestamp;
	cus = event.cus;
	elevator = event.elevator;
}

int Event::getFloor() const
{
	return floor;
}

unsigned int Event::getDirection() const
{
	return direction;
}

unsigned long int Event::getId() const {
	return id;
	}


unsigned long int Event::setId(unsigned long int newId) {
	id = newId;
	return id;
	}
			
string Event::getName() const {
	return name;
	}

string Event::setName(string newName) {
	if (newName == "") newName = "Un-named Event";
	name = newName;
	return name;
	}
	
unsigned int Event::getType() const
{
	return type;
}

double Event::getTime() const
{
	return timestamp;
}

Customer* Event::getCustomer() const
{
	return cus;
}

int Event::getElevator() const
{
	return elevator;
}

bool Event::operator ==(Event& a)
{
	return ((floor == a.floor) && (direction == a.direction) && (type == a.type) && (timestamp == a.timestamp) && (cus == a.cus) && (elevator == a.elevator));
}

bool Event::operator !=(Event& a)
{
	return !(*this == a);
}

Event Event::operator=(const Event& a)
{
	id = a.id;
	name = a.name;
	floor = a.floor;
	direction = a.direction;
	type = a.type;
	timestamp = a.timestamp;
	cus = a.cus;
	elevator = a.elevator;
	return *this;
}

bool Event::operator !=(vector<Event>::iterator it)
{
	return !((floor == it->floor) && (direction == it->direction) && (type == it->type) && (timestamp == it->timestamp) && (cus == it->cus) && (elevator == it->elevator));
}

bool Event::operator ==(vector<Event>::iterator it)
{
	return !(*this == it);
}

Event Event::operator =(vector<Event>::iterator it)
{
	floor = it->floor;
	direction = it->direction;
	type = it->type;
	timestamp = it->timestamp;
	cus = it->cus;
	elevator = it->elevator;
	return *this;
}

bool Event::operator >(Event& a)
{
	return (timestamp < a.timestamp);
}

bool Event::operator <(Event& a)
{
	return (timestamp > a.timestamp);
}

bool Event::operator >=(Event& a)
{
	return (timestamp <= a.timestamp);
}

bool Event::operator <=(Event& a)
{
	return (timestamp >= a.timestamp);
}

void Event::increaseTime(double val)
{
	timestamp += val;
}

void Event::process()
{
	filebuf fb;
	fb.open("EventLog.log", ios::out | ios::app);
	if (!fb.is_open()) {
		cout<<"\nERROR opening file. Exiting...\n";
		exit(1);
		}
	ostream fout(&fb);
	
	fout<<"At time "<<getTime()<<" : ";
	if (type == CUST_CALL) {
		fout<<"Customer "<<cus->getId()<<" arrives at floor number "<<cus->getAt()<<" and places a call in the ";
		if (cus->getDir() == UP) fout<<"UP direction."<<endl;
		else if (cus->getDir() == DOWN) fout<<"DOWN direction."<<endl;
		else {
			cerr<<"ERROR: Trace -> Event.cpp ->process() -> Unknown Direction."<<endl; 
			exit(1);
			}
		}
	else if (type == CUST_GO) {
		fout<<"Customer "<<cus->getId()<<" in Elevator "<<getElevator()<<" would like to go to floor number "<<cus->getTo()<<endl;
		}
	else if (type == ENTER) {
		fout<<"Elevator "<<getElevator()<<" arrives at floor number "<<cus->getAt()<<" and customer "<<cus->getId()<<" enters the elevator"<<endl;
		}
	else if (type == LEAVE) {
		fout<<"Customer "<<cus->getId()<<" leaves Elevator "<<getElevator()<<" at floor "<<cus->getTo()<<endl;
		}
	else
	{
		cerr<<"ERROR: Trace -> Event.cpp ->process() -> Unknown Event type."<<endl; 
		exit(1);
		}
		
	fb.close();
}

void Event::show()
{
	if (type == CUST_CALL) cout<<"\t\tEvent of customer call ";
	else if (type == CUST_GO) cout<<"\t\tEvent of customer go ";
	else if (type == ENTER) cout<<"\t\tEvent of enter ";
	else if (type == LEAVE) cout<<"\t\tEvent of leave ";
	else
	{
		cerr<<"ERROR: Trace -> Event.cpp ->process() -> Unknown Event type."<<endl; 
		exit(1);
	}
	cout<<"at timestamp "<<timestamp<<endl;
}
