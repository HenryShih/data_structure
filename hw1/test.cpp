#include<iostream>
#include<vector>
using namespace std;

void go(vector<int> &v){
    for(int i = 0;i < 5; i++)
        v.push_back(i);
}


int main(){
    vector<int> v;
    go(v);
    cout << v.size() << endl;
    return 0;
}
