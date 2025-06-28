#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<algorithm> 
#include<stdlib.h>
#include<memory.h>
using namespace std;
//���룺1 9  12 14 15  -1 ����¹
//���룺20 22 11 -1 ��
string animal[] = { "���","����","����","����","����¹","��","��Ǯ��" };

string feature[] = { "��ë","����","����ë","���","���µ�","����","��Ȯ��","��צ","�۾���ǰ��","����","��ۻ","�ƺ�ɫ","�а��ߵ�",

//    0        1      2       3      4         5       6       7         8        9      10       11    12

	 "�к�ɫ����","����","����","�����","����Ӿ","�ڰ���ɫ","�Ʒ�","������","����","��ʳ��","����",

	//       13        14      15     16       17      18        19     20      21      22      23    

		 "���","������","����","����","����¹","��","��Ǯ��" };

//     24     25     26    27       28      29    30

typedef struct {  //��Ź���Ľṹ�� 
	int relation[6];   //��ϵ 
	int name;		  //������  
}Rule;

typedef struct { // ��ſ��ܵĶ��� 
	int animal;       // name 
	float confidence; //���Ŷ� = ����������� / ����������;
	int site;         // ��rule�е�λ��
	int num;          // ����������� 
	int size;         // ��animal�������������� 
}Result;

vector<Result> result;
// �����   -1 ���������� 
Rule rule[15] = { {{0,-1},20},{{1,-1},20},{{2,-1},21},{{3,4,-1},21},{{5,-1},22},
		{{6,7,8,-1},22},{{20,9,-1},23},{{20,10,-1},23},{{20,22,11,12,-1},30},
		{{20,22,11,13,-1},29},{{23,14,15,12,-1},28},{{23,13,-1},27},
		{{21,14,15,16,18,-1},26},{{21,19,-1},25},{{21,17,18,16,-1},24} };

int flag[24] = { 0 };//��Ǹ��������Ƿ�ѡ��

int IsAnimal(int a);
int change_speices(); // ����������� ������Ĺ���������� 
int fnum();   // ��ȡflag��ǵ���Ŀ 
int z_inference(); //�������� 
int category(); // ���������� 
int cal_confi(); // �������Ŷ� 
int r_inference(); //�������� 
void input();   //���� 
void menu();   //ѡ��˵� 
bool Compare(const Result& a, const Result& b) {
	return a.confidence > b.confidence;
}
void Rsort(vector<Result>& r) {
	sort(r.begin(), r.end(), Compare);
	return;
}//��������
//ѡ�������˵� 
void menu() {
	for (int i = 0; i < 24; i++) {
		if (i % 4 == 0 && i != 0)
			cout << endl;
		cout << setiosflags(ios::left) << setw(3) << i << ".";
		cout << setiosflags(ios::left) << setw(15) << feature[i];
	}
	memset(flag, 0, sizeof(flag));//��ʼ����־λ
}
//��������ֵ  ѡ������ 
void input() {
	for (int i = 0; i < 24; i++)
		flag[i] = 0;
	int  ti = 0;
	cout << "\ninput selection(end -1):";
	while (ti != -1) {
		cin >> ti;
		if (ti >= 0 && ti <= 23)
			flag[ti] = 1;
		else if (ti != -1) {
			cout << "Input error! Please enter a number between 0~23!" << endl;  //notanimal=25
			cin.clear();		//��������������
			cin.sync(); 		//������뻺����
			cout << "Please continue to enter: ";
		}
	}
}
//��ĳ���� ������ĳ������ 
int IsAnimal(int a) {
	if (a >= 24 && a <= 30)
		return 1;
	return 0;
}
// �ж��Ƿ�ĳһ������ 
int IsAnimal_speices(int a) {
	if (a >= 20 && a <= 23)
		return 1;
	return 0;
}
// ����flag�����б�ǵ����� 
int fnum() {
	int fum = 0;
	for (int i = 0; i < 24; i++)
		if (flag[i] == 1)
			fum++;
	return fum;
}
//�����ӡ�������
int category() {
	bool k;
	int count = 0;
	for (int i = 20; i < 24; i++) {
		k = false;
		if (flag[i] == 1) {
			k = true;
			count++;
			if (count == 1)
				cout << "Can't reason about specific animals! Category is ";
			cout << setiosflags(ios::left) << setw(10) << feature[i];
		}
	}
	cout << endl;
	if (!k)
		cout << "Sorry! No such animal in the system" << endl;
	return 1;
}

// change_speices --�� flag �����仯  �����Ƿ��� �������� �����õ�����ʵ ���
//�� ��ë --�����鶯��  �ͽ�flag�в��鶯�������һ ������ë��һ����flag��0
int change_speices() {
	int i, j, k, ti;
	bool t;
	int temp[23] = { 0 }; //��ʱ 
	int f[23] = { 0 }; // ���ʹ�ù���flag[] &  < 20  20 ������ 
	for (i = 0; i < 8; i++) { // rule ǰ8�� ���� 
		t = true;
		j = 0;
		ti = rule[i].relation[j];
		while (ti != -1) {
			if (flag[ti] == 1) temp[ti] = 1;
			else {
				memset(temp, 0, sizeof(temp));
				t = false;
				break;
			}
			j++;
			ti = rule[i].relation[j];
		}
		if (t) {
			for (int k = 0; k <= 20; k++)
				if (temp[k] == 1)
					f[k] = 1;
			flag[rule[i].name] = 1;
		}
		memset(temp, 0, sizeof(temp));
	}
	// ���������ʵ  ��ɾ��  ������� 
	for (i = 0; i <= 20; i++)
		if (f[i] == 1)
			flag[i] = 0;
	return 1;
}
// ���¼������Ŷ� 
int cal_confi() {
	for (int i = 0; i < result.size(); i++) {
		for (int j = 8; j < 15; j++) {
			if (result[i].animal == rule[j].name) {
				result[i].confidence = 1.0 * result[i].num / result[i].size;
				break;
			}
		}
	}
	return 1;
}


//����  ˫������ -- ����������ȥ ��ʵ���� ������������ 
int z_inference() {
	int ti, num;
	int i, j;
	int fum = fnum();
	cout << endl;
	for (i = 8; i < 15; i++) {  //������� 
		Result temp;
		j = 0; num = 0;
		ti = rule[i].relation[j];
		while (ti != -1) {
			if (flag[ti] == 1) num++;
			j++;
			ti = rule[i].relation[j];
		}
		// ��ʱ j  ������rule[i]�����е������� 
		if (num != 0 && fum <= j) {  //  ����������С�ڵ��ڵ���� ����flag�����б��λ��Ŀ���ڴ˶�����������򲻷���result�� 
			if (IsAnimal(rule[i].name)) { // �Ǿ���Ķ��� 
				temp.animal = rule[i].name;
				int size = j; // rule[i]�����е�������
				temp.size = size;
				temp.confidence = 1.0 * num / size;
				temp.site = i;
				temp.num = num;
				result.push_back(temp);
			}
		}
	}

	if (!result.empty())
		Rsort(result);  //�����ŶȴӸߵ������� 


	//��ӡ������vector
	for (vector<Result>::iterator it = result.begin(); it != result.end(); ++it) {
		cout << setiosflags(ios::left) << setw(10) << feature[(*it).animal] << " ";
		cout << (*it).confidence << " " << endl;
	}
	cout << endl;

	// �ж� -- δѯ�� --�������� �� 
	if (result.empty()) { // �����������޷����κ�һ��������  ����û�����ֶ���  ������һ�ֶ������ (ϵͳ���޴˶����������  
		category();
	}
	else if (result.front().confidence == 1.0) { // ���ܸ��������պ������  ����������û���� 
		cout << "This animal is " << feature[result.front().animal] << endl;
		result.clear(); // ���  
		return 1;
	}
	else // ����������ȫ  ��������  ѯ������ 
		r_inference();
}
//������������  ���뷴������ 
int r_inference() {
	if (result.size() == 0) {
		Result temp;
		int k;
		cout << "��ʼ��������" << endl;
		cout << "ѡ������Ҫ����Ķ��1.��죻2.�����̣�3.����4.����5.����¹��6.����7.��Ǯ��" << endl;
		cin >> k;
		//cout << k;
		k--;
		temp.animal = 24 + k;
		temp.confidence = 0;

		if (k == 0) { temp.size = 4; temp.site = 14; }
		else if (k == 1) { temp.size = 2;  temp.site = 13; }
		else if (k == 2) { temp.size = 5; temp.site = 12; }
		else if (k == 3) { temp.size = 2;  temp.site = 11; }
		else if (k == 4) { temp.size = 4;  temp.site = 10; }
		else if (k == 5) { temp.size = 4; temp.site = 9; }
		else if (k == 6) {
			temp.size = 4; temp.site = 8;
		}
		//temp.size = 0;
		temp.num = 0;
		result.push_back(temp);
		for (int l = 0; l < 24; l++) {
			flag[0] = 0;
		}

	}
	vector<Result>::iterator it = result.begin();
	int enquire[24];  // �������ѯ�ʹ����������� 0 N  1 Y 2 D��0 ����û�д����� 1 ������  2 �����������֪���� 
	memset(enquire, -1, sizeof(enquire));//�����ʼ����Ϊ-1

	for (int i = 0; i < result.size();) {// �����Ŷ���߿�ʼѯ��
		bool in_i = true; // i ++ �ı�� 
		//cout <<"�˶���������"<< result[i].size << endl;;
		int  nu = result[i].size;
		for (int j = 0; j < nu; j++) {  // ѯ�� δ˵�� ���� 
			//cout << flag[rule[result[i].site].relation[j]]<<endl;
			if (flag[rule[result[i].site].relation[j]] == 0) {
				int en = rule[result[i].site].relation[j];
				char c = ' ';
				if (enquire[en] == -1) { // ������δ��ѯ�ʹ� �����ѯ����� ����ֱ���жϴ��� 
					cout << "Does this animal have this characteristic?" << feature[rule[result[i].site].relation[j]] << endl;
					cout << "Y(y) or N(n) or D(don't know) : ";
					cin >> c;
					while (c != 'Y' && c != 'y' && c != 'N' && c != 'n' && c != 'D' && c != 'd') {
						cout << "Please enter Y(y) or N(n) or D(d)!" << endl;
						cin >> c;
					};
				}

				if (enquire[en] == 1 || c == 'Y' || c == 'y') { //�д�����  �ı����Ŷ�
					result[i].num++;
					enquire[en] = 1;
				}
				else if (enquire[en] == 0 || c == 'N' || c == 'n') { // û�д�����  ֱ��ȥ��
					enquire[en] = 0;
					result.erase(it + i);  // eraseɾ���� i������  ����ɾ������Ԫ�أ�����������ָ��ɾ��֮ǰԪ�غ�ĵ�һ��Ԫ�أ�
					in_i = false;  // ��� ������Ԫ�� �� i������ 
					if (result.empty()) //  result Ϊ�� ������ �˳� 
						category();
					break;
				}
				else if (enquire[en] == 2 || c == 'D' || c == 'd') { enquire[en] = 2; }  // ��ȷ������֪��  ���ŶȲ��ı� 	
			}
		}
		if (in_i)
			++i;
	}

	if (!result.empty()) {
		// �ı����Ŷ� 
		cal_confi();
		if (result.size() > 1) //��������
			Rsort(result);

		//�ж� -- ѯ�ʺ�  -- ˫������� 
		if (result.front().confidence == 1.0) {
			cout << "This animal is " << feature[result.front().animal] << endl;
		}
		else {
			cout << "Possible animals (confidence from big to small) :";
			for (vector<Result>::iterator it = result.begin(); it != result.end(); ++it) {
				cout << setiosflags(ios::left) << setw(10) << feature[(*it).animal] << " ";
				cout << (*it).confidence << " " << endl;
			}
			cout << endl;
		}
		result.clear(); // ��� 
	}

	return 1;
}
int main() {
	char q = 0;
	int a = 1;
	while (q != 'N' && q != 'n') {
		cout << "��ѡ��ʹ���������������������1����������2����������" << endl;
		cin >> a;

		if (a == 1) {
			menu();
			input();
			change_speices();
			z_inference();
		}
		else if (a == 2) {
			r_inference();
		}
		cout << "\n������(Y/N)" << endl;
		cin >> q;
		system("cls");
	}
	return 0;
}
