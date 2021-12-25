#include<iostream>
#include<fstream>
#include<vector>

using namespace std;



long long quicksort(vector<int> &v, int l, int r){
	if(l < r){
		long long rtv = 0;
		int i = l;
		int j = r+1;
		int pivot = v[l];
		do{
			do{i++;} while(i < r && v[i] < pivot);
			do{j--;} while(v[j] > pivot);
			if(i < j) {
				rtv++;
				int swap = v[i];
				v[i] = v[j];
				v[j] = swap;
			}
		}while(i < j);
		if(v[l] != v[j])
			rtv++;
		int swap = v[l];
		v[l] = v[j];
		v[j] = swap;
		return quicksort(v, l, j-1) + quicksort(v, j+1, r) + rtv;
	}
	return 0;
}

int main(int argc, char **argv){
	ifstream in;
	ofstream out;
	in.open(argv[1]);
	out.open(argv[2]);
	int i;
	vector<int> s;
	while(in >> i){
		s.push_back(i);
	}

	long long ans;
	ans = quicksort(s, 0, s.size()-1);
	out << ans << endl;
	/*
	for(int i = 0; i < s.size(); i++)
		cout << s[i] << " ";
	cout << endl;
	*/
    return 0;
}
