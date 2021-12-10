#ifndef MAXHEAP
#define MAXHEAP

#include<iostream>

using namespace std;

 
class MaxHeap{
private:
    int *arr;
    int size;
    int capacity;
public:
    MaxHeap();
    MaxHeap(int);
    MaxHeap(const MaxHeap&);
    ~MaxHeap();
    void add(int);
    int del();
    void level_order(ostream&);
    void in_order(ostream&, int i = 1);
    void post_order(ostream&m, int i = 1);
    void pre_order(ostream&, int i = 1);
};

#endif
