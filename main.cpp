/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : main.cpp

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

#include <iostream>
#include <string>
#include <sstream>
#include "Simulator.h"

using namespace std;

template <class T>
bool from_string(T& t, 
                 const string& s, 
                 ios_base& (*f)(ios_base&))
{
  istringstream iss(s);
  return !(iss >> f >> t).fail();
}

void usage (string a) {
	cout<<"Usage: "<< a <<" <Number of Floors> <Number of Elevators> <Customers to Simulate> [OPTIONAL : <Minimum inter-arrival Time = 0> <Maximum inter-arrival time = 20> <Elevator speed = 5> <Whether users are sane = true> ]. \n";
	}

int main (int argc, char *argv[]) {

	if ( argc < 4 ) { // argc should be atleast 4
		
		usage(string(argv[0]));
		return 1;
		}
	
	else {
		unsigned int no_floors, no_elevators, cus_to_simulate;
  
 		if(from_string<unsigned int>(no_floors, string(argv[1]), dec));		
  		else {
  			cout << "Invalid Number of Floors" << endl;
  			usage(string(argv[0]));
  			return 1;
  			}
  		if(from_string<unsigned int>(no_elevators, string(argv[2]), dec));			
  		else {
  			cout << "Invalid Number of Elevators" << endl;
  			usage(string(argv[0]));
  			return 1;
  			}
  		if(from_string<unsigned int>(cus_to_simulate, string(argv[3]), dec));			
  		else {
  			cout << "Invalid Number of Customers to Simulate" << endl;
  			usage(string(argv[0]));
  			return 1;
  			}
  		
  		double cus_arrival_min, cus_arrival_max;
  		float speed;
  		bool sane;
  		
  		if (argc >= 5) {
  			if(from_string<double>(cus_arrival_min, string(argv[4]), dec)) {
  				if (cus_arrival_min < 0) cus_arrival_min = 0;
  				}		
  			else {
  				cout << "Invalid Minimum Inter-arrival Time" << endl;
  				usage(string(argv[0]));
  				return 1;
  				}
  			}
  		else {
  			cus_arrival_min = 0;
  			}
  			
  		if (argc >= 6) {
  			if(from_string<double>(cus_arrival_max, string(argv[5]), dec)) {
  				if (cus_arrival_max < 0) cus_arrival_max = 20;
  				}		
  			else {
  				cout << "Invalid Maximum Inter-arrival Time" << endl;
  				usage(string(argv[0]));
  				return 1;
  				}
  			}
  		else {
  			cus_arrival_max = 20;
  			}
  			
  		
  			
  		if (argc >= 7) {
  			if(from_string<float>(speed, string(argv[6]), dec)) {
  				if (speed < 0) speed = 5;
  				}		
  			else {
  				cout << "Invalid Speed" << endl;
  				usage(string(argv[0]));
  				return 1;
  				}
  			}
  		else {
  			speed = 5;
  			}
  			
  		if (argc >= 8) {
  			if (string(argv[7]) == "true") sane = true;
  			else if (string(argv[7]) == "false") sane = false;	
  			else {
  				cout << "Invalid Sane boolean" << endl;
  				usage(string(argv[0]));
  				return 1;
  				}
  			}
  		else {
  			sane = true;
  			}
  		
  			
  		if (sane) {
  			Simulator sim(1, "_sim1", no_floors, no_elevators, cus_to_simulate, cus_arrival_min, cus_arrival_max, speed, sane);
			sim.startSimulation();
			}
		else {
			Simulator sim_1(1, "_sim1", no_floors, no_elevators, cus_to_simulate, cus_arrival_min, cus_arrival_max, speed, true);
			sim_1.startSimulation();
			
			Simulator sim_2(2, "_sim2", no_floors, no_elevators, cus_to_simulate, cus_arrival_min, cus_arrival_max, speed, false);
			sim_2.startSimulation();
			}
    
		return 0;
		}
	};

