//linked_binary_tree.hpp
#pragma once

#include <iostream>
#include <vector>

template <typename E>
class LinkedBinaryTree{
    protected:
        class Node {
            //public for convenience
            public:
                E element;
                Node* parent;
                Node* left{nullptr};
                Node* right{nullptr};
                Node(E e, Node* p=nullptr): element{e}, parent{p}{};
        };// end of Node class

    protected:
        Node* rt{nullptr}; // root
        int sz{0}; // size

    public:
        class Position {
            private:
                // Raw pointer to a Node
                Node* node;
                // allow outer class access to node pointer
                friend class LinkedBinaryTree;
            public:
                // Wraps a Node* pointer 
                //(default is nullptr)
                Position(Node* nd=nullptr): node{nd} {};

                // operator (based on node pointer)
                bool operator==(Position other) const{
                    return node == other.node; 
                }
                bool operator!=(Position other) const{
                    return node != other.node;
                }
                bool is_null() const{
                    return node == nullptr; 
                }
                bool is_root() const{
                    return node->parent == nullptr;
                }
                bool is_external() const{
                    return (node->left == nullptr) && (node->right == nullptr);
                }
                E& element(){ // get reference to element
                    return node->element;
                }
                const E& element() const{
                    return node->element; 
                }

                Position parent() const{
                    return Position(node->parent); 
                }
                Position left() const{
                    return Position(node->left);
                }
                Position right() const{
                    return Position(node->right);
                }
                std::vector<Position> children() const{
                    std::vector<Position> result;
                    //left child if valid
                    if (node->left != nullptr) 
                        result.push_back(Position(node->left));
                    //right child if valid
                    if (node->right != nullptr) 
                        result.push_back(Position(node->right));

                    return result;
                }
                int num_children() const{
                    int result{0};
                    if (node->left != nullptr)
                        result++;
                    if (node->right != nullptr) 
                        result++;
                    return result;
                }
        };  // end of Position class
        LinkedBinaryTree() = default; //tree with zero nodes
        int size() const{
            return sz;
        }
        bool empty() const{
            return sz == 0; 
        }
        Position root() const{
            return Position(rt); 
        }
        std::vector<Position> positions() const{
            std::vector<Position> gather;
            if (rt) 
                inorder(Position(rt), gather);
            return gather;
        }
        void add_root(const E& e=E()){
            rt = new Node(e);
            sz = 1;
        }
        void add_left(Position p, const E& e){
            //create new node with p as parent
            auto new_node = new Node{e, p.node};
            //new node is left child of p
            p.node->left = new_node;
            //increase size
            sz++;
        }
        void add_right(Position p, const E& e){
            //create new node with p as parent
            auto new_node = new Node{e, p.node};
            //new node is right child of p
            p.node->right = new_node;
            //increase size
            sz++;
        }

        void erase(Position p){
            // Get the actual node pointer from Position wrapper
            Node* nd = p.node;

            // lone child or else nullptr
            Node* child{nd->left==nullptr ? nd->right : nd->left};

            // child's grandparent becomes parent
            if (child != nullptr)
                child->parent = nd->parent;

            //update node's parent's 
            //left or right pointer to point child
            //if root to be removed then child is root
            if (nd == rt)
                rt = child;
            else if (nd->parent->left == nd) //left
                nd->parent->left = child;
            else
                nd->parent->right = child; //right
            sz--;
            delete nd;
        }
        void attach(Position p, LinkedBinaryTree& left, LinkedBinaryTree& right){
            Node* nd = p.node; // get Node pointer
            nd->left = left.rt; //set left child
            nd->right = right.rt; //set right child
            sz += left.sz + right.sz;

            // If the left tree is not empty, 
            //update its root's parent pointer
            if (left.rt) 
                left.rt->parent = nd;
            // If the right tree is not empty, 
            //update its root's parent pointer
            if (right.rt) 
                right.rt->parent = nd;

            // Reset left and right trees to be empty
            left.sz = right.sz = 0;
            left.rt = right.rt = nullptr;
        }
    // ------------- Rule-of-five support ----------------
    private:
        void tear_down(Node* nd){
            if (nd != nullptr) {
                tear_down(nd->left);
                tear_down(nd->right);
                delete nd;
            }
        }
        static Node* clone(Node* model){
            // base case
            if (model == nullptr) 
                return nullptr;

            Node* new_root = new Node(model->element);
            //Recursively clone the left subtree.
            //If left child exists, set its parent to new root
            new_root->left = clone(model->left);
            if (new_root->left) 
                new_root->left->parent = new_root;

            //Recursively clone the right subtree.
            //If right child exists, set its parent to new root
            new_root->right = clone(model->right);
            if (new_root->right) 
                new_root->right->parent = new_root;
            
                //return the newly cloned root node
            return new_root;
        }

    public:
        ~LinkedBinaryTree(){
            tear_down(rt); 
        }
        
        // copy constructor and copy assignment
        LinkedBinaryTree(const LinkedBinaryTree& other)
        : sz{other.sz}, rt{clone(other.rt)} {}

        LinkedBinaryTree& operator=(const LinkedBinaryTree& other){
            if (this != &other) { 
                tear_down(rt);
                rt = clone(other.rt);
                sz = other.sz;
            }
            return *this;
        }

        // move constructor and move assignment
        LinkedBinaryTree(LinkedBinaryTree&& other)
        : sz{other.sz}, rt{other.rt} {
            other.sz = 0;
            other.rt = nullptr;
        }

        LinkedBinaryTree& operator=(LinkedBinaryTree&& other){
            if (this != &other) {                       
                std::swap(sz, other.sz);
                std::swap(rt, other.rt); 
            }
            return *this;
        }

    // ******************* Assignment ******************* 
    private:
        int count_left_leaves_rec(Node* nd) const {
            if (nd == nullptr) {
                return 0;
            }
            int count = 0;
            // check if the left child is a leaf node
            if (nd->left != nullptr && nd->left->left == nullptr && nd->left->right == nullptr) {
                count = 1;
            }
            // recursively count left leaves in left and right subtrees
            count += count_left_leaves_rec(nd->left);
            count += count_left_leaves_rec(nd->right);
            return count;
        }

    public:
        int count_left_leaves() const{
            return count_left_leaves_rec(rt);
        }

        int count_left_leaves_bfs() const {
            if (rt == nullptr) {
                return 0;
            }

            int count = 0;
            std::vector<Node*> queue;
            queue.push_back(rt);

            while (!queue.empty()) {
                Node* current = queue.front();
                queue.erase(queue.begin());
                // check if left child exists and is a leaf
                if (current->left != nullptr) {
                    if (current->left->left == nullptr && current->left->right == nullptr) {
                        count++;
                    }
                    queue.push_back(current->left);
                }
                // add right child to queue if it exists
                if (current->right != nullptr) {
                    queue.push_back(current->right);
                }
            }
            return count;
        }
};

