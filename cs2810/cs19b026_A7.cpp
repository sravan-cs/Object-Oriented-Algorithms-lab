#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct edgeNode{
    int u,v,w;
};

class Graph{
    protected:
    int vertCount;
    edgeNode** edges;
    int edgeCount;
    bool updated=0;
    public:
    Graph (int n){
        vertCount=n;
        edgeCount=0;
        edges=new edgeNode*[1000];
    }//constructor initialising edges
    void AddV();
    void AddE(int a,int b,int w);
    void DelE(int a,int b);//necessary functions are being declared
};

void Graph::AddV(){
    vertCount++;
    updated=0;
}

void Graph::AddE(int a,int b,int w){
    if(a>=vertCount || b>=vertCount){cerr<<"error/n";}
    else{
        bool flag=0;
        edgeNode* temp;
        edgeNode* l=new edgeNode;
        if(a>b){
            int c=a;
            a=b;
            b=c;
        }
        l->u=a;
        l->v=b;
        l->w=w;
        for(int i=0;i<edgeCount;i++){
            if(edges[i]->w>w){flag=1;}
            else if(edges[i]->w==w){
                if(edges[i]->u>a){flag=1;}
                else if(edges[i]->u==a){
                    if(edges[i]->v>b){flag=1;}
                }
            }
            if(flag){
                temp=edges[i];
                edges[i]=l;
                l=temp;
            }
        }
        edges[edgeCount]=l;
        edgeCount++;        
        updated=0;
    }       
}

void Graph::DelE(int a,int b){
    if(a>=vertCount || b>=vertCount){cerr<<"error/n";}
    else{
        bool flag=0;
        for(int i=0;i<edgeCount;i++){
            if((edges[i]->u==a && edges[i]->v==b)  || (edges[i]->v==a && edges[i]->u==b)){flag=1;}
            if(flag && i<edgeCount-1){
                edges[i]=edges[i+1];
            }
        }
        if(!flag){cerr<<"error"<<endl;}
        else{edgeCount--;}
        updated=0;
    }
}

class MST : public Graph{
    edgeNode** tree;
    int TedgeCount;
    public:
    MST(int n) : Graph(n){
        tree=new edgeNode*[1000];
        TedgeCount=n-1;
    }
    void Prims(int v);
    void Kruskal();
    void TreeUptodate();
    void DisplayTree();
};

void MST::DisplayTree(){
    for(int i=0;i<TedgeCount-1;i++){
        int min=i;
        for(int j=i+1;j<TedgeCount;j++){
            if(tree[min]->w>tree[j]->w){min=j;}
            else if(tree[min]->w==tree[j]->w){
                if(tree[j]->u<tree[min]->u){min=j;}
                else if(tree[j]->u==tree[min]->u){
                    if(tree[j]->v<tree[min]->v){min=j;}
                }
            }
        }
        edgeNode* temp=tree[min];
        tree[min]=tree[i];
        tree[i]=temp;
    }
    for(int i=0;i<TedgeCount;i++){

             cout<<tree[i]->u<<" "<<tree[i]->v<<" "<<tree[i]->w<<endl;
    }
}

void MST::TreeUptodate(){
    if(updated){cout<<"YES"<<endl;}
    else{cout<<"NO"<<endl;}
}


void Union(int *a,int b,int c){
    a[b]=c;
}

int find(int*a,int i){
    if (a[i] == -1)
        return i;
    return find(a,a[i]);
}

void MST::Kruskal(){
    TedgeCount=0;
    delete (tree);
    tree=new edgeNode*[1000];
    int* disjoint=new int [vertCount];
    for(int i=0;i<vertCount;i++){
        disjoint[i]=-1;
    }
    int totalWeight=0;
    for(int i=0;i<edgeCount;i++){
        int x=find(disjoint,edges[i]->u);
        int y=find(disjoint,edges[i]->v);
        if(x!=y){
            tree[TedgeCount]=edges[i];
            TedgeCount++;
            Union(disjoint,x,y);
            totalWeight+=edges[i]->w;
            //if(TedgeCount>=vertCount-1){break;}
        }
    }
    updated=1;
    cout<<totalWeight<<endl;
}

void MST::Prims(int v){
    updated=1;
    int totalWeight=0;
    delete (tree);
    tree=new edgeNode*[1000];
    int *included=new int[vertCount];
    for(int i=0;i<vertCount;i++){
        included[i]=0;
    }
    included[v]=1;
    
    for(int i=0;i<vertCount-1;i++){
        edgeNode* min=new edgeNode;
        min->w=5001;
        for(int j=0;j<edgeCount;j++){
            if(!(included[edges[j]->u]&&included[edges[j]->v]) && (included[edges[j]->u]||included[edges[j]->v])){
                if(min->w > edges[j]->w){
                    min=edges[j];
                }
                else if(min->w == edges[j]->w){
                    if(included[min->u]){
                        if(included[edges[j]->u]){
                            if(min->v>edges[j]->v){min=edges[j];}
                            else if(min->v==edges[j]->v){if(included[min->u]>included[edges[j]->u]){min=edges[j];}}
                        }
                        else{
                            if(min->v>edges[j]->u){min=edges[j];}
                            else if(min->v==edges[j]->u){if(included[min->u]>included[edges[j]->v]){min=edges[j];}}
                        }
                    }
                    else{
                        if(included[edges[j]->u]){
                            if(min->u>edges[j]->v){min=edges[j];}
                            else if(min->u==edges[j]->v){if(included[min->v]>included[edges[j]->u]){min=edges[j];}}
                        }
                        else{
                            if(min->u>edges[j]->u){min=edges[j];}
                            else if(min->u==edges[j]->u){if(included[min->v]>included[edges[j]->v]){min=edges[j];}}
                        }
                    }
                }
            }
        }
        if(included[min->u]){
            included[min->v]=i+2;
        }
        else{included[min->u]=i+2;}
        totalWeight+=min->w;
        tree[i]=min;
    }
    TedgeCount=vertCount-1;
    cout<<totalWeight<<endl;
    
}


int main() {
    int n,q;
    cin>>n>>q;
    MST M(n);
    for(int i=0;i<q;i++){
        string s;
        cin>>s;
        if(s=="ADDV"){
            M.AddV();
        }
        else if(s=="ADDE"){
            int a,b,w;
            cin>>a>>b>>w;
            M.AddE(a,b,w);
        }
        else if(s=="DELE"){
            int a,b;
            cin>>a>>b;
            M.DelE(a,b);
        }
        else if (s=="Kruskal"){
            M.Kruskal();
        }
        else if(s=="TreeUptodate"){
            M.TreeUptodate();
        }
        else if(s=="DisplayTree"){
            M.DisplayTree();
        }
        else if(s=="Prims"){
            int v;
            cin>>v;
            M.Prims(v);
        }
    }
    return 0;
}
