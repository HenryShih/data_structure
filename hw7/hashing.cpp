#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include<cmath>
#define table_size 3331177
using namespace std;

int int2prime[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

struct record{
	int total_cnt;
	int cnt_arr[26];
	string str;
};



int hash_fun(int *cnt_arr){
	int rtv = 0;
	for(int i = 0; i < 26; i++)
		rtv += cnt_arr[i] * i * int2prime[i];
	rtv %= table_size;
	return rtv;
}

vector<record> hash_table[table_size];

int main(int agvc, char **argv){
	ifstream input, target;
	ofstream out;

	input.open(argv[1]);
	target.open(argv[2]);
	out.open(argv[3]);
/*

	cout << "table_size = " << table_size << endl;

	clock_t start = clock();
	cout << "time = " << fixed << setprecision(2) <<(clock()-start)/(float)CLOCKS_PER_SEC << endl;
	cout << "start of program\n";
*/

	string str;
	while(input >> str){
		record tmp = {.total_cnt = 0, .cnt_arr = {0}, .str = str};
		for(int i = 0; i < str.size(); i++){
			tmp.total_cnt++;
			tmp.cnt_arr[str[i] - 'a']++; 
		}
		int index = hash_fun(tmp.cnt_arr);
		hash_table[index].push_back(tmp);
	}
/*
	cout << "time = " << fixed << setprecision(2) << (clock()-start)/(float)CLOCKS_PER_SEC << endl;
	cout << "end of building table\n";
*/

	int cnt_max = -1;
	while(target >> str){
		int total_cnt = 0;
		int cnt_arr[26] = {0};
		for(int i = 0; i < str.size(); i++){
			total_cnt++;
			cnt_arr[str[i] - 'a']++;
		}
		int index = hash_fun(cnt_arr);
		bool flag = false;
		int cnt = 0;
		for(int i = 0; i < hash_table[index].size(); i++){
			record tmp = hash_table[index][i];
			if(total_cnt == tmp.total_cnt){
				bool if_same = true;
				for(int i = 0; i < 26; i++){
					if(cnt_arr[i] != tmp.cnt_arr[i])
						if_same = false;
				}
				if(if_same){
					cnt++;
					flag = true;
					out << tmp.str << " ";
				}
			}
		}
		cnt_max = max(cnt, cnt_max);
		if(!flag)
			out << '0' ;
		out << '\n';
	}
/*
	cout << "time = " << fixed << setprecision(2) << (clock()-start)/(float)CLOCKS_PER_SEC << endl;
	cout << "end of serching\n";

	int cnt_have = 0, cnt_dont_have = 0, max_num = -1;
	for(int i = 0; i < table_size; i++){
		if(!hash_table[i].empty()){
			cnt_have++;
			max_num = max(max_num, (int)hash_table[i].size());
		}
		else
			cnt_dont_have++;
	}

	cout << "with table_size = " << table_size << endl;
	cout << "cnt_have = " << cnt_have << endl;
	cout << "cnt_dont_have = " << cnt_dont_have << endl;
	cout << "max bucket size = " << max_num << endl;
	cout << "max outpue number = " << cnt_max << endl;
*/
	return 0;
}