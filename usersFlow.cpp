#include <iostream>
using namespace std; int lineNo=2;
#include <fstream>
ofstream streamLI("flowOutput.txt");
/*fun=1*/void fun_call(){ lineNo=4; streamLI<<lineNo<<endl;
/*push->*/    for(int i=0; i<5; i++){ lineNo=5; streamLI<<lineNo<<endl;
        int m=i; lineNo=6; streamLI<<lineNo<<endl;
        m+=m; lineNo=7; streamLI<<lineNo<<endl;
/*pop->*/    }
/*fun=0*/ /*|funEnd|*/ }
/*fun=1*/int main(){ lineNo=11; streamLI<<lineNo<<endl;
    int n = 5; lineNo=12; streamLI<<lineNo<<endl;
/*push->*/    while(n--){ lineNo=13; streamLI<<lineNo<<endl;
/*push->*/        if(n>2){ lineNo=14; streamLI<<lineNo<<endl;
/*push->*/            if(n<10){ lineNo=15; streamLI<<lineNo<<endl;
/*push->*/                for(int j=0; j<n; j++){ lineNo=16; streamLI<<lineNo<<endl;
                    int m=j; lineNo=17; streamLI<<lineNo<<endl;
                    m=m%3; lineNo=18; streamLI<<lineNo<<endl;
/*pop->*/                }
/*pop->*/            }
/*push->*/            else{ lineNo=21; streamLI<<lineNo<<endl;
/*push->*/                for(int k=0; k<2*n; k++){ lineNo=22; streamLI<<lineNo<<endl;
/*push->*/                    if(k == 5){ lineNo=23; streamLI<<lineNo<<endl;
                        int m=k; lineNo=24; streamLI<<lineNo<<endl;
                        m*=m; lineNo=25; streamLI<<lineNo<<endl;
/*pop->*/                    }
/*pop->*/                }
/*pop->*/            }
/*pop->*/        }
/*push->*/        else{ lineNo=30; streamLI<<lineNo<<endl;
            fun_call(); lineNo=31; streamLI<<lineNo<<endl;
/*pop->*/        }
/*pop->*/    }
lineNo=34; streamLI<<lineNo<<endl;    return 0;
/*fun=0*/ /*|funEnd|*/ }
