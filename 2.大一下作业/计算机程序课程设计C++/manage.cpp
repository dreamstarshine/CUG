#include"manage.h"
#include<iostream>
#include<vector>
#include<cstdlib>
#include<iomanip>
#include<fstream>
#include<sstream>
void manage::input() {
	ifstream ifs1;
	ifs1.open("student.txt", ios::in);
	if (!ifs1.is_open()) {
		cout << "student.txt文件未打开！" << endl;
	}
	else {
		cout << "student.txt文件已打开！" << endl;
	}
	student temp1;
	string buf1;
	while (getline(ifs1, buf1))
	{
		if (buf1 == "#END")break;
		if (buf1[0] < '0' || buf1[0]>'9')continue;
		istringstream is(buf1);
		is >> temp1.m_ID >> temp1.m_name >> temp1.m_class >> temp1.m_major;
		m_a.push_back(temp1);
    }
	for (auto it = m_a.begin(); it != m_a.end(); it++) {
		cout << (*it).m_ID << '\t' << (*it).m_name << '\t' << (*it).m_class << '\t' << (*it).m_major << endl;
	}
	ifs1.close();
	ifstream ifs2;
	ifs2.open("score.txt", ios::in);
	if (!ifs2.is_open()) {
		cout << "score.txt文件未打开！" << endl;
	}
	else {
		cout << "score.txt文件已打开！" << endl;
	}
	course temp2;
	string buf2;
	while (getline(ifs2, buf2))
	{
		if (buf2 == "#END")break;
		if (buf2[0] < '0' || buf2[0]>'9') continue;
		istringstream is(buf2);
		is >> temp2.m_ID >> temp2.m_name >> temp2.m_course >> temp2.m_score;
		for (int i = 0; i < m_a.size(); ++i) {
			if(temp2.m_ID==m_a[i].m_ID)
			m_a[i].m_cs.push_back(temp2);
		}
	}
	/*for (int i = 0; i < m_a.size(); ++i) {
		for (auto it = m_a[i].m_cs.begin(); it != m_a[i].m_cs.end(); it++) {
			cout << (*it).m_ID << '\t' << (*it).m_name << '\t' << (*it).m_course << '\t' << (*it).m_score << endl;
		}
	}*/
	ifs2.close();
	ifstream ifs3;
	ifs3.open("module.txt", ios::in);
	if (!ifs3.is_open()) {
		cout << "module.txt文件未打开！" << endl;
	}
	else {
		cout << "module.txt文件已打开！" << endl;
	}
	string m_number;
	string m_course;
	double m_credit;
	string buf3;
	while (getline(ifs3, buf3))
	{
		if (buf3 == "#END")break;
		if (buf3[0] < '0' || buf3[0]>'9')continue;
		istringstream is(buf3);
		is >> m_number >> m_course >> m_credit;
		for (int i = 0; i < m_a.size(); ++i) {
			for (int j = 0; j < m_a[i].m_cs.size(); ++j) {
				if (m_a[i].m_cs[j].m_course == m_course) {
					m_a[i].m_cs[j].m_credit = m_credit;
				}
			}
		}
	}
	ifs3.close();
	double sum(0),failed(0);
	for (int i = 0; i < m_a.size(); ++i) {
		for(int j=0;j<m_a[i].m_cs.size();++j){
			if (m_a[i].m_cs[j].m_score >= 60) {
				sum += m_a[i].m_cs[j].m_credit;
			} 
			else {
				++failed;
			}

		}
		m_a[i].m_completed = sum;
		if (sum >= 50) m_a[i].m_uncompleted = 0;
		else { 
			m_a[i].m_uncompleted = 50 - sum; 
		}
		m_a[i].m_failed = failed;
		sum = 0;
		failed = 0;
	}
}
     void manage::remove() {
		string s;
		char c;
		cout << "请输入你想删除的学生名字:" << endl;
		cin >> s;
		cout << "你确认要删除这个学生的信息吗?Y/N" << endl;
		cin >> c;
		if(c == 'Y' || c == 'y') {
			for (int i = 0; i < m_a.size(); ++i) {
				if (m_a[i].m_name == s) {
					for (int j = i + 1; j <m_a.size(); ++j) {
						swap(m_a[j - 1], m_a[j]);
					}
				}
			}
			if (m_a[m_a.size() - 1].m_name != s) {
				cout << "该学生不存在！" << endl;
			}
			else {
				m_a.pop_back();
				cout << "该学生信息已删除！" << endl;
			}
		}
	 }
	void manage::change() {
		string s, t;
		char c;
		cout << "请输入你想修改信息的学生姓名：" << endl;
		cin >> s;
		double score;
		do {
			cout << "请输入你想修改的课程(如果未显示修改成功，则学生或课程不存在)：" << endl;
			cin >> t;
			for (int i = 0; i <m_a.size(); ++i) {
				if (m_a[i].m_name == s) {
					for (int j = 0; j<m_a[i].m_cs.size(); ++j) {
						if (m_a[i].m_cs[j].m_course == t) {
							cout << "请输入你想修改成绩：" << endl;
							cin >> score;
							m_a[i].m_cs[j].m_score = score;
							cout << "修改成功！" << endl;
						}
					}
				}
			}
			system("pause");
			cout << "你还想继续修改吗？Y/N" << endl;
			cin >> c;
		} while (c == 'Y' || c == 'y');
	}
	void manage::add() {
		string s;
		course a;
		char c, h;
		do {
			cout << "请输入你想新增科目和成绩的学生名字：（如果未显示，则学生不存在）" << endl;
			cin >> s;
			do {
				for (int i = 0; i <m_a.size(); ++i) {
					if (m_a[i].m_name == s) {
						cout << "请输入你想增加的科目名称：" << endl;
						cin >> a.m_course;
						cout << "请输入这个科目的分数：" << endl;
						cin >> a.m_score;
						a.m_ID = m_a[i].m_ID;
						a.m_name = m_a[i].m_name;
						ifstream ifs3;
						ifs3.open("module.txt", ios::in);
						if (!ifs3.is_open()) {
							cout << "module.txt文件未打开！" << endl;
						}
						string m_number;
						string m_course;
						double m_credit;
						string buf3;
						while (getline(ifs3, buf3))
						{
							if (buf3 == "#END")break;
							if (buf3[0] < '0' || buf3[0]>'9')continue;
							istringstream is(buf3);
							is >> m_number >> m_course >> m_credit;
						    for (int j = 0; j < m_a[i].m_cs.size(); ++j) {
								if (a.m_course== m_course) {
									a.m_credit= m_credit;
									if (a.m_score >= 60) {
										m_a[i].m_completed += m_credit;
									}
									else {
										++m_a[i].m_failed;
									}
									if (m_a[i].m_completed >= 50) { 
										m_a[i].m_uncompleted = 0; }
									else {
										m_a[i].m_uncompleted = 50 - m_a[i].m_completed;
									}
									
								}
							}
						}

						ifs3.close();
						m_a[i].m_cs.push_back(a);
						break;
					}
				}
				system("pause");
				cout << "你还想继续增加该学生的科目和分数吗？Y/N" << endl;
				cin >> c;
			} while (c == 'Y' || c == 'y');
			cout << "你还想增加另一个学生的科目和分数吗？Y/N" << endl;
			cin >> h;
		} while (h == 'Y' || h == 'y');
	}
void manage::rank() {
	for (int i = 0; i < m_a.size()-1; ++i) {
		for (int j = m_a.size()-1; j > i; --j) {
			if (m_a[j].m_ID < m_a[j-1].m_ID) {
				swap(m_a[j].m_ID, m_a[j - 1].m_ID);
			}
		}
	}
}
void manage::search1() {
	string s;
	cout << "请输入你想查找的学生姓名：" << endl;
	cin >> s;
	cout << "查找到的信息如下所示(如果学生不存在：输出为空白)：" << endl;
	for (int i = 0; i <m_a.size(); ++i) {
		if (m_a[i].m_name == s) {
			for (auto &j : m_a[i].m_cs) {
				cout <<'\t'<<j.m_course <<'\t'<< j.m_score << endl;
			}
		}
	}
	system("pause");
}
void manage::search2() {
	string s;
	cout << "请输入你想查找的班号：" << endl;
	cin >> s;
	cout << "查找到的信息如下所示（如果班级不存在：输出为空白）：" << endl;
	vector<student>vi;
	for (int i = 0; i < m_a.size(); ++i) {
		vi.push_back(m_a[i]);
	}
	for (int i = 0; i <vi.size()-1; ++i) {
		for (int j =vi.size()-1; j > i; --j) {
			if (vi[j].m_completed>vi[j-1].m_completed) {
				swap(vi[j], vi[j-1]);
			}
		}
	}
	system("pause");
	ofstream outfile;
	outfile.open("student2.txt", ios::app);
	if (!outfile.is_open()) {
		cout << "student2.txt文件未打开！" << endl;
	}
	for (int i = 0; i <vi.size(); i++) {
		if (vi[i].m_class == s) {
			cout << '\t' << "姓名" << '\t' << "已修学分" << '\n';
			cout << '\t' << vi[i].m_name << '\t' << vi[i].m_completed << '\n';
			cout << '\t' << "课程" << '\t' << "分数" << '\n';
			outfile << '\t' << "姓名" << '\t' << "已修学分" << '\n';
			outfile << '\t' << vi[i].m_name << '\t' << vi[i].m_completed << '\n';
			outfile << '\t' << "课程" << '\t' << "分数" << '\n';
			for (auto &j:vi[i].m_cs) {
			cout<<'\t'<<j.m_course<<'\t' << j.m_score<<'\n';
			outfile<< '\t' << j.m_course << '\t' << j.m_score << '\n';
			}
			cout << "---------------------------------------------------------\n";
			outfile << "---------------------------------------------------------\n";
		}
	}
	outfile.close();
}
void manage::search3() {
	string s;
	cout << "请输入你要查找的课程名称：" << endl;
	cin >> s;
	cout << "查找到的信息如下所示（如果课程不存在：输出为空白）：" << endl;
	vector<course>a;
	course c;
	int k(0);
	for (int i = 0; i <m_a.size(); ++i) {
		for (int j = 0; j <m_a[i].m_cs.size(); ++j) {
			if (m_a[i].m_cs[j].m_course == s) {
			c.m_ID = m_a[i].m_ID;
			c.m_name=m_a[i].m_name;
			c.m_number = m_a[i].m_class;
			c.m_course = s;
			c.m_score = m_a[i].m_cs[j].m_score;
			a.push_back(c);
			++k;
			}
		}
	}
	system("pause");
	for (int i = 0; i < a.size()-1; ++i) {
		for (int j = a.size() - 1; j > i; --j) {
			if (a[j].m_score > a[j - 1].m_score)
				swap(a[j], a[j - 1]);
		}
	}
	ofstream outfile;
	outfile.open("student2.txt", ios::app);
	if (!outfile.is_open()) {
		cout << "student2.txt文件未打开！" << endl;
	}
	else {
		cout << "student2.txt文件已打开！" << endl;
	}
	cout << '\t' << "#学号(ID)" << '\t' << "姓名" << '\t' << "班级" << '\t' << "课程名称" << '\t' << "成绩" << '\n';
	outfile<< '\t' << "#学号(ID)" << '\t' << "姓名" << '\t' << "班级" << '\t' << "课程名称" << '\t' << "成绩" << '\n';
	for (auto& i : a) {
		cout << '\t' << i.m_ID << '\t' << i.m_name << '\t' << i.m_number << '\t' << i.m_course << '\t' << i.m_score << '\n';
		outfile << '\t' << i.m_ID << '\t' << i.m_name << '\t' << i.m_number << '\t' << i.m_course << '\t' << i.m_score << '\n';
	}
	outfile.close();
}
void manage::search4() {
	ofstream outfile;
	outfile.open("student2.txt", ios::app);
	if (!outfile.is_open()) {
		cout << "student2.txt文件未打开！" << endl;
	}
	else {
		cout << "student2.txt文件已打开！" << endl;
	}
	cout << "查找到的信息如下所示：" << endl;
	vector<student>vi;
	for (int i = 0; i < m_a.size(); ++i) {
		vi.push_back(m_a[i]);
	}
	for (int i = 0; i < vi.size() - 1; ++i) {
		for (int j = vi.size() - 1; j > i; --j) {
			if (vi[j].m_completed > vi[j - 1].m_completed) {
				swap(vi[j], vi[j - 1]);
			}
		}
	}
	for (int i = 0; i <vi.size(); ++i) {
		cout << '\t' <<"#学号(ID)"<<'\t'<< "姓名"<<'\t'<<"班级" << '\t'<<"专业" <<'\t'<< "已修学分" << '\n';
		outfile<< '\t' << "#学号(ID)" << '\t' << "姓名" << '\t' << "班级" << '\t' << "专业" << '\t' << "已修学分" << '\n';
		cout <<'\t'<< vi[i].m_ID<<'\t'<< vi[i].m_name<<'\t'<< vi[i].m_class <<'\t'<<vi[i].m_major<<'\t'<< vi[i].m_completed<<'\n';
		outfile<<'\t' << vi[i].m_ID << '\t' << vi[i].m_name << '\t' << vi[i].m_class << '\t' << vi[i].m_major << '\t' << vi[i].m_completed << '\n';
		cout << '\t' << "课程" << '\t' << "分数" << '\n';
		outfile << '\t' << "课程" << '\t' << "分数" << '\n';
		for (int j = 0; j <vi[i].m_cs.size(); ++j) {
			cout << '\t' << vi[i].m_cs[j].m_course <<'\t'<< vi[i].m_cs[j].m_score << '\n';
			outfile << '\t' << vi[i].m_cs[j].m_course << '\t' << vi[i].m_cs[j].m_score << '\n';
		}
		cout << "---------------------------------------------------------\n";
		outfile << "---------------------------------------------------------\n";
	}
	outfile.close();
}
void manage::statistic1() {
	double average = 0;//平均数
	double dev = 0;//标准差
	double pass = 0;//合格率
	double sum = 0;
	int k = 0;
	int n = 0;
	int q = 0;
	vector<string>a;
	ifstream ifs3;
	ifs3.open("module.txt", ios::in);
	if (!ifs3.is_open()) {
		cout << "module.txt文件未打开！" << endl;
	}
	string m_number;
	string m_course;
	double m_credit;
	string buf3;
	while (getline(ifs3, buf3))
	{
		if (buf3 == "#END")break;
		if (buf3[0] < '0' || buf3[0]>'9')continue;
		istringstream is(buf3);
		is >> m_number >> m_course >> m_credit;
		a.push_back(m_course);
	}
	ifs3.close();
	ofstream outfile;
	outfile.open("student2.txt", ios::app);
	if (!outfile.is_open()) {
		cout << "student2.txt文件未打开！" << endl;
	}
	string s;
	cout << "输入你想查找的班级：（如果不显示，则不存在）" << endl;
	cin >> s;
	while (1) {
		vector<int>b;
		for (int i = 0; i < m_a.size(); ++i) {
			if (m_a[i].m_class == s) {
				for (int j = 0; j < m_a[i].m_cs.size(); ++j) {
					if (m_a[i].m_cs[j].m_course == a[k]) {
						sum += m_a[i].m_cs[j].m_score;
						b.push_back(m_a[i].m_cs[j].m_score);
						++n;
					}
				}
			}
		}
		average = sum / n;
		for (int m = 0; m < b.size(); ++m) {
			dev += pow(b[m] - average, 2);
		}
		dev = sqrt(dev / n);
		cout << "课程名称：" << '\t' << a[k] << '\n';
		outfile << "课程名称：" << '\t' << a[k] << '\n';
		cout << "该课程的平均成绩：" << '\t' << average << '\n';
		outfile << "该课程的平均成绩：" << '\t' << average << '\n';
		cout << "该课程的标准差：" << '\t' << dev << '\n';
		outfile << "该课程的标准差：" << '\t' << dev << '\n';
		cout << "该门课不及格的学生信息如下所示：" << '\n';
		outfile << "该门课不及格的学生信息如下所示：" << '\n';
		for (int i = 0; i < m_a.size(); ++i) {
			if (m_a[i].m_class == s) {
				for (int j = 0; j < m_a[i].m_cs.size(); ++j) {
					if (m_a[i].m_cs[j].m_course == a[k]) {
						if (m_a[i].m_cs[j].m_score < 60) {
							cout << m_a[i].m_name << '\n';
							++q;
						}
					}
				}
			}
		}
		cout << "该课程的合格率：" << (double)(n - q) / n << '\n';
		outfile << "该课程的合格率：" << (double)(n - q) / n << '\n';
		cout << "---------------------------------------------------------\n";
		outfile << "---------------------------------------------------------\n";
		++k;
		sum = 0;
		dev = 0;
		n = 0;
		q = 0;
		if (k == 25) break;
	}
}
	void manage::statistic2(){
	ofstream outfile;
	outfile.open("student2.txt", ios::app);
	if (!outfile.is_open()) {
		cout << "student2.txt文件未打开！" << endl;
	}
	else {
		cout << "student2.txt文件已打开！" << endl;
	}
	rank();
	cout << '\t' << "学号" << '\t' << "姓名" << '\t' << "班级" << '\t'<<"需要完成的总学分"<<'\t' << "完成的总学分" << '\t' << "未修学分"
		<< '\t' << "不及格的课程数" << '\n';
	outfile<< '\t' << "#学号(ID)" << '\t' << "姓名" << '\t' << "班级" << '\t' << "需要完成的总学分" << '\t' << "完成的总学分" << '\t' << "未修学分"
		<< '\t' << "不及格的课程数" << '\n';
	for (int i = 0; i < m_a.size(); ++i) {
		cout << '\t' << m_a[i].m_ID << '\t' << m_a[i].m_name << '\t' << m_a[i].m_class << '\t' << m_a[i].m_total << '\t' << m_a[i].m_completed
			<< '\t' << m_a[i].m_uncompleted<< '\t' << m_a[i].m_failed << '\n';
		outfile<< '\t' << m_a[i].m_ID << '\t' << m_a[i].m_name << '\t' << m_a[i].m_class << '\t' << m_a[i].m_total << '\t' << m_a[i].m_completed
			<< '\t' << m_a[i].m_uncompleted << '\t' << m_a[i].m_failed << '\n';
	}
	outfile<< "#END" << endl;
	outfile.close();
}
void manage::fuzzy_search() {
	string c;
	char r;
	do {
		cout << "请输入你想查询的学生名字的一部分:" << endl;
		cin >> c;
		vector<student>vi;
		char a;
		cout << '\t' << "学号" << '\t' << "姓名" << '\t' << "班级" << '\t' << "专业"
			<< '\t' << "需完成的总学分" << '\t' << "已完成的学分" << '\t' << "不及格科目" << '\t' << "未修学分" << endl;
		for (int i = 0; i < m_a.size(); ++i) {
			for (int j = 0; j < m_a[i].m_name.size(); ++j) {
				if (m_a[i].m_name.find(c) != string::npos) {
					cout << '\t' << m_a[i].m_ID << '\t' << m_a[i].m_name << '\t' << m_a[i].m_class << '\t' << m_a[i].m_major
						<< '\t' << m_a[i].m_total << '\t' << m_a[i].m_completed << '\t' << m_a[i].m_failed << '\t' << m_a[i].m_uncompleted << endl;
					vi.push_back(m_a[i]);
					break;
				}
			}
		}
		cout << "你想进行二次选择吗？Y/N" << endl;
		cin >> a;
		if (a == 'Y' || a == 'y') {
			cout << "请选择你想查询的学生姓名:" << endl;
			cin >> c;
			for (int i = 0; i < vi.size(); ++i) {
				if (vi[i].m_name.find(c) != string::npos) {
					cout << '\t' << vi[i].m_name << '\t' << vi[i].m_ID << '\t' << vi[i].m_class << '\t' << vi[i].m_major
						<< '\t' << vi[i].m_total << '\t' << vi[i].m_completed << '\t' << vi[i].m_failed << '\t' << vi[i].m_uncompleted << endl;
					break;
				}
			}
		}
		cout << "你想要继续模糊查询吗？Y/N" << endl;
		cin >> r;
	} while (r == 'Y' || r == 'y');
}
void manage::write_in() {
	ofstream outfile;
	outfile.open("score.txt", ios::out);
	if (!outfile.is_open()) {
		cout << "score.txt文件未打开！" << endl;
	}
	outfile << '\t' << "#学号" << '\t' << "姓名" << '\t' << "课程名称" << '\t' << "成绩" << endl;
	for (int i = 0; i < m_a.size(); ++i) {
		for (int j = 0; j < m_a[i].m_cs.size(); ++j) {
			outfile << '\t' << m_a[i].m_cs[j].m_ID << '\t' << m_a[i].m_cs[j].m_name << '\t' << m_a[i].m_cs[j].m_course <<
				'\t' << m_a[i].m_cs[j].m_score << '\n';
		}
	}
	outfile << "#END";
	cout << "已将信息写入！" << endl;
	outfile.close();
}