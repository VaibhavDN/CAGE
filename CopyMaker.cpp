#include <iostream>
#include <fstream>
using namespace std;

void makeCopy(string filePath){
    string data;
    ifstream inputFile;
    ofstream outputFile;
    inputFile.open(filePath);
    outputFile.open("temp.cpp");

    while(!inputFile.eof()){
        getline(inputFile, data);
        outputFile<<data<<endl;
    }

    inputFile.close();
    outputFile.close();

    cout<<"Copy created.."<<endl;
}

int main(){
    string filePath;
    cout<<"Enter the file path to start lexer: ";
    cin>>filePath;
    makeCopy(filePath);
    return 0;
}
