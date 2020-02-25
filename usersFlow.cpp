#include <iostream>
#include <vector>
#include <queue>
using namespace std; int lineNo=4;
class Node{
    private:
    vector<pair<string, int> >variable_records;
    Node *leftPtr = NULL, *rightPtr = NULL;
    public:
    Node(string dataType, int lineNumber){
        variable_records.emplace_back(make_pair(dataType, lineNumber));
/*fun=0*/    }
/*fun=1*/    void setRightPtr(Node *ptrReceived){ lineNo=13; cout<<lineNo<<endl;
        rightPtr = ptrReceived; lineNo=14; cout<<lineNo<<endl;
/*fun=0*/    }
/*fun=1*/    void setLeftPtr(Node *ptrReceived){ lineNo=16; cout<<lineNo<<endl;
        leftPtr = ptrReceived; lineNo=17; cout<<lineNo<<endl;
/*fun=0*/    }
    Node* getRightPtr(){
        return rightPtr;
/*fun=0*/    }
    Node* getLeftPtr(){
        return leftPtr;
/*fun=0*/    }
    vector<pair<string, int> > getData(){
        return variable_records;
/*fun=0*/    }
/*fun=0*/};
class BST{
    private:
    Node* createNewNode(string dataType, int lineNumber){
        return new Node(dataType, lineNumber);
/*fun=0*/    }
    public:
    Node* insert(Node *root, string dataType, int lineNumber){
        if(root == NULL){
            root = createNewNode(dataType, lineNumber);
/*fun=0*/        }
        else if(root->getData().at(0).second <= lineNumber){
            root->setRightPtr(insert(root->getRightPtr(), dataType, lineNumber));
/*fun=0*/        }
        else{
            root->setLeftPtr(insert(root->getLeftPtr(), dataType, lineNumber));
/*fun=0*/        }
        return root;
/*fun=0*/    }
    //* BFS
/*fun=1*/    void displayData(Node *root){ lineNo=48; cout<<lineNo<<endl;
/*push->*/        if(root == NULL){ lineNo=49; cout<<lineNo<<endl;
lineNo=50; cout<<"return_exit-> "<<lineNo<<endl;             return;
/*pop->*/        }
        vector <pair<string, int> > varInfo; lineNo=52; cout<<lineNo<<endl;
        queue <Node*> breadth_first; lineNo=53; cout<<lineNo<<endl;
        breadth_first.emplace(root); lineNo=54; cout<<lineNo<<endl;
        Node* changeLine = NULL; lineNo=55; cout<<lineNo<<endl;
        breadth_first.emplace(changeLine); lineNo=56; cout<<lineNo<<endl;
/*push->*/        while(!breadth_first.empty()){ lineNo=57; cout<<lineNo<<endl;
            /* lineNo=58; cout<<lineNo<<endl;
            * Inserting 5 2 8 1 3 7 9 in queue lineNo=59; cout<<lineNo<<endl;
            * 5 NULL lineNo=60; cout<<lineNo<<endl;
            * NULL 2 8 lineNo=61; cout<<lineNo<<endl;
            * 2 8 NULL lineNo=62; cout<<lineNo<<endl;
            * 8 NULL 1 3 lineNo=63; cout<<lineNo<<endl;
            * NULL 1 3 7 9 lineNo=64; cout<<lineNo<<endl;
            * 1 3 7 9 NULL lineNo=65; cout<<lineNo<<endl;
            * so on.... lineNo=66; cout<<lineNo<<endl;
            * Using NULL for line change. lineNo=67; cout<<lineNo<<endl;
            * When NULL is encountered all children nodes are already in the queue so lineNo=68; cout<<lineNo<<endl;
            * pop NULL and insert NULL at the back at the same time. lineNo=69; cout<<lineNo<<endl;
            */ lineNo=70; cout<<lineNo<<endl;
/*push->*/            if(breadth_first.front() == NULL){ lineNo=71; cout<<lineNo<<endl;
                cout<<"\n"; lineNo=72; cout<<lineNo<<endl;
                breadth_first.pop(); lineNo=73; cout<<lineNo<<endl;
                breadth_first.emplace(changeLine); lineNo=74; cout<<lineNo<<endl;
/*pop->*/            }
/*push->*/            if(breadth_first.front() != NULL){ lineNo=76; cout<<lineNo<<endl;
/*push->*/                if(breadth_first.front()->getLeftPtr() != NULL){ lineNo=77; cout<<lineNo<<endl;
                breadth_first.emplace(breadth_first.front()->getLeftPtr()); lineNo=78; cout<<lineNo<<endl;
/*pop->*/                }
/*push->*/                if(breadth_first.front()->getRightPtr() != NULL){ lineNo=80; cout<<lineNo<<endl;
                    breadth_first.emplace(breadth_first.front()->getRightPtr()); lineNo=81; cout<<lineNo<<endl;
/*pop->*/                }
                varInfo = breadth_first.front()->getData(); lineNo=83; cout<<lineNo<<endl;
                cout<<varInfo.at(0).first<<" "<<varInfo.at(0).second<<" "; lineNo=84; cout<<lineNo<<endl;
/*pop->*/            }
            breadth_first.pop(); lineNo=86; cout<<lineNo<<endl;
/*pop->*/        }
/*fun=0*/    }
/*fun=0*/};
/*fun=1*/int main(){ lineNo=90; cout<<lineNo<<endl;
    Node *root = NULL; lineNo=91; cout<<lineNo<<endl;
    BST bst; lineNo=92; cout<<lineNo<<endl;
    root = bst.insert(root, "int", 5); lineNo=93; cout<<lineNo<<endl;
    root = bst.insert(root, "float", 8); lineNo=94; cout<<lineNo<<endl;
    root = bst.insert(root, "string", 2); lineNo=95; cout<<lineNo<<endl;
    root = bst.insert(root, "float", 1); lineNo=96; cout<<lineNo<<endl;
    root = bst.insert(root, "string", 3); lineNo=97; cout<<lineNo<<endl;
    root = bst.insert(root, "int", 7); lineNo=98; cout<<lineNo<<endl;
    root = bst.insert(root, "bool", 9); lineNo=99; cout<<lineNo<<endl;
    bst.displayData(root); lineNo=100; cout<<lineNo<<endl;
lineNo=101; cout<<"return_exit-> "<<lineNo<<endl;     return 0;
/*fun=0*/}
