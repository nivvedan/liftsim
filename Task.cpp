/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : Task.cpp

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
#include<string>

#include "Task.h"

using namespace std;

Task::Task(unsigned long int task_id, string task_name, unsigned int task_type, unsigned int task_direction, int task_destination, double time)
{
	destination = task_destination;
	direction = task_direction;
	type = task_type;
	timestamp = time;
	//associatedEvents.clear();
	//if (task_name == "") name = "Un-named Task";
}

Task::Task(const Task& task)
{
	destination = task.destination;
	direction = task.direction;
	type = task.type;
	timestamp = task.timestamp;
	vector<Event*>::const_iterator it;
	/*for (it = (task.associatedEvents).begin() ; it != (task.associatedEvents).end() ; ++it)
	{
		associatedEvents.push_back(*it);
	}*/
}

int Task::getDest() const
{
	return destination;
}

unsigned int Task::getDirection() const
{
	return direction;
}
/*
string Task::setName(string newName)
{
	if (newName == "") newName = "Un-named Task";
	name = newName;
	return name;
}
*/
unsigned int Task::getType() const
{
	return type;
}

double Task::getTime() const
{
	return timestamp;
}

bool Task::operator ==(Task& a)
{
	return ((destination == a.destination) && (direction == a.direction) && (type == a.type) && (timestamp == a.timestamp));
}

bool Task::operator !=(Task& a)
{
	return !(*this == a);
}

Task Task::operator=(const Task& a)
{
	destination = a.destination;
	direction = a.direction;
	type = a.type;
	timestamp = a.timestamp;
	vector<Event*>::const_iterator it;
	/*for (it = (a.associatedEvents).begin() ; it != (a.associatedEvents).end() ; ++it)
	{
		associatedEvents.push_back(*it);
	}*/
	return *this;
}

bool Task::operator !=(vector<Task>::iterator it)
{
	return !((destination == it->destination) && (direction == it->direction) && (type == it->type) && (timestamp == it->timestamp));
}

bool Task::operator ==(vector<Task>::iterator it)
{
	return ((destination == it->destination) && (direction == it->direction) && (type == it->type) && (timestamp == it->timestamp));
}

Task Task::operator =(vector<Task>::iterator it)
{
	destination = it->destination;
	direction = it->direction;
	type = it->type;
	timestamp = it->timestamp;
	vector<Event*>::iterator temp_it;

	/*
	------------------ OLD CODE (DIFEERENT IMPLEMENTATION) ---------------------
	
	for (temp_it = (it->associatedEvents).begin() ; temp_it < (it->associatedEvents).end() ; ++temp_it)
	{
		associatedEvents.push_back(*temp_it);
	}
	
	*/
	return *this;
}
/*
------------------ OLD CODE (DIFEERENT IMPLEMENTATION) ---------------------

void Task::addEvent(Event* ev)
{
	cout<<"ADDING EVENT WITH TIMESTAMP "<<ev->getTime()<<endl;
	associatedEvents.push_back(ev);
	vector<Event*>::iterator it;
	//cout<<associatedEvents.size()<<endl;
	for (it = associatedEvents.begin() ; it < associatedEvents.end() ; ++it)
	{
		(*it)->show();
	}
}

void Task::increaseTimeStamp(double val)
{	
	vector<Event*>::iterator it;
	for (it = associatedEvents.begin() ; it < associatedEvents.end() ; ++it)
	{
		(*it)->increaseTime(val);
		if (DEBUG) cout<<"Increasing timestamp by "<<val<<" for event "<<(*it)->getType()<<endl;
	}
}

void Task::showEvents()
{
	vector<Event*>::iterator it;
	//cout<<associatedEvents.size()<<endl;
	for (it = associatedEvents.begin() ; it < associatedEvents.end() ; ++it)
	{
		(*it)->show();
	}
}

void Task::clearEvents()
{
	associatedEvents.clear();
}


*/
