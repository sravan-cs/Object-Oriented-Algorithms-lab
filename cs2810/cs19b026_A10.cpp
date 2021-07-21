#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Board{
    vector<vector<bool>> b;//b stores where the mines are present
    int n;
    vector<vector<bool>> revealed;//this shows if the block is reaveled
    public:
    Board(int k){
        n=k;
        revealed=vector<vector<bool>>(n,vector<bool>(n,0));
        b=vector<vector<bool>>(n,vector<bool>(n,0));
    }//initialising the variables
    void place_mine(int pos);
    int player_pick(int i,int j);
    void mark(int i,int j);//declaring the appropriate functions
};

void Board::place_mine(int pos){
    int i=pos/n;
    int j=pos%n;
    b[i][j]=1;
}//placing the mine 

void Board::mark(int i,int j){//it marks all the revealed blocks after player chooses i,j
    revealed[i][j]=1;
    int temp=0;
    bool flag=0;
    //checking if there is a mine surrounding the block
    if(i+1<n){
        flag=1;
        if(b[i+1][j]){temp++;}
    }
    if(i-1>=0){
        flag=1;
        if(b[i-1][j]){temp++;}
    }
    if(j+1<n){
        flag=1;
        if(b[i][j+1]){temp++;}
    }
    if(j-1>=0){
        flag=1;
        if(b[i][j-1]){temp++;}
    }
    if(i+1<n && j+1<n){
        flag=1;
        if(b[i+1][j+1]){temp++;}
    }
    if(i-1>=0 && j-1>=0){
        flag=1;
        if(b[i-1][j-1]){temp++;}
    }
    if(i+1<n && j-1>=0){
        flag=1;
        if(b[i+1][j-1]){temp++;}
    }
    if(i-1>=0 && j+1<n){
        flag=1;
        if(b[i-1][j+1]){temp++;}
    }
    if(temp==0 && flag){//if there is no mine sorrounding , marking the surrounding blocks
        if(i+1<n ){
            if(!revealed[i+1][j]){mark(i+1,j);}
        }
        if(i-1>=0){
            if(!revealed[i-1][j]){mark(i-1,j);}
        }
        if(j+1<n){
            if(!revealed[i][j+1]){mark(i,j+1);}
        }
        if(j-1>=0){
            if(!revealed[i][j-1]){mark(i,j-1);}
        }
        if(i+1<n && j+1<n){
            if(!revealed[i+1][j+1]){mark(i+1,j+1);}
        }
        if(i-1>=0 && j-1>=0){
            if(!revealed[i-1][j-1]){mark(i-1,j-1);}
        }
        if(i+1<n && j-1>=0){
            if(!revealed[i+1][j-1]){mark(i+1,j-1);}
        }
        if(i-1>=0 && j+1<n){
            if(!revealed[i-1][j+1]){mark(i-1,j+1);}
        }
    }
}

int Board::player_pick(int i, int j){//it counts the number of revealed blocks
    if(b[i][j]){return -1;}
    mark(i,j);
    int count=0;
    for(int l=0;l<n;l++){
        for(int m=0;m<n;m++){
            if(revealed[l][m]){count++;}
        }
    }
    return count;
}


int main() {
    int n,m;
    cin>>n>>m;
    Board b(n);
    for(int i=0;i<m;i++){
        int pos;
        cin>>pos;
        b.place_mine(pos);
    }
    int i,j;
    while(cin>>i){
        cin>>j;
        int k=b.player_pick(i,j);
        if(k==-1){
            cout<<"Lost"<<endl;
            break;
        }
        if(k==n*n-m){
            cout<<"Won"<<endl;
            break;
        }
        cout<<k<<endl;
    }
    
    
    return 0;
}
