#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
#define NO_OF_CHARACTERS 27

class TrieNode{
    private:
    TrieNode *childAlphabet[NO_OF_CHARACTERS];
    bool isEndOfWord = false;
    int keyWordType = -1;

    public:
    TrieNode(){
        //Initialize all 26 children as NULL
        for(int counter=0; counter<NO_OF_CHARACTERS; counter++){
            childAlphabet[counter] = NULL;
        }
    }

    void setEndOfWord(){
        isEndOfWord = true;
    }

    void unsetEndOfWord(){
        isEndOfWord = false;
    }

    void setKeyWordType(int type){
        keyWordType = type;
    }

    int getKeyWordType(){
        return keyWordType;
    }

    bool getIsEndOfWord(){
        return isEndOfWord;
    }

    TrieNode** getChildAlphabetArray(){
        return childAlphabet;
    }
};

class Trie{
    public:
    TrieNode *head = NULL, *childPointer = NULL;

    Trie(){
        string key_word;
        int key_word_type;
        vector<pair<string, int> > key_words_vector;
        ifstream filestream("CppKeyWords.txt");
        //filestream.exceptions(ifstream::failbit);
        while(!filestream.eof()){
            filestream>>key_word>>key_word_type;
            key_words_vector.emplace_back(make_pair(key_word, key_word_type));
        }
        filestream.close();

        for(pair<string, int> key_word_pair : key_words_vector){
            //cout<<key_words_vector[key_word]<<endl;
            key_word = key_word_pair.first;
            key_word_type = key_word_pair.second;
            try{
                insertInTrie(key_word, key_word_type);
            }
            catch(exception e){
                cout<<e.what()<<endl;
            }
        }
    }

    TrieNode* createNode(){
        return new TrieNode();
    }

    void insertInTrie(string word, int key_word_type){
        if(head == NULL){
            head = createNode();
        }
        childPointer = head;
        
        for(int counter=0; counter<word.length(); counter++){
            int index = word[counter] - 'a';
            if(index == -2){    //When character is _ ascii 95
                index = 26;
            }
            else if(index<0 || index>25){
                cout<<"index <0 or >25"<<endl;
                continue;
            }

            if(childPointer->getChildAlphabetArray()[index] == NULL){
                childPointer->getChildAlphabetArray()[index] = createNode();
                childPointer = childPointer->getChildAlphabetArray()[index];
            }
            else{
                childPointer = childPointer->getChildAlphabetArray()[index];
            }

            if(index == 26){
                cout<<static_cast<char>(index+97-26-2);
            }
            else{
                cout<<static_cast<char>(index+97);
            }
        }
        cout<<endl;
        childPointer->setEndOfWord();
        childPointer->setKeyWordType(key_word_type);
    }

    int searchInTrie(string wordToSearch){
        childPointer = head;
        for(int counter=0; counter<wordToSearch.length(); counter++){
            int index = wordToSearch[counter] - 'a';
            if(index == -2){    //When character is _ ascii 95
                index = 26;
            }
            else if(index<0 || index>25){
                continue;
            }

            if(childPointer->getChildAlphabetArray()[index] == NULL){
                return -1;
            }
            childPointer = childPointer->getChildAlphabetArray()[index];
        }

        if(childPointer->getIsEndOfWord()){
            return childPointer->getKeyWordType();
        }

        return -1;
    }
};

int main(){
    Trie trie;
    cout<<trie.searchInTrie("int")<<endl;
    return 0;
}