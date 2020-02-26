#include <iostream>
#include <vector>
#include <queue>
using namespace std; int lineNo=4;
#include <fstream>
ofstream streamLI("flowOutput.txt");
class Node{
    private:
    vector<pair<string, int> >variable_records;
    Node *leftPtr = NULL, *rightPtr = NULL;
    public:
    Node(string dataType, int lineNumber){
        variable_records.emplace_back(make_pair(dataType, lineNumber));
/*fun=0*/     }
/*fun=1*/    void setRightPtr(Node *ptrReceived){ lineNo=16; streamLI<<lineNo<<endl;
        rightPtr = ptrReceived; lineNo=17; streamLI<<lineNo<<endl;
/*fun=0*/ /*|funEnd|*/     }
/*fun=1*/    void setLeftPtr(Node *ptrReceived){ lineNo=20; streamLI<<lineNo<<endl;
        leftPtr = ptrReceived; lineNo=21; streamLI<<lineNo<<endl;
/*fun=0*/ /*|funEnd|*/     }
    Node* getRightPtr(){
        return rightPtr;
/*fun=0*/     }
    Node* getLeftPtr(){
        return leftPtr;
/*fun=0*/     }
    vector<pair<string, int> > getData(){
        return variable_records;
/*fun=0*/     }
/*fun=0*/ };
class BST{
    private:
    Node* createNewNode(string dataType, int lineNumber){
        return new Node(dataType, lineNumber);
/*fun=0*/     }
    public:
    Node* insert(Node *root, string dataType, int lineNumber){
        if(root == NULL){
            root = createNewNode(dataType, lineNumber);
/*fun=0*/         }
        else if(root->getData().at(0).second <= lineNumber){
            root->setRightPtr(insert(root->getRightPtr(), dataType, lineNumber));
/*fun=0*/         }
        else{
            root->setLeftPtr(insert(root->getLeftPtr(), dataType, lineNumber));
/*fun=0*/         }
        return root;
/*fun=0*/     }
    //* BFS
/*fun=1*/    void displayData(Node *root){ lineNo=59; streamLI<<lineNo<<endl;
/*push->*/        if(root == NULL){ lineNo=60; streamLI<<lineNo<<endl;
lineNo=61; streamLI<<lineNo<<endl;            return;
/*pop->*/        }
        vector <pair<string, int> > varInfo; lineNo=64; streamLI<<lineNo<<endl;
        queue <Node*> breadth_first; lineNo=65; streamLI<<lineNo<<endl;
        breadth_first.emplace(root); lineNo=67; streamLI<<lineNo<<endl;
        Node* changeLine = NULL; lineNo=68; streamLI<<lineNo<<endl;
        breadth_first.emplace(changeLine); lineNo=69; streamLI<<lineNo<<endl;
/*push->*/        while(!breadth_first.empty()){ lineNo=71; streamLI<<lineNo<<endl;
            /* lineNo=72; streamLI<<lineNo<<endl;
            * Inserting 5 2 8 1 3 7 9 in queue lineNo=73; streamLI<<lineNo<<endl;
            * 5 NULL lineNo=74; streamLI<<lineNo<<endl;
            * NULL 2 8 lineNo=75; streamLI<<lineNo<<endl;
            * 2 8 NULL lineNo=76; streamLI<<lineNo<<endl;
            * 8 NULL 1 3 lineNo=77; streamLI<<lineNo<<endl;
            * NULL 1 3 7 9 lineNo=78; streamLI<<lineNo<<endl;
            * 1 3 7 9 NULL lineNo=79; streamLI<<lineNo<<endl;
            * so on.... lineNo=80; streamLI<<lineNo<<endl;
            * Using NULL for line change. lineNo=81; streamLI<<lineNo<<endl;
            * When NULL is encountered all children nodes are already in the queue so lineNo=82; streamLI<<lineNo<<endl;
            * pop NULL and insert NULL at the back at the same time. lineNo=83; streamLI<<lineNo<<endl;
            */ lineNo=84; streamLI<<lineNo<<endl;
/*push->*/            if(breadth_first.front() == NULL){ lineNo=85; streamLI<<lineNo<<endl;
                cout<<"\n"; lineNo=86; streamLI<<lineNo<<endl;
                breadth_first.pop(); lineNo=87; streamLI<<lineNo<<endl;
                breadth_first.emplace(changeLine); lineNo=88; streamLI<<lineNo<<endl;
/*pop->*/            }
/*push->*/            if(breadth_first.front() != NULL){ lineNo=91; streamLI<<lineNo<<endl;
/*push->*/                if(breadth_first.front()->getLeftPtr() != NULL){ lineNo=92; streamLI<<lineNo<<endl;
                breadth_first.emplace(breadth_first.front()->getLeftPtr()); lineNo=93; streamLI<<lineNo<<endl;
/*pop->*/                }
/*push->*/                if(breadth_first.front()->getRightPtr() != NULL){ lineNo=96; streamLI<<lineNo<<endl;
                    breadth_first.emplace(breadth_first.front()->getRightPtr()); lineNo=97; streamLI<<lineNo<<endl;
/*pop->*/                }
                varInfo = breadth_first.front()->getData(); lineNo=100; streamLI<<lineNo<<endl;
                cout<<varInfo.at(0).first<<" "<<varInfo.at(0).second<<" "; lineNo=101; streamLI<<lineNo<<endl;
/*pop->*/            }
            breadth_first.pop(); lineNo=104; streamLI<<lineNo<<endl;
/*pop->*/        }
/*fun=0*/ /*|funEnd|*/     }
/*fun=0*/ };
/*fun=1*/int main(){ lineNo=109; streamLI<<lineNo<<endl;
    Node *root = NULL; lineNo=110; streamLI<<lineNo<<endl;
    BST bst; lineNo=111; streamLI<<lineNo<<endl;
    root = bst.insert(root, "int", 5); lineNo=112; streamLI<<lineNo<<endl;
    root = bst.insert(root, "float", 8); lineNo=113; streamLI<<lineNo<<endl;
    root = bst.insert(root, "string", 2); lineNo=114; streamLI<<lineNo<<endl;
    root = bst.insert(root, "float", 1); lineNo=115; streamLI<<lineNo<<endl;
    root = bst.insert(root, "string", 3); lineNo=116; streamLI<<lineNo<<endl;
    root = bst.insert(root, "int", 7); lineNo=117; streamLI<<lineNo<<endl;
    root = bst.insert(root, "bool", 9); lineNo=118; streamLI<<lineNo<<endl;
    bst.displayData(root); lineNo=119; streamLI<<lineNo<<endl;
lineNo=120; streamLI<<lineNo<<endl;    return 0;
/*fun=0*/ /*|funEnd|*/ }
