#include"list.h"
#include<iostream>

using namespace std;


//List
template <typename t>
List<t>::List(){
    first = NULL;
    last = NULL;
    size = 0;
}

template <typename t>
List<t>::List(const List<t> &list){
    ListNode<t> *ptr1, *ptrold, *ptrprev;
    ptrold = list.first;
    ptrprev = NULL;
    ptr1 = new ListNode<t>(ptrold -> data);
    first = ptr1;
    first -> prev = NULL;
    first -> next = NULL;
    ptrprev = ptr1;
    ptrold = ptrold -> next;
    for(int i = 1; i < size; i++){
        ptr1 = new ListNode<t>(ptrold -> data);
        ptr1 -> prev = ptrprev;
        ptrprev -> next = ptr1;
        ptr1 -> next = NULL;
        ptrprev = ptr1;
        ptrold = ptrold -> next;
    }
    last = ptr1;
    size = list.size;
}

template <typename t>
List<t>::~List(){
    ListNode<t> *ptr1, *ptr2;
    ptr1 = first;
    ptr2 = NULL;
    for(int i = 0; i < size; i++){
        ptr2 = ptr1;
        ptr1 = ptr1 -> next;
        delete ptr2;
    }
}

template <typename t>
ListIterator<t> List<t>::begin_it() const{
    ListIterator<t> it(this);
    it.ptr = first;
    return it;
}

template <typename t>
ListIterator<t> List<t>::last_it() const{
    ListIterator<t> it(this);
    it.ptr = last;
    return it;
}

template <typename t>
void List<t>::add(t data, ListIterator<t> it){
    ListNode<t> *p;
    p = new ListNode<t>(data);
    p -> prev = it.ptr;
    p -> next = it.ptr -> next;
    it.ptr -> next -> prev = p;
    it.ptr -> next = p;
    size++;
}

template <typename t>
void List<t>::del(ListIterator<t> it){
    ListNode<t> *p1, *p2;
    p1 = it.ptr -> prev;
    p2 = it.ptr -> next;
    p1 -> next = p2;
    p2 -> prev = p1;
    delete it.ptr;
    size--;
}

template <typename t>
void List<t>::push(t data){
    ListNode<t> *p;
    p = new ListNode<t>(data);
    p -> prev = last;
    p -> next = NULL;
    last = p;
    size++;
}
template <typename t>
int List<t>::get_size() const{
    return size;
}
//ListNode
template <typename t>
ListNode<t>::ListNode(){
    prev = next = NULL;
    data = 0;
}
template <typename t>
ListNode<t>::ListNode(t in){
    data = in;
    prev = next = NULL;
}

//ListIterator
template <typename t>
ListIterator<t>::ListIterator(List<t> &l):list(l){
    ptr = l.first;;
}

template <typename t>
void ListIterator<t>::prev(){
    ptr = ptr -> prev;
}

template <typename t>
void ListIterator<t>::next(){
    ptr = ptr -> next;
}

template <typename t>
t ListIterator<t>::get_data(){
    return ptr -> data;
}






int main(){
    List<int> list;

    for(int i = 0;i < 10; i ++){
        list.push(i);
    }
    ListIterator<int> it(list);
    for(int i = 0;i < list.get_size();i++){
        cout << it.get_data() << endl;;
        it.next();
    }
        

}



