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
		cout << "\t          欢迎使用学生成绩管理系统           \n";
		cout << "\t---------------------------------------------\n";
		cout << "\t           [1]录入学生成绩                   \n";
		cout << "\t           [2]删除学生信息                   \n";
		cout << "\t           [3]修改学生成绩                   \n";
		cout << "\t           [4]增加学生科目和成绩             \n";
		cout << "\t           [5]查找学生信息                   \n";
		cout << "\t           [6]统计学生信息                   \n";
		cout << "\t           [7]模糊查询信息                   \n";
		cout << "\t           [8]将修改后的信息重新写入文件     \n";
		cout << "\t           [0]安全退出                       \n";
		cout << "\t---------------------------------------------\n";
		cout << "\t            你要选择的功能为                 \n";
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
				cout << "\t请输入查找的方式：\n";
				cout << "\t1、根据姓名查找某个学生的所有课程成绩信息。\n";
				cout << "\t2、根据班号查找某个班所有学生的已学课程的成绩信息。\n";
				cout << "\t3、根据课程名查找选修该门课所有学生的成绩信息。\n";
				cout << "\t4、查找所有学生的已选课程成绩信息。\n";
				cout << "\t5、退出查找。\n";
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
					cout << "已成功退出！" << endl;
					break;
				default:
					cout << "没有此选项，请重新选择!" << endl;
					break;
				}
				if (k == 5)break;
				cout << "你还想继续查找吗?Y/N" << endl;
				cin >> c;
			} while (c == 'Y' || c == 'y');
			system("pause");
			break;
		case 6:
			char h;
			int i;
			do {
				cout << "请输入统计方式" << endl;
				cout << "1、对班级单科成绩进行统计。" << endl;
				cout << "2、对学生的成绩进行统计。" << endl;
				cin >> i;
				switch (i) {
				case 1:
					grades.statistic1();
					break;
				case 2:
					grades.statistic2();
					break;
				default:
					cout << "没有此选项！" << endl;
					break;
				}
				cout << "你还想继续统计吗？" << endl;
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
			cout << "没有该选项，请重新选择！" << endl;
			break;
		}
	}
	return 0;
}