#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//function used in implementing the method in matrix class to search for an element using binarysearch
int binSearch(int* a,int first,int last,int x){
    int mid=(first+last)/2;
    if(x<a[first]){return -1;}
    if(x>a[last]){return last;}//checking the base conditions
    if(a[mid]==x){
        if(a[mid+1]!=x){return mid;}
        else{return binSearch(a,mid+1,last,x);}
    }
    if(first==last){return first;}
    if(a[mid]>x) {
        last=mid-1;
        return binSearch(a,first,last,x);
    }
    else {
        if(a[mid+1]>x){return mid;}
        first=mid+1;
        return binSearch(a,first,last,x);
    }//calling the function recursively to search for the element in the half part of the array
    
}

class Matrix{
    public:
    int**m;
    int r;
    int c;//variables used to store the matrix , number of rows, number of columns respectively
    Matrix (int**matrix,int row,int column){
        m=matrix;
        r=row;
        c=column;
    }//constructor initialising the variables
    int binarySearch(int x,int k);
    int *matrixSearch(int x);//methods are declared
};

//function to find the element in a row using the binarysearch
int Matrix::binarySearch(int x, int k){
    return binSearch(m[k],0,c-1,x);
}

//function to search for the first occurance of an element 
int* Matrix::matrixSearch(int x){
    int *result;
    result=(int *)malloc(2*sizeof(int));
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(m[i][j]==x){
                result[0]=i;
                result[1]=j;
                return result;
            }
        }
    }//searching for the element trversing by the matrix in order
    result[0]=-1;
    result[1]=-1;
    return result;
}

//class derived from the base class Matrix
class MatrixMedian: public Matrix{
    public:
    using Matrix::Matrix;//calling the constructor;
    int upperBound(int x,int k);
    int findMedian();//declaring the methods
};

//function to find the upperbound for the element in a given row
int MatrixMedian::upperBound(int x,int k){
    int i=binarySearch(x,k);//inheriting the binarySearch method from the class Matrix
    if(i==-1){return 0;}
    else if(i==c-1){return -1;}//checking the base cases
    else{return i+1;}
    return-1;
}

//function to find the median of a matrix of odd order and row sorted with time complexity O(nlogm)
int MatrixMedian::findMedian(){
    if(c*r==1){return m[0][0];}//base case
    int idealCount=(c*r)/2;
    int min=m[0][0];
    int max=m[0][c-1];
    for(int i=0;i<r;i++){
        if(m[i][0]<min){min=m[i][0];}
        if(m[i][c-1]>max){max=m[i][c-1];}
    }//finding the minimum and maximum in the matrix
    int mid;
    int repCount=0;
    //the while loop splits the interval in which the median is present logarithamically
    while(max>min){
        int moreThanCount=0;
        mid=(min+max)/2;
        for (int i=0;i<r;i++){
            int u=upperBound(mid,i);
            if(u==-1){u=c;}
            moreThanCount+=c-u;
        }//finding the number of elements greater than mid
        if(min==max-1){//the if statement only comes into picture when there are negative numbers near the median
            repCount++;//if the condition is repeated more than once there is a negative number involved
            if(repCount==2){
                moreThanCount=0;
                for (int i=0;i<r;i++){
                    int u=upperBound(min,i);
                    if(u==-1){u=c;}
                    moreThanCount+=c-u;
                }
                if(moreThanCount<=idealCount){return min;}
                else{return max;}//handling the negative number case
            }
        }
        if(moreThanCount>idealCount){
            min=mid+1;
        }
        else{
            max=mid;
        }//searching for the median in the next half interval
    }
    return max;
}

int main() {
    int n,m;
    cin>>n>>m;
    int**mat;
    mat=(int**)malloc(n*sizeof(int*));
    for(int i=0;i<n;i++){
        mat[i]=(int*)malloc(m*sizeof(int));
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>mat[i][j];
        }
    }//storing the input matrix
    int q;
    cin>>q;
    Matrix M(mat,n,m);
    MatrixMedian Mm(mat,n,m);
    //addressing the queries and printing the output
    for(int i=0;i<q;i++){
        string s;
        cin>>s;
        if(s=="BS"){
            int x,k;
            cin>>x>>k;
            cout<<M.binarySearch(x,k)<<endl;
        }
        if(s=="MS"){
            int x;
            cin>>x;
            int* loc=(int*)malloc(2*sizeof(int));
            loc=M.matrixSearch(x);
            cout<<loc[0]<<" "<<loc[1]<<endl;
        }
        if(s=="Median"){
            cout<<Mm.findMedian()<<endl;
        }
    }
    return 0;
}