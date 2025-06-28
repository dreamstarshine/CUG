#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<algorithm> 
#include<stdlib.h>
#include<memory.h>
using namespace std;
//输入：1 9  12 14 15  -1 长颈鹿
//输入：20 22 11 -1 虎
string animal[] = { "企鹅","海燕","鸵鸟","斑马","长颈鹿","虎","金钱豹" };

string feature[] = { "有毛","产奶","有羽毛","会飞","会下蛋","吃肉","有犬齿","有爪","眼睛盯前方","有蹄","反刍","黄褐色","有暗斑点",

//    0        1      2       3      4         5       6       7         8        9      10       11    12

	 "有黑色条纹","长脖","长腿","不会飞","会游泳","黑白两色","善飞","哺乳类","鸟类","肉食类","蹄类",

	//       13        14      15     16       17      18        19     20      21      22      23    

		 "企鹅","信天翁","鸵鸟","斑马","长颈鹿","虎","金钱豹" };

//     24     25     26    27       28      29    30

typedef struct {  //存放规则的结构体 
	int relation[6];   //关系 
	int name;		  //推理结果  
}Rule;

typedef struct { // 存放可能的动物 
	int animal;       // name 
	float confidence; //置信度 = 满足的特性数 / 所含特征数;
	int site;         // 在rule中的位置
	int num;          // 满足的特征数 
	int size;         // 此animal的所含总特征数 
}Result;

vector<Result> result;
// 规则库   -1 代表规则结束 
Rule rule[15] = { {{0,-1},20},{{1,-1},20},{{2,-1},21},{{3,4,-1},21},{{5,-1},22},
		{{6,7,8,-1},22},{{20,9,-1},23},{{20,10,-1},23},{{20,22,11,12,-1},30},
		{{20,22,11,13,-1},29},{{23,14,15,12,-1},28},{{23,13,-1},27},
		{{21,14,15,16,18,-1},26},{{21,19,-1},25},{{21,17,18,16,-1},24} };

int flag[24] = { 0 };//标记各个特征是否选择

int IsAnimal(int a);
int change_speices(); // 将可以推理出 动物类的规则推理出来 
int fnum();   // 获取flag标记的数目 
int z_inference(); //正向推理 
int category(); // 输出动物类别 
int cal_confi(); // 计算置信度 
int r_inference(); //反向推理 
void input();   //输入 
void menu();   //选择菜单 
bool Compare(const Result& a, const Result& b) {
	return a.confidence > b.confidence;
}
void Rsort(vector<Result>& r) {
	sort(r.begin(), r.end(), Compare);
	return;
}//进行排序
//选择特征菜单 
void menu() {
	for (int i = 0; i < 24; i++) {
		if (i % 4 == 0 && i != 0)
			cout << endl;
		cout << setiosflags(ios::left) << setw(3) << i << ".";
		cout << setiosflags(ios::left) << setw(15) << feature[i];
	}
	memset(flag, 0, sizeof(flag));//初始化标志位
}
//特征输入值  选择数字 
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
			cin.clear();		//清除流错误错误标记
			cin.sync(); 		//清空输入缓冲区
			cout << "Please continue to enter: ";
		}
	}
}
//是某动物 而不是某种物种 
int IsAnimal(int a) {
	if (a >= 24 && a <= 30)
		return 1;
	return 0;
}
// 判断是否某一物种类 
int IsAnimal_speices(int a) {
	if (a >= 20 && a <= 23)
		return 1;
	return 0;
}
// 返回flag数组中标记的总数 
int fnum() {
	int fum = 0;
	for (int i = 0; i < 24; i++)
		if (flag[i] == 1)
			fum++;
	return fum;
}
//输出打印物种类别
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

// change_speices --》 flag 发生变化  推理是否有 物种种类 并将用到的事实 清空
//如 有毛 --》哺乳动物  就将flag中哺乳动物的项置一 并将有毛这一特征flag清0
int change_speices() {
	int i, j, k, ti;
	bool t;
	int temp[23] = { 0 }; //临时 
	int f[23] = { 0 }; // 标记使用过的flag[] &  < 20  20 哺乳类 
	for (i = 0; i < 8; i++) { // rule 前8个 规则 
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
	// 推理过的事实  则删除  保留结果 
	for (i = 0; i <= 20; i++)
		if (f[i] == 1)
			flag[i] = 0;
	return 1;
}
// 重新计算置信度 
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


//推理  双向推理 -- 正向推理不下去 事实不够 采用逆向推理 
int z_inference() {
	int ti, num;
	int i, j;
	int fum = fnum();
	cout << endl;
	for (i = 8; i < 15; i++) {  //检查规则库 
		Result temp;
		j = 0; num = 0;
		ti = rule[i].relation[j];
		while (ti != -1) {
			if (flag[ti] == 1) num++;
			j++;
			ti = rule[i].relation[j];
		}
		// 此时 j  保存则rule[i]所含有的特征数 
		if (num != 0 && fum <= j) {  //  给定特征数小于等于的情况 （即flag数组中标记位数目大于此动物的特征数则不放入result） 
			if (IsAnimal(rule[i].name)) { // 是具体的动物 
				temp.animal = rule[i].name;
				int size = j; // rule[i]所含有的特征数
				temp.size = size;
				temp.confidence = 1.0 * num / size;
				temp.site = i;
				temp.num = num;
				result.push_back(temp);
			}
		}
	}

	if (!result.empty())
		Rsort(result);  //对置信度从高到低排序 


	//打印排序后的vector
	for (vector<Result>::iterator it = result.begin(); it != result.end(); ++it) {
		cout << setiosflags(ios::left) << setw(10) << feature[(*it).animal] << " ";
		cout << (*it).confidence << " " << endl;
	}
	cout << endl;

	// 判断 -- 未询问 --正向推理 后 
	if (result.empty()) { // 给定特征数无法用任何一规则推理  可能没有这种动物  可能是一种动物类别 (系统中无此动物，则输出类别）  
		category();
	}
	else if (result.front().confidence == 1.0) { // 可能给的特征刚好推理出  可能特征还没用完 
		cout << "This animal is " << feature[result.front().animal] << endl;
		result.clear(); // 清空  
		return 1;
	}
	else // 特征描述不全  逆向推理  询问特征 
		r_inference();
}
//特征不足推理  进入反向推理 
int r_inference() {
	if (result.size() == 0) {
		Result temp;
		int k;
		cout << "开始逆向推理" << endl;
		cout << "选择你想要推理的动物：1.企鹅；2.信天翁；3.鸵鸟；4.斑马；5.长颈鹿；6.虎；7.金钱豹" << endl;
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
	int enquire[24];  // 用来标记询问过的特征数组 0 N  1 Y 2 D（0 代表没有此特征 1 代表有  2 代表不请楚、不知道） 
	memset(enquire, -1, sizeof(enquire));//数组初始化均为-1

	for (int i = 0; i < result.size();) {// 从置信度最高开始询问
		bool in_i = true; // i ++ 的标记 
		//cout <<"此动物特征数"<< result[i].size << endl;;
		int  nu = result[i].size;
		for (int j = 0; j < nu; j++) {  // 询问 未说明 特征 
			//cout << flag[rule[result[i].site].relation[j]]<<endl;
			if (flag[rule[result[i].site].relation[j]] == 0) {
				int en = rule[result[i].site].relation[j];
				char c = ' ';
				if (enquire[en] == -1) { // 此特征未被询问过 则输出询问语句 否则直接判断处理 
					cout << "Does this animal have this characteristic?" << feature[rule[result[i].site].relation[j]] << endl;
					cout << "Y(y) or N(n) or D(don't know) : ";
					cin >> c;
					while (c != 'Y' && c != 'y' && c != 'N' && c != 'n' && c != 'D' && c != 'd') {
						cout << "Please enter Y(y) or N(n) or D(d)!" << endl;
						cin >> c;
					};
				}

				if (enquire[en] == 1 || c == 'Y' || c == 'y') { //有此特征  改变置信度
					result[i].num++;
					enquire[en] = 1;
				}
				else if (enquire[en] == 0 || c == 'N' || c == 'n') { // 没有此特征  直接去掉
					enquire[en] = 0;
					result.erase(it + i);  // erase删除后 i不自增  就能删除最后的元素（迭代器就是指向删除之前元素后的第一个元素）
					in_i = false;  // 如果 擦除了元素 则 i不自增 
					if (result.empty()) //  result 为空 输出类别 退出 
						category();
					break;
				}
				else if (enquire[en] == 2 || c == 'D' || c == 'd') { enquire[en] = 2; }  // 不确定、不知道  置信度不改变 	
			}
		}
		if (in_i)
			++i;
	}

	if (!result.empty()) {
		// 改变置信度 
		cal_confi();
		if (result.size() > 1) //重新排序
			Rsort(result);

		//判断 -- 询问后  -- 双向推理后 
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
		result.clear(); // 清空 
	}

	return 1;
}
int main() {
	char q = 0;
	int a = 1;
	while (q != 'N' && q != 'n') {
		cout << "请选择使用正向推理或者逆向推理：1、正向推理；2、逆向推理" << endl;
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
		cout << "\n继续？(Y/N)" << endl;
		cin >> q;
		system("cls");
	}
	return 0;
}
