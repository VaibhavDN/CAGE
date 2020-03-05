#include <iostream>
using namespace std;


int main(){ //depth 1 level 0
    int n = 5;
    if(n>2){    //depth 2 level 1
        if(n<10){   //depth 3 level 2
            for(int j=0; j<n; j++){ //depth 4 level 3
                //pass
            }
        }
        else{   //depth 3 level 2
            for(int k=0; k<2*n; k++){   //depth 4 level 3
                if(k == 5){ //depth 5 level 4
                    //pass
                }
            }
        }
    }
    return 0;
}

/*
4 6 0
12 14 3
11 15 2
18 20 4
17 21 3
16 22 2
10 23 1
8 25 0
*/
