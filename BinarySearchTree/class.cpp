#include "class.hpp"
#include <iostream>

//Public member

template <typename TYPE>
Table<TYPE>::Table(){
    root_ = nullptr;
}

template <typename TYPE>
Table<TYPE>::~Table(){

}

//Input: Key of the tree.
//Output: Bool value which tell if key "is in" the tree. 
template <typename TYPE>
bool Table<TYPE>::operator()(std::string key){
    return (Search(key, root_) != nullptr) ? true : false;
}

//Input: Key of tree, Item you want to storage.
//Output: None
template <typename TYPE>
void Table<TYPE>::Insert(std::string key, TYPE item){
    if(Search(key, root_) != nullptr){
        std::cout << "This key already has registered" << std::endl;
        return;
    }
    //Insertion part
    if(root_ != nullptr){
        Node<TYPE> *add_node;
        add_node = GetInsertedNode(key, item, root_);
        add_node -> key = key;
        add_node -> item = item;
        add_node -> left = nullptr;
        add_node -> right = nullptr;
    }
    else{
        try{
            root_ = new Node<TYPE>;
        }catch(std::bad_alloc& e){
            std::cout << e.what() << std::endl;
            exit(1);
        }
        root_ -> key = key;
        root_ -> item = item;
        root_ -> left = nullptr;
        root_ -> right = nullptr;
    }

    return;
}

//Input: Key of node you want to remove.
//Output: None
template <typename TYPE>
void Table<TYPE>::operator-=(std::string key){
    if(Search(key, root_) == nullptr){
        std::cout << "This node doesn't exist" << std::endl;
        return;
    } 
    Node<TYPE> *delete_node = Remove(key, root_, root_);
    delete delete_node;
    return;
}


//Input:None
//Output:None
template <typename TYPE>
void Table<TYPE>::PrintTree(){
    PrintTreeDFS(root_);
    return;
}

//Private member

//Input: Key of node pointer you want to search, Node pointer
//Output: Node pointer which you want to search, but return "nullptr" in case there isn't the node.
//This function is used recursively.
template <typename TYPE>
Node<TYPE> *Table<TYPE>::Search(std::string key, Node<TYPE> *node){
    if(node == nullptr){
        return nullptr;
    }

    if(key.compare(node -> key) == 0){
        return node;
    }
    else if(key.compare(node -> key) < 0){
        return Search(key, node -> left);
    }
    else{
        return Search(key, node -> right);
    }
}

//Input: Key of node, Item of node you want to register, Candidate of parent node pointer, 
//Output: Node pointer you want to register.
//This function allocates memory space for the child node
//and registers the child node with the parent node,
//then it returns a pointer to the child node.
//Child nodes must be initialized by the caller
//<Caution>
//This function works assuming that the keys of the binary tree are unique and the binary tree isn't empty.
//This function is used recursively.
template <typename TYPE>
Node<TYPE> *Table<TYPE>::GetInsertedNode(std::string key, TYPE item, Node<TYPE> *parent_node){
    if(key.compare(parent_node -> key) < 0){
        if(parent_node -> left == nullptr){
            Node<TYPE> *child_node;
            try{
                child_node = new Node<TYPE>;
            }catch(std::bad_alloc& e){
                std::cout << e.what() << std::endl;
                exit(1);
            }
            parent_node -> left = child_node;
            return child_node;
        }
        else{
            return GetInsertedNode(key, item, parent_node -> left);
        }
    }
    else{
        if(parent_node -> right == nullptr){
            Node<TYPE> *child_node;
            try{
                child_node = new Node<TYPE>;
            }catch(std::bad_alloc& e){
                std::cout << e.what() << std::endl;
                exit(1);
            }
            parent_node -> right = child_node;
            return child_node;
        }
        else{
            return GetInsertedNode(key, item, parent_node -> right);
        }
    }
}

//Input:Key of node, Node which start searching
//Output:None
//This function search the node pointer which must be deallocated,
//then it returns its node pointer.
//"delete_node" must be deallocated by caller
//<Caution>
//This function works assuming that the keys of the binary tree are unique and the binary tree isn't empty.
//This function is used recursively.
template <typename TYPE>
Node<TYPE> *Table<TYPE>::Remove(std::string key, Node<TYPE> *parent_node, Node<TYPE> *node){
    if(key.compare(node -> key) == 0){
        Node<TYPE> *delete_node;
        delete_node = node;
        parent_node -> left = node -> left;
        parent_node -> right = node -> right;

        return delete_node;
    }
    else if(key.compare(node -> key) < 0){
        return Remove(key, node, node -> left);
    }
    else{
        return Remove(key, node, node -> right);
    }
}


//Input:Node which start displaying
//Output:Node
//Print the binary tree using by DFS
template <typename TYPE>
void Table<TYPE>::PrintTreeDFS(Node<TYPE> *node){
    if(node == nullptr){
        return;
    }
    else{
        std::cout << node -> key << ": " << node -> item;
        std::cout << "(";
        PrintTreeDFS(node -> left);
        std::cout << ",";
        PrintTreeDFS(node -> right);
        std::cout << ")";
    }
}

//Symbolization
template Table<int>::Table();
template Table<int>::~Table();
template bool Table<int>::operator()(std::string);
template void Table<int>::Insert(std::string, int);
template void Table<int>::operator-=(std::string);
template void Table<int>::PrintTree();
template Node<int> *Table<int>::Search(std::string, Node<int>*);
template Node<int> *Table<int>::GetInsertedNode(std::string, int, Node<int>*);
template Node<int> *Table<int>::Remove(std::string, Node<int>*, Node<int>*); 


