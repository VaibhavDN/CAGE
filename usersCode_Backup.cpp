#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node{
    private:
    vector<pair<string, int> >variable_records;
    Node *leftPtr = NULL, *rightPtr = NULL;

    public:
    Node(string dataType, int lineNumber){
        variable_records.emplace_back(make_pair(dataType, lineNumber));
    }

    void setRightPtr(Node *ptrReceived){
        rightPtr = ptrReceived;
    }

    void setLeftPtr(Node *ptrReceived){
        leftPtr = ptrReceived;
    }

    Node* getRightPtr(){
        return rightPtr;
    }

    Node* getLeftPtr(){
        return leftPtr;
    }

    vector<pair<string, int> > getData(){
        return variable_records;
    }
};

class BST{
    private:
    Node* createNewNode(string dataType, int lineNumber){
        return new Node(dataType, lineNumber);
    }
    
    public:
    Node* insert(Node *root, string dataType, int lineNumber){
        if(root == NULL){
            root = createNewNode(dataType, lineNumber);
        }
        else if(root->getData().at(0).second <= lineNumber){
            root->setRightPtr(insert(root->getRightPtr(), dataType, lineNumber));
        }
        else{
            root->setLeftPtr(insert(root->getLeftPtr(), dataType, lineNumber));
        }

        return root;
    }

    //* BFS
    void displayData(Node *root){
        if(root == NULL){
            return;
        }

        vector <pair<string, int> > varInfo;
        queue <Node*> breadth_first;

        breadth_first.emplace(root);
        Node* changeLine = NULL;
        breadth_first.emplace(changeLine);

        while(!breadth_first.empty()){
            /*
            * Inserting 5 2 8 1 3 7 9 in queue
            * 5 NULL
            * NULL 2 8
            * 2 8 NULL
            * 8 NULL 1 3
            * NULL 1 3 7 9
            * 1 3 7 9 NULL
            * so on....
            * Using NULL for line change.
            * When NULL is encountered all children nodes are already in the queue so 
            * pop NULL and insert NULL at the back at the same time.
            */
            if(breadth_first.front() == NULL){
                cout<<"\n";
                breadth_first.pop();
                breadth_first.emplace(changeLine);
            }

            if(breadth_first.front() != NULL){
                if(breadth_first.front()->getLeftPtr() != NULL){
                breadth_first.emplace(breadth_first.front()->getLeftPtr());
                }

                if(breadth_first.front()->getRightPtr() != NULL){
                    breadth_first.emplace(breadth_first.front()->getRightPtr());
                }

                varInfo = breadth_first.front()->getData();
                cout<<varInfo.at(0).first<<" "<<varInfo.at(0).second<<" ";
            }
            
            breadth_first.pop();
        }
    }
};

int main(){
    Node *root = NULL;
    BST bst;
    root = bst.insert(root, "int", 5);
    root = bst.insert(root, "float", 8);
    root = bst.insert(root, "string", 2);
    root = bst.insert(root, "float", 1);
    root = bst.insert(root, "string", 3);
    root = bst.insert(root, "int", 7);
    root = bst.insert(root, "bool", 9);
    bst.displayData(root);
    return 0;
}