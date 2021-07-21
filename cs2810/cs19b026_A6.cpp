#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

template<class T> struct node{
    int vertInd;
    T weight;
    node<T>* next;
    int status;
};//the node to used in adjLists

template<class T> class Graph{
    int vertCount;
    node<T>** adjLists;
    public:
    Graph (int n){
        vertCount=n;
        adjLists=(node<T>**)malloc(vertCount*sizeof(node<T>*));
        for (int i=0;i<vertCount;i++){
            node<T>* head=new node<T>;
            head->vertInd=i;
            head->next=NULL;
            adjLists[i]=head;
        }
    }//constructor initialising nodes for every vertex
    void AddV();
    void AddE(int a,int b,T w);
    void DelE(int a,int b);
    void BFS(int a);
    void SSP(int a);//necessary functions are being declared
};

template<class T>
void Graph<T>::AddV(){
    vertCount++;
    node<T>** temp1;//temporary lists of new capacity
    temp1=(node<T>**)malloc(vertCount*sizeof(node<T>*));
    node<T>* temp2=new node<T>;
    temp2->vertInd=vertCount-1;
    temp2->next=NULL;
    for(int i=0;i<vertCount-1;i++){
        temp1[i]=adjLists[i];
    }//copying the nodes of old lists into the new one
    temp1[vertCount-1]=temp2;
    free (adjLists);
    adjLists=temp1;
}

template<class T>
void Graph<T>::AddE(int a,int b,T w){
    if(a>=vertCount || b>=vertCount){cerr<<"error/n";}
    else{
        node<T>* temp1=new node<T>;//temp1 stores the new node to be added
        temp1->vertInd=b;
        temp1->weight=w;
        temp1->next=NULL;
        temp1->status=0;
        
        node<T>* temp2=adjLists[a];//temp2 stores the pointer to the head of the adjlist of 'a'
        bool flag=0;//flag to know if the node to be inserted at the last
        while(temp2->next!=NULL){
            if(temp2->next->weight > temp1->weight){
                node<T>* temp=new node<T>;
                temp=temp2->next;
                temp2->next=temp1;
                temp1->next=temp;
                flag=1;
                break;
            }
            else if(temp2->next->weight < temp1->weight){
                temp2=temp2->next;
            }
            //the node is inserted in the order of weight
            else if(temp2->next->weight == temp1->weight){
                if(temp2->next->vertInd >= temp1->vertInd){
                    node<T>* temp=new node<T>;
                    temp=temp2->next;
                    temp2->next=temp1;
                    temp1->next=temp;
                    flag=1;
                    break;
                }
                else if(temp2->next->vertInd < temp1->vertInd){
                    temp2=temp2->next;
                }
                //if the weights are equal the node is inserted in order of indices
            }
            
        }
        if(!flag){temp2->next=temp1;}//if the node is not inserted it is inserted at the end
        
        //the entire thing we have done until now is repeated for the adjlist of 'b' vertex since it is an undirected graph
        node<T>* temp3=new node<T>;
        temp3->vertInd=a;
        temp3->weight=w;
        temp3->next=NULL;
        temp3->status=0;
        
        node<T>* temp4=adjLists[b];
        flag=0;
        while(temp4->next!=NULL){
            if(temp4->next->weight > temp3->weight){
                node<T>* temp=new node<T>;
                temp=temp4->next;
                temp4->next=temp3;
                temp3->next=temp;
                flag=1;
                break;
            }
            else if(temp4->next->weight < temp3->weight){
                temp4=temp4->next;
            }
            else if(temp4->next->weight == temp4->weight){
                if(temp4->next->vertInd >= temp3->vertInd){
                    node<T>* temp=new node<T>;
                    temp=temp4->next;
                    temp4->next=temp1;
                    temp3->next=temp;
                    flag=1;
                    break;
                }
                else if(temp4->next->vertInd < temp3->vertInd){
                    temp4=temp4->next;
                }
            }
        }    
        if(!flag){temp4->next=temp3;}
    }
}

template<class T>
void Graph<T>::DelE(int a,int b){
    if(a>=vertCount || b>=vertCount){cerr<<"error/n";}
    else{
        node<T>* temp1=adjLists[a];
        bool flag=0;
        while(temp1->next!=NULL){
            if(temp1->next->vertInd==b){
                temp1->next=temp1->next->next;
                flag=1;
                break;
            }
            temp1=temp1->next;
        }//checking for the edge connecting 'a' to 'b' in the adjlist of 'a' vertex and removing it if present 
        if(!flag){cerr<<"error\n";}//printing error if the edge is present
        else{
            node<T>* temp2=adjLists[b];
            while(temp2->next!=NULL){
                if(temp2->next->vertInd==a){
                    temp2->next=temp2->next->next;
                    break;
                }
                temp2=temp2->next;
            }
        }//if the edge is present, removing the node in adjlist of 'b' vertex
    }
}

template<class T>
void Graph<T>::BFS(int a){
    for(int i=0;i<vertCount;i++){
        adjLists[i]->status=0;
    }//making alll the nodes unvisited initially
    
    queue<node<T>*> q;
    q.push(adjLists[a]);
    adjLists[a]->status=1;
    //pushing the source into the queue
    
    while(!q.empty()){
        node<T>* temp=q.front()->next;
        cout<<q.front()->vertInd<<" ";
        q.pop();
        while(temp!=NULL){
            if(adjLists[temp->vertInd]->status==0){
                q.push(adjLists[temp->vertInd]);
                adjLists[temp->vertInd]->status=1;
            }//visiting the children of queue front if not visited already
            temp=temp->next;
        }
    }
    
}


template<class T>
void Graph<T>::SSP(int a){
    int* d=new int[vertCount];
    for(int i=0;i<vertCount;i++){
        if(i==a){d[i]=0;}
        else{d[i]=INT_MAX;}
    }//d array stores the min distances of vertices from 'a' after the end of the function
    
    for(int i=0;i<vertCount;i++){
        adjLists[i]->status=0;
    }
    typedef pair<T,int> p;
    priority_queue<p,vector<p>,greater<p>> q;//priority queue with minimum element at the front
    //the priority is determined by the first element of the pair i.e the distance from 'a'
    
    p s;
    s.first =0;
    s.second=a;
    adjLists[a]->status=1;
    q.push(s);//pushing the source into the queue
    
    while(!q.empty()){//performin the SSP algorithm
        int idx=q.top().second;
        q.pop();//popping the minimum among the unvisited nodes from the queue
        node<T> *temp=adjLists[idx]->next;
        adjLists[idx]->status=1;
        
        while(temp!=NULL){
            long long int dist=d[idx]+temp->weight;
            if(adjLists[temp->vertInd]->status==0 && dist<d[temp->vertInd]){
                d[temp->vertInd]=dist;
                p k;
                k.first=dist;
                k.second=temp->vertInd;
                q.push(k);
            }//if the children of the queue top are not visited and are nearest from 'a' when 'a' to top and top to child is less than 'a' to child 
            temp=temp->next;
        }
    }
    
    
    for(int i=0;i<vertCount;i++){
        cout<<d[i]<<" ";
    }
}    

int main() {
    int n,q;
    cin>>n>>q;
    Graph<int> g(n);
    for(int i=0;i<q;i++){
        string s;
        cin>>s;
        if(s=="ADDV"){
            g.AddV();
        }
        else if(s=="ADDE"){
            int a,b,w;
            cin>>a>>b>>w;
            g.AddE(a,b,w);
        }
        else if(s=="DELE"){
            int a,b;
            cin>>a>>b;
            g.DelE(a,b);
        }
    }
    for(int i=0;i<2;i++){
        string s;
        cin>>s;
        if(s=="BFS"){
            int a;
            cin>>a;
            g.BFS(a);
            cout<<endl;
        }
        else if(s=="SSP"){
            int b;
            cin>>b;
            g.SSP(b);
            cout<<endl;
        }
    }//taking the input and performin the required functions
    return 0;
}
