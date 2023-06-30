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

    SqList(int size, int length, ...);

    /*
    deep copy constructor
    */
    SqList(const SqList<T>& list);

    /*
    deep copy assignment operator
    */
    void operator=(const SqList<T>& list);

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

    const T& getData(int i) const{
        return data[i];
    }

    void setData(int i, const T& elem) {
        data[i] = elem;
    }

    /*
        delete the element having the minimum value in the list(assuming it's unique),
        returning the value of the element.
        if there is more than one element with the minium value, delete the element that first appear.
    */
    T customDelete() throw(std::string);

    void swap(T& a, T& b);

    void reverse();

    void printAll();

    void deleteAllValueX(T x);

    void bubbleSort(bool order);

    void deleteAllValuesBetween_s_And_t(const T& s, const T& t, bool strategy = 0);

    bool isAscending();

    void beingNoSameElement(bool strategy = 0);

    /*
        在pos上插入一个元素elem。pos是位序，而非数组下标
    */
    void insertAt_pos(int pos, T elem);

    /*
        反转表中第s个元素到第e个元素之间的元素，包括两个端点元素。s,e>0
    */
    void reverse(int s, int e);

    /*
        长度为length的表的前后两部分分别作为长度为m和m的两个表，交换两个表的位置
    */
    bool swapTwoPart(int m, int n);

    /*
        数组中的每天元素循环左移n个位置，swapTwoPart()是这个函数的一个特例
    */
    void cyclicLeftShift(int n);

    /*
        返回具有值x的元素的数组下标
    */
    int binarySearch(T x);

    int find_x_and_DoSth(int x);

    /*
        合并另一个表和当前表到一个新表，返回合并生成的表。
        strategy=0:将scdList追加到该list的尾部；
        strategy=1:先分别排成两个升序序列，再合并成一个升序序列。1：两个升序合成一个升序；2：两个序列连接，再升序排序
    */
    SqList<T> emergetoNewList(SqList<T> scdList, bool strategy = 0);

    /*
        将另一个表合并到当前的表。
    */
    void emerge(SqList<T> scdList, bool strategy = 0);

    /*
        求两个序列的中位数，即他们合并之后的升序序列的中位数。
    */
    T middleElement(SqList<T> scdList) {
    
    }

    /*
        求序列的主元素。
    */
    T mainElement(SqList<T> scdList) {

    }
};//SqList






template<class T>
inline SqList<T>::SqList(int size, int length, ...) {
    if (size >= length) {
        this->length = length;
        this->size = size;
        data = new T[size];
        va_list vaList;
        va_start(vaList, length);
        for (int i = 0; i < length; ++i)
            data[i] = va_arg(vaList, T);
        va_end(vaList);
    }
}

/*
deep copy constructor
*/
template<class T>
inline SqList<T>::SqList(const SqList<T>& list) {
    length = list.length;
    size = list.size;
    data = new T[size];//first to inite the member pointer, otherwise it would be a wild pointer.
    for (int i = 0; i <= length - 1; ++i) {
        data[i] = list.data[i];
    }
}

template<class T>
void SqList<T>::operator=(const SqList<T>& list) {
    length = list.length;
    size = list.size;
    if (data != nullptr)
        delete[] data;
    data = new T[size];
    for (int i = 0; i <= length - 1; ++i) {
        data[i] = list.data[i];
    }
}

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

template<class T>
inline void SqList<T>::printAll() {
    for (int i = 0; i <= length - 1; ++i) {
        if (i == length - 1) {
            std::cout << data[i] << std::endl;
            return;
        }
        std::cout << data[i] << ", ";
    }
}

template<class T>
inline void SqList<T>::deleteAllValueX(T x) {
    for (int i = length - 1; i >= 0; --i) {
        if (data[i] == x) {
            for (int j = i; j <= length - 2; ++j) {
                data[i] = data[i + 1];
            }
            --length;
        }
    }
}

template<class T>
inline void SqList<T>::bubbleSort(bool order) {
    bool swapFlag = 1;
    for (int i = 0; i <= length - 2; ++i) {
        if (swapFlag == 1) {//checking out if there are swapings in this round.
            swapFlag = 0;
            for (int j = 0; j <= length - 2 - i; ++j) {
                if (order == 0) {//sort in ascending order
                    if (data[j]>data[j + 1]) {
                        swap(data[j], data[j + 1]);
                        swapFlag = 1;
                    }
                }
                else {//sort in descending order
                    if (data[j]<data[j + 1]) {
                        swap(data[j], data[j + 1]);
                        swapFlag = 1;
                    }
                }
            }
        }
        else
            return;
    }
}

template<class T>
inline void SqList<T>::deleteAllValuesBetween_s_And_t(const T& s, const T& t, bool strategy) {
    if (s>t) {
        std::cout << "wrong s and t!" << std::endl;
        return;
    }
    if (length == 0) {
        std::cout << "empty list!" << std::endl;
        return;
    }
    if (strategy == 0) {//first sort this list in ascending order.
        bubbleSort(0);
        int sPos, tPos;
        bool sPosFound = 0; bool tPosFound = 0;
        for (int i = 0; i <= length - 1; ++i) {
            if (sPosFound == 0) {
                if (data[i] >= s) {
                    sPos = i;
                    sPosFound = 1;
                }
            }
            if (tPosFound == 0) {
                if (data[i] >= t) {
                    tPos = i;
                    tPosFound = 1;
                }
                if (tPosFound == 1) {//to incorrect tPos in case there are the same element int the list
                    while (tPos + 1 != length - 1 && data[tPos + 1] == data[tPos]) {
                        ++tPos;
                    }
                }
            }
        }
        int deleteCount = tPos - sPos + 1;
        if (tPos != length - 1) {
            for (int i = 0; i <= deleteCount; ++i) {
                if (sPos + i <= length - 1) {
                    data[sPos + i] = data[tPos + 1 + i];
                }
            }
        }
        length = length - deleteCount;
    }//strategy=0
    else {//not to sort this list in ascenging order in advance.
        for (int i = length - 1; i >= 0; --i) {
            if (data[i] >= s && data[i] <= t) {
                if (i != length - 1) {
                    for (int j = i; j <= length - 1; ++j) {
                        data[j] = data[j + 1];
                    }
                }
                --length;
            }
        }
    }//strategy==1
}

template<class T>
inline bool SqList<T>::isAscending() {
    for (int i = 0; i <= length - 2; ++i) {
        if (data[i]>data[i + 1])
            return false;
    }
    return true;
}

template<class T>
inline void SqList<T>::beingNoSameElement(bool strategy) {
    if (length == 0 || length == 1)
        return;
    if (strategy == 0) {//get this list in ascending order first
        if (!isAscending())
            bubbleSort(0);
        T pre = data[length - 1];
        for (int i = length - 2; i >= 0; --i) {
            if (data[i] == pre) {
                for (int j = i; j <= length - 2; ++j) {
                    data[j] = data[j + 1];
                }
                --length;
            }
            else {
                pre = data[i];
            }
        }
    }//strategy==0
    else {//not to make this list in ascending order in advance.
        for (int i = 0; i <= length - 1; ++i) {
            for (int j = i + 1; j <= length - 1;) {
                if (data[j] == data[i]) {
                    for (int k = j; k <= length - 2; ++k) {
                        data[k] = data[k + 1];
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

/*
在pos上插入一个元素elem。pos是位序，而非数组下标
*/
template<class T>
inline void SqList<T>::insertAt_pos(int pos, T elem) {
    if (pos >= 1 || pos <= length + 1) {
        if (length + 1>size) {//like vector' mechanism
            size += 10;
            T* temp = new T[size];
            for (int i = 0; i <= length - 1; ++i)
                temp[i] = data[i];
            if (data)
                delete[] data;
            data = temp;
        }
        for (int i = length - 1; i >= pos - 1; --i)
            data[i + 1] = data[i];
        data[pos - 1] = elem;
        ++length;
    }
}

/*
    反转表中第s个元素到第e个元素之间的元素，包括两个端点元素。s,e>0，s,n为位序
*/
template<class T>
inline void SqList<T>::reverse(int s, int e) {
    if (s >= e)
        return;
    for (int i = 0; i < (e - s + 1) / 2; ++i) {
        swap(data[s - 1 + i], data[e - 1 - i]);
    }
}

/*
长度为length的表的前后两部分分别作为长度为m和m的两个表，交换两个表的位置
*/
template<class T>
inline bool SqList<T>::swapTwoPart(int m, int n) {
    if (m + n != length)
        return false;
#if 0//strategy 1:挪
    for (int i = 0; i <= n - 1; ++i) {
        T temp = data[m + i];
        for (int j = 0; j <= m - 1; ++j) {
            data[m + i - j] = data[m + i - j - 1];
        }
        data[i] = temp;
    }
    return true;
#elif 0//strategy 2:另一种挪法*
    for (int i = 0; i <= n - 1; ++i) {
        T temp = data[length - 1];
        for (int j = 0; j <= length - 1; ++j)
            data[length - 1 - j] = data[length - 1 - 1 - j];
        data[0] = temp;
    }
    return 0;
#elif 0//stratrgy 3:先reverse，再swap，最后reverse多出部分
    reverse(1, m);
    reverse(m + 1, m + n);
    int minLength = std::min<int>(m, n);
    for (int i = 0; i <= minLength - 1; ++i)
        swap(data[0 + i], data[length - 1 - i]);
    if (m>n)
        reverse(n + 1, n + int(std::abs(m - n)));
    else if (m<n)
        reverse(m + 1, m + int(std::abs(m - n)));
    return true;
#elif 0//strategy 4:三个reverse*
    reverse(1, m);
    reverse(m + 1, m + n);
    reverse(1, m);
    return true;
#else //strategy 5:辅助数组 auxiliary array
    T *auxArr = new T[size_t(n + m)];//前面的数组长度为m,后者为n;note: 模板创建不了静态数组，因为要编译器分配，要知道类型的大小。
    for (int i = 0; i <= n - 1; ++i)
        auxArr[i] = data[m + i];
    for (int i = 0; i <= m - 1; ++i)
        auxArr[n + i] = data[i];

    for (int i = 0; i <= m + n - 1; ++i)
        data[i] = auxArr[i];

    return true;
#endif
}

/*
数组中的每天元素循环左移n个位置，swapTwoPart()是这个函数的一个特例
*/
template<class T>
inline void SqList<T>::cyclicLeftShift(int n) {
    reverse(1, n);
    reverse(n + 1, length);
    reverse(1, length);
}

template<class T>
inline int SqList<T>::binarySearch(T x) {
    if (!isAscending())
        return -2;
    int low = 0; int high = length - 1;
    int mid = (low + high) / 2;
    while (low < high) {
        if (data[mid] > x)
            high = mid - 1;
        else if (data[mid] < x)
            low = mid + 1;
        else
            return mid;
        mid = (low + high) / 2;
    }
    return -1;//表中无被查元素
}

template<class T>
inline int SqList<T>::find_x_and_DoSth(int x) {
    int index = binarySearch(x);
    if (index == -2)//表非升序表
        return -2;
    if (index == -1) {//表中无被查元素
        if (length + 1 > size) {
            size += 10;
            T* temp = new T[size];
            for (int i = 0; i <= length - 1; ++i)
                temp[i] = data[i];
            if (data)
                delete[] data;
            data = temp;
        }
        int insertPos;
        for (insertPos = 0; insertPos <= length - 1; ++insertPos)
            if (data[insertPos] > x)
                break;
        for (int i = length - 1; i >= insertPos; --i)
            data[i + 1] = data[i];
        data[insertPos] = x;
        ++length;
        return 1;
    }
    else {//表中有被查元素
        if (index != length - 1)
            swap(data[index], data[index + 1]);
        return 2;
    }
}


/*
strategy=0:将scdList追加到该list的尾部；
strategy=1:先分别排成两个升序序列，再合并成一个升序序列。1：两个升序合成一个升序；2：两个序列连接，再升序排序
*/
template<class T>
inline SqList<T> SqList<T>::emergetoNewList(SqList<T> scdList, bool strategy) {
    if (strategy == 0) {
        SqList<T> retList(length + scdList.getLength(), length + scdList.getLength());
        for (int i = 0; i <= length - 1; ++i)
            retList.setData(i, data[i]);
        for (int i = 0; i <= scdList.getLength() - 1; ++i)
            retList.setData(length + i, scdList.getData(i));
        return retList;
    }
    else {//strategy = 1
#if 0 //实现：两个序列连接，再升序排序
        SqList<T> retList(length + scdList.getLength(), length + scdList.getLength());
        for (int i = 0; i <= length - 1; ++i)
            retList.setData(i, data[i]);
        for (int i = 0; i <= scdList.getLength() - 1; ++i)
            retList.setData(length + i, scdList.getData(i));
        retList.bubbleSort(0);
#else //实现：两个升序合成一个升序
        if (!isAscending())
            bubbleSort(0);
        if (!isAscending())
            scdList.bubbleSort(0);
        SqList<T> retList(length + scdList.getLength(), length + scdList.getLength());

        int i_scdL = 0; int i_thisL = 0;//i_scdL for scdList, i_thisL for this list, i_retL for retList
        for (int i_retL = 0; i_scdL <= scdList.getLength() - 1 && i_thisL <= length - 1; ++i_retL) {
            if (scdList.getData(i_scdL) <= data[i_thisL]) {
                retList.setData(i_retL, scdList.getData(i_scdL));
                ++i_scdL;
            }
            else {
                retList.setData(i_retL, data[i_thisL]);
                ++i_thisL;
            }
        }
        //note: 没插完的表的“指针”还没有达到表尾的下一元素。
        //某一个表插完，对应的“指针”已经指定表尾的下一个元素。
        if (i_scdL <= scdList.getLength()) {//scdList插入完了，this list的后续直接追加到目的retList
            while (i_thisL <= length) {
                retList.setData(i_thisL + i_scdL, data[i_thisL]);
                ++i_thisL;
            }
        }
        if (i_thisL <= length) {////this list插入完了，scdList的后续直接追加到目的retList
            while (i_scdL <= scdList.getLength()) {
                retList.setData(i_scdL + i_thisL, scdList.getData(i_scdL));
                ++i_scdL;
            }
        }
#endif
        return retList;
    }
}

template<class T>
inline void SqList<T>::emerge(SqList<T> scdList, bool strategy) {
    if (length + scdList.getLength() > size) {//increase only the size as necessary，not length.
        size = length + scdList.getLength();
        T* temp = new T[size];
        for (int i = 0; i <= length - 1; ++i)
            temp[i] = data[i];
        if (data)
            delete[] data;
        data = temp;
    }
    if (strategy == 0) {//strategy == 0
        for (int i = 0; i <= scdList.getLength() - 1; ++i) {
            data[length] = scdList.getData(i);
            ++length;
        }
    }
    else {//strategy == 1 实现:一个表中的元素逐个插入到另一个表中。
        for (int i = 0; i <= scdList.getLength() - 1; ++i) {
            int j;
            for (j = 0; j <= length - 1; ++j) {
                if (scdList.getData(i) <= data[j]) {//查到插入位置j(0<=j<=length-1)，需要挪位置
                    for (int k = length; k >= j + 1; --k) {
                        data[k] = data[k - 1];
                    }
                    break;//已经查到位置，跳出去，不要破坏了正确的j
                }     
            }
            //此时的j就是要插入的位置
            data[j] = scdList.getData(i);
            ++length;
        }
    }
}
