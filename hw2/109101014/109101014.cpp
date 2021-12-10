#include<iostream>
#include<iomanip>
#include<fstream>
#define endl '\n'
#define max_size 1000000
using namespace std;


template <typename T>
class Queue{
private:
    T *ptr;
    int size;
    int front;
    int rear;
public:
    Queue();
    Queue(int);
    ~Queue();
    void push(T);
    T pop();
    T pop_rear();
    int get_size() const;
    bool empty() const;
    void print(ostream &) const;
};

template <typename T>
int find_longest_queue(Queue<T>[], int array_size);

template <typename T>
void print(ostream&, Queue<T>[], int array_size);

int main(int argc, char **argv){
    ifstream input;
    ofstream output;
    input.open(argv[1]);
    output.open(argv[2]);
    if(!input.is_open()){
        cout << "Error opening file." << endl;
        exit(1);
    }
    int n;
    char op[10];
    int on, i = 1;
    char task;
    input >> n;
    Queue<char> queues[n], done[n];
    while(1){
        input >> op;
        if(op[0] == 'A') {
            input >> on >> task;
            queues[on-1].push(task);
        }
        else if(op[0] == 'E'){
            input >> on; 
            if(!queues[on-1].empty()){
                char did = queues[on-1].pop();
                done[on-1].push(did); 
            }
            else{
                int i = find_longest_queue(queues, n);
                //cout << "longest queue: "  << i+1 << endl;
                if(i != -1){
                    char did = queues[i].pop_rear();
                    done[on-1].push(did);
                }
            }
        }
        else if(op[0] == 'S') break;
        /*
        cout << "***" << i++ << "***" << endl;
        cout << op << ' '<< on ;
        if(op[0] == 'A') cout << ' '<< task;
        cout << endl;
        cout << "Queuing" << endl;
        print(cout, queues, n);
        cout << "Executed" << endl;
        print(cout, done, n);
        cout << "---------------------------" << endl;
        */
    }
    //output
    output << "Queuing" << endl;
    print(output, queues, n);
    output << "Executed" << endl;
    print(output, done, n);
    input.close();
    output.close();
    return 0;
}

template <typename T>
Queue<T>::Queue():size(0), front(0), rear(0){
    ptr = new T[max_size];
}

template <typename T>
Queue<T>::Queue(int a):size(0), front(0), rear(0){
    ptr = new T[a];
}

template <typename T>
Queue<T>::~Queue(){
    delete [] ptr;
}

template <typename T>
void Queue<T>::push(T t){
    ptr[rear++] = t;
    size++;
}

template <typename T>
T Queue<T>::pop(){
    front++;
    size--;
    return ptr[front-1];
}

template <typename T>
T Queue<T>::pop_rear(){
    rear--;
    size--;
    return ptr[rear];
}

template <typename T>
int Queue<T>::get_size() const{
   return size;
}

template <typename T>
bool Queue<T>::empty() const{ 
    if(size == 0) return true;
    else return false;
}

template <typename T>
void Queue<T>::print(ostream & out) const{
    for(int i = front; i < rear; i++){
        out << *(ptr + i);
    }
}

template <typename T>
int find_longest_queue(Queue<T> arr[], int s){
    int rtv = -1, longest = -1;
    for(int i = 0; i < s; i++){
        if(arr[i].get_size() > longest){
            longest = arr[i].get_size();
            rtv = i;
        }
    }
    return rtv;
}

template <typename T>
void print(ostream& out, Queue<T> arr[], int size){
    for(int i = 0; i < size; i++){
        out << i+1 << ' ';
        arr[i].print(out);
        out << endl;
    }
}




