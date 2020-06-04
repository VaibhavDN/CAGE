#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class compile
{
    char f_name[100];
    public:
    compile(char n[100])
    {
        int  i = 0;
        while(n[i] != '\0')
        {
            f_name[i] = n[i];
            i++;
        }
        f_name[i] = '\0';
    }
    void save(string code)
    {
        fstream file;
        file.open(f_name, ios::out);
        file << code;
        file.close();
    }

    void debug(string code)
    {
        for(int i = 0; i < code.length(); ++i)
        {
            if(code[i] == '{')
            {
                int j = i;
                while(code[--j] != '\n');
                code[j] = ' ';
            }
        }
        fstream file;
        file.open("usersCode2.cpp", ios::out);
        file << code;
        file.close();
        system("./VisualizeFlow");
    }

    void comp()
    {
        char s2[200] = "gnome-terminal -x sh -c 'g++ "; //+ f_name + "; ./a.out;echo ; echo ;echo Execution complete; echo press enter to exit; read line'";
        char s3[200] = "; echo; echo Code executes here : -; echo; echo;./a.out;echo ; echo ;echo Execution complete; echo press enter to exit; read line'";
        strcat(s2, f_name);
        strcat(s2, s3);
        system(s2);
    }
};