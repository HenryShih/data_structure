#ifndef LIST_H
#define LIST_H
#include<iostream>

//forward declaration
template <typename t>
class List;
template <typename t>
class ListNode;
template <typename t>
class ListIterator;

//class definition
template <typename t>
class List{
public:
    friend class ListIterator<t>;
    List();
    List(const List<t>&);
    ~List();
    ListIterator<t> begin_it() const;
    ListIterator<t> last_it() const;
    void add(t, ListIterator<t>);
    void del(ListIterator<t>);
    void push(t);
    int get_size() const;
private:
    ListNode<t> *first;
    ListNode<t> *last;
    int size;
};
template <typename t>
class ListNode{
public:
    friend class List<t>;
    friend class ListIterator<t>;
    ListNode();
    ListNode(t);
private:
    t data;
    ListNode<t>* prev;
    ListNode<t>* next;
};
template <typename t>
class ListIterator{
public:
    friend class List<t>;
    ListIterator(List<t>&);
    void prev();
    void next();
    t get_data();
private:
    List<t> &list;
    ListNode<t> *ptr;
};



#endif
