#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
#define NO_OF_CHARACTERS 27

class TrieNode{
    private:
    TrieNode *childAlphabet[NO_OF_CHARACTERS];
    bool isEndOfWord = false;

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
        vector<string> key_words_vector;
        ifstream filestream("CppKeyWords.txt");
        //filestream.exceptions(ifstream::failbit);
        while(!filestream.eof()){
            filestream>>key_word;
            key_words_vector.emplace_back(key_word);
        }
        filestream.close();

        for(string key_word : key_words_vector){
            //cout<<key_words_vector[key_word]<<endl;
            try{
                insertInTrie(key_word);
            }
            catch(exception e){
                cout<<e.what()<<endl;
            }
        }
    }

    TrieNode* createNode(){
        return new TrieNode();
    }

    void insertInTrie(string word){
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
    }

    bool searchInTrie(string wordToSearch){
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
                return false;
            }
            childPointer = childPointer->getChildAlphabetArray()[index];
        }

        if(childPointer->getIsEndOfWord()){
            return true;
        }

        return false;
    }
};

int main(){
    Trie trie;
    cout<<trie.searchInTrie("include")<<endl;
    return 0;
}