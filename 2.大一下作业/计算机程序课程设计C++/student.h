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
	string  m_class;//���
	string m_major;
	double m_total = 50;
	double m_completed = 0;//����ɵ�ѧ��
	double m_uncompleted = 0;//δ��ɵ�ѧ��
	double m_failed = 0;//�ɼ��������Ŀ
	vector<course> m_cs;//������ȡÿ��ͬѧ�Ŀ�Ŀ�Լ����� ��m_course_score
};
#endif;
