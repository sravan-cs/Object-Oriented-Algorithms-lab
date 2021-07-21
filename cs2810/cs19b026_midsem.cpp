#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<cstdlib>
using namespace std;

class Batsman{
    public:
    int player_id;
    int total_matches;
    int total_runs;
    int not_outs;
    int balls_faced;//declaring the variables need to store a players information
    Batsman(){}//default constructor
    Batsman(int i,int m,int r,int no,int b){
        player_id=i;
        total_matches=m;
        total_runs=r;
        not_outs=no;
        balls_faced=b;
    }// constructor initialising the variables
    float perf;
    void performance(int avg_matches);
    bool operator < (Batsman b);//declaring the required functions
};

void Batsman::performance(int avg_matches){//this function takes input as average matches and stores the players performance in the public variable perf
    float r=total_runs;
    float m=avg_matches;
    float b=balls_faced;
    perf=r*m/b;//calculating the performance 
}

bool Batsman::operator <(Batsman b){
    return this->perf < b.perf;
}//overloading the < operator based on performances

int Partition(int first,int last,Batsman** record){//helper function for sort function
    int i=first;
    Batsman* pivot = record[first];
    for(int j=first+1;j<=last;j++){
        if(*record[j]<*pivot){
            i++;
            Batsman* x=record[i];
            record[i]=record[j];
            record[j]=x;
        }
    }//vec[i] is always smaller element than pivot and vec[j] is not smaller which means that after the compleation of the loop first i elements are smaller than pivot and the remaining are not smaller than pivot
    Batsman* x=record[first];
    record[first]=record[i];
    record[i]=x;
    return i;
}

void Sort(int first,int last,Batsman** record){//performing quick sort to sort the given input according to the performance values
    if(first<last){
        int p=Partition(first,last,record);//p is the index of the element which is in its corrct position after doing the function
        if(p!=0){Sort(first,p-1,record);}
        Sort(p+1,last,record);//sorting the unsorted parts of the array
    }
}
int Partition(int first,int last,int* a){//function overloaded to sort integer array
    int i=first;
    int pivot=a[i];//choosing the pivot as the first element
    for(int j=first+1;j<=last;j++){
        if(a[j]<pivot){
            i++;
            int x=a[i];
            a[i]=a[j];
            a[j]=x;
        }
    }//vec[i] is always smaller element than pivot and vec[j] is not smaller which means that after the compleation of the loop first i elements are smaller than pivot and the remaining are not smaller than pivot
    int x=a[first];
    a[first]=a[i];
    a[i]=x;
    return i;
}


void Sort(int first,int last,int*a){//quick sort the integer array
    if(first<last){
        int p=Partition(first,last,a);//p is the index of the element which is in its corrct position after doing the function
        if(p!=0){Sort(first,p-1,a);}
        Sort(p+1,last,a);//sorting the unsorted parts of the array
    }
}


void PrintFarthestK(int n,Batsman** record,int k){//this function prints the ids of k farthest batsmans in ascending order
    int i=0;//index at the start of the array
    int j=n-1;//index at the end
    int idx=0;//to keep count of number of visitings to the array
    while(i<n/2 && j>n/2){
        if(idx==k){break;}
        idx++;
        if(abs(record[i]->perf-record[n/2]->perf)>abs(record[j]->perf-record[n/2]->perf)){
            i++;
        }
        else{
            j--;
        }
    }//storing the informaton about farthest k indices in i and j
    while(idx<k && i<n/2){
        i++;
        idx++;
    }
    while(idx<k && j>n/2){
        j--;
        idx++;
    }
    //if any one of i or j reaches the median the other one is increased according to k
    int * arr=new int [k];
    idx=0;
    for(int m=0;m<i;m++){
        arr[idx]=record[m]->player_id;
        idx++;
    }
    for(int m=j+1;m<n;m++){
        arr[idx]=record[m]->player_id;
        idx++;
    }
    //storing the k farthest ids in the array arr
    Sort(0,k-1,arr);//sorting the arr in ascending order
    for(int m=0;m<k;m++){
        cout<<arr[m]<<" ";
    }//printing the k farthest ids in ascending order
    cout<<endl;
}


int main() {
    int n;
    cin>>n;
    Batsman** record = new Batsman*[n];//record[i] stores the pointer to the i_th Batsman object
    int avg_matches=0;//variable to calculate the average matches
    for(int i=0;i<n;i++){
        int id,m,r,no,b;
        cin>>id>>m>>r>>no>>b;
        Batsman * temp=new Batsman[1];
        temp[0]=Batsman (id,m,r,no,b);
        record[i]=temp;
        avg_matches+=m;
    }//taking the input
    avg_matches/=n;
    for(int i=0;i<n;i++){
        record[i]->performance(avg_matches);
    }//calculating the performance of every Batsman
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        string s;
        cin>>s;
        bool flag=0;//to know if the array is sorted
        if(s=="Sort"){
            if(!flag){Sort(0,n-1,record);}//sort the array if not sorted
            flag=1;
            for(int j=0;j<n;j++){
                cout<<record[j]->player_id<<" ";
                cout<<record[j]->total_matches<<" ";
                cout<<record[j]->total_runs<<" ";
                cout<<record[j]->not_outs<<" ";
                cout<<record[j]->balls_faced<<" ";
                cout<<endl;
            }
        }//printing the sorted Batsmans information
        else if(s=="X"){
            int k;
            cin>>k;
            if(!flag){Sort(0,n-1,record);}//if not sorted sort the array
            if(n==k){
                for(int m=0;m<n;m++){
                    cout<<record[m]->player_id<<" ";
                }
                cout<<endl;
            }//if k=n then print the entire ids
            else{PrintFarthestK(n,record,k);}
        }
    }
    return 0;
}
