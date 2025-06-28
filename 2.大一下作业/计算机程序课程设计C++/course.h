#ifndef COURSE_H
#define COURSE_H
#include<iostream>
#include<stdlib.h>
using namespace std;
class course {
	friend class student;
	friend class manage;
private:
	string m_ID;//学号
	string m_number;//课程编号
	string  m_name;//姓名
	string m_course;//课程名
	double m_score;//课程分数
	double m_credit;//课程学分
};
#endif