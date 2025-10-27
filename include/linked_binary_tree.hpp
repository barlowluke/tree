//linked_binary_tree.hpp
#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

template <typename E>
class LinkedBinaryTree{
    protected:
        class Node {
            // practice writing code yourself and match with slides
        };// end of Node class

    protected:
        Node* rt{nullptr}; // root
        int sz{0}; // size

    public:
        class Position {
            private:
                // practice writing code yourself and match with slides
            public:
                // Wraps a Node* pointer 
                //(default is nullptr)
                Position(Node* nd=nullptr): node{nd} {};

                // operator (based on node pointer)
                bool operator==(Position other) const{
                    // practice writing code yourself and match with slides
                }
                bool operator!=(Position other) const{
                    // practice writing code yourself and match with slides
                }
                bool is_null() const{
                    // practice writing code yourself and match with slides
                }
                bool is_root() const{
                    // practice writing code yourself and match with slides
                }
                bool is_external() const{
                    // practice writing code yourself and match with slides
                }
                E& element(){ // get reference to element
                    // practice writing code yourself and match with slides
                }
                const E& element() const{
                    // practice writing code yourself and match with slides
                }

                Position parent() const{
                    // practice writing code yourself and match with slides
                }
                Position left() const{
                    // practice writing code yourself and match with slides
                }
                Position right() const{
                    // practice writing code yourself and match with slides
                }
                
                std::vector<Position> children() const{
                    // practice writing code yourself and match with slides
                }
                int num_children() const{
                    // practice writing code yourself and match with slides
                }
        };  // end of Position class
        LinkedBinaryTree() = default; //tree with zero nodes
        int size() const{
            // practice writing code yourself and match with slides
        }
        bool empty() const{
            // practice writing code yourself and match with slides
        }
        Position root() const{
            // practice writing code yourself and match with slides
        }
        std::vector<Position> positions() const{
            // practice writing code yourself and match with slides
        }
        void add_root(const E& e=E()){
            // practice writing code yourself and match with slides
        }
        void add_left(Position p, const E& e){
            // practice writing code yourself and match with slides
        }
        void add_right(Position p, const E& e){
            // practice writing code yourself and match with slides
        }

        void erase(Position p){
            // practice writing code yourself and match with slides
        }

        void attach(Position p, LinkedBinaryTree& left, LinkedBinaryTree& right){
            // practice writing code yourself and match with slides
        }
    // ------------- Rule-of-five support ----------------
    private:
        void tear_down(Node* nd){
            // practice writing code yourself and match with slides
        }
        static Node* clone(Node* model){
            // practice writing code yourself and match with slides
        }

    public:
        ~LinkedBinaryTree(){
            // practice writing code yourself and match with slides
        }
        
        // copy constructor and copy assignment
        LinkedBinaryTree(const LinkedBinaryTree& other){
            // practice writing code yourself and match with slides
        }

        LinkedBinaryTree& operator=(const LinkedBinaryTree& other){
            // practice writing code yourself and match with slides
        }

        // move constructor and move assignment
        LinkedBinaryTree(LinkedBinaryTree&& other){
            // practice writing code yourself and match with slides
        }

        LinkedBinaryTree& operator=(LinkedBinaryTree&& other){
            // practice writing code yourself and match with slides
        }

    // ******************* Assignment ******************* 
    private:
        // Helper functions in case you want to write

    public:
        int count_left_leaves() const{
            // ToDo (use recursion)
            //count nodes that are leaves in a binary tree and that are the left child of their respective parent. The root is not counted.
        }

        int count_left_leaves_bfs() const {
            // ToDo (use breadth first search)
            //count nodes that are leaves in a binary tree and that are the left child of their respective parent. The root is not counted.
        }
};