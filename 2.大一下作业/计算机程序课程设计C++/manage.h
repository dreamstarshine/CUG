#ifndef MANAGE_H
#define MANAGE_H
#include "student.h"
using namespace std;
class manage {
	friend class student;
public:
	vector<student>m_a;
	void input();//录入函数
	void remove();//删除函数
	void change();//修改函数
	void add();//增加函数
	void search1();//根据姓名查找
	void search2();//根据班号查找
	void search3();//根据课程名查找
	void search4();//查找所有学生已选课程信息
	void statistic1();//根据班级统计
	void statistic2();//根据学生统计
	void rank();//按学号默认排序
	void fuzzy_search();//模糊查找函数
	void write_in();//重新写入文件函数
};
#endif