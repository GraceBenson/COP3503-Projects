//
// Created by grace on 3/2/2018.
//

#ifndef PA2_PA2_H
#define PA2_PA2_H
#include <cstdio>
#include <string>

//functions
void printMenu();
int getChoice();
std::string getProgramName();
int getProgramSize();

//class Node{
//    public:
//        std::string program;
//        int size;
//        Node * next;
//};

class LinkedList {
    private:
        struct Node {
            std::string program;
            int size;
            Node *next;
        };
        typedef struct Node * nodePointer;
            nodePointer head;
            nodePointer tail;

    public:
        // member functions
        LinkedList();
        void addNode(std::string);
        void addProgram(int, std::string, std::string);   // Adds node to the list using best/worst algorithm
        void killProgram(std::string);
        void printMemory();
        void fragmentation();
        int checkName(std::string);
        void worstFitAdd(std::string, int);
        void bestFitAdd(std::string, int);

};

#endif //PA2_PA2_H
