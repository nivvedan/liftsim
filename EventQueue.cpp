/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : EventQueue.cpp

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

#include "EventQueue.h"

using namespace std;

int EventQueue::size() const {
	return theQueue.size();
	}
	
bool EventQueue::empty() const {
	return theQueue.empty();
	}
	
const Event& EventQueue::next() {
	
	double min_time = theQueue.front().getTime();
	list<Event>::iterator min_it = theQueue.begin();
	
	for (list<Event>::iterator it=theQueue.begin(); it!=theQueue.end(); ++it) {
		if (it->getTime() < min_time) {
			min_time = it->getTime();
			min_it = it;
			}
		}
	return *min_it;
	}
	
Event EventQueue::pop() {
	
	double min_time = theQueue.front().getTime();
	list<Event>::iterator min_it = theQueue.begin();
	
	for (list<Event>::iterator it=theQueue.begin(); it!=theQueue.end(); ++it) {
		if (it->getTime() < min_time) {
			min_time = it->getTime();
			min_it = it;
			}
		}
	Event* saved_event = new Event(*min_it);
	theQueue.erase(min_it);
	return *saved_event;
	}
	
double EventQueue::getMinTime() {
	
	double min_time = theQueue.front().getTime();
	
	for (list<Event>::iterator it=theQueue.begin(); it!=theQueue.end(); ++it) {
		if (it->getTime() < min_time) {
			min_time = it->getTime();
			}
		}
	return min_time;
	}
	
const Event& EventQueue::push(Event& e) {
	
	theQueue.push_back(e);
	return e;
	}
	
const Event& EventQueue::findById(unsigned long int ev_id) {
	
	for (list<Event>::iterator it=theQueue.begin(); it!=theQueue.end(); ++it) {
		if (it->getId() == ev_id) {
			return *it;
			}
		}
	}

Event EventQueue::deleteById(unsigned long int ev_id) {
	
	list<Event>::iterator it;
	for (it=theQueue.begin(); it!=theQueue.end(); ++it) {
		if (it->getId() == ev_id) {
			break;
			}
		}
	
	Event* saved_event = new Event(*it);
	theQueue.erase(it);
	return *saved_event;
	}

void EventQueue::increaseTime(int el_no, double inc_val, double lim)
{
	list<Event>::iterator it;
	for (it = theQueue.begin() ; it != theQueue.end() ; ++it)
	{
		if ((it->getElevator() == el_no) && (it->getTime() > lim))
		{
			it->increaseTime(inc_val);
			//cout<<"Increasing time of this event by "<<inc_val<<endl;
			//it->show();
		}
		//else it->show();
	}
}
