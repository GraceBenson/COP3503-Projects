#include <iostream>
#include "pa2.h"

int main(int argc, char ** argv) {
    LinkedList * programList = new LinkedList;
    std::string algorithm = argv[1];
    int userChoice = 0;

    if(argc == 2){
        if(algorithm == "best"){
            std::cout << "Using best fit algorithm.\n\n";
        }
        else if(algorithm == "worst"){
            std::cout << "Using worst fit algorithm.\n\n";
        }
        else{
            std::cout << "'best' or 'worst' argument not found.\n";
            return 0;
        }
    }

    printMenu();

    while(userChoice != 5) {
        userChoice = getChoice();
        switch (userChoice) {
            case 1:
                // Add program
                programList->addProgram(getProgramSize(), getProgramName(), algorithm);
                break;
            case 2:
                // Kill program
                programList->killProgram(getProgramName());
                break;
            case 3:
                // Fragmentation
                programList->fragmentation();
                break;
            case 4:
                // Print Memory
                programList->printMemory();
                break;
            case 5:
                break;
            default:
                std::cout << "Unknown input.\n";
                break;
        }
    }
    return 0;
}

// Define functions

void printMenu() {
    /*
     * Displays menu of program functions and returns user choice
     */

    std::cout << "1. Add program\n"
              << "2. Kill program\n"
              << "3. Fragmentation\n"
              << "4. Print memory\n"
              << "5. Exit\n\n";
}

int getChoice(){
    /*
     * Gets user choice from user
     * Input - userChoice
     * Returns - userChoice
     */

    int userChoice;
    std::cout << "choice - ";
    std::cin >> userChoice;

    // Integer validation
    while(userChoice != 1 && userChoice != 2 && userChoice != 3 && userChoice != 4 && userChoice != 5){
        std::cout << "\nInput must be an integer between 1 and 5.\n\n";

        // Clear input stream
        std::cin.clear();
        std::cin.ignore(900000, '\n');
        std::cin >> userChoice;
    }
    std::cout << std::endl;

    return userChoice;
}

std::string getProgramName(){
    /*
     * Gets program name from user
     * Input - program name
     * Returns - string programName
     */

    std::string programName;
    std::cout << "Program name - ";
    std::cin >> programName;
    std::cout << std::endl;
    return programName;
}

int getProgramSize(){
    /*
     * Gets the six=ze of the program from user
     * Input - program size
     * Returns - size
     */

    int size;
    std::cout << "Program size (KB) - ";
    std::cin >> size;
    return size;
}

LinkedList::LinkedList() {
    /*
     * Linked list constructor
     */

    head = NULL;
    tail = NULL;

    // Initializes list with 32 pages of memory
    for(int x = 0; x < 32; x++){
        addNode("FREE");
    }
}

void LinkedList::addNode(std::string program) {
    /*
     * Adds a new node to end of list
     * Used in linked list initialization
     * Parameters - program name
     */
    nodePointer newNode = new Node;
    newNode->next = NULL;
    newNode->size = 0;
    newNode->program = program;

    if(head != NULL){
        tail->next = newNode;
        tail = newNode;
    }
    else{
        head = newNode;
        tail = newNode;
    }
}

void LinkedList::printMemory() {
    /*
     * Prints linked list
     */
    int count = 0;
    nodePointer currNode = head;

    while(currNode != NULL){
        if(count % 8 == 0){ // 8 programs in each row
            std::cout << std::endl;
        }
        std::cout << currNode->program << " ";
        currNode = currNode->next;
        count++;
    }
    std::cout <<"\n\n";
}

void LinkedList::killProgram(std::string program) { //Need to retake size
    /*
     * Remove a program from memory
     * Parameters - program name
     */

    nodePointer currNode = head; // Set to head to iterate through list
    int pages = 0;  // Keep track of pages reclaimed

    while(currNode != NULL){
        if(currNode->program == program){
            currNode->program = "FREE";
            currNode->size = 0;
            pages += 1;
        }
        else if(currNode->next == NULL){
            std::cout << "Program " << program << " successfully killed, " << pages << " page(s) reclaimed.\n\n";
            return;
        }
        else{
            currNode = currNode->next;
        }

    }
}

void LinkedList::fragmentation() {
    /*
     * Counts the number of contiguous programs
     */

    nodePointer currNode = head;
    int count = 0;

    while(currNode != NULL){    // While a node exists
        if(currNode->program != "FREE" && (currNode->next->program == "FREE" || currNode->next == NULL)){
            // If current node program name is not 'FREE,' and the next node is or is null
            count += 1;
        }
        currNode = currNode->next;
    }

    std::cout << "There are " << count << " fragment(s).\n\n";
}

int LinkedList::checkName(std::string program) {
    /*
     * Checks that the program to be added is not already running
     * Parameters - program name
     * Returns
     *      -1: means program already running
     *
     */

    nodePointer currNode = head;

    while(currNode != NULL){
        if(currNode->program == program){
            return -1;
        }
        currNode = currNode->next;
    }
    return 1;
}

void LinkedList::bestFitAdd(std::string program, int size) {
    /*
     * Adds program to list using best fit method
     * Fits program into the smallest space available that will fit program
     * Parameters - program name, size
     */

    int min = 33, currMin = 1, count = 1, index = 0;

    // Find the longest contiguous nodes
    for(nodePointer currNode = head; currNode->next != NULL; currNode = currNode->next) {
        if (currNode->program == "FREE") {
            currMin += 1;
            count++;

            if (currNode->next->program != "FREE") {
                currMin++;
                count++;

                // Change max to current max, if max is less than currMax
                if (min > currMin) {
                    min = currMin;
                    index = count - currMin;
                }
                currMin = 1;
            }
        }
        else {
            if (currNode->program != "FREE") {
            }
            count++;
            currMin = 1;
        }
    }

    // In case loop exited early when currNode->next is NULL
    if(min > currMin){
        min = currMin;
        index = count - min;
    }

    int pages = 0; // page count

    // Check that program size will fit
    if(size/4 <= min) {
        // If it fits assign program
        int x = 0;
        for (nodePointer currNode = head; currNode != NULL; currNode = currNode->next) {
            if (x == index) {
                while (size > 0) {
                    currNode->program = program;
                    currNode->size = size;
                    pages++;
                    min--;
                    size -= 4;
                    currNode = currNode->next;
                }
            }
            x++;
        }
        std::cout << "Program " << program << " added successfully: " << pages << " page(s) used.\n\n";
    }
    else{
        std::cout << "Error: Not enough memory for Program " << program << ".\n\n";
        return;
    }
}

void LinkedList::worstFitAdd(std::string program, int size) {
    /*
     * Adds program to list using worst fit algorithm
     * Fits program into largest space available
     * Parameters - program name, size
     */

    int max = 1, currMax = 1, count = 1, index = 0;

    // Find the longest contiguous nodes
    for(nodePointer currNode = head; currNode->next != NULL; currNode = currNode->next){
        if(currNode->program == "FREE" && currNode->next->program == "FREE"){
            currMax++;
        }
        else{
            // Change max to current max, if max is less than currMax
            if(max < currMax){ // each node will hold 4 KB
                max = currMax;
                index = count - currMax;
            }
            currMax = 1;
        }
        count++;
    }

    // In case loop exited early when currNode->next is NULL
    if(max < currMax){
        max = currMax;
        index = count - max;
    }

    int pages = 0; // page count

    // Check that program size will fit
    if(size/4 <= max) {
        // If it fits assign program
        int x = 0;
        for (nodePointer currNode = head; currNode != NULL; currNode = currNode->next) {
            if (x == index) {
                while (size > 0) {
                    currNode->program = program;
                    currNode->size = size;
                    pages++;
                    max--;
                    size -= 4;
                    currNode = currNode->next;
                }
            }
            x++;
        }
        std::cout << "Program " << program << " added successfully: " << pages << " page(s) used.\n\n";
    }
    else{
        std::cout << "Error: Not enough memory for Program " << program << ".\n\n";
        return;
    }
}


void LinkedList::addProgram(int size, std::string program, std::string algorithm) {
    /*
     * Adds program using best/worst fit algorithm
     * Parameters - program name, size, fit algorithm
     */

    if(checkName(program) == -1){
        std::cout << "Error: Program " << program << " already running.\n\n";
        return;
    }
    if(algorithm == "best"){
        bestFitAdd(program, size);
    }
    else if(algorithm == "worst"){
        worstFitAdd(program, size);
    }
}