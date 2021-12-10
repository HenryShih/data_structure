#include<iostream>
#include<fstream>
#include"maxheap.h"

using namespace std;

int main(int argc, char**argv){
    ifstream in;
    ofstream out;
    in.open(argv[1]);
    out.open(argv[2]);
    MaxHeap pq;
    int op;
    while(in >> op){
        int add;
        switch(op){
            case 0:
                in >> add;
                pq.add(add);
                break;
            case 1:
                pq.del();
                break;
            case 2:
                pq.level_order(cout);
                cout << endl;
                break;
            case 3:
                pq.pre_order(cout);
                cout << endl;
                break;
            case 4:
                pq.in_order(cout);
                cout << endl;
                break;
            case 5:
                pq.post_order(cout);
                cout << endl;
                break;
        }

    }

    return 0;
}
