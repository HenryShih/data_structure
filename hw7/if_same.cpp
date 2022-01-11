#include<iostream>
#include<fstream>
#include<string>

using namespace std;


int main(int argc, char **argv){
    ifstream in1, in2;
    in1.open(argv[1]);
    in2.open(argv[2]);
    bool flag = true;
    string str1, str2;
    int i = 0;
    while(getline(in1, str1) && getline(in2, str2)){
        i++;
        if(str1 != str2){
            flag = false;
            cout << "the lines " << i << " are different\n";
        }
    }

    if(flag)
        cout << "two files are same, and there are " << i << " lines in each file\n";
    else
        cout << "two files are different\n";

    return 0;
}
