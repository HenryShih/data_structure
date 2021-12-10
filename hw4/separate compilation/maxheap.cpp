#include<iostream>
#include<fstream>
#include"maxheap.h"
using namespace std;


//constructors
template <class t>
MaxHeap<t>::MaxHeap(){
    size = 0;
    capacity = 100;
    arr = new t[100];
}

template <class t>
MaxHeap<t>::MaxHeap(int capa){
    size = 0;
    capacity = capa+1;
    arr = new t[capacity];
}

template <class t>
MaxHeap<t>::MaxHeap(const MaxHeap &a){
    size = a.size;
    capacity = a.capacity;
    arr = new t[capacity];
    for(int i = 1; i <= size; i++)
        arr[i] = a.arr[i];
}

//dectructor
template <class t>
MaxHeap<t>::~MaxHeap(){
    delete[] arr;
}

//member function
template <class t>
void MaxHeap<t>::add(t add){
    if(size == capacity-1){
        t *newarr = new t[size + 101];
        for(int i = 1; i <= size; i++)
            newarr[i] = arr[i];
        delete [] arr;
        arr = newarr;
    }
    int i = ++size;
    while(1){
        if(i == 1) 
            break;
        if(arr[i/2] < add){
            arr[i] = arr[i/2];
            i /= 2;
        }
        else        
            break;
    }
    arr[i] = add;
}

template <class t>
t MaxHeap<t>::del(){
    t root = arr[1];
    t last = arr[size];
    size--;
    int i = 1;
    while(1){
        if(arr[2*i] > last || arr[2*i+1] > last){
            if(arr[2*i] > arr[2*i+1]){
                arr[i] = arr[2*i];
                i = 2*i;
            }
            else{
                arr[i] = arr[2*i+1];
                i = 2*i+1;
            }
        }
        else{
            break;
        }
    }
    arr[i] = last;
    return root;
}


template <class t>
void MaxHeap<t>::level_order(ostream& out){
    for(int i = 1; i <= size; i++)
        out << arr[i] << " ";
}

template <class t>
void MaxHeap<t>::in_order(ostream &out, int i){   
     if(2*i <= size)
        in_order(out, 2*i);
    out << arr[i] << " ";
    if(2*i+1 <= size)
        in_order(out, 2*i+1);
}

template <class t>
void MaxHeap<t>::post_order(ostream &out, int i){
     if(2*i <= size)
        in_order(out, 2*i);
    if(2*i+1 <= size)
        in_order(out, 2*i+1);
    out << arr[i] << " ";
}

template <class t>
void MaxHeap<t>::pre_order(ostream &out, int i){ 
    out << arr[i] << " ";    
    if(2*i <= size)
        in_order(out, 2*i);
    if(2*i+1 <= size)
        in_order(out, 2*i+1);
}
















