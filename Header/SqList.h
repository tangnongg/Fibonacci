#pragma once

#include <string>
#include <iostream>
#include <cstdarg>

template <class T>
class SqList{
    private:
    T* data;
    int length;
    int size;

    public:
    SqList(){
        length=0;
        size=0;
        data=nullptr;
    }

    SqList(int size){
        this->size=size;
        data=new T[size];
        length=0;
    }

    SqList(int size, int length, ...){
        this->size=size;
        data=new T[size];
        va_list vaList;
        va_start(vaList, length);
        for(int i=0; i<length; ++i)
            data[i]=va_arg(vaList, T);
        va_end(vaList);
        this->length=length;
    }

    /*
    deep copy constructor
    */
    SqList(const SqList<T>& list){
        length=list.length;
        size=list.size;
        data=new T[size];//first to inite the member pointer, otherwise it would be a wild pointer.
        for(int i=0; i<=length-1; ++i){
            data[i]=list.data[i];
        }
    }

    /*
    deep copy assignment operator
    */
    void operator=(const SqList<T>& list){
        length=list.length;
        size=list.size;
        if(data!=nullptr)
            delete[] data;
        data=new T[size];
        for(int i=0; i<=length-1; ++i){
            data[i]=list.data[i];
        }
    }

    ~SqList(){
        if(data!=nullptr)
            delete[] data;
    }

    const int& getLength() const{
        return length;
    }

    const int& getSize() const{
        return size;
    }

    const T* getData() const{
        return data;
    }

    /*
        delete the element having the minimum value in the list(assuming it's unique),
        returning the value of the element.
        if there is more than one element with the minium value, delete the element that first appear.
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
                    else{//sort in descending order
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

    void deleteAllValuesBetween_s_And_t(const T& s, const T& t, bool strategy=0){
        if(s>t){
            std::cout << "wrong s and t!"<< std::endl;
            return;
        }
        if(length==0){
            std::cout << "empty list!" << std::endl;
            return;
        }
        if(strategy==0){//first sort this list in ascending order.
            bubbleSort(0);
            int sPos, tPos;
            bool sPosFound=0; bool tPosFound=0;
            for(int i=0; i<=length-1; ++i){
                if(sPosFound==0){
                    if(data[i]>=s){
                        sPos=i;
                        sPosFound=1;
                    }
                }
                if(tPosFound==0){
                    if(data[i]>=t){
                        tPos=i;
                        tPosFound=1;
                    }
                    if(tPosFound==1){//to incorrect tPos in case there are the same element int the list
                        while(tPos+1!=length-1 && data[tPos+1]==data[tPos]){
                            ++tPos;
                        }
                    }
                }
            }
            int deleteCount=tPos-sPos+1;
            if(tPos!=length-1){
                for(int i=0; i<=deleteCount; ++i){
                    if(sPos+i<=length-1){
                        data[sPos+i]=data[tPos+1+i];
                    }
                }
            }
            length=length-deleteCount;
        }//strategy=0
        else{//not to sort this list in ascenging order in advance.
            for(int i=length-1; i>=0; --i){
                if(data[i]>=s && data[i]<=t){
                    if(i!=length-1){
                        for(int j=i; j<=length-1; ++j){
                            data[j]=data[j+1];
                        }
                    }
                    --length;
                }
            }
        }//strategy==1
    }

    bool isAscending(){
        for(int i=0; i<=length-2; ++i){
            if(data[i]>data[i+1])
                return false;
        }
        return true;
    }

    void beingNoSameElement(bool strategy=0){
        if(length==0 || length==1)
            return;
        if(strategy==0){//get this list in ascending order first
            if(!isAscending())
                bubbleSort(0);
            T pre=data[length-1];
            for(int i=length-2; i>=0; --i){
                if(data[i]==pre){
                    for(int j=i; j<=length-2; ++j){
                        data[j]=data[j+1];
                    }
                    --length;
                }
                else{
                    pre=data[i];
                }
            }
        }//strategy==0
        else{//not to make this list in ascending order in advance.
            for(int i=0; i<=length-1; ++i){
                for(int j=i+1; j<=length-1;){
                    if(data[j]==data[i]){
                        for(int k=j; k<=length-2; ++k){
                            data[k]=data[k+1];
                        }
                        --length;
                    }
                    else {
                        ++j;
                    }
                }
            }
        }
    }

    void insertAt_pos(int pos, T elem){
        
    }
};//SqList




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