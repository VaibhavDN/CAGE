#include <iostream>
using namespace std;

void fun_call(){
    for(int i=0; i<5; i++){
        int m=i;
        m+=m;
    }
}

int main(){
    int n = 5;
    while(n--){
        if(n>2){
            if(n<10){
                for(int j=0; j<n; j++){
                    int m=j;
                    m=m%3;
                }
            }
            else{
                for(int k=0; k<2*n; k++){
                    if(k == 5){
                        int m=k;
                        m*=m;
                    }
                }
            }
        }
        else{
            fun_call();
        }
    }
    return 0;
}