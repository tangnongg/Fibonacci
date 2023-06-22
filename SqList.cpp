#include "Header/SqList.h"
#include <sys/types.h>
#include <iostream>

//template is not class,
//only a certain instance of the template(i.e. a class) can have member functions 
/*
template <typename newT>
void SqList<newT>::print(){}

void SqList<T>::print(){}

void Sqlist::print(){
    std::cout<<"'a member function of a template' not including template argments."
            <<std::endl;
} 
*/