#ifndef COURSE_H
#define COURSE_H
#include<iostream>
#include<stdlib.h>
using namespace std;
class course {
	friend class student;
	friend class manage;
private:
	string m_ID;//ѧ��
	string m_number;//�γ̱��
	string  m_name;//����
	string m_course;//�γ���
	double m_score;//�γ̷���
	double m_credit;//�γ�ѧ��
};
#endif