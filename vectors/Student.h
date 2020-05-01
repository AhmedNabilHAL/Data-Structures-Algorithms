#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
#include "FCIvector.h"

#include "Course.h"

class Student{
	std::string sName;
	int sID;
	std::string sDepartment;
	FCIvector<Course> loc;
	static int cnt;
public:
	// constuctors:
	Student();
	Student(std::string sName, FCIvector<Course>& loc, int sID = cnt, std::string sDeparment = "Unassigned");
	Student(const Student& s);
	// ================================================================================
	// printing:
	void printInfo();
	friend std::ostream& operator<<(std::ostream& out, const Student& s);
	// ================================================================================
	// add a course to list of courses
	void addCourse(const Course c);

};

int Student::cnt;
std::ostream& operator<<(std::ostream& out, const Student& s);

#endif
