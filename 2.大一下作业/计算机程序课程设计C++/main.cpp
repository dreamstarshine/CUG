#include"student.h"
#include"course.h"
#include"manage.h"
#include<iostream>
using namespace std;
int main() {
	int key;
	int k;
	manage grades;
	while (1) {
		cout << "\t          ��ӭʹ��ѧ���ɼ�����ϵͳ           \n";
		cout << "\t---------------------------------------------\n";
		cout << "\t           [1]¼��ѧ���ɼ�                   \n";
		cout << "\t           [2]ɾ��ѧ����Ϣ                   \n";
		cout << "\t           [3]�޸�ѧ���ɼ�                   \n";
		cout << "\t           [4]����ѧ����Ŀ�ͳɼ�             \n";
		cout << "\t           [5]����ѧ����Ϣ                   \n";
		cout << "\t           [6]ͳ��ѧ����Ϣ                   \n";
		cout << "\t           [7]ģ����ѯ��Ϣ                   \n";
		cout << "\t           [8]���޸ĺ����Ϣ����д���ļ�     \n";
		cout << "\t           [0]��ȫ�˳�                       \n";
		cout << "\t---------------------------------------------\n";
		cout << "\t            ��Ҫѡ��Ĺ���Ϊ                 \n";
		cin >> key;
		if (key == 0) break;
		switch (key) {
		case 1:
			grades.input();
			system("pause");
			break;
		case 2:
			grades.remove();
			system("pause");
			break;
		case 3:
			grades.change();
			system("pause");
			break;
		case 4:
			grades.add();
			system("pause");
			break;
		case 5:
			grades.rank();
			char c;
			do {
				cout << "\t��������ҵķ�ʽ��\n";
				cout << "\t1��������������ĳ��ѧ�������пγ̳ɼ���Ϣ��\n";
				cout << "\t2�����ݰ�Ų���ĳ��������ѧ������ѧ�γ̵ĳɼ���Ϣ��\n";
				cout << "\t3�����ݿγ�������ѡ�޸��ſ�����ѧ���ĳɼ���Ϣ��\n";
				cout << "\t4����������ѧ������ѡ�γ̳ɼ���Ϣ��\n";
				cout << "\t5���˳����ҡ�\n";
				cin >> k;
				switch (k) {
				case 1:
					grades.search1();
					break;
				case 2:
					grades.search2();
					break;
				case 3:
					grades.search3();
					break;
				case 4:
					grades.search4();
					break;
				case 5:
					cout << "�ѳɹ��˳���" << endl;
					break;
				default:
					cout << "û�д�ѡ�������ѡ��!" << endl;
					break;
				}
				if (k == 5)break;
				cout << "�㻹�����������?Y/N" << endl;
				cin >> c;
			} while (c == 'Y' || c == 'y');
			system("pause");
			break;
		case 6:
			char h;
			int i;
			do {
				cout << "������ͳ�Ʒ�ʽ" << endl;
				cout << "1���԰༶���Ƴɼ�����ͳ�ơ�" << endl;
				cout << "2����ѧ���ĳɼ�����ͳ�ơ�" << endl;
				cin >> i;
				switch (i) {
				case 1:
					grades.statistic1();
					break;
				case 2:
					grades.statistic2();
					break;
				default:
					cout << "û�д�ѡ�" << endl;
					break;
				}
				cout << "�㻹�����ͳ����" << endl;
				cin >> h;
			} while (h == 'Y' || h == 'y');
			system("pause");
			break;
		case 7:
			grades.rank();
			grades.fuzzy_search();
			system("pause");
			break;
		case 8:
			grades.write_in();
			system("pause");
			break;
		default:
			cout << "û�и�ѡ�������ѡ��" << endl;
			break;
		}
	}
	return 0;
}