/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : Elevator.cpp

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
#include<cmath>

#include "Elevator.h"

using namespace std;

Elevator::Elevator(unsigned long int el_id, string el_name, float pos, float time)
{
	id = el_id;
	position = pos;
	status = IDLE;
	direction = IDLE;
	tasks.clear();
	staticTime = time;
	currentTime = 0;
	idleTime = 0;
	customers.clear();
	avgWaitingTime = 0;
	totWaitingTime = 0;
	totReachingTime = 0;
	avgReachingTime = 0;
	customerServed = 0;
	customerIn = 0;
}

int Elevator::getId()
{
	return id;
}

float Elevator::getPosition() const
{
	return position;
}

unsigned int Elevator::getDirection() const
{
	return direction;
}

unsigned int Elevator::getStatus() const
{
	return status;
}

const Task& Elevator::getProcessingTask() const
{
	return processingTask;
}

Task& Elevator::addTask(Task& task, int flag)
{
	if (status == IDLE)
	{
		tasks.push_back(task);
		if (flag == 1)
		{
			status = BUSY;
			if (task.getDest() > position) direction = UP;
			else if (task.getDest() < position) direction = DOWN;
		}
		return task;
	}
	else
	{
		vector<Task>::iterator it;
		if (task.getType() == GO)
		{
			if ((direction == UP) && (task.getDest() >= position))
			{
				for (it = tasks.begin() ; (it <= tasks.end()) && (it->getDest() > position) && (it->getDirection() != DOWN) ; ++it)
				{
					if (it == tasks.end()) break;
					if (task.getDest() > it->getDest()) continue;
					else break;
				}
				if (task.getDest() != it->getDest())
				{
					tasks.insert(it,task);
					return task;
				}
				else return *it;
			}
			else if ((direction == UP) && (task.getDest() < position))
			{
				for (it = tasks.begin() ; it <= tasks.end() ; ++it)
				{
					if (it == tasks.end()) break;
					if (it->getDest() > position) continue;
					else break;
				}
				for (it = it ; (it <= tasks.end()) && (it->getDirection() != UP) ; ++it)
				{
					if (it == tasks.end()) break;
					if (it->getDest() < task.getDest()) break;
					else if (it->getDest() == task.getDest()) break;
					else continue;
				}
				if (it->getDest() != task.getDest())
				{
					tasks.insert(it,task);	
					return task;
				}
				else return *it;
			}
			else if ((direction == DOWN) && (task.getDest() <= position))
			{
				for (it = tasks.begin() ; (it <= tasks.end()) && (it->getDest() < position) && (it->getDirection() != UP) ; ++it)
				{
					if (it == tasks.end()) break;
					if (task.getDest() < it->getDest()) continue;
					else break;
				}
				if (task.getDest() != it->getDest())
				{
					tasks.insert(it,task);
					return task;
				}
				else return *it;
			}
			else if ((direction == DOWN) && (task.getDest() > position))
			{
				for (it = tasks.begin() ; it <= tasks.end() ; ++it)
				{
					if (it == tasks.end()) break;
					if (it->getDest() < position) continue;
					else break;
				}
				for (it = it ; (it <= tasks.end()) && (it->getDirection() != DOWN) ; ++it)
				{
					if (it == tasks.end()) break;
					if (it->getDest() > task.getDest()) break;
					else if (it->getDest() == task.getDest()) break;
					else continue;
				}
				if (it->getDest() != task.getDest())
				{
					tasks.insert(it,task);
					return task;
				}
				else return *it;
			}
			else
			{
				cout<<"The lift is doomed. Exiting...."<<endl;
				exit(0);
			}
		}
		else if (task.getType() == CALL)
		{
			int temp;
			vector<Task>::iterator min_it;
			vector<Task>::iterator max_it;
			if ((direction == UP) && (task.getDest() >= position))
			{
				if (task.getDirection() == UP)
				{
					if (DEBUG) cout<<"Up, UP & dest>pos"<<endl;
					for (it = tasks.begin() ; (it <= tasks.end()) && (it->getDest() > position) && (it->getDirection() != DOWN) ; ++it)
					{
						if (it == tasks.end()) break;
						if (task.getDest() > it->getDest()) continue;
						else break;
					}
					if (task.getDest() != it->getDest())
					{
						tasks.insert(it,task);
						return task;
					}
					else return *it;
				}
				else if (task.getDirection() == DOWN)
				{
					if (DEBUG) cout<<"Up, DOWN & dest>pos"<<endl;
					temp = (tasks.begin())->getDest();
					max_it = tasks.begin();
					for (it = tasks.begin() ; it < tasks.end() ; ++it)
					{
						if (it->getDest() > temp)
						{
							max_it = it;
							temp = it->getDest();
						}
						else continue;
					}
					it = max_it;
					while (it->getDest() > task.getDest())
					{
						if (it == tasks.end()) break;
						if (task.getDest() == it->getDest()) break;
						else ++it;
					}
					if (task.getDest() != it->getDest())
					{
						if (temp < task.getDest()) ++it;
						tasks.insert(it,task);
						return task;
					}
					else return *it;
				}
				else
				{
					cout<<"Unknown direction of task. Exiting...."<<endl;
					exit(0);
				}
			}
			else if ((direction == UP) && (task.getDest() < position))
			{
				
				if (task.getDirection() == DOWN)
				{
					if (DEBUG) cout<<"Up, DOWN & dest<pos"<<endl;
					for (it = tasks.begin() ; it != tasks.end() ; ++it)
					{
						if (it->getDest() > position) continue;
						else break;
					}
					for (it = it ; (it <= tasks.end()) && (it->getDirection() != UP) ; ++it)
					{
						if (it == tasks.end()) break;
						if (it->getDest() < task.getDest()) break;
						else if (it->getDest() == task.getDest()) break;
						else continue;
					}
					if (it->getDest() != task.getDest())
					{
						tasks.insert(it,task);	
						return task;
					}
					else return *it;
				}
				else if (task.getDirection() == UP)
				{
					if (DEBUG) cout<<"Up, UP & dest<pos"<<endl;
					temp = (tasks.begin())->getDest();
					min_it = tasks.begin();
					for (it = tasks.begin() ; it < tasks.end() ; ++it)
					{
						if (it->getDest() < temp)
						{
							min_it = it;
							temp = it->getDest();
						}
						else continue;
					}
					if (temp >= position)
					{
						tasks.push_back(task);
						return task;
					}
					else
					{
						it = min_it;
						while (it->getDest() < task.getDest())
						{
							if (it->getDest() == task.getDest()) break;
							if (it == tasks.end()) break;
							else ++it;
						}
						if (it->getDest() != task.getDest())
						{
							if (temp > task.getDest()) ++it;
							tasks.insert(it,task);
							return task;
						}
						else return *it;
					}
				}
				else
				{
					cout<<"Unknown direction of task. Exiting...."<<endl;
					exit(0);
				}
			}
			else if ((direction == DOWN) && (task.getDest() <= position))
			{
				if (task.getDirection() == DOWN)
				{
					if (DEBUG) cout<<"Down, DOWN & dest<pos"<<endl;
					for (it = tasks.begin() ; (it <= tasks.end()) && (it->getDest() < position) && (it->getDirection() != UP) ; ++it)
					{	
						if (it == tasks.end()) break;
						if (task.getDest() < it->getDest()) continue;
						else break;
					}
					if (task.getDest() != it->getDest())
					{
						tasks.insert(it,task);
						return task;
					}
					else return *it;
				}
				else if (task.getDirection() == UP)
				{
					if (DEBUG) cout<<"Down, UP & dest<pos"<<endl;
					temp = (tasks.end())->getDest();
					min_it = tasks.begin();
					for (it = tasks.begin() ; it < tasks.end() ; ++it)
					{
						if (it->getDest() < temp)
						{
							min_it = it;
							temp = it->getDest();
						}
						else continue;
					}
					it = min_it;
					while (it->getDest() < task.getDest())
					{
						if (task.getDest() == it->getDest()) break;
						if (it == tasks.end()) break;
						else ++it;
					}
					if (task.getDest() != it->getDest())
					{
						if (temp > task.getDest()) ++it;
						tasks.insert(it,task);
						return task;
					}
					else return *it;
				}
				else
				{
					cout<<"Unknown direction of task. Exiting...."<<endl;
					exit(0);
				}
			}
			else if ((direction == DOWN) && (task.getDest() > position))
			{
				if (task.getDirection() == UP)
				{
					if (DEBUG) cout<<"Down, UP  & dest>pos"<<endl;
					for (it = tasks.begin() ; it <= tasks.end() ; ++it)
					{
						if (it == tasks.end()) break;
						if (it->getDest() < position) continue;
						else break;
					}
					for (it = it ; (it <= tasks.end()) && (it->getDirection() != DOWN) ; ++it)
					{
						if (it == tasks.end()) break;
						if (it->getDest() > task.getDest()) break;
						else if (it->getDest() == task.getDest()) break;
						else continue;
					}
					if (it->getDest() != task.getDest())
					{
						tasks.insert(it,task);
						return task;
					}
					else return *it;
				}
				else if (task.getDirection() == DOWN)
				{
					if (DEBUG) cout<<"Down, DOWN  & dest>pos"<<endl;
					temp = (tasks.begin())->getDest();
					max_it = tasks.begin();
					for (it = tasks.begin() ; it < tasks.end() ; ++it)
					{
						if (it->getDest() > temp)
						{
							max_it = it;
							temp = it->getDest();
						}
						else continue;
					}
					if (temp <= position)
					{
						tasks.push_back(task);
						return task;
					}
					else
					{
						it = max_it;
						while (it->getDest() > task.getDest())
						{
							if (it->getDest() == task.getDest()) break;
							if (it == tasks.end()) break;
							else ++it;
						}
						if (it->getDest() != task.getDest())
						{
							if (temp < task.getDest()) ++it;
							tasks.insert(it,task);
							return task;
						}
						else return *it;
					}
				}
				else cout<<"Unknown direction of task. Exiting...."<<endl;
			}
			else
			{
				cout<<"The lift is doomed. Exiting...."<<endl;
				exit(0);
			}
		}
		else
		{
			cout<<"Unknown task. Exiting...."<<endl;
			exit(0);
		}
	}
}

const Task& Elevator::processNextTask()
{
	if (tasks.size() == 0)
	{
		status = IDLE;
		direction = IDLE;
		Task x(0 , "" , DEFAULT , DEFAULT , DEFAULT);
		processingTask = x;
	}
	else
	{
		vector<Task>::iterator it1 = tasks.begin();
		if (abs(it1->getDest() - position) < 0.01) tasks.erase(it1);
		if (tasks.size() == 0)
		{
			status = IDLE;
			direction = IDLE;
			
			Task y(0, "", DEFAULT , DEFAULT , DEFAULT);
			processingTask = y;
		}
		else
		{
			status = BUSY;
			vector<Task>::iterator it;
			it = tasks.begin();
			processingTask = it;
			if (processingTask.getDest() > position) direction = UP;
			else direction = DOWN;
		}
	}
	return processingTask;
}

void Elevator::removeTask(Task& task)
{
	vector<Task>::iterator it;
	for (it = tasks.begin() ; it < tasks.end() ; ++it)
	{
		if (task != it) continue;
		else
		{
			tasks.erase(it);
			break;
		}
	}
}

float Elevator::getFinishTime(Task& task)
{
	vector<Task>::iterator it;
	double x = currentTime;
	float pos = position;
	for (it = tasks.begin() ; it < tasks.end() ; ++it)
	{
		x += abs(it->getDest() - pos)*staticTime;
		pos = it->getDest();
		if (task == it) break;
	}
	return x;
}

void Elevator::showStatus()
{
	if (status == IDLE) cout<<"The elevator number "<<getId()<<" is IDLE at floor "<<position<<endl;
	else
	{
		if (direction == UP) cout<<"The elevator number "<<getId()<<" is BUSY at floor "<<position<<" going in UP direction"<<endl;
		else if (direction == DOWN) cout<<"The elevator number "<<getId()<<" is BUSY at floor "<<position<<" going in DOWN direction"<<endl;
	}
	vector<Task>::iterator it;
	cout<<"The tasks assigned to this elevator are : "<<endl;
	for (it = tasks.begin() ; it < tasks.end() ; ++it)
	{
		if (it->getType() == GO) cout<<"Go to floor "<<it->getDest()<<" at time "<<it->getTime()<<endl;
		else if (it->getType() == CALL)
		{
			cout<<"Call to floor "<<it->getDest();
			if (it->getDirection() == UP) cout<<" in UP direction";
			else if (it->getDirection() == DOWN) cout<<" in DOWN direction";
			else cout<<"Unkown task. Exiting...."<<endl;
			cout<<" at time "<<it->getTime()<<endl;
		}
		else
		{
			cout<<"Unknown task. Exiting...."<<endl;
			exit(0);
		}
	}
}

void Elevator::update(Timer time)
{
	double temp = currentTime;
	currentTime = time.getCurrentTime();
	if (status == IDLE) idleTime += time.getCurrentTime() - temp;
	if (direction == UP) position += (time.getCurrentTime() - temp)/staticTime;
	else if (direction == DOWN) position -= (time.getCurrentTime() - temp)/staticTime;
}

void Elevator::addCustomer(Customer cus)
{
	customers.push_back(cus);
	customerIn++;
}

void Elevator::removeCustomer(Customer* cus)
{
	vector<Customer>::iterator it;
	for (it = customers.begin() ; it < customers.end() ; ++it)
	{
		if (*it == cus) customers.erase(it);
		else continue;
	}
	customerServed++;
	if (DEBUG) cout<<"CUSTOMERS SERVED : "<<customerServed<<endl<<endl;
}

void Elevator::updateAvg(double time)
{
	totWaitingTime += currentTime - time;
	avgWaitingTime = totWaitingTime/customerIn;
}

double Elevator::updateTasks(Task task)
{
	double inc_val = 0;
	vector<Task>::iterator it;
	vector<Task>::iterator max_it, min_it;
	vector<Task>::iterator it1, it2;
	int floor_max, floor_min, floor;
	int floor1 = -1, floor2 = -1, floor3 = 10001, floor4 = 10001;
	floor_max = (tasks.begin())->getDest();
	floor_min = (tasks.begin())->getDest();
	max_it = tasks.begin();
	min_it = tasks.begin();
	for (it = tasks.begin() ; it  < tasks.end() ; ++it)
	{
		if (floor_max < it->getDest())
		{
			floor_max = it->getDest();
			max_it = it;
		}
		if (floor_min > it->getDest())
		{
			floor_min = it->getDest();
			min_it = it;
		}
	}
	if (DEBUG) cout<<"MAX FLOOR IS "<<max_it->getDest()<<endl;
	if (DEBUG) cout<<"MIN FLOOR IS "<<min_it->getDest()<<endl;
	if (tasks.size() > 1)
	{
		if (floor_max == task.getDest())
		{
			if (floor_max < position)
			{
				if (max_it != tasks.begin())
				{
					it1 = max_it - 1;
					floor1 = it1->getDest();
				}
				it2 = max_it + 1;
				if (it2 != tasks.end())
				{
					floor2 = it2->getDest();
				}
				if (floor1 > floor2) floor = floor1;
				else if (floor2 > floor1) floor = floor2;
				else floor = max_it->getDest();
				inc_val += abs(floor_max - floor)*2*staticTime;
			}
		}
		else if (floor_min == task.getDest())
		{
			if (floor_min > position)
			{ 
				if (min_it != tasks.begin())
				{
					it1 = min_it - 1;
					floor3 = it1->getDest();
				}
				it2 = min_it + 1;
				if (it2 != tasks.end())
				{
					floor4 = it2->getDest();
				}
				if (floor3 < floor4) floor = floor3;
				else if (floor4 < floor3) floor = floor4;
				else floor = min_it->getDest();
				inc_val += abs(floor - floor_min)*staticTime*2;
			}
		}
	}
	return inc_val;
}

double Elevator::getAvgWaitingTime()
{
	return avgWaitingTime;
}

double Elevator::getIdleTime()
{
	return idleTime/currentTime;
}

double Elevator::getTime()
{
	return currentTime;
}

void Elevator::printStatus()
{
	filebuf fb;
	fb.open("StatusLog.log", ios::out | ios::app);
	if (!fb.is_open()) {
		cout<<"\nERROR opening file. Exiting...\n";
		exit(1);
		}
	ostream fout(&fb);
	
	if (status == IDLE) fout<<"The elevator number "<<getId()<<" is IDLE at floor "<<position<<endl;
	else
	{
		if (direction == UP) fout<<"The elevator number "<<getId()<<" is BUSY at floor "<<position<<" going in UP direction";
		else if (direction == DOWN) fout<<"The elevator number "<<getId()<<" is BUSY at floor "<<position<<" going in DOWN direction";
		fout<<" carrying "<<customers.size()<<" customers"<<endl;
	}
	fb.close();
	
}

void Elevator::updateReach(Customer* cus)
{
	totReachingTime += (currentTime - cus->getTime());
	avgReachingTime = totReachingTime/customerServed;
}

double Elevator::getAvgReachingTime()
{
	return avgReachingTime;
}
