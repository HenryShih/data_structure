#ifndef MAXHEAP
#define MAXHEAP

#include<iostream>

using namespace std;

template <class t>
class MaxHeap{
private:
    t *arr;
    int size;
    int capacity;
public:
    MaxHeap();
    MaxHeap(int);
    MaxHeap(const MaxHeap&);
    ~MaxHeap();
    void add(t);
    t del();
    void level_order(ostream&);
    void in_order(ostream&, int i = 1);
    void post_order(ostream&m, int i = 1);
    void pre_order(ostream&, int i = 1);
};

#endif
