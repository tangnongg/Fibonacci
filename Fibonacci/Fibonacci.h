#pragma once

class Fibonacci{
public:
    int fun(int n){
        if(n==0)
            return 0;
        else if(n==1)
            return 1;
        else if(n>1){
            int former=0;
            int later=1;
            int i=2;
            while(i<=n){
                int tem=former+later;
                former=later;
                later=tem;
                ++i;
            }
            return later;
        }
        return -1;
    }

    int recursiveFun(int n){
        if(n==0)
            return 0;
        else if(n==1)
            return 1;
        else if(n>1)
            return recursiveFun(n-2)+recursiveFun(n-1);
        return -1;
    }
};