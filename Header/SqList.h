#pragma once

#include <string>
#include <iostream>
#include <cstdarg>

template <class T>
class SqList{
    private:
    T* data;
    int length;

    public:
    SqList(int size){
        data=new T[size];
        length=0;
    }

    SqList(int size, int length, ...){
        data=new T[size];
        va_list vaList;
        va_start(vaList, length);
        for(int i=0; i<length; ++i)
            data[i]=va_arg(vaList, T);
        va_end(vaList);
        this->length=length;
    }

    ~SqList(){
        delete [] data;
    }

    /*
        delete the element having the minimum value in the list(assuming it's unique),
        returning the value of the element.
    */
    T customDelete() throw(std::string);

    void swap(T& a, T& b);

    void reverse();

    void printAll(){
        for(int i=0; i<=length-1; ++i){
            if(i==length-1){
                std::cout<<data[i]<<std::endl;
                return;
            }
            std::cout<<data[i]<<", ";
        }
    }

    void deleteAllValueX(T x){
        for(int i=length-1; i>=0; --i){
            if(data[i]==x){
                for(int j=i; j<=length-2; ++j){
                    data[i]=data[i+1];
                }
                --length;
            }
        }
    }

    void bubbleSort(bool order){
        bool swapFlag=1;
        for(int i=0; i<=length-2; ++i){
            if(swapFlag==1){//checking out if there are swapings in this round.
                swapFlag=0;
                for(int j=0; j<=length-2-i; ++j){
                    if(order==0){//sort in ascending order
                        if(data[j]>data[j+1]){
                            swap(data[j], data[j+1]);
                            swapFlag=1;
                        }
                    }
                    else{
                        if(data[j]<data[j+1]){
                            swap(data[j], data[j+1]);
                            swapFlag=1;
                        }
                    }
                }
            }
            else 
                return;
        }
    }
};


template <typename T>
T SqList<T>::customDelete() throw(std::string){
    if(length==0){
        try{
            throw std::string("the linear list is empty!");
        }
        catch(std::string str){
            throw str;
        }
    }

    int minIndex=0;
    for(int i=0; i<=length-1; ++i){
        if(data[i]<data[minIndex])
            minIndex=i;
    }
    T temp=data[minIndex];
    data[minIndex]=data[length-1];
    --length;
    return temp;
}


template <typename T>
void SqList<T>::swap(T &a, T &b){
    T temp=a;
    a=b;
    b=temp;
}


template <typename newT>
void SqList<newT>::reverse(){
    if(length==0){
        std::cout<<"the linear list is empty!"<<std::endl;
        exit(-1);
    }

    for(int i=0; i<=length/2-1; ++i)
        swap(data[i], data[length-1-i]);
}