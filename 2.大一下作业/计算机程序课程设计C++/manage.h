#ifndef MANAGE_H
#define MANAGE_H
#include "student.h"
using namespace std;
class manage {
	friend class student;
public:
	vector<student>m_a;
	void input();//¼�뺯��
	void remove();//ɾ������
	void change();//�޸ĺ���
	void add();//���Ӻ���
	void search1();//������������
	void search2();//���ݰ�Ų���
	void search3();//���ݿγ�������
	void search4();//��������ѧ����ѡ�γ���Ϣ
	void statistic1();//���ݰ༶ͳ��
	void statistic2();//����ѧ��ͳ��
	void rank();//��ѧ��Ĭ������
	void fuzzy_search();//ģ�����Һ���
	void write_in();//����д���ļ�����
};
#endif