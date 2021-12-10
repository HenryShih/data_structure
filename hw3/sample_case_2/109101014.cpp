#include<iostream>
#include<list>
#include<fstream>

using namespace std;

struct Term{
    int coef, exp[3];
};



//function forward declaration
list<Term> add(list<Term>&, list<Term>&);
list<Term> sub(list<Term>&, list<Term>&);
list<Term> mul(list<Term>&, list<Term>&);
int if_bigger(Term&, Term&);
void print(list<list<Term> > &polys, ostream&);
bool if_zero(list<Term> &);


int main(int argc, char** argv){
    ifstream in;
    ofstream out;
    in.open(argv[1]);
    out.open(argv[2]);    
    list<list<Term> > polys;
    int op;
    while(in >> op){
        //out << "op = " << op << endl;
        int n, a, b, coef, exp[3];
        Term term;
        list<Term> poly;
        list<list<Term> >::iterator it1, it2;
        it1 = it2 = polys.begin();
        switch(op){
            case 0:
                in >> n;
                for(int i = 0; i < n; i++){
                    in >> term.coef >> term.exp[0] >> term.exp[1] >> term.exp[2];
                    poly.push_back(term);
                }
                polys.push_back(poly);
                break;
            case 1:
                in >> a >> b;
                while(a--) it1++;
                while(b--) it2++;
                poly = add(*it1, *it2);
                polys.push_back(poly);
                break;
            case 2:
                in >> a >> b;
                while(a--) it1++;
                while(b--) it2++;
                poly = sub(*it1, *it2);
                polys.push_back(poly);
                break;
            case 3:
                in >> a >> b;
                while(a--) it1++;
                while(b--) it2++;
                poly = mul(*it1, *it2);
                polys.push_back(poly);
                break;
            case 4:
                in >> a;
                while(a--) it1++;
                polys.erase(it1);
                break;
        }
        //print(polys);
    }
    print(polys, out);


    return 0;
}

//function forward definition
list<Term> add(list<Term>& a, list<Term>& b){
    list<Term> rt;
    list<Term>::iterator it1, it2;
    it1 = a.begin();
    it2 = b.begin();
    if(if_zero(a)) it1++;
    if(if_zero(b)) it2++;
    while(it1 != a.end() && it2 != b.end()){
        int cmp = if_bigger(*it1, *it2);
        Term term;
        switch(cmp){
            case 1:
                rt.push_back(*it1);
                it1++;
                break;
            case -1:
                rt.push_back(*it2);
                it2++;
                break;
            case 0:
                term.coef = it1 -> coef + it2 -> coef;
                if(term.coef != 0){
                    for(int i = 0; i < 3; i++)
                        term.exp[i] = it1 -> exp[i];
                    rt.push_back(term);
                }
                it1++; it2++;
                break;
        }
    }
    while(it1 != a.end()){
        rt.push_back(*it1);
        it1++;
    } 
    while(it2 != b.end()){
        rt.push_back(*it2);
        it2++;
    }
    if(rt.size() == 0){
        Term term;
        term.coef = term.exp[0] = term.exp[1] = term.exp[2] = 0;
        rt.push_back(term);
    }
    return rt;
}   
list<Term> sub(list<Term>& a, list<Term>& b){
    list<Term> rt;
    list<Term>::iterator it1, it2;
    it1 = a.begin();
    it2 = b.begin();
    Term term;
    if(if_zero(a)) it1++;
    if(if_zero(b)) it2++;
    while(it1 != a.end() && it2 != b.end()){
        int cmp = if_bigger(*it1, *it2);
        switch(cmp){
            case 1:
                rt.push_back(*it1);
                it1++;
                break;
            case -1:
                term.coef = -(it2 -> coef);
                for(int i = 0; i < 3; i ++)
                    term.exp[i] = it2 -> exp[i];
                rt.push_back(term);
                it2++;
                break;
            case 0:
                term.coef = it1 -> coef - it2 -> coef;
                if(term.coef != 0){
                    for(int i = 0; i < 3; i++)
                        term.exp[i] = it1 -> exp[i];
                    rt.push_back(term);
                }
                it1++; it2++;
                break;
        }
    }
    while(it1 != a.end()){
        rt.push_back(*it1);
        it1++;
    } 
    while(it2 != b.end()){
        term.coef = -(it2 -> coef);
        for(int i = 0; i < 3; i++)
            term.exp[i] = it2 -> exp[i];
        rt.push_back(term);
        it2++;
    }
    if(rt.size() == 0){
        term.coef = term.exp[0] = term.exp[1] = term.exp[2] = 0;
        rt.push_back(term);
    }
    return rt;
}
list<Term> mul(list<Term>& a, list<Term>& b){
    list<Term> rt;
    list<Term>::iterator it1, it2, it3;
    Term term;
    it1 = a.begin();
    it2 = b.begin();
    it3 = rt.begin();
    if(if_zero(a)) it1++;
    if(if_zero(b)) it2++;
    while(it1 != a.end()){
        it2 = b.begin();
        it3 = rt.begin();
        while(it2 != b.end()){
            term.coef = it1 -> coef * it2 -> coef;
            for(int i = 0; i < 3; i++)
                term.exp[i] = (it1 -> exp[i]) + (it2 -> exp[i]);
            while(1){
                if(it3 == rt.end()){
                    rt.push_back(term);
                    break;
                }
                int cmp = if_bigger(*it3, term);
                if(cmp == 1)
                    it3++;
                else if(cmp == 0){
                    it3 -> coef += term.coef;
                    break;
                }
                else{
                    rt.insert(it3, term);
                    break;
                }
            }
            it2++;
        }
        it1++;
    }
    if(rt.size() == 0){
        Term term;
        term.coef = term.exp[0] = term.exp[1] = term.exp[2] = 0;
        rt.push_back(term);
    }
    return rt;
}


int if_bigger(Term &a, Term &b){
    if(a.exp[0] > b.exp[0]) return 1;
    else if(a.exp[0] < b.exp[0]) return -1;
    else{
        if(a.exp[1] > b.exp[1]) return 1;
        else if(a.exp[1] < b.exp[1]) return -1;
        else{    
            if(a.exp[2] > b.exp[2]) return 1;
            else if(a.exp[2] < b.exp[2]) return -1;
            else return 0;
        }
    }
}



void print(list<list<Term> > &polys, ostream &out){
    for(list<list<Term> >::iterator it1 = polys.begin(); it1 != polys.end(); it1++){
        out << it1->size() << endl;
        for(list<Term>::iterator it2 = it1->begin(); it2 != it1->end(); it2++){
            out << it2 -> coef ;
            for(int i = 0; i < 3; i++)
                out << ' ' << it2 -> exp[i];
            out << endl;
        }
    }
}

bool if_zero(list<Term> &poly){
    Term term = poly.front();
    if(term.coef == 0 && term.exp[0] == 0 &&  term.exp[1] == 0 && term.exp[2] == 0)
        return true;
    else 
        return false;
}
