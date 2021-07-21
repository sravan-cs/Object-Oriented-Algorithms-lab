#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class MaxExchange{
    vector<vector<bool>> colour;
    vector<int> nation_colour;
    vector<vector<float>> nation_currency;
    int col_count;
    int nation_count;
    public:
    MaxExchange(int c){
        colour=vector<vector<bool>>(c,vector<bool>(c,0));
        for(int i=0;i<c;i++){colour[i][i]=1;}
        col_count=c;
    }
    void initialize_nations(int n){
        nation_colour=vector<int>(n);
        nation_currency=vector<vector<float>> (n,vector<float>(n));
        nation_count=n;
    }
    void addC(int a,int b);
    void addNCo(int a,int b);
    void addNCu(int a,int b,float c);
    float calc_max(int s,int d);
};

void MaxExchange::addC(int a,int b){
    colour[a][b]=1;
    colour[b][a]=1;
}//adds an edge between two colours

void MaxExchange::addNCo(int a,int b){
    nation_colour[a]=b;
}//the arraay indicates which colour does a nation belong

void MaxExchange::addNCu(int a,int b,float c){
    nation_currency[a][b]=c;
}//it adds the directed weighted edge between two nations indicating the exchange value


float MaxExchange::calc_max(int s, int d){
    vector<float> ar(nation_count);//array to keep track of maximum exchange possible
    for(int i=0;i<nation_count;i++){
        ar[i]=0;
    }
    ar[s]=1;
    
    for (int i = 1; i <nation_count; i++) {//for each i we are getting maximum exchange value for a particular target if there is no cycle
        for (int j = 0; j <nation_count; j++) {
            for (int k = 0; k <nation_count; k++){
                if(colour[nation_colour[j]][nation_colour[k]]){
                    float weight = nation_currency[j][k];
                    if (ar[j] * weight > ar[k])
                        ar[k] = ar[j] * weight;
                }
            }
        }
    }

    if(ar[d]!=0){
        for (int i = 0; i < nation_count; i++) {
            for(int j=0;j<nation_count;j++){
                if(colour[nation_colour[i]][nation_colour[j]]){
                    float weight = nation_currency[i][j];
                    if (ar[i] * weight > ar[j] ) {
                        return -1;
                    }
                }
            }
        }//if there is an increasing weight cycle then the maximum will be further increased
    }
    
    return ar[d];
}


int main() {
    int c,m;
    cin>>c>>m;
    MaxExchange M(c);
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        M.addC(a,b);
    }
    int n;
    cin>>n;
    M.initialize_nations(n);
    for(int i=0;i<n;i++){
        int nc;
        cin>>nc;
        M.addNCo(i,nc);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            float cu;
            cin>>cu;
            M.addNCu(i,j,cu);
        }
    }
    int q;
    cin>>q;
    for(int i=0;i<q;i++){
        int s,t,x;
        cin>>s>>t>>x;
        float temp=M.calc_max(s,t);
        if(temp==0){cout<<-1<<endl;}
        else if(temp==-1){cout<<"INF"<<endl;}
        else{printf("%.3f\n",temp*x);}
        
    }
      
    return 0;
}
