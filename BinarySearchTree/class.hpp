#ifndef CLASS_ISP2_REPORT2_6320091
#define CLASS_ISP2_REPORT2_6320091

#include <string>

//Node of binary search tree
//Left node is smaller than parent node
//Right node is larger than parent node
template <typename TYPE>
struct Node {
    std::string key;
    TYPE item;
    Node *left;
    Node *right;
};

//Class for an encapsulation of an abstract binary search tree 
template <typename TYPE>
class Table{
public:
    Table();
    ~Table();
    //Search function
    bool operator()(std::string); 
    void Insert(std::string, TYPE);
    //Remove function
    void operator-=(std::string); 
    void PrintTree();

private:
    //Binary tree root
    Node<TYPE> *root_; 
    Node<TYPE> *Search(std::string, Node<TYPE>*);

    Node<TYPE> *GetInsertedNode(std::string, TYPE, Node<TYPE>*);
    Node<TYPE> *Remove(std::string, Node<TYPE>*, Node<TYPE>*);
    void PrintTreeDFS(Node<TYPE>*);
    
};

#endif