#include <iostream>
#include <fstream>

using namespace std;

class compile
{
    string f_name;
    public:
    void save(string code)
    {
        fstream file;
        f_name = "ts1.cpp";
        file.open(f_name, ios::out);
        file << code;
        file.close();
    }

    void comp()
    {
        system("gnome-terminal -x sh -c 'g++ ts1.cpp -o ts1 ; ./ts1;echo ; echo ;echo Execution complete; echo press enter to exit; rm ts1; read line'");
    }
};