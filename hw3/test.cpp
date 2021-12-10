#include<iostream>

using namespace std;


class Test{
public:
    Test();
    ~Test();
private:
    int data;
    int *ptr;
};

Test::Test(){
    ptr = new int;
}

Test::~Test(){
    delete ptr;
    cout << "Destrctor!\n";
}


int main(){
    Test* ptr = new Test;
    cout << "new a Test object\n";
    delete ptr;
    cout << "delete the object\n";


    return 0;
}
