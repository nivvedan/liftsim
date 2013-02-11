/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : matrix.h

Copyright (C) 2011 Nivvedan

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
    
    
Author:

Nivvedan
nivvedan@iitb.ac.in


File Created on : Wednesday, October 12, 2011.
Last modified on : Tuesday, 15 November, 2011.

*/

#ifndef _MATRIX_
#define _MATRIX_

#include<iostream>
#include<vector>

using namespace std;

template <class Obj>
class matrix {

	public:
		const Obj& at(int x, int y) const;						// Returns the object at (x,y)
		const vector<Obj>& at(int x) const;						// Returns the vector of objects at x
		Obj& at(int x, int y);									// Sets the object at (x,y)
		vector<Obj>& at(int x);									// Sets the vector of objects at y
		const vector<Obj>& operator[] (int row) const;			// As usual
		vector<Obj>& operator[] (int row);						// As usual
		int length() const;										// Returns length of matrix
		int width() const;										// Returns width of matrix
		void resize(int size);									// Resizes the matrix
		matrix(int l=0, int b=0);								// Constructor
		~matrix() {
			}
	
	private:
		int len;
		int wid;		
		vector< vector<Obj> > mat;
	
	};

#endif
