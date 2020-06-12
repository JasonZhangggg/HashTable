/*Jason Zhang
 * Hash Table
 */

#include <iostream>

#ifndef TABLE_H
#define TABLE_H

using namespace std;
//student struct
struct Student
{
	char firstName[80];
	char lastName[80];
	int id;
	float gpa;
};
//node struct
struct Node
{
	Node* next = NULL;
	Student* student;
};

class Table{
	public:
		Table();
		//take in input for add
		void addParse();
		//add student
		void addStudent(Student*);
		//del student
		void delStudent();
		//print
		void print();
		//get hash val
		int hash(char*);
		//add a node
		void addNode(Student*, int, Node** &);
		//delete a node
		void delNode(int, int);
		//rehash list
		void rehash(int);
	private:
		//size of list
		int size;
		//list itself
		Node** list;
};
#endif
