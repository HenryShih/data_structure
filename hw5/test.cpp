#include<iostream>
#include<fstream>

using namespace std;

int main(){
	ifstream in;
	in.open("sample1.in");
	cout << in.is_open()<< endl;
	int i ,j = 10;
	char garbage[10000];
	int n = 0;
	in >> i >> j;
	cout << i<< j;
	while(in >> i){
		n++;
		cout  << i << endl;
	}

	cout << endl;
	in.close();
	in.open("sample1.in");
	while(in.getline(garbage, 10000)){
		n++;
		cout  << garbage<< endl;
	}

}