/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : Simulator.cpp

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
#include<ctime>
#include<cmath>


#include "Simulator.h"


#define DEBUG_SIM false  	// Set the DEBUG flag to true to toggle to debugging mode.

using namespace std;

Simulator::Simulator(unsigned long int sim_id, string sim_name, int no_flrs, int no_els, int cus_to_sim, double arrival_min, double arrival_max, float el_speed, bool sanity) : system (no_els, no_flrs, el_speed) {
	id = sim_id;
	name = sim_name;
	
	if (sim_name == "") name = "Un-named Simulator";
	
	cout<<"\n --- Simulation Parameters --- "<<endl;
	
	floors = no_flrs;
	cout<<"\n Number of Floors = "<<floors;
	elevators = no_els;
	cout<<"\n Number of Elevators = "<<elevators;
	
	cusTimeMin = arrival_min;
	cout<<"\n Minimum Arrival Time = "<<cusTimeMin;
	cusTimeMax = arrival_max;
	cout<<"\n Maximum Arrival Time = "<<cusTimeMax;
	
	speed = el_speed; 	// In seconds/Floor
	cout<<"\n Speed of the Elevator = "<<speed;
	sane = sanity;
	cout<<"\n Whether the users are sane : "<<sane;
	
	cusToSimulate = cus_to_sim;
	cout<<"\n Number of users to simulate = "<<cusToSimulate<<endl;
	arrived = 0;
	departed = 0;
	
	cout<<endl;
	cout<<"--- Simulation Begins ---\n"<<endl;
	cout<<"Simulation Running..."<<endl;
	
	filebuf fb;
	fb.open("StatusLog.log", ios::out | ios::trunc);
	if (!fb.is_open()) {
		cout<<"\nERROR opening file. Exiting...\n";
		exit(1);
		}
	ostream fout(&fb);
	
	fout<<" --- STATUS LOG OF ELEVATORS--- \n\n";
	
	fb.close();
	
	fb.open("EventLog.log", ios::out | ios::trunc);
	if (!fb.is_open()) {
		cout<<"\nERROR opening file. Exiting...\n";
		exit(1);
		}
	ostream eout(&fb);
	
	eout<<" --- SIMULATION EVENT LOG --- \n\n";
	
	fb.close();
	
	};

unsigned long int Simulator::getId() const {
	return id;
	}


unsigned long int Simulator::setId(unsigned long int newId) {
	id = newId;
	return id;
	}
			
string Simulator::getName() const {
	return name;
	}

string Simulator::setName(string newName) {
	if (newName == "") newName = "Un-named Simulator";
	name = newName;
	return name;
	}
	
double Simulator::getCurrentTime() const {	// Gets the Current Clock time.
	clock.getCurrentTime();
	}
	
bool Simulator::startSimulation() {
	srand(time(NULL));
	double enq_time = 0;
	int cus_id = 1;
	int ev_id = 1;
	for (int i = 1; i<= 5; i++) {
			
		enq_time += cusTimeMin + (double)(fmod((double)rand(),(double)(10000*(cusTimeMax - cusTimeMin + 1))))/10000.0;	
		
		Customer* newCus = new Customer(cus_id, "", enq_time, floors, sane);
		Event newEvent(ev_id, "", CUST_CALL, newCus->getDir(), newCus->getAt(), enq_time, newCus);
		system.upcomingEvents.push(newEvent);
		
		if (DEBUG_SIM) {	// The DEBUG flag
			cout<<"Setting up Customer "<<cus_id<<" to arrive at floor "<<newCus->getAt()<<" at time = "<<enq_time<<endl;
			}
		
		cus_id++;
		ev_id++;
		}
	
	while (departed < cusToSimulate) {
		
		while (enq_time - system.upcomingEvents.getMinTime() < cusTimeMax) {
			enq_time += cusTimeMin + (double)(fmod((double)rand(),(double)(10000*(cusTimeMax - cusTimeMin + 1))))/10000.0;	
		
		Customer* newCus = new Customer(cus_id, "", enq_time, floors, sane);
		Event newEvent(ev_id, "", CUST_CALL, newCus->getDir(), newCus->getAt(), enq_time, newCus);
		system.upcomingEvents.push(newEvent);
		
		if (DEBUG_SIM) {	// The DEBUG flag
			cout<<"Setting up Customer "<<cus_id<<" to arrive at floor "<<newCus->getAt()<<" at time = "<<enq_time<<endl;
			}
			
		cus_id++;
		ev_id++;
		}
		
		Event to_process = system.upcomingEvents.pop();
		
		if (DEBUG_SIM) {	// The DEBUG flag
			cout<<"Processing Event-id "<<to_process.getId()<<" with timestamp "<<to_process.getTime()<<endl;
			}
		clock.updateTick(to_process.getTime());
		to_process.process();
		system.update(clock);
		
		if (DEBUG_SIM) {	// The DEBUG flag
			cout<<"Clock Updated"<<endl;
			}
		
		Event new_event;
		new_event = system.giveEvent(to_process);
		if (DEBUG_SIM) {	// The DEBUG flag
			cout<<"Event Given"<<endl;
			}

		if (to_process.getType() == ENTER) {
			Event go_evnt(ev_id, "", CUST_GO, DEFAULT, to_process.getCustomer()->getTo(), to_process.getTime(), to_process.getCustomer(), to_process.getElevator());
			go_evnt.process();
			new_event = system.giveEvent(go_evnt);
			ev_id++;
			}
		if (new_event.getType() != DEFAULT) {
			if (DEBUG_SIM) cout<<"Pushing Event "<<new_event.getType()<<endl; // The DEBUG flag
			system.upcomingEvents.push(new_event);
			}
		if (to_process.getType()==LEAVE) {
			if (DEBUG_SIM) cout<<"Leave Event "<<endl; // The DEBUG flag
			departed++;
			}
		}
		system.printMetrics();
	}
		
		
	
