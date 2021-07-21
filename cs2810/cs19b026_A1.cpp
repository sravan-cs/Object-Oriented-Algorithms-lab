#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


class Matrix{
    
    public:
    int** mat;//pointer to create a 2D array
    int order;//to store the order of the matrix
    Matrix(int n,int** m){
        this->order=n;
        this->mat=m;
    }//class constructor initialising the order and the matrix
    void spSum();
    void mod();
    void maad(int x,Matrix m);
    void mrs(int k,Matrix m);//the functions declared to perform thee asked operations
    
};
    void Matrix::spSum(){
        for(int i=0;i<order;i++){
            int sum=0;
            for(int j=0;j<order;j++){
                    if((i+j)%2==1){
                        sum=sum+mat[j][i];
                        }
                    else{sum=sum+mat[i][j];}
            }//travelling the matrix row to row and checking if the index sum is odd and also performing the sum of newly formed row(virtual row)
            if(i==0){printf("%d",sum);}
            else{printf(",%d",sum);}
        }
        printf("\n");
    }

    void Matrix::mod(){
        int* result;//array to store the result of operations on each row
        long long int product;//to store the prduct of results of each row
        result=(int*)malloc(order*sizeof(int));
        for (int i=0;i<order;i++){
            if(i%3==0){
                int max=this->mat[i][0];
                for(int j=1;j<this->order;j++){
                    if(this->mat[i][j]>max){max=this->mat[i][j];}
                }
                result[i]=max;
            }//finding the maximum in the row if remainder of row index with 3 is 0
            else if(i%3==1){
                int min=this->mat[i][0];
                for(int j=1;j<this->order;j++){
                    if(this->mat[i][j]<min){min=this->mat[i][j];}
                }
                result[i]=min;
            }//finding the minimum in the row if remainder of row index with 3 is 1
            else{
                float avg=this->mat[i][0];
                for(int j=1;j<this->order;j++){
                    avg = avg+this->mat[i][j];
                }
                float o=this->order;
                avg=(avg/o);
                result[i]=avg;
            }//else finding the floor of average of the row
        }
        product=result[0];
        for (int i=1;i<order;i++){
            product = product*result[i];
        }
        printf("%lld\n",product);
    }

    void Matrix::maad(int x, Matrix m){

        if(x==1){
            for(int i=0;i<this->order;i++){
                for(int j=0;j<this->order;j++){
                    printf("%d ",this->mat[j][i]+m.mat[i][j]);
                }
                printf("\n");
            }
        }//traversing each element of the array row to row and adding the second matrix to the virtually swapped first matrix
        else if(x==2){
            for(int i=0;i<m.order;i++){
                for(int j=0;j<m.order;j++){
                    printf("%d ",this->mat[i][j]+m.mat[j][i]);
                }
                printf("\n");
            }
        }//traversing each element of the array row to row and adding the first matrix to the virtually swapped second matrix
        
    }

    void Matrix::mrs(int k,Matrix m){
        int o=order*order;//size of the temporary array
        k=k%o;
        int * temp;//temporary array to store the matrix sum row by row
        temp=(int*)malloc(o*sizeof(int));
        int l=0;
        for(int i=0;i<order;i++){
            for (int j=0;j<order;j++){
                temp[l]=this->mat[i][j]+m.mat[i][j];
                l++;
            }
        }//storing the sum of two matrices in the array
        for(l=0;l<o;l++){
            if(l<k){
                printf("%d ",temp[o-k+l]);
            }
            else {
                printf("%d ",temp[l-k]);
            }
            if(l%order==order-1){printf("\n");}
        }//printing the virtually shifted sum of matrices stored in the array
    }


int main() {
    int q;
    int n;
    cin>>q;
    cin>>n;
    int** mat1;
    mat1=(int**)malloc(n*sizeof(int*));
    for (int i=0;i<n;i++){
        mat1[i]=(int*)malloc(n*sizeof(int));
    }
    for(int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            cin>>mat1[i][j];
        }
    }//storing the first input matrx in mat1
    Matrix m1(n,mat1);//creating the object of Matrix class
    int** mat2;
    mat2=(int**)malloc(n*sizeof(int*));
    for (int i=0;i<n;i++){
        mat2[i]=(int*)malloc(n*sizeof(int));
    }
    for(int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            cin>>mat2[i][j];
        }
    }//storing the second input matrx in mat1
    Matrix m2(n,mat2);//creating the object of Matrix class
    string s;
    for(int i=0;i<q;i++){
        cin>>s;
        if(s=="SPSUM"){m1.spSum();}
        else if(s=="MOD"){m1.mod();}
        else if(s=="MRS"){
            int k=0;
            cin>>k;
            m1.mrs(k,m2);
        }
        else if(s=="MADD"){
            int x;
            cin>>x;
            m1.maad(x,m2);
        }
    }//performing the asked operations
    return 0;
}