#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Batsman{
    public:
    int player_id;
    int total_matches;
    int total_runs;
    int not_outs;
    int balls_faced;
    Batsman(){}
    Batsman(int i,int m,int r,int no,int b){
        player_id=i;
        total_matches=m;
        total_runs=r;
        not_outs=no;
        balls_faced=b;
    }
    float perf;
    void performance(int avg_matches);
    bool operator < (Batsman b);
};

void Batsman::performance(int avg_matches){
    float r=total_runs;
    float m=avg_matches;
    float b=balls_faced;
    perf=r*m/b;
}

bool Batsman::operator <(Batsman b){
    return this->perf < b.perf;
}

int Partition(int first,int last,Batsman** record){
    int i=first;
    Batsman* pivot = record[first];
    for(int j=first+1;j<=last;j++){
        if(*record[j]<*pivot){
            i++;
            Batsman* x=record[i];
            record[i]=record[j];
            record[j]=x;
        }
    }
    Batsman* x=record[first];
    record[first]=record[i];
    record[i]=x;
    return i;
}

void Sort(int first,int last,Batsman** record){
    if(first<last){
        int p=Partition(first,last,record);//p is the index of the element which is in its corrct position after doing the function
        if(p!=0){Sort(first,p-1,record);}
        Sort(p+1,last,record);//sorting the unsorted parts of the array
    }
}

void PrintFarthestK(int n,Batsman** record){
    Batsman** temp=new Batsman*[n];
    int i=0;
    int j=n-1;
    while(i<n/2 && j>n/2){
        
    }
}


int main() {
    int n;
    cin>>n;
    Batsman** record = new Batsman*[n];
    int avg_matches=0;
    for(int i=0;i<n;i++){
        int id,m,r,no,b;
        cin>>id>>m>>r>>no>>b;
        Batsman * temp=new Batsman[1];
        temp[0]=Batsman (id,m,r,no,b);
        record[i]=temp;
        avg_matches+=m;
    }
    avg_matches/=n;
    for(int i=0;i<n;i++){
        record[i]->performance(avg_matches);
    }
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        string s;
        cin>>s;
        bool flag=0;
        if(s=="Sort"){
            Sort(0,n-1,record);
            flag=1;
            for(int j=0;j<n;j++){
                cout<<record[j]->player_id<<" ";
                cout<<record[j]->total_matches<<" ";
                cout<<record[j]->total_runs<<" ";
                cout<<record[j]->not_outs<<" ";
                cout<<record[j]->balls_faced<<" ";
                cout<<endl;
            }
        }
        else if(s=="X"){
            int k;
            cin>>k;
            if(!flag){Sort(0,n-1,record);}
            PrintFarthestK(n,record);
        }
    }
    return 0;
}
