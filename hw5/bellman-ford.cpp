#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>

#define MAX_NODE_NUM 101
using namespace std;

int adjmatrix[MAX_NODE_NUM][MAX_NODE_NUM];
int d[MAX_NODE_NUM];
vector<int> record[MAX_NODE_NUM];
vector<int> negative_cycle;

int main(int argc, char** argv){
	ifstream in;
	ofstream out;
	in.open(argv[1]);
	out.open(argv[2]);
	char garbage[10000];
	int hh;
	int n = 0;
	while(in >> hh){
		n++;
	}
	n = sqrt(n);
	in.close();
	in.open(argv[1]);
	//read adjacency matrix
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++){
			in >> adjmatrix[i][j];
		}
	//initialization
	for(int i = 0; i < MAX_NODE_NUM; i++)
		d[i] = 10000000;
	
	d[0] = 0;

	//for(int i = 0; i < n; i++)
	record[0].push_back(0);

	//run Bellman-Ford algorithm
	for(int k = 0; k < n-1; k++){
		//cout << "******round k = " << k << endl;
		for(int i = 0; i < n; i++){
			//cout << "---vertex " << i << endl;
			for(int j = 0; j < n; j++)
				// j -> i
				if(adjmatrix[j][i]){
					//cout << "edge " << j << " -> " << i << endl;
					//cout << "   " << "now d[" << i << "] = " << d[i] << ", d[" << j << "] = " << d[j] << ", distanece between = " << adjmatrix[j][i] << endl;
					if(d[i] > d[j] + adjmatrix[j][i]){
						d[i] = d[j] + adjmatrix[j][i];
						record[i] = record[j];
						record[i].push_back(i);
					}
				}
		}
		//for(int i = 0; i < n; i++)
		//	cout << "d[" << i << "] = " << d[i] << endl;
	}

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(adjmatrix[j][i])
				// j -> i
				if(d[i] > d[j] + adjmatrix[j][i]){
					//detect negative cycle, including j -> i, i -> j
					negative_cycle = record[j];
					negative_cycle.push_back(i);
				}


	if(negative_cycle.size()){
		////cout << "detect negative cycle with size " << negative_cycle.size() << endl;
		int start = negative_cycle[0];
		for(int i = 0; i < negative_cycle.size(); i++){
			if(i)
				out << "-";
			out << negative_cycle[i] ;
			if(negative_cycle[i] == start && i)
				break;
		}
		out << endl;
	}
	else{
		for(int i = 1; i < n; i++){
			//cout << record[i].size() << endl;
			for(int j = 0; j < record[i].size(); j++){
				if(j)
					out << "-";
				out << record[i][j];
			}
			out << " " << d[i] << endl;
		}
	}
	out << endl;


	return 0;
}