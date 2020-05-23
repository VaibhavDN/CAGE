#include <stack>
#include <string>
#include "Parser.cpp"
using namespace std;

class LineInserter{
    private:
    set<char> lineToIgnoreIfCharPresent = {'}', ':'};
    stack<int> curlyBrackets;
    stack<string> block_line_stack;
    int lineNo = 0, initialized = 0, paranOpen = 0, node_counter = 0;
    int paranClose = 0, functionOpen = 0, skip = 0, funStartNotifier = 0, level = -1;   //level of how deep is block inside other blocks
    string line, dataToWrite = "";
    vector<string> block_first_line;
    map<int, string> user_code_linewise;

    public:

    void insert_block_first_line(string line){
        //Remove space from front
        reverse(line.begin(), line.end());
        while (line[line.length()-1] == ' ' || line[line.length()-1] == '\t')
        {
            line.pop_back();
        }
        reverse(line.begin(), line.end());
        block_first_line.emplace_back(line);
    }

    int mainLineInserter(){
        Splitter splitter;

        ofstream streamLIBlock("flowNode.txt");
        ifstream stream;
        stream.open(USER_CODE);
        while(!stream.eof()){
            getline(stream, line);
            lineNo++;
            user_code_linewise.insert(make_pair(lineNo, line));
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
            if(tokenizedLine[0][0] == "userDefinedDT" && tokenizedLine[0].size() > 1){
                cout<<"\n\n|"<<tokenizedLine[0][1]<<"|\n"<<endl;                
                splitter.insert_code_analyzer(tokenizedLine[0][1], 12);
                splitter.generateIntermediateLanguage();
                tokenizedLine = splitter.getIntermediate_lang_vector();
                cout<<"\n\n|"<<tokenizedLine[0][1]<<"|\n"<<endl;
                //exit(1);
            }

            if(functionOpen == 0){
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
                        level++;
                        node_counter++;
                        continue;
                    }
                    else if(tokenizedLine[0][counter] == "}" && functionOpen == 1){ //For inline functions
                        functionOpen = 0;
                        level--;
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
                    level++;
                    node_counter++;
                }
                else{
                    paranOpen = 0;
                    paranClose = 0;

                    for(int counter=0; counter<tokenizedLine[0].size(); counter++){
                        if(tokenizedLine[0][counter] == "{" && functionOpen == 1){
                            curlyBrackets.push(lineNo);
                            dataToWrite+="/*push->*/";
                            level++;
                            block_line_stack.push(line);
                            node_counter++;
                        }
                        else if(tokenizedLine[0][counter] == "}"){
                            if(curlyBrackets.size() > 1){
                                int top = curlyBrackets.top();
                                curlyBrackets.pop();
                                streamLIBlock<<top<<" "<<lineNo<<" "<<level<<endl;
                                string top_line = block_line_stack.top();
                                block_line_stack.pop();
                                insert_block_first_line(top_line);
                                cout<<"Line: "<<top<<" Top line pop-> "<<top_line<<endl;
                                dataToWrite+="/*pop->*/";
                                skip = 1;
                                level--;
                            }
                            else{   //Function ends
                                dataToWrite+="/*fun=0*/ ";
                                if(functionOpen == 1){
                                    int top = curlyBrackets.top();
                                    curlyBrackets.pop();
                                    streamLIBlock<<top<<" "<<lineNo<<" "<<level<<endl;
                                    string top_line = block_line_stack.top();
                                    block_line_stack.pop();
                                    insert_block_first_line(top_line);
                                    cout<<"Line: "<<top<<" Top line |funEnd| "<<top_line<<endl;
                                    dataToWrite+="/*|funEnd|*/ ";
                                    level--;
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
                    curlyBrackets.push(lineNo);
                    block_line_stack.push(line);
                    //streamLIBlock<<lineNo<<" ";
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
        streamLIBlock.close();

        ofstream nodeCountStream;
        nodeCountStream.open("NodeCount.txt");
        nodeCountStream<<node_counter<<endl;
        nodeCountStream.close();

        ofstream stream_write;
        stream_write.open("usersFlow.cpp", ios_base::out);
        stream_write<<dataToWrite;
        stream_write.close();

        mainParser(splitter);   //! Just to generate complete Int_lang.cage for analysis and nothing else.
        try{
            system("rm flowOutput.txt");
            system("rm usersFlow");
            system("g++ usersFlow.cpp -o usersFlow");
            system("./usersFlow");
        }
        catch(exception &e){
            cout<<e.what()<<endl;
        }
        return 0;
    }

    vector<string> getFunFirstLine(){
        return block_first_line;
    }

    map<int, string> get_user_code_linewise(){
        return user_code_linewise;
    }
};
