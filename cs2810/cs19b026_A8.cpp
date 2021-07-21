#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class EDD{
    string s1,s2;
    int **m;
    bool assigned=0;
    bool computed=0;//declaring the required variables
    public:
    EDD(){m=(int **)malloc(sizeof(int*));}
    void assign(string a,string b);
    void compdist();
    int dist();
    void table();//declaring the required functions
};

void EDD::assign(string a, string b){
    s1=a;
    s2=b;
    assigned=1;
    computed=0;
    free (m);//every time we assign a new set of strings we create a new matrix
    int l1=a.size();
    int l2=b.size();
    m=(int **)malloc((l1+1)*sizeof(int*));
    for(int i=0;i<=l1;i++){
    m[i]=(int *)malloc((l2+1)*sizeof(int));
    }//creating the matrix of required size
}

int Min(int a,int b,int c){
    if(a>b){
        if(b>c){return c;}
        else{return b;}
    }
    else{
        if(a>c){return c;}
        else{return a;}
    }
}//function to find minimum among three variables

void EDD::compdist(){//compute the minimum edit distance using dynamic programming
    if(!assigned){throw("error");}
    computed=1;
    int l1=s1.size();
    int l2=s2.size();
    for(int i=0;i<=l2;i++){m[0][i]=i;}
    for(int i=1;i<=l1;i++){
        m[i][0]=i;
        for(int j=1;j<=l2;j++){
            int ins = m[i][j-1] + 1;
            int del = m[i-1][j] + 1;
            int rep;
            if(s1[i-1]!=s2[j-1]){rep = m[i-1][j-1]+1;}
            else{rep = m[i-1][j-1];}
            m[i][j]=Min(ins,del,rep);
        }
    }
}

int EDD::dist(){
    if(!assigned){throw ("error");}//throwing an error if the strings are not assigned
    if(assigned && computed){return m[s1.size()][s2.size()];}
    else{
        compdist();
        return m[s1.size()][s2.size()];
    }//returning the minimum edit distance
}

void EDD::table(){
    if(!assigned){throw("error");}
    if(assigned && !computed){compdist();}
    for(int i=1;i<s1.size()+1;i++){
        for(int j=1;j<s2.size()+1;j++){
            cout<<m[i][j]<<" ";
        }
        cout<<endl;
    }//printing the table used in the dynamic programming
}


int main() {
    int q;
    cin>>q;
    EDD e;
    for(int i=0;i<q;i++){
        string s;
        cin>>s;
        if(s=="assign"){
            string a,b;
            cin>>a>>b;
            e.assign(a,b);
        }
        else if(s=="compdist"){
            try{e.compdist();}
            catch(string s){cout<<s<<endl;}
        }
        else if(s=="dist"){
            try{
                cout<<e.dist()<<endl;
            }
            catch(string s){cout<<s<<endl;}
        }
        else if(s=="table"){
            try{e.table();}
            catch(string s){cout<<s<<endl;}
        }
    }
    return 0;
}
