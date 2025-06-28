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
		cout << "student.txt�ļ�δ�򿪣�" << endl;
	}
	else {
		cout << "student.txt�ļ��Ѵ򿪣�" << endl;
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
		cout << "score.txt�ļ�δ�򿪣�" << endl;
	}
	else {
		cout << "score.txt�ļ��Ѵ򿪣�" << endl;
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
		cout << "module.txt�ļ�δ�򿪣�" << endl;
	}
	else {
		cout << "module.txt�ļ��Ѵ򿪣�" << endl;
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
		cout << "����������ɾ����ѧ������:" << endl;
		cin >> s;
		cout << "��ȷ��Ҫɾ�����ѧ������Ϣ��?Y/N" << endl;
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
				cout << "��ѧ�������ڣ�" << endl;
			}
			else {
				m_a.pop_back();
				cout << "��ѧ����Ϣ��ɾ����" << endl;
			}
		}
	 }
	void manage::change() {
		string s, t;
		char c;
		cout << "�����������޸���Ϣ��ѧ��������" << endl;
		cin >> s;
		double score;
		do {
			cout << "�����������޸ĵĿγ�(���δ��ʾ�޸ĳɹ�����ѧ����γ̲�����)��" << endl;
			cin >> t;
			for (int i = 0; i <m_a.size(); ++i) {
				if (m_a[i].m_name == s) {
					for (int j = 0; j<m_a[i].m_cs.size(); ++j) {
						if (m_a[i].m_cs[j].m_course == t) {
							cout << "�����������޸ĳɼ���" << endl;
							cin >> score;
							m_a[i].m_cs[j].m_score = score;
							cout << "�޸ĳɹ���" << endl;
						}
					}
				}
			}
			system("pause");
			cout << "�㻹������޸���Y/N" << endl;
			cin >> c;
		} while (c == 'Y' || c == 'y');
	}
	void manage::add() {
		string s;
		course a;
		char c, h;
		do {
			cout << "����������������Ŀ�ͳɼ���ѧ�����֣������δ��ʾ����ѧ�������ڣ�" << endl;
			cin >> s;
			do {
				for (int i = 0; i <m_a.size(); ++i) {
					if (m_a[i].m_name == s) {
						cout << "�������������ӵĿ�Ŀ���ƣ�" << endl;
						cin >> a.m_course;
						cout << "�����������Ŀ�ķ�����" << endl;
						cin >> a.m_score;
						a.m_ID = m_a[i].m_ID;
						a.m_name = m_a[i].m_name;
						ifstream ifs3;
						ifs3.open("module.txt", ios::in);
						if (!ifs3.is_open()) {
							cout << "module.txt�ļ�δ�򿪣�" << endl;
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
				cout << "�㻹��������Ӹ�ѧ���Ŀ�Ŀ�ͷ�����Y/N" << endl;
				cin >> c;
			} while (c == 'Y' || c == 'y');
			cout << "�㻹��������һ��ѧ���Ŀ�Ŀ�ͷ�����Y/N" << endl;
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
	cout << "������������ҵ�ѧ��������" << endl;
	cin >> s;
	cout << "���ҵ�����Ϣ������ʾ(���ѧ�������ڣ����Ϊ�հ�)��" << endl;
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
	cout << "������������ҵİ�ţ�" << endl;
	cin >> s;
	cout << "���ҵ�����Ϣ������ʾ������༶�����ڣ����Ϊ�հף���" << endl;
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
		cout << "student2.txt�ļ�δ�򿪣�" << endl;
	}
	for (int i = 0; i <vi.size(); i++) {
		if (vi[i].m_class == s) {
			cout << '\t' << "����" << '\t' << "����ѧ��" << '\n';
			cout << '\t' << vi[i].m_name << '\t' << vi[i].m_completed << '\n';
			cout << '\t' << "�γ�" << '\t' << "����" << '\n';
			outfile << '\t' << "����" << '\t' << "����ѧ��" << '\n';
			outfile << '\t' << vi[i].m_name << '\t' << vi[i].m_completed << '\n';
			outfile << '\t' << "�γ�" << '\t' << "����" << '\n';
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
	cout << "��������Ҫ���ҵĿγ����ƣ�" << endl;
	cin >> s;
	cout << "���ҵ�����Ϣ������ʾ������γ̲����ڣ����Ϊ�հף���" << endl;
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
		cout << "student2.txt�ļ�δ�򿪣�" << endl;
	}
	else {
		cout << "student2.txt�ļ��Ѵ򿪣�" << endl;
	}
	cout << '\t' << "#ѧ��(ID)" << '\t' << "����" << '\t' << "�༶" << '\t' << "�γ�����" << '\t' << "�ɼ�" << '\n';
	outfile<< '\t' << "#ѧ��(ID)" << '\t' << "����" << '\t' << "�༶" << '\t' << "�γ�����" << '\t' << "�ɼ�" << '\n';
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
		cout << "student2.txt�ļ�δ�򿪣�" << endl;
	}
	else {
		cout << "student2.txt�ļ��Ѵ򿪣�" << endl;
	}
	cout << "���ҵ�����Ϣ������ʾ��" << endl;
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
		cout << '\t' <<"#ѧ��(ID)"<<'\t'<< "����"<<'\t'<<"�༶" << '\t'<<"רҵ" <<'\t'<< "����ѧ��" << '\n';
		outfile<< '\t' << "#ѧ��(ID)" << '\t' << "����" << '\t' << "�༶" << '\t' << "רҵ" << '\t' << "����ѧ��" << '\n';
		cout <<'\t'<< vi[i].m_ID<<'\t'<< vi[i].m_name<<'\t'<< vi[i].m_class <<'\t'<<vi[i].m_major<<'\t'<< vi[i].m_completed<<'\n';
		outfile<<'\t' << vi[i].m_ID << '\t' << vi[i].m_name << '\t' << vi[i].m_class << '\t' << vi[i].m_major << '\t' << vi[i].m_completed << '\n';
		cout << '\t' << "�γ�" << '\t' << "����" << '\n';
		outfile << '\t' << "�γ�" << '\t' << "����" << '\n';
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
	double average = 0;//ƽ����
	double dev = 0;//��׼��
	double pass = 0;//�ϸ���
	double sum = 0;
	int k = 0;
	int n = 0;
	int q = 0;
	vector<string>a;
	ifstream ifs3;
	ifs3.open("module.txt", ios::in);
	if (!ifs3.is_open()) {
		cout << "module.txt�ļ�δ�򿪣�" << endl;
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
		cout << "student2.txt�ļ�δ�򿪣�" << endl;
	}
	string s;
	cout << "����������ҵİ༶�����������ʾ���򲻴��ڣ�" << endl;
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
		cout << "�γ����ƣ�" << '\t' << a[k] << '\n';
		outfile << "�γ����ƣ�" << '\t' << a[k] << '\n';
		cout << "�ÿγ̵�ƽ���ɼ���" << '\t' << average << '\n';
		outfile << "�ÿγ̵�ƽ���ɼ���" << '\t' << average << '\n';
		cout << "�ÿγ̵ı�׼�" << '\t' << dev << '\n';
		outfile << "�ÿγ̵ı�׼�" << '\t' << dev << '\n';
		cout << "���ſβ������ѧ����Ϣ������ʾ��" << '\n';
		outfile << "���ſβ������ѧ����Ϣ������ʾ��" << '\n';
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
		cout << "�ÿγ̵ĺϸ��ʣ�" << (double)(n - q) / n << '\n';
		outfile << "�ÿγ̵ĺϸ��ʣ�" << (double)(n - q) / n << '\n';
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
		cout << "student2.txt�ļ�δ�򿪣�" << endl;
	}
	else {
		cout << "student2.txt�ļ��Ѵ򿪣�" << endl;
	}
	rank();
	cout << '\t' << "ѧ��" << '\t' << "����" << '\t' << "�༶" << '\t'<<"��Ҫ��ɵ���ѧ��"<<'\t' << "��ɵ���ѧ��" << '\t' << "δ��ѧ��"
		<< '\t' << "������Ŀγ���" << '\n';
	outfile<< '\t' << "#ѧ��(ID)" << '\t' << "����" << '\t' << "�༶" << '\t' << "��Ҫ��ɵ���ѧ��" << '\t' << "��ɵ���ѧ��" << '\t' << "δ��ѧ��"
		<< '\t' << "������Ŀγ���" << '\n';
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
		cout << "�����������ѯ��ѧ�����ֵ�һ����:" << endl;
		cin >> c;
		vector<student>vi;
		char a;
		cout << '\t' << "ѧ��" << '\t' << "����" << '\t' << "�༶" << '\t' << "רҵ"
			<< '\t' << "����ɵ���ѧ��" << '\t' << "����ɵ�ѧ��" << '\t' << "�������Ŀ" << '\t' << "δ��ѧ��" << endl;
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
		cout << "������ж���ѡ����Y/N" << endl;
		cin >> a;
		if (a == 'Y' || a == 'y') {
			cout << "��ѡ�������ѯ��ѧ������:" << endl;
			cin >> c;
			for (int i = 0; i < vi.size(); ++i) {
				if (vi[i].m_name.find(c) != string::npos) {
					cout << '\t' << vi[i].m_name << '\t' << vi[i].m_ID << '\t' << vi[i].m_class << '\t' << vi[i].m_major
						<< '\t' << vi[i].m_total << '\t' << vi[i].m_completed << '\t' << vi[i].m_failed << '\t' << vi[i].m_uncompleted << endl;
					break;
				}
			}
		}
		cout << "����Ҫ����ģ����ѯ��Y/N" << endl;
		cin >> r;
	} while (r == 'Y' || r == 'y');
}
void manage::write_in() {
	ofstream outfile;
	outfile.open("score.txt", ios::out);
	if (!outfile.is_open()) {
		cout << "score.txt�ļ�δ�򿪣�" << endl;
	}
	outfile << '\t' << "#ѧ��" << '\t' << "����" << '\t' << "�γ�����" << '\t' << "�ɼ�" << endl;
	for (int i = 0; i < m_a.size(); ++i) {
		for (int j = 0; j < m_a[i].m_cs.size(); ++j) {
			outfile << '\t' << m_a[i].m_cs[j].m_ID << '\t' << m_a[i].m_cs[j].m_name << '\t' << m_a[i].m_cs[j].m_course <<
				'\t' << m_a[i].m_cs[j].m_score << '\n';
		}
	}
	outfile << "#END";
	cout << "�ѽ���Ϣд�룡" << endl;
	outfile.close();
}