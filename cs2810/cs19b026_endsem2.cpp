#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class GraphOp{//class to perform the graph operations
    vector<vector<bool>> g1;
    int n;
    public:
    GraphOp(int v){
        n=v;
        g1=vector<vector<bool>>(n,vector<bool>(n,0));
    }
    void gadd(int u,int v);
    bool** operator +(bool** g2);
    bool** operator -(bool** g2);
    bool** operator %(bool** g2);
    void lexi(bool** g2);//declaring the necessary functions
};

void GraphOp::gadd(int u,int v){
    g1[u][v]=1;
    g1[v][u]=1;
}//adding an edge in the first graph


bool** GraphOp::operator +(bool** g2){
    bool ** out=new bool*[n];
    for(int i=0;i<n;i++){
        out[i]=new bool[n];
        for(int j=0;j<n;j++){out[i][j]=0;}
        for(int j=i;j<n;j++){
            if(g1[i][j] || g2[i][j]){out[i][j]=1;}
        }
    }
    return out;
}//finding the edges in the graph formed by adding two graphs 

bool** GraphOp::operator -(bool** g2){
    bool ** out=new bool*[n];
    for(int i=0;i<n;i++){
        out[i]=new bool[n];
        for(int j=0;j<n;j++){out[i][j]=0;}
        for(int j=i;j<n;j++){
            if(g1[i][j] && !g2[i][j]){out[i][j]=1;;}
        }
    }
    return out;
}//finding the edges in the graph formed by performing minus on two graphs 

bool** GraphOp::operator %(bool** g2){
    bool ** out=new bool*[n];
    for(int i=0;i<n;i++){
        out[i]=new bool[n];
        for(int j=0;j<n;j++){out[i][j]=0;}
        for(int j=i;j<n;j++){
            if(g1[i][j] ^ g2[i][j]){out[i][j]=1;}
        }
    }
    return out;
}//finding the edges in the graph formed by performing mod on two graphs 

void GraphOp::lexi(bool** g2){
    int edge_count=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                for(int l=0;l<n;l++){
                    if(g1[i][k]){edge_count++;}
                    else if(i==k){
                        edge_count+=g2[j][l];
                    }
                }
            }
        }
    }//we are counting every edge twice 
    cout<<edge_count/2<<endl;   
}//finding the edges in the graph formed by performing lexicographic product on two graphs 


int main() {
    int n;
    cin>>n;
    GraphOp g1(n);
    bool** g2=new bool*[n];
    int m;
    cin>>m;
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g1.gadd(u,v);
    }
    cin>>m;
    for(int i=0;i<n;i++){
        g2[i]=new bool[n];
        for(int j=0;j<n;j++){
            g2[i][j]=0;
        }
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g2[u][v]=1;
        g2[v][u]=1;
    }
    int q;
    cin>>q;
    for(int i=0;i<q;i++){
        string s;
        cin>>s;
        if(s=="ADD"){
            bool** temp=g1+g2;
            int count=0;
            for(int j=0;j<n;j++){
                for(int k=0;k<n;k++){
                    if(temp[j][k]){count++;}
                }
            }
            cout<<count<<endl;
        }
        else if(s=="MINUS"){
            bool** temp=g1-g2;
            int count=0;
            for(int j=0;j<n;j++){
                for(int k=0;k<n;k++){
                    if(temp[j][k]){count++;}
                }
            }
            cout<<count<<endl;
        }
        else if(s=="MOD"){
            bool** temp=g1%g2;
            int count=0;
            for(int j=0;j<n;j++){
                for(int k=0;k<n;k++){
                    if(temp[j][k]){count++;}
                }
            }
            cout<<count<<endl;
        }
        else if(s=="LexicographicProduct"){
            g1.lexi(g2);
        }
    }
    return 0;
}