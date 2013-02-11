/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : ElevatorSystem.cpp

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
#include<cstdlib>
#include<fstream>

#include "ElevatorSystem.h"

using namespace std;

ElevatorSystem::ElevatorSystem(int no_elevators, int no_floors, float speed)
{
	number = no_elevators;
	floors = no_floors;
	elevators.clear();
	for (int i=1 ; i<=no_elevators ; i++)
	{
		elevators.push_back(Elevator(i,"", 0, speed));
	}
	allCustomers.resize(no_floors + 1);
}

int ElevatorSystem::FindBestElevator(Task task)
{
	vector<Elevator>::iterator it;
	double min;
	int x;
	Task temp_task;
	for (it = elevators.begin() ; it != elevators.end() ; ++it)
	{
		if (DEBUG) cout<<"Trace -> FBE() -> Before AddTask()"<<endl;
		temp_task = it->addTask(task, 0);
		if (DEBUG) cout<<"For elevator "<<it->getId()<<", current position is "<<it->getPosition()<<", and the time to arrive is "<<it->getFinishTime(temp_task)<<endl;
		if (it == elevators.begin())
		{
			min = it->getFinishTime(temp_task);
			x = it->getId();
		}
		else
		{
			if (min > it->getFinishTime(temp_task))
			{
				min = it->getFinishTime(temp_task);
				x = it->getId();
			}
			else continue;
		}
	}
	if (temp_task == task)
	{
		for (it = elevators.begin() ; it != elevators.end() ; ++it)
		{
			it->removeTask(task);
		}
	}
	if (DEBUG)	cout<<"The best elevator is "<<x<<endl;
	return x;
}

double ElevatorSystem::FindBestTime(Task task)
{
	vector<Elevator>::iterator it;
	double min;
	int x;
	Task temp_task;
	for (it = elevators.begin() ; it < elevators.end() ; it++)
	{
		temp_task = it->addTask(task, 0);
		if (it == elevators.begin())
		{
			min = it->getFinishTime(temp_task);
			x = it->getId();
		}
		else
		{
			if (min > it->getFinishTime(temp_task))
			{
				min = it->getFinishTime(temp_task);
				x = it->getId();
			}
			else continue;
		}
	}
	if (temp_task == task)
	{
		for (it = elevators.begin() ; it < elevators.end() ; it++)
		{
			it->removeTask(task);
		}
	}
	return min;
}

double ElevatorSystem::FindTime(int e, Task task)
{
	vector<Elevator>::iterator it = elevators.begin();
	it += e-1;
	double min;
	Task temp_task;
	temp_task = it->addTask(task, 0);
	min = it->getFinishTime(temp_task);
	if (temp_task == task)
	{
		for (it = elevators.begin() ; it < elevators.end() ; it++)
		{
			it->removeTask(task);
		}
	}
	return min;
}

void ElevatorSystem::showSystem()
{
	vector<Elevator>::iterator it;
	for (it = elevators.begin() ; it < elevators.end() ; it++)
	{
		it->showStatus();
	}
}

Task& ElevatorSystem::giveTask(int e, Task t)
{
	vector<Elevator>::iterator it;
	it = elevators.begin();
	it += e-1;
	return it->addTask(t, 0);
}

void ElevatorSystem::doTask(int e)
{
	vector<Elevator>::iterator it;
	it = elevators.begin();
	it += e-1;
	it->processNextTask();
}

void ElevatorSystem::update(Timer t)
{
	vector<Elevator>::iterator it;
	for (it = elevators.begin() ; it < elevators.end() ; ++it) it->update(t);
}

Event& ElevatorSystem::giveEvent(Event ev)
{
	int x;
	double y;
	if (ev.getType() == CUST_CALL)
	{
		Task* t1 = new Task(0 , "" , CALL , (ev.getCustomer())->getDir() , (ev.getCustomer())->getAt() , (ev.getCustomer())->getTime());
		x = FindBestElevator(*t1);
		vector<Elevator>::iterator it;
		it = elevators.begin();
		it += x-1;
		y = FindTime(x, *t1);
		Event* ev1  = new Event(0 , "" , ENTER , (*t1).getDirection() , (*t1).getDest() , y , ev.getCustomer() , x);
		addCustomer((ev.getCustomer())->getAt(), *(ev.getCustomer()));
		if (DEBUG) cout<<"Trace : ES -> GiveEvent() ->Event Created"<<endl;
		Task t_1 = it->addTask(*t1, 1);
		upcomingEvents.increaseTime(x, it->updateTasks(t_1), y);
		if (DEBUG) showSystem();
		printStatus();
		return *ev1;
	}
	else if (ev.getType() == CUST_GO)
	{
		Task* t2 = new Task(0 , "" , GO , DEFAULT , (ev.getCustomer())->getTo() , (ev.getCustomer())->getTime());
		x = ev.getElevator();
		vector<Elevator>::iterator it;
		it = elevators.begin();
		it += x-1;
		y = FindTime(x, *t2);
		Event* ev2 = new Event(0 , "" , LEAVE , (*t2).getDirection() , (*t2).getDest() , y , ev.getCustomer() , x);
		Task t_2 = it->addTask(*t2, 1);
		Customer custo = *(ev.getCustomer());
		it->addCustomer(custo);
		it->updateAvg((ev.getCustomer())->getTime());
		upcomingEvents.increaseTime(x, it->updateTasks(t_2), y);
		if (DEBUG) showSystem();
		printStatus();
		return *ev2;
	}
	else if (ev.getType() == LEAVE)
	{
		vector<Elevator>::iterator it = elevators.begin();
		it += ev.getElevator() - 1;
		it->updateReach(ev.getCustomer());
		it->removeCustomer(ev.getCustomer());
		Event* ev_temp = new Event;
		it->processNextTask();
		if (DEBUG) showSystem();
		printStatus();
		return *ev_temp;
	}
	else if (ev.getType() == ENTER)
	{
		vector<Elevator>::iterator it = elevators.begin();
		it += ev.getElevator() - 1;
		it->processNextTask();
		Event* temp_ev = new Event;
		if (DEBUG) showSystem();
		printStatus();
		return *temp_ev;
	}
	else
	{
		cout<<"Doomed Simulation"<<endl;
		cout<<ev.getType()<<endl;
		exit(0);
	}
}

void ElevatorSystem::addCustomer(int floor, Customer cus)
{
	(allCustomers.at(floor)).push_back(cus);
}

void ElevatorSystem::removeCustomer(int floor, Customer cus)
{
	vector<Customer>::iterator it;
	for (it = (allCustomers.at(floor)).begin() ; it < (allCustomers.at(floor)).end() ; ++it)
	{
		if (cus == it) (allCustomers.at(floor)).erase(it);
		else continue;
	}
}

void ElevatorSystem::printMetrics()
{
	int no = 0;
	double total_wait = 0, avg_wait;
	double total_idle = 0, avg_idle;
	double total_reach = 0, avg_reach;
	vector<Elevator>::iterator it;
	for (it = elevators.begin() ; it != elevators.end() ; ++it)
	{
		total_wait += it->getAvgWaitingTime();
		total_idle += it->getIdleTime();
		total_reach += it->getAvgReachingTime();
		no++;
	}
	it = elevators.begin();
	avg_wait = total_wait/no;
	avg_idle = total_idle/no;
	avg_reach = total_reach/no;
	double avg_busy = 1 - avg_idle;
	
	cout<<"\n\n--- SIMULATION METRICS ---\n"<<endl;
	cout<<"The average waiting time of the customers is "<<avg_wait<<endl;
	cout<<"The average reaching time of the customers per floor is "<<avg_reach<<endl;
	cout<<"The average fraction of the time elevators are busy is "<<avg_busy<<endl;
	cout<<"The time taken to simulate is "<<it->getTime()<<endl;
	cout<<"The power factor is "<<(it->getTime())*avg_busy<<endl;
}

void ElevatorSystem::printStatus()
{
	vector<Elevator>::iterator it;
	it = elevators.begin();
	
	filebuf fb;
	fb.open("StatusLog.log", ios::out | ios::app);
	if (!fb.is_open()) {
		cout<<"\nERROR opening file. Exiting...\n";
		exit(1);
		}
	ostream fout(&fb);
	fout<<"At time "<<it->getTime()<<" : "<<endl;
	fb.close();
	for (it = elevators.begin() ; it != elevators.end() ; ++it)
	{
		it->printStatus();
	}
	
}	

