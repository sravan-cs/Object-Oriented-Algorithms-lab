#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<climits>
using namespace std;
//function to calculate the distance between two pairs of coordinates
float find_dist(pair<int,int> p1,pair<int,int> p2){
    int a=p1.first;
    int b=p1.second;
    int c=p2.first;
    int d=p2.second;
    return sqrt((a-c)*(a-c)+(b-d)*(b-d));
}


class TSP{
    int n;
    vector<vector<float>> m;//2D array to store the ditance between points
    vector<pair<int,int>> coordinates;//array to store the coordinates
    public:
    TSP(int n){
        this->n=n;
        m=vector<vector<float>>(n,vector<float>(n,0));
        }
    void add(int a,int b);
    void initialise();
    int min_tour();//required functions are declared
    
};

void TSP::add(int a,int b){
    pair<int,int> p(a,b);
    coordinates.push_back(p);
}//adding the coordinates of a point

void TSP::initialise(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            m[i][j]=find_dist(coordinates[i],coordinates[j]);
        }
    }
}//finding the distances matrix

//function to find the unvisited point which is minimum distance from the subtour
pair<int,int> find_min_unvisited(vector<bool> visited,vector<vector<float>> m,int n){
    float min=INT_MAX;
    pair<int,int> p;
        for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i!=j && min>m[i][j]){
                if((visited[i] && !visited[j] ) || (visited[j] && !visited[i] )){
                    p.first=i;
                    p.second=j;
                    min=m[i][j];
                }
            }
        }
    }
    return p;
}

struct node{
    int value;
    node* next;
};//node to make the list of subtour

//function to insert the new node in the subtour in the suitable position
float insert(node* head,int d,int size,vector<vector<float>> m){
    float min=INT_MAX;
    node* temp=head;
    node* temp2=temp;
    for(int i=0;i<size;i++){
        if(min>m[temp->value][d]+m[temp->next->value][d]-m[temp->value][temp->next->value]){
            min=m[temp->value][d]+m[temp->next->value][d]-m[temp->value][temp->next->value];
            temp2=temp;
        }
        temp=temp->next;
    }
    node* temp3=new node;
    temp3->value=d;
    temp3->next=temp2->next;
    temp2->next=temp3;
    return min;
}

//function to find the minimum tour 
int TSP::min_tour(){
    vector<bool> visited(n,0);
    float min=m[0][1];
    pair<int,int> p(0,1);
    node* head=new node;
    //finding the minimum pair of starting points
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i!=j && min>m[i][j]){
                p.first=i;
                p.second=j;
                min=m[i][j];
            }
        }
    }
    
    head->value=p.first;
    head->next=NULL;
    node* tail=new node;
    tail->value=p.second;
    tail->next=head;
    head->next=tail;
    //this list indicates the inital tour of two points
    int size=2;
    visited[p.first]=1;
    visited[p.second]=1;
    float min_path=min*2;
    //the below loop inserts the nodes according to the nearest neighbour insertion algorithm
    for(int i=0;i<n-2;i++){
        p=find_min_unvisited(visited,m,n);
        int temp;
        if(visited[p.first]){
            temp=p.second;
        }
        if(visited[p.second]){
            temp=p.first;
        }
        visited[p.first]=1;
        visited[p.second]=1;
        min_path+=insert(head,temp,size,m);
        size++;
    }
    return min_path;
    
}

int main() {
    int n;
    cin>>n;
    TSP t(n);
    for(int i=0;i<n;i++){
        int a,b;
        cin>>a>>b;
        t.add(a,b);
    }
    t.initialise();
    int d=t.min_tour();
    cout<<d<<endl;
    return 0;
}
