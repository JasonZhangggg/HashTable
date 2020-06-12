/*Jason Zhang
 *Hash Table
 * */

#include <iostream>
#include <vector>
#include <cstring>
#include <math.h>
#include <fstream>

#include "Table.h"
using namespace std;

void add(Table*&);
void deleteStudent(Table*&);
void printVec(Table*);
void addRand(int, Table*&);
int main(){
	//start studentNum at 1 because i increment studentNum after i add in the random student
	int studentNum = 1;
	//table
	Table* ta = new Table();
	while(true){
		//take in input
		char* input = new char();
		cout<<"Input ADD to add a student, PRINT to print the students, DELETE to delete a student, ADDRAND to add a random student, and QUIT to exit the program."<<endl;
		cin.getline(input, sizeof(input));
		//convert to uppercase
		for(int i = 0; i<sizeof(input); i++){
			input[i] = toupper(input[i]);
		}

		if(strcmp(input, "ADD") == 0){
			//add student
			add(ta);
			cin.ignore(1000, '\n');
			//increment studentNum
			studentNum++;
		}

		else if(strcmp(input, "PRINT") == 0){
			//print
			printVec(ta);
		}

		else if(strcmp(input, "DELETE") == 0){
			//del student
			deleteStudent(ta);
			cin.ignore(1000, '\n');
			//decrease studentNum
			studentNum--;
		}

		else if(strcmp(input, "QUIT") == 0){
			return 0;
		}
		else if(strcmp(input, "ADDRAND") == 0){
			//add random student
			addRand(studentNum, ta);
			//increase studentNum
			studentNum++;		
		}
		else{
			cout<<"That is invalid."<< endl;
		}
	}
}
void add(Table* &ta){
	ta->addParse();
}
void deleteStudent(Table* &ta){
	ta->delStudent();
}

void printVec(Table* ta){
	ta->print();
}
void addRand(int studentNum, Table* &ta){
	//student	
	Student* temp = new Student();
	ifstream fileStream1;
	ifstream fileStream2;
	fileStream1.open("firstnames.txt");
	fileStream2.open("lastnames.txt");
	//generate random number from 1-100
	int random = rand()%100;
	//keep reading until that line
	for(int i = 0; i<random; i++){
		fileStream1.getline(temp->firstName, sizeof(firstName));
		fileStream2.getline(temp->lastName, sizeof(lastName));
	}
	//random gpa
	temp->gpa = (float)(rand()%400)/100;
	//get id based on studentNum
	temp->id = studentNum;
	//add the student
	ta->addStudent(temp);
}
