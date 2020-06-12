/*Jason Zhang
 *Hash Table
 * */


#include <iostream>
#include <cstring>
#include "Table.h"

using namespace std;

Table::Table(){
	//set size and set all of list's values to NULL
	size = 100;
	list = new Node*[size];
	for(int i = 0; i<size; i++){
		list[i] = NULL;
	}
}
//take in input for add
void Table::addParse(){
	Student* in = new Student();
	cout<<"What is the first name of the student?"<<endl;
	cin.getline(in->firstName, 80);
	cout<<"What is the last name of the student?"<<endl;
	cin.getline(in->lastName, 80);
	cout<<"What is the student's id?"<<endl;
	cin>>in->id;
	cout<<"What is the student's gpa?"<<endl;
	cin>>in->gpa;       	
	addStudent(in);
}
//calculate the hash value and add the student
void Table::addStudent(Student* in){
	int index = (hash(in->firstName)+hash(in->lastName))%size;
	addNode(in, index, list);
}
int Table::hash(char* in){
	//add up the ascii values of the name
	int total = 0;
	for(int i = 0; i<sizeof(in); i++){
		total +=(int)(in[i]);
	}
	//mod it by the size of list
	total %= size;
	return total;
}
void Table::addNode(Student* in, int hash, Node** &l){
	int i = 0;
	//if it is the first chain, init a new node
	if(l[hash] == NULL){
		l[hash] = new Node();
		//set the node value to student
		l[hash]->student = in;
		return;
	}
	//otherwise keep looping until NULL
	else{
		Node* cur = l[hash];
		while(cur->next != NULL){
			cur = cur->next;	
			i++;
		}
		//add the student in at the end of the linked list
		cur->next = new Node();
		cur->next->student = in;
	}
	//if there are more then 3 values in a linked list rehash
	if(i>3){
		rehash(in->id);
	}
}
void Table::delNode(int hash, int id){
	Node* cur = list[hash];
	Node* past = NULL;
	while(cur != NULL){
		//find the location of student
		if(cur->student->id == id){
			//if it is the root case, just set val to node
			if(past == NULL){
				list[hash] = NULL;
			}
			//otherwise set the prev's next to the current next, skipping over current
			else{ 
				past->next = list[hash]->next;
			}
			return;
		}
		//iterate
		past = cur;
		cur = cur->next;
	}
}
void Table::print(){
	//loop through list
	for(int i = 0; i<size; i++){
		if(list[i] != NULL){
			//loop through linked list and print info
			Node* cur = list[i];
			while(cur != NULL){
				Student* s = cur->student;
				cout<<s->firstName<<" "<<s->lastName<<" has the ID "<<s->id<<" and the GPA "<<s->gpa<<endl;
				cur = cur->next;
			}
		}
	}
}
//take in input to delete student
void Table::delStudent(){
	char* first = new char();
	char* last = new char();
	int id;
	cout<<"What is the student's first name?"<<endl;
	cin.getline(first, sizeof(first));
	cout<<"What is the student's last name?"<<endl;
	cin.getline(last, sizeof(last));
	cout<<"What is the student's ID?"<<endl;
	cin>>id;
	//find hash value
	int index = (hash(first)+hash(last))%size;
	delNode(index, id);
}
void Table::rehash(int id){
	//double size
	size*=2;
	Node** temp = new Node*[size];
	//loop through list
	for(int i = 0; i<sizeof(list); i++){
		if(list[i] != NULL){
			//iterate through linked list
			Node* cur = list[i];
			while(cur != NULL){
				//recalc hash value and add it into temp list
				Student* s = cur->student;
				int index = (hash(s->firstName)+hash(s->lastName)+2*id)%size;
				addNode(s, index, temp);
				cur = cur->next;
			}
		}
	}
	//set temp list to current list
	delete[]list;
	list = temp;
}
