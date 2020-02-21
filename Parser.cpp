#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

class FileOperations{
    private:
    string line;
    string dataInFile;

    public:
    FileOperations(){
        try{
            ifstream stream;
            stream.exceptions(ifstream::failbit);
            stream.open("usersCode.cpp");
            while(!stream.eof()){
                getline(stream, line);
                dataInFile+=line+"\n";
            }
            stream.close();
        }catch(exception& e){
            cout<<"Exception while opening usersCode: "<<e.what()<<endl;
        }
    }

    string getDataInFile(){
        return dataInFile;
    }
};

class Splitter : public FileOperations{
    private:
    set<char> delimiter = {' ', ',', '(', ')', '{', '}', ';', '<', '>', '*', ':', '!', '=', '.', '\"', '\'', '/'};
    vector<vector<string> >splitLines;

    public:
    Splitter(){
        vector<string> char_seq_vector;
        string char_sequence = "";
        string characters = getDataInFile();
        for(char character : characters){
            if(character == '\n'){
                if(char_sequence.length() > 0){
                    char_seq_vector.emplace_back(char_sequence);
                    char_sequence = "";
                }
                splitLines.emplace_back(char_seq_vector);
                char_seq_vector.clear();
                char_sequence = "";
                //cout<<endl;
            }
            else if(delimiter.find(character) == delimiter.end() && character != '\t'){
                char_sequence+=character;
            }
            else{
                if(char_sequence.length() > 0){
                    //cout<<char_sequence<<" ";
                    char_seq_vector.emplace_back(char_sequence);
                    char_sequence = "";
                }

                if(character != ' '){
                    //cout<<string(1, character)<<" ";
                    char_seq_vector.emplace_back(string(1, character));
                }
            }
            character = '\0';
        }
    }

    void viewSplitLines(){
        for(int counter=0; counter<splitLines.size(); counter++){
            for(int innerCounter=0; innerCounter<splitLines.at(counter).size(); innerCounter++){
                cout<<"\'"<<splitLines.at(counter).at(innerCounter)<<"\', ";
            }
            cout<<endl;
        }
    }
};

int main(){
    Splitter splitter;
    splitter.viewSplitLines();
    
    return 0;
}