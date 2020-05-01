
#include "Student.h"
#include "FCIvector.h"
#include "FCIvector.cpp"

Student::Student(){
	this->sName = "Unknown";
	this->sID = this->cnt++;
	this->sDepartment = "Unassigned";
	this->loc.clear();
}
Student::Student(std::string sName, FCIvector<Course>& loc, int sID, std::string sDeparment){
	this->sName = sName;
	this->sID = sID; this->cnt++;
	this->sDepartment = sDeparment;
	this->loc.clear();
	for (int i = 0; i < loc.size(); ++i) this->loc.push_back(loc[i]);
}
Student::Student(const Student& s){
	this->sName = s.sName;
	this->sID = s.sID; this->cnt++;
	this->sDepartment = s.sDepartment;
	this->loc.clear();
	for (int i = 0; i < loc.size(); ++i) this->loc.push_back(s.loc[i]);
}
void Student::addCourse(const Course c){
	this->loc.push_back(c);
}
void Student::printInfo(){
	std::cout << "Name: " << this->sName << std::endl;
	std::cout << "ID: " << this->sID << std::endl;
	std::cout << "Department: " << this->sDepartment << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Student& s){
	out << "Name: " << s.sName << std::endl;
	out << "ID: " << s.sID << std::endl;
	out << "Department: " << s.sDepartment;
	return out;
}

