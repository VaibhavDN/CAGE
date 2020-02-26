#include <iostream>
#include <fstream>
#include <set>
#include <stack>
#include "Parser.cpp"
using namespace std;

int main(){
    set<char> lineToIgnoreIfCharPresent = {'}', ':'};
    stack<char> curlyBrackets;
    int lineNo = 0, initialized = 0, paranOpen = 0, paranClose = 0, functionOpen = 0, skip = 0, funStartNotifier = 0;
    string line, dataToWrite = "";

    Splitter splitter;

    ofstream streamLIFun("flowNode.txt");
    ifstream stream;
    stream.open("usersCode.cpp");
    while(!stream.eof()){
        getline(stream, line);
        lineNo++;
        while (line[line.length()-1] == ' ' || line[line.length()-1] == '\t')
        {
            line.pop_back();
        }
        if(line.length() == 0){
            //lineNo--;
            continue;
        }
        //cout<<line<<endl;
        splitter.setDataToTokenize(line+"\n");
        splitter.runSplitter();
        splitter.viewSplitLines();
        splitter.generateIntermediateLanguage();
        vector<vector<string> > tokenizedLine = splitter.getIntermediate_lang_vector();
        if(tokenizedLine[0][0] == "primaryDT" && functionOpen == 0){
            for(int counter=0; counter<tokenizedLine[0].size(); counter++){
                if(tokenizedLine[0][counter] == "("){
                    paranOpen = 1;
                }
                else if(tokenizedLine[0][counter] == ")" && paranOpen == 1){
                    paranClose = 1;
                }
                else if(tokenizedLine[0][counter] == "{" && paranClose == 1){
                    functionOpen = 1;
                    funStartNotifier = 1;
                    paranOpen = 0;
                    paranClose = 0;
                    dataToWrite+="/*fun=1*/";
                    continue;
                }
                else if(tokenizedLine[0][counter] == "}" && functionOpen == 1){ //For inline functions
                    functionOpen = 0;
                }
            }
        }
        else{
            if(tokenizedLine[0][0] == "{" && paranClose == 1){
                dataToWrite+="/**fun=1*/";
                functionOpen = 1;
                funStartNotifier = 1;
                paranOpen = 0;
                paranClose = 0;
            }
            else{
                paranOpen = 0;
                paranClose = 0;

                for(int counter=0; counter<tokenizedLine[0].size(); counter++){
                    if(tokenizedLine[0][counter] == "{" && functionOpen == 1){
                        curlyBrackets.push('{');
                        dataToWrite+="/*push->*/";
                    }
                    else if(tokenizedLine[0][counter] == "}"){
                        if(curlyBrackets.size() > 0){
                            curlyBrackets.pop();
                            dataToWrite+="/*pop->*/";
                            skip = 1;
                        }
                        else{   //Function ends
                            dataToWrite+="/*fun=0*/ ";
                            if(functionOpen == 1){
                                streamLIFun<<lineNo<<endl;
                                dataToWrite+="/*|funEnd|*/ ";
                            }
                            functionOpen = 0;
                        }
                    }
                    else if(tokenizedLine[0][counter] == "return_exit" && functionOpen == 1){
                        dataToWrite+="lineNo=" + to_string(lineNo) + "; streamLI<<lineNo<<endl;";
                        skip = 1;
                    }
                }
            }

        }

        if(functionOpen == 1 && skip == 0){
            dataToWrite+=line + " lineNo=" + to_string(lineNo) + "; streamLI<<lineNo<<endl;\n";
            if(funStartNotifier == 1){
                funStartNotifier = 0;
                streamLIFun<<lineNo<<" ";
            }
        }
        else{
            dataToWrite+=line + "\n";
            skip = 0;
        }

        if(tokenizedLine[0][0] != "preprocessor" && initialized == 0){
            initialized = 1;
            dataToWrite.pop_back(); //pop \n added by lines above
            dataToWrite+= " int lineNo=" + to_string(lineNo) + ";\n#include <fstream>\nofstream streamLI(\"flowOutput.txt\");\n";
            //lineNo+=2;
        }
    }
    stream.close();
    streamLIFun.close();

    ofstream stream_write;
    stream_write.open("usersFlow.cpp", ios_base::out);
    stream_write<<dataToWrite;
    stream_write.close();
    mainParser();
    return 0;
}