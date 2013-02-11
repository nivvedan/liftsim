/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : Object.cpp

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

#include "Object.h"

using namespace std;

Object::Object(unsigned long int object_id, string object_name) {
	id = object_id;
	if (object_name == "") object_name = "Un-named Object";
	name = object_name;
	}

unsigned long int Object::getId() const {
	return id;
	}


unsigned long int Object::setId(unsigned long int newId) {
	id = newId;
	return id;
	}
			
string Object::getName() const {
	return name;
	}

string Object::setName(string newName) {
	if (newName == "") newName = "Un-named Object";
	name = newName;
	return name;
	}

