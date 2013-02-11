/*

This file is a part of program liftsim for the course project of the course CS 293 - Data Structures and Algorithms Lab.

File Name : matrix.cpp

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


#include<iostream>

#include"matrix.h"

using namespace std;

template <class Obj>
const Obj& matrix<Obj>::at(int x, int y) const {
	return (mat.at(x).at(y));
	}

template <class Obj>	
const vector<Obj>& matrix<Obj>::at(int x) const {
	return mat.at(x);
	}

template <class Obj>
Obj& matrix<Obj>::at(int x, int y) {
	return (mat.at(x).at(y));
	}

template <class Obj>	
vector<Obj>& matrix<Obj>::at(int x) {
	return mat.at(x);
	}
	
template<class Obj>
matrix<Obj>::matrix(int l, int b) : mat (l) {
	if ((l<0)||(b<0)) {
		l=0;
		b=0;
		};
	len = l;
	wid = b;
	for (int i=0; i<l; i++) {
		mat[i].resize(b);
		}
	}
	
template<class Obj>
void matrix<Obj>::resize(int size) {
	mat.resize(size);
	}
	
template <class Obj>
const vector<Obj>& matrix<Obj>::operator[] (int row) const {
	return mat.at(row);
	}
	
template <class Obj>
vector<Obj>& matrix<Obj>::operator[] (int row) {
	return mat.at(row);
	}

template<class Obj>
int matrix<Obj>::length() const {
	return len;
	}

template<class Obj>	
int matrix<Obj>::width() const {
	return wid;
	}

