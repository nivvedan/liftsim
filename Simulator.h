/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : Simulator.h

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

#ifndef __SIMULATOR__
#define __SIMULATOR__

#include<iostream>
#include<string>

#include "Timer.h"
#include "Event.h"
#include "ElevatorSystem.h"


using namespace std;


class Simulator {	
	
	private:
		unsigned long int id;
		string name;
		
		int floors;
		int elevators;
		
		int cusTimeMin;
		int cusTimeMax;
		
		int cusToSimulate;
		int arrived;
		int departed;
		
		float speed;
		bool sane;
		
		ElevatorSystem system;		
		Timer clock;
			
	public:
		Simulator(unsigned long int sim_id, string sim_name, int no_flrs, int no_els, int cus_to_sim = 5, double arrival_min = 0, double arrival_max = 20, float el_speed = 1, bool sanity = true);
			
		unsigned long int getId() const;
		unsigned long int setId(unsigned long int newId);
		
		string getName() const;
		string setName(string newname);
		
		double getCurrentTime() const; // Returns the current time
		bool startSimulation();
		
	};


#endif

