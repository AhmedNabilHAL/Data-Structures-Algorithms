#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>

class Course{
	std::string courseName;
	std::string courseCode;
	char courseGrade;
	float coursePoint;
	int courseYear;
	int courseSemester;
public:
	// constuctors:
	Course();
	Course(std::string courseName, std::string courseCode = "Unknown", char courseGrade = 'U', float coursePoint = -1, int courseYear = -1, int courseSemester = -1);
	Course(const Course& c);
	//================================================================================
	// printing:
	void printCourseInfo();
	friend std::ostream& operator<<(std::ostream& out, const Course& c);
};

std::ostream& operator<<(std::ostream& out, const Course& c);

#endif
