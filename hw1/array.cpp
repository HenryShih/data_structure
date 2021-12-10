#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

class Term{
    public:
        Term();
        Term(int, int, int);
        int row, column, value;
};
void trans(vector<Term> &);
bool cmp_first_matrix(const Term&, const Term&);
bool cmp_second_matrix(const Term&, const Term&);
vector<Term> multiply(const vector<Term>&, const vector<Term>&, int, int);
void print_matrix(vector<Term>, int, int,  ostream &);
void print_terms(const vector<Term>&);
int main(int argc, char **argv){
    int in, cnt1, cnt2, m, n, p, q;
    string ins;
    ifstream input;
    ofstream output;
    input.open(argv[1]);
    output.open(argv[2]);
    vector<Term> A, B, C;
    getline(input, ins);
    n = 0;
    while(1){
        input >> ins;
        n++;
        //cout <<"ins = " <<ins << endl;
        if(ins == ";")
            break;
        if(ins[0] != '0')
            A.push_back(Term(1, n, stoi(ins)));
    }
    n--;
    //cout << "n = " << n << endl;
    m = 1;
    while(1){
        m++;
        for(int i = 1; i <= n+1; i++){
            input >> ins;
            //cout <<"i = "<< i<< ", ins = " << ins << endl;
            if(ins == "B") break;
            if(ins[0] != '0' && i!=n+1)
                A.push_back(Term(m, i, stoi(ins)));
        }
        if(ins == "B") break;
    }
    m--;
    input >> ins;
    A.push_back(Term(m+1, n+1, 1));
    //cout << "i get here" << endl;    
    q = 0;
    while(1){
        input >> ins;
        q++;
        //cout << "!ins = "<< ins << endl;
        if(ins == ";")
            break;
        if(ins[0] != '0')
            B.push_back(Term(1, q, stoi(ins)));
    }
    q--;
    //cout << "hello" << endl;
    p = 1;
    while(input >> ins){
        //cout << "ins = "<< ins << endl;
        p++;
        for(int i = 1; i <= q+1; i++){
            if(ins[0] != '0'&& i!=q+1)
                B.push_back(Term(p, i, stoi(ins)));
            if(i != q) input >> ins;
        }      
    }
    B.push_back(Term(p+1, q+1, 1));
    //cout << "m = "<< m << ", n = " << n << ", p = "<< p<<", q = "<<q <<endl;    
    if(n == p){}
    else if(m == p){
        trans(A);
        int tmp = n;
        n = m;
        m = tmp;
        //cout << "m==p"<< endl;
    }
    else if(n == q){
        trans(B);
        int tmp = q;
        q = p;  
        p = tmp;
        cout << "n==q" << endl;
    }
    else if(m == q){
        trans(A);
        trans(B);
        int tmp = n;
        n = m;
        m = tmp;
        tmp = q;
        q = p;
        p = tmp;
        cout << "m==q"<< endl;
    }
    sort(A.begin(), A.end(), cmp_first_matrix);
    sort(B.begin(), B.end(), cmp_second_matrix);
    //cout << "sort is finished\n";
    //print_terms(A);
    //print_terms(B);
    //print_matrix(A, m, n, cout);
    //print_matrix(B, p, q, cout);
    C = multiply(A, B, m, q);
    //cout << "multiply is finished\n";
    print_matrix(C, m, q, output);


    return 0;
}

Term::Term(){};
Term::Term(int a, int b, int c):row(a), column(b), value(c){}

void trans(vector<Term> &v){
    for(int i = 0; i < v.size(); i++){
        int row, column;
        row = v[i].row;
        column = v[i].column;
        v[i].row = column;
        v[i].column = row;
    };
}

bool cmp_first_matrix(const Term &a, const Term &b){
    if(a.row < b.row) return true;
    else if(a.row == b.row) 
        if(a.column < b.column) return true;
        else return false;
    else return false;
}

bool cmp_second_matrix(const Term &a, const Term &b){
    if(a.column < b.column) return true;
    else if(a.column == b.column)
        if(a.row < b.row) return true;
        else return false;
    else return false;
}

vector<Term> multiply(const vector<Term> &a, const vector<Term> &b, int m,int q){
    vector<Term> c;
    int ia = 0, ia_record, ib = 0;
    for(int i = 1; i <= m; i++){
        while(a[ia].row < i) ia++;
        ia_record = ia;
        ib = 0;
        for(int j = 1; j <= q; j++){
            //cout << "i = "<< i << ",  j = " << j << endl;
            ia = ia_record;
            while(b[ib].column < j) ib++;
            int sum = 0;
            while(1){
                //cout << "ia = " << ia << ",  ib =  "<< ib << endl;
                if(a[ia].row > i || b[ib].column > j) break;
                if(a[ia].column == b[ib].row) sum += a[ia++].value * b[ib++].value;
                else if(a[ia].column > b[ib].row) ib++;
                else ia++;
            }
            //cout << "i = "<< i << ",  j = " << j << ", sum = " << sum << endl;
            if(sum) c.push_back(Term(i, j, sum));
        }
    }
    return c;    
}

void print_terms(const vector<Term> &v){
    for(int i = 0; i < v.size(); i++){
        cout << '(' << v[i].row << ", "<< v[i].column << ", " << v[i].value << ')';
        cout << endl;
    }
    cout << endl;
}

void print_matrix(vector<Term> v, int m, int n, ostream &out){
    //out << m << 'x' << n << endl;
    sort(v.begin(), v.end(), cmp_first_matrix); 
    //print_terms(v);
    int iv = 0;
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(v[iv].row == i && v[iv].column == j){
                out  << v[iv].value << ' ' ;
                iv++;
            }
            else
                out << 0 << ' ';
        }
        out << ';'  << endl;;
    }
}





