#include "CodeAnalyzer.cpp"

class FileOperations{
    private:
    string line;
    string dataInFile;
    vector<vector<string> > intermediate_lang;

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

    void setIntermediate_lang_vector(vector<vector<string> > vec){
        intermediate_lang = vec;
    }

    void write_intermediate_lang(){
        try{
            ofstream stream;
            stream.open("Int_Lang.cage", ios_base::out);
            for(int counter = 0; counter<intermediate_lang.size(); counter++){
                for(int innerCounter = 0; innerCounter<intermediate_lang.at(counter).size(); innerCounter++){
                    stream<<intermediate_lang.at(counter).at(innerCounter)<<" ";
                }
                stream<<"\n";
            }
            stream.close();
        }
        catch(exception e){
            cout<<e.what()<<endl;
        }
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

    void generateIntermediateLanguage(){
        Trie trie;
        Key_word_category key_word_category;
        vector<vector<string> > newSplitLines;
        for(int counter=0; counter<splitLines.size(); counter++){
            vector<string> new_word_vector; 
            for(int innerCounter=0; innerCounter<splitLines.at(counter).size(); innerCounter++){
                string word_in_vec = splitLines.at(counter).at(innerCounter);
                int key = trie.searchInTrie(word_in_vec);
                if(key != -1){
                    string category = key_word_category.getCategory(key);
                    new_word_vector.emplace_back(category);
                    cout<<"\'"<<category<<"\', ";
                }
                else{
                    new_word_vector.emplace_back(word_in_vec);
                    cout<<"\'"<<word_in_vec<<"\', ";
                }
            }
            newSplitLines.emplace_back(new_word_vector);
            new_word_vector.clear();
            cout<<endl;
        }

        setIntermediate_lang_vector(newSplitLines);
        write_intermediate_lang();
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
    splitter.generateIntermediateLanguage();
    return 0;
}