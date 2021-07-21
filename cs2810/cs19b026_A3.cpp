#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Value{
    int v;
    Value* next;
};//defining the stack node used for implementing stack using linked list

class Stack{
    Value* head;//head pointer of the stack(dummy node)
    public:
    void StackInit(){
        head=new Value;
    }//initialising thhe stack
    void freeStackHead(){
        delete(head);
    }//functin for deleting the head pointer after usege to avoid conflicts
    void Push(int x);
    int Pop();
    int Top();
    int isEmpty();//stack operations declared
};

void Stack::Push(int x){
    Value* temp;
    temp=new Value;
    temp->v=x;
    temp->next=head->next;
    head->next=temp;
    
}//inserting the new node at the begining of the list

int Stack::isEmpty(){
    return head->next==NULL;
}//checking if the stack is empty

int Stack::Top(){
    if(head->next==NULL){return -1;}
    else {return head->next->v;}
}//returning the top of the stack if the stack is not empty

int Stack::Pop(){
    if(head->next==NULL){return -1;}
    else{
        Value* temp=head->next;
        int result=temp->v;
        head->next=temp->next;
        delete(temp);
        return result;
    }
}//removing and returning the top of the sttsck if the stack is not empty

struct Vertex{
    int index;
    int status;//to identify weather the vertex is already visited in DFS
    int Parent;//it gives the parent of the given vertex
};//to store the attributes of each vertex

class Graph{
    int ** adjMat;//to store the adjacency matrix
    Vertex* v;//array of vertex objects
    int n;
    public:
    Graph(int n){
        this->n=n;
        adjMat=(int**)malloc(n*sizeof(int*));
        v=(Vertex*)malloc(n*sizeof(Vertex));
        for(int i=0;i<n;i++){
            v[i].index=i;
            adjMat[i]=(int*)malloc(n*sizeof(int));
            for(int j=0;j<n;j++){
                adjMat[i][j]=0;
            }
        }
    }//initialising the adjacency matrix and vetrtex array
    Graph operator +=(pair<int,int> p);
    Graph operator -=(pair<int,int> p);
    int detectCycle();
    void DfsCycleHelper(int i);//helper function for the detectCycle function
    int reach(int a,int b);
    int components();//graph methods are declared
};

Graph Graph::operator +=(pair<int,int> p){
    this->adjMat[p.first][p.second]=1;
    this->adjMat[p.second][p.first]=1;
    return *this;
    }//+= operator is overloaded to add an edge in the graph

Graph Graph::operator -=(pair<int,int> p){
    this->adjMat[p.first][p.second]=0;
    this->adjMat[p.second][p.first]=0;
    return *this;
}//-= operator is overloaded to delete an edge in the graph

int flag=0;//global vaiable used in the below two functions to check if there is a cycle
int Graph::detectCycle(){//fnction to check if ther eis a cycle
    for (int i=0;i<n;i++){
        v[i].status=0;
        v[i].Parent=-1;
    }//initialising the vertex objects for the DFS
    for (int i=0;i<n;i++){
        if(v[i].status==0){DfsCycleHelper(i);}
    }//calling the recursive DFS
    return flag;
}

void Graph::DfsCycleHelper(int i){//helper function for detectCycle
    v[i].status=1;
    for(int j=0;j<n;j++){//DFS traversal of the graph in a recursive manner
        if(adjMat[i][j]==1){
            if(v[j].status==0){
                v[j].Parent=i;
                DfsCycleHelper(j);
                }
            else{
            if(v[i].Parent!=j){//checking for the back edge
                flag=1;
                break;
            }
            }
            
        }
    }
    v[i].status=2;
}

int Graph::reach(int a, int b){//function to check if there is a path from a to b in the graph
    for (int i=0;i<n;i++){
        v[i].status=0;
        v[i].Parent=-1;
    }//initialising the vertex objects
    Stack s;//stack object to implement DFS non recursively
    s.StackInit();
    s.Push(a);
    v[a].status=1;
    while(s.isEmpty()!=1){//performing the DFS from vertex a
        int i=s.Pop();
        if(i==b){
            s.freeStackHead();
            return 1;
        }//if there is a vertex b in the DFS path from a then return 1
        for(int j=0;j<n;j++){
            if(adjMat[i][j]==1){
                if(v[j].status==0){
                    v[j].Parent=i;
                    v[j].status=1;
                    s.Push(j);
                }
            }
        }
        v[i].status=2;
    }
    s.freeStackHead();
    return 0;//if there is no vertex b in the DFS path from a then return 0
}

int Graph::components(){//function to calculate the number of connected components in the graph
    for (int i=0;i<n;i++){
        v[i].status=0;
        v[i].Parent=-1;
    }//initialising the vertex objects
    Stack s;//stack object to implement DFS non recursively
    s.StackInit();
    int comp=0;//it maintains the count of number of components
    for(int i=0;i<n;i++){
        if(v[i].status==0){
            s.Push(i);
            comp++;//if the vertex is unvisited after a DFS then it should be forming a new component(except for the source)
        }
        while(s.isEmpty()!=1){//performing the DFS to travel a particular connected component
            int k=s.Pop();
            for(int j=0;j<n;j++){
                if(adjMat[k][j]==1){
                    if(v[j].status==0){
                        v[j].Parent=k;
                        v[j].status=1;
                        s.Push(j);
                    }
                }
            }
            v[k].status=2;
        }
    }
    s.freeStackHead();
    return comp;//returning the number of connected components
}

int main() {
    Stack s;
    s.StackInit();//creating a stack object to perform the stack operations
    int q;
    cin>>q;
    string str;
    for(int i=0;i<q;i++){//taking the input and performing the given stack operations
        cin>>str;
        if(str=="push"){
            int x;
            cin>>x;
            s.Push(x);
        }
        else if(str=="pop"){
            cout<<s.Pop()<<endl;
        }
        else if(str=="top"){
            cout<<s.Top()<<endl;
        }
        else if(str=="empty"){
            cout<<s.isEmpty()<<endl;
        }
    }
    s.freeStackHead();//deleting the stack head pointer after the usage
    int n;
    cin>>n;
    Graph g(n);//graph object to perform the graph operations
    int m;
    cin>>m;
    for(int i=0;i<m;i++){//taking the input and performing the given graph operations
        cin>>str;
        if(str=="add"){
            pair<int,int>p;
            cin>>p.first>>p.second;
            g+=p;
        }
        else if(str=="del"){
            pair<int,int>p;
            cin>>p.first>>p.second;
            g-=p;
        }
        else if(str=="cycle"){
            cout<<g.detectCycle()<<endl;
        }
        else if(str=="components"){
            cout<<g.components()<<endl;
        }
        else if(str=="reach"){
            int a,b;
            cin>>a>>b;
            cout<<g.reach(a,b)<<endl;
        }
    }
    return 0;
}
