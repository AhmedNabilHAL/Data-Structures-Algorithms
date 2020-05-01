
#include "Course.h"

Course::Course(){
	this->courseName = "Unknown";
	this->courseCode = "Unknown";
	this->courseGrade = 'U';
	this->coursePoint = -1;
	this->courseYear = -1;
	this->courseSemester = -1;
}
Course::Course(std::string courseName, std::string courseCode, char courseGrade, float coursePoint, int courseYear, int courseSemester){
	this->courseName = courseName;
	this->courseCode = courseCode;
	this->courseGrade = courseGrade;
	this->coursePoint = coursePoint;
	this->courseYear = courseYear;
	this->courseSemester = courseSemester;
}
Course::Course(const Course& c){
	this->courseName = c.courseName;
	this->courseCode = c.courseCode;
	this->courseGrade = c.courseGrade;
	this->coursePoint = c.coursePoint;
	this->courseYear = c.courseYear;
	this->courseSemester = c.courseSemester;
}
void Course::printCourseInfo(){
	std::cout << "Course Name: " << this->courseName << std::endl;
	std::cout << "Course Code: " << this->courseCode << std::endl;
	std::cout << "Course Grade: " << this->courseGrade << std::endl;
	std::cout << "Course Point: " << this->coursePoint << std::endl;
	std::cout << "Course Year: " << this->courseYear << std::endl;
	std::cout << "Course Semester: " << this->courseSemester << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Course& c){
	out << "Course Name: " << c.courseName << std::endl;
	out << "Course Code: " << c.courseCode << std::endl;
	out << "Course Grade: " << c.courseGrade << std::endl;
	out << "Course Point: " << c.coursePoint << std::endl;
	out << "Course Year: " << c.courseYear << std::endl;
	out << "Course Semester: " << c.courseSemester;
	return out;
}

