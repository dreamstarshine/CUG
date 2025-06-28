#ifndef STUDENT_H
#define STUDENT_H
#include<iostream>
#include<vector>
#include<string>
#include"course.h"
using namespace std;
class student {
	friend class course;
	friend class manage;
private:
    string m_name;
	string m_ID;//ID
	string  m_class;//班号
	string m_major;
	double m_total = 50;
	double m_completed = 0;//已完成的学分
	double m_uncompleted = 0;//未完成的学分
	double m_failed = 0;//成绩不及格科目
	vector<course> m_cs;//用来获取每个同学的科目以及分数 即m_course_score
};
#endif;
