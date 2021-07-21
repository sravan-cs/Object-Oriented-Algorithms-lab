#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include<string>
#include <algorithm>
using namespace std;

template<class T> class Vector{
    private:
    T* vec;
    size_t capacity;
    size_t currentSize;
    public:
    Vector(){
        vec=new T[1];
        capacity=1;
        currentSize=0;
    }//default constructor creating the array with one item
    Vector(size_t c){
        vec=new T[c+1];
        capacity=c;
        currentSize=0;
    }//constructor creating the array of size c
    Vector(size_t c,T x){
        vec=new T[c+1];
        for(size_t i=0;i<c;i++){
            vec[i]=x;
        }//constructor creating the array of size c and initialising them to x
        capacity=c;
        currentSize=c;
    }
    void freeSpace(){
        delete(vec);
    }//acts like a destructor
    size_t cap();
    size_t size();
    void push(T x);
    void pop();
    T front();
    T back();
    T operator[](size_t i);
    void sort(int first,int last);
    void printVector();//the public functions are declared
    protected:
    int partition(int first,int last);//the protected function is declared
};
template<class T>
size_t Vector<T>::cap(){
    return capacity;
}//returns the capacity of the vector
template<class T>
size_t Vector<T>::size(){
    return currentSize;
}//returns the size of the vector

template<class T>
void Vector<T>::push(T x){
    if(capacity!=currentSize){
        vec[currentSize]=x;
        currentSize++;
    }//inserting the element at the last if the array is not full
    else{
        T* temp=new T[2*capacity+1];
        for(size_t i=0;i<capacity;i++){
            temp[i]=vec[i];
        }//creating the array of double capacity if the array is full and copying the previous elements
        temp[capacity]=x;
        delete (vec);//deleting the previous array
        capacity*=2;
        currentSize++;
        vec=temp;
    }
}

template<class T>
void Vector<T>::pop(){
    if(currentSize!=0){currentSize--;}
}//removing the last element if exists

template<class T>
T Vector<T>::front(){
    if(currentSize==0){return -1;}
    else{return vec[0];}
}//returning the first element of the array if exists
template<class T>
T Vector<T>::back(){
    if(currentSize==0){return -1;}
    else {return vec[currentSize-1];}
}//returning the last element of the array if exist

template<class T>
T Vector<T>::operator[](size_t i){
    if(currentSize==0 || i>=currentSize){return -1;}
    else{return vec[i];}
}//overloading the [] operator to return the i th value in the array

template<class T>
void Vector<T>::sort(int first,int last){
    if(first<last){
        int p=partition(first,last);//p is the index of the element which is in its corrct position after doing the function
        if(p!=0){sort(first,p-1);}
        sort(p+1,last);//sorting the unsorted parts of the array
    }
}

template<class T>
int Vector<T>::partition(int first,int last){
    int i=first;
    int pivot=vec[i];//choosing the pivot as the first element
    for(int j=first+1;j<=last;j++){
        if(vec[j]<pivot){
            i++;
            int x=vec[i];
            vec[i]=vec[j];
            vec[j]=x;
        }
    }//vec[i] is always smaller element than pivot and vec[j] is not smaller which means that after the compleation of the loop first i elements are smaller than pivot and the remaining are not smaller than pivot
    int x=vec[first];
    vec[first]=vec[i];
    vec[i]=x;
    return i;
}

template<class T>
void Vector<T>::printVector(){
    for(size_t i=0;i<currentSize;i++){
        cout<<vec[i]<<" ";
    }
    cout<<endl;
}//functon to print a vector

int main() {
    string s;
    getline(cin,s);
    int c=-1;
    int x=-1;
    Vector<int> v;
    int index=7;
    if(index<s.size()){
        while(s[index]-'0'>=0 && s[index]-'0'<=9){
            if(c==-1){c++;}
            c=s[index]-'0'+c*10;
            index++;
        }
    }//checking if there is a 'c' and taking it if present
    index++;
    if(index<s.size()){
        while(s[index]-'0'>=0 && s[index]-'0'<=9){
            if(x==-1){x++;}
            x=s[index]-'0'+x*10;
            index++;
        }
    }//checking if there is an 'x' and taking it if present
    if(c!=-1 && x==-1){v=Vector<int> (c);}
    if(c!=-1 && x!=-1){v=Vector<int> (c,x);}//calling the constructors accordingly
    int q;
    cin>>q;
    for(int i=0;i<q;i++){
        cin>>s;
        if(s=="push"){
            cin>>x;
            v.push(x);
        }
        else if(s=="pop"){
            v.pop();
        }
        else if (s=="front"){
            cout<<v.front()<<endl;
        }
        else if(s=="back"){
            cout<<v.back()<<endl;
        }
        else if(s=="capacity"){
            cout<<v.cap()<<endl;
        }
        else if(s=="size"){
            cout<<v.size()<<endl;
        }
        else if(s=="element"){
            int j;
            cin>>j;
            cout<<v[j]<<endl;
        }
        else if(s=="sort"){
            v.sort(0,v.size()-1);
            v.printVector();
        }
    }//performing the given instructions on the vector
    v.freeSpace();
     
    
    return 0;
}
