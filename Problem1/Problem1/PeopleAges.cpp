#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <unordered_set>
#include "conio.h"

using namespace std;

// Person class to hold the name, born and dead year

class Person{

private:
	string name;
	int born;
	int dead;

public:
	Person(string name,int born,int dead) :name(name),born(born),dead(dead){
		if(dead>2000)
			this->dead = -1;
	}
	~Person(){
	}

	// A person is alive if the dead year is NULL or dead year > current year
	bool isAlive(int currentYear){
		if(this->dead != -1 && this->dead <= currentYear){
			return false;
		}
		else
			return true;
	}

	string getName(){
		return name;
	}
	int getBorn(){
		return born;
	}
	int getDead(){
		return dead;
	}
};

// generate a random year given a base 
// year generated is dependent on range (assuming its 30 for born year)
int getRandomYear(int base, int minrange, int maxrange){
	return base + minrange + rand()%(maxrange -minrange);
}

//generate a random string of given size
string getRandomString(int size){
	string str;
	for (int i = 0; i < size; ++i)
	{
		int randomChar = rand()%(26);        
		str += 'A' + randomChar;
	}
	return str;
}

// fill in the data set with random names, born {1900,2000}, dead {1900,2000} 
void createPeopleDataSet(vector<Person>& peopleSet, int setSize){

	cout<<"Creating persons : "<<endl;
	Person *newPerson;
	int born=1900,dead=2000;
	string name;
	int minrange = 0, maxrange=50; //range to generate random years i.e (1900 + range)
	int minagerange = 60,maxagerange = 90;
	// create a seed to generate random string size for first and last names and random born and dead years
	srand(time(NULL));


	for(int i = 0;i<setSize;i++){
		name = getRandomString(rand()%5+3) + " " + getRandomString(rand()%5+3);
		born = getRandomYear(1900,minrange,maxrange);
		dead = getRandomYear(born,minagerange,maxagerange);
		newPerson = new Person(name, born, dead);
		peopleSet.push_back(*newPerson);
	}
}

// given a data set with born, dead year of people
// run through the dataset and check if person:isAlive()
// print the status of the person
void listStatusOfPeople(vector<Person>& peopleSet,int currentYear){
	string status = "alive";
	for(Person per : peopleSet){
		status = per.isAlive(currentYear)?"alive":"dead";
		cout<<"Name : "<< per.getName()<< "\tborn : "<<per.getBorn()<< "\tdead : "<<per.getDead()<<"\tis " + status<<endl;
	}
}

// given a data set of people with names, born year and dead year 

int findBirthYearWithMaxAlive(vector<Person>& peopleSet,int currentYear){

	// multiset used to store the born years of people who are alive
	// count operation on multiset is linear
	unordered_multiset<int> aliveBirthYear;

	// some performance measurement code
	// capture start time of operation
	FILETIME ft1,ft2;
	GetSystemTimeAsFileTime(&ft1);
	ULARGE_INTEGER theTime;
	theTime.LowPart = ft1.dwLowDateTime;
	theTime.HighPart = ft1.dwHighDateTime;
	__int64 ft164Bit = theTime.QuadPart;

	// run through the dataset and check if person isAlive()
	// if true, insert the birth year into the multiset
	for(Person person : peopleSet){
		if(person.isAlive(currentYear))
			aliveBirthYear.insert(person.getBorn());
	}

	// to count the birth year with the most number of people alive
	int finalMax = INT_MIN;
	int yearMax = -1;
	
	// cycle through the years
	// non-optimized: this for loop counts the number of years multiple times
	for(int year : aliveBirthYear){
		// count the number of occurrences of 'year' in the set 
		// linear complexity on the number of elements counted
		int countYear = aliveBirthYear.count(year);

		// keep track of the maximum count and the corresponding year 
		if(finalMax <= countYear){
			finalMax = countYear;
			yearMax = year;
		}
	}

	// capture end time of operation
	GetSystemTimeAsFileTime(&ft2);
	ULARGE_INTEGER theTime2;
	theTime2.LowPart = ft2.dwLowDateTime;
	theTime2.HighPart = ft2.dwHighDateTime;
	__int64 ft264Bit = theTime2.QuadPart;

	cout<<endl<<"Method 1 : Non-Optimized"<<endl;
	cout<<"Total number of people alive : "<<aliveBirthYear.size()<<endl;

	if(finalMax>INT_MIN)		
		cout<<"Year : " <<yearMax<<"\tPeople Alive : " <<finalMax<<endl;
	else 
		cout<<"No one is alive !!! :("<<endl;
	
	// calculate the time the operation took
	cout<<"Operation took : "<<(ft264Bit - ft164Bit)*100<<" nanoseconds"<<endl;


	// capture start time of operation
	GetSystemTimeAsFileTime(&ft1);
	theTime.LowPart = ft1.dwLowDateTime;
	theTime.HighPart = ft1.dwHighDateTime;
	ft164Bit = theTime.QuadPart;

	finalMax = INT_MIN;
	yearMax = -1;
	// optimized version - use this if 
	// this loop only counts the number of year once ...and skips over to the next year
	for(unordered_multiset<int>::iterator index=aliveBirthYear.begin(); index!=aliveBirthYear.end(); index++){
		
		// count the number of occurrences of 'year' in the set 
		// linear complexity on the number of elements counted
		int countYear = aliveBirthYear.count(*index);
		
		// keep track of the maximum count and the corresponding year 
		if(finalMax <= countYear){
			finalMax = countYear;
			yearMax = *index;
			while(countYear-- > 0)  // skip to the next year in the set
				index++;
		}
	}

	// capture end time of operation
	GetSystemTimeAsFileTime(&ft2);
	theTime2.LowPart = ft2.dwLowDateTime;
	theTime2.HighPart = ft2.dwHighDateTime;
	ft264Bit = theTime2.QuadPart;

	cout<<endl<<"Method 2 : Optimized"<<endl;
	cout<<"Total number of people alive : "<<aliveBirthYear.size()<<endl;

	if(finalMax>INT_MIN)		
		cout<<"Year : " <<yearMax<<"\tPeople Alive : " <<finalMax<<endl;
	else 
		cout<<"No one is alive !!! :("<<endl;

	// calculate the time the operation took
	cout<<"Operation took : "<<(ft264Bit - ft164Bit)*100<<" nanoseconds"<<endl;
	
	return yearMax;
}

int main(int argc, char *argv[]){

	// default is to create a list of 100 people with random names, birth year (1900 + 30 range ) and death year (2000 - 30 range)

	vector<Person> listOfPeople;
	int numberofPeople = 100;
	int currentYear = 2015;
	
	// provide arguments to set the number of people and current year
	if(argc>1){
		numberofPeople = atoi(argv[1]);
	}
	if(argc>2){
		currentYear = atoi(argv[2]);
	}
	
	//create a data set of the "numberOfPeople" size
	createPeopleDataSet(listOfPeople,numberofPeople);
	
	//print the current status of all people in the dataset
	listStatusOfPeople(listOfPeople,2000);

	//find and print the year with maximum people alive
	int birthYear = findBirthYearWithMaxAlive(listOfPeople,2000);

	if(birthYear != -1)
		cout<<endl<<"The born year with maximum number of people alive is : "<<birthYear<<endl;
	else
		cout<<endl<<"So...I cannot find the born year with maximum number of people alive"<<endl;

	_getch();
	return 0;
}
