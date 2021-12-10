#include<iostream>
#include"maxheap.h"
using namespace std;


//constructors
 
MaxHeap::MaxHeap(){
    size = 0;
    capacity = 100;
    arr = new int[100];
}

 
MaxHeap::MaxHeap(int capa){
    size = 0;
    capacity = capa+1;
    arr = new int[capacity];
}

 
MaxHeap::MaxHeap(const MaxHeap &a){
    size = a.size;
    capacity = a.capacity;
    arr = new int[capacity];
    for(int i = 1; i <= size; i++)
        arr[i] = a.arr[i];
}

//dectructor
 
MaxHeap::~MaxHeap(){
    delete[] arr;
}

//member function
 
void MaxHeap::add(int add){
    if(size == capacity-1){
        int *newarr = new int[size + 101];
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

 
int MaxHeap::del(){
    int root = arr[1];
    int last = arr[size];
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


 
void MaxHeap::level_order(ostream& out){
    for(int i = 1; i <= size; i++)
        out << arr[i] << " ";
}

 
void MaxHeap::in_order(ostream &out, int i){   
     if(2*i <= size)
        in_order(out, 2*i);
    out << arr[i] << " ";
    if(2*i+1 <= size)
        in_order(out, 2*i+1);
}

 
void MaxHeap::post_order(ostream &out, int i){
     if(2*i <= size)
        in_order(out, 2*i);
    if(2*i+1 <= size)
        in_order(out, 2*i+1);
    out << arr[i] << " ";
}

 
void MaxHeap::pre_order(ostream &out, int i){ 
    out << arr[i] << " ";    
    if(2*i <= size)
        in_order(out, 2*i);
    if(2*i+1 <= size)
        in_order(out, 2*i+1);
}
















