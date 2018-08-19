//
// Created by grace on 3/26/2018.
//

#ifndef PA3_PA3_H
#define PA3_PA3_H

#include <string>
#include <cstdlib>
#include <vector>

std::string getFileName();
bool isUpperCase(std::string);
bool isNumber(std::string);
void printStack(class Stack);

class Stack {

private:
    std::vector<std::string> stack;
    int size;

public:
    void pop();
    void push(std::string);
    bool isEmpty();
    std::string top();
};

#endif //PA3_PA3_H
