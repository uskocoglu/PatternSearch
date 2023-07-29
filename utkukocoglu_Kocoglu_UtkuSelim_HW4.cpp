#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include "strutils.h"
#include "utkukocoglu_Kocoglu_UtkuSelim_HW4_myClass.h"

using namespace std;
/*************************
Author: Utku Selim Kocoglu
Date: 07 April 2021
Purpose: Given a file which consists of bitstrings in a matrix form, the user enters a bitstring of himself and the program tries to find that bitstring in that file
*************************/

//a struct to keep matrix indices
struct cellStruct{
	char ch;
	bool flag;
};

int main(){
	DynIntStack stack;
	DynIntStack print;
	ifstream input;
	string filename;
	int rows, columns;
	string str;
	char ch;
	cout << "Please enter the number of rows: ";
	cin >> rows;
	cout << "Please enter the number of columns: ";
	cin >> columns;
	cout << "Please enter the name of the input file that contains the matrix: ";
	cin >> filename;
	input.open(filename.c_str());
	//if the file cannot be opened, input again
	while (input.fail()){
		cout << "File cannot be opened." << endl; 
		cout << "Please enter the name of the input file again: ";
		cin >> filename;
		input.open(filename.c_str());
	}
	//construct a matrix
	cellStruct** matrix;
	matrix = new cellStruct*[rows];
	for (int i=0; i<rows; i++){
		matrix[i] = new cellStruct[columns];
	}
	//insert the element in the file into a struct type matrix
	for (int i=0; i<rows; i++){
		for (int j=0; j<columns; j++){
			input >> ch;
			matrix[i][j].ch = ch;
			matrix[i][j].flag = false;
		}
	}
	cout << endl;

	cout << "Please enter a string of bits to search (CTRL+Z to quit): ";
	cin.ignore( numeric_limits< streamsize >::max(), '\n' );
	//user enters a bitstring in a loop until the user enters ctrl+z
	while(getline(cin, str)){
		int d1, d2;
		int d3, d4;
		int ss = 0;
		int k = 0;
		int r = 0;
		int c = 0;
		for (int i=0; i<rows; i++){
			for (int j=0; j<columns; j++){
				matrix[i][j].flag = false;
			}
		}
		//check the first index of the string
		if (str[0] != matrix[0][0].ch){
			matrix[0][0].flag = true;
			cout << "The bit string " << str << " could not be found." << endl << endl;
			cout << "Please enter a string of bits to search (CTRL+Z to quit): ";
		}
		else{
			stack.push(r, c);		//add the found index to the stack
			ss++;
			k = 1;
			//this loop finds and adds the indices to a stack in order to print the bitstring path at the end of the program
			while ((k<str.size()) && (matrix[0][0].flag == false) && (r+c != rows+columns-2)){

				if (str[k] == matrix[r][c+1].ch && matrix[r][c+1].flag == false){
					stack.push(r, c+1);		//add the found index to the stack
					c++;
					k++;
					ss++;
				}
				else{
					
					if (str[k] == matrix[r+1][c].ch && matrix[r+1][c].flag == false){
						stack.push(r+1, c);		//add the found index to the stack
						r++;
						k++;
						ss++;
					}

					else{
						for (int i=1; i<ss; i++){
							stack.pop(d1, d2);		//pop the wrong index from the stack
						}
						matrix[r][c].flag = true;
						k = 1; 
						r = 0;
						c = 0;
						ss = 1;
					}
				}
		}
			if (k == str.size()){
				//pop from a stack and push to another
				for (int i=0; i<str.size(); i++){
					stack.pop(d3, d4);
					print.push(d3, d4);
				}
				cout << "The bit string " << str << " is found following these cells:" << endl;
				for (int i=0; i<str.size(); i++){
					print.pop(d3, d4);
					cout << "(" << d3 << ", " << d4 << ")" << " ";
				}
				cout << endl << "\nPlease enter a string of bits to search (CTRL+Z to quit): ";
			}
			else{
				cout << "The bit string " << str << " could not be found." << endl << endl;
				cout << "Please enter a string of bits to search (CTRL+Z to quit): ";
			}
		}
	}
	cout << "Program ended successfully." << endl << endl;
	return 0;
}