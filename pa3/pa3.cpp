#include <iostream>
#include <fstream>
#include <stack>
#include "pa3.h"

int main() {
    Stack keywords;
    Stack delimiters;
    Stack operators;
    Stack identifiers;
    Stack constants;
    Stack errors;   // Errors stack

    // Used for matching purposes
    int loopCount = -1; // count nested for loop depth
    int forCount = 0;
    int openParenthesis = 0, closeParenthesis = 0, commas = 0;
    int numBegin = 0, numEnd = 0;
    int equals = 0, semicolons = 0;

    std::ifstream file;
    std::string word;
    std::string fileName;

    fileName = getFileName();
    file.open(fileName.c_str());    // open file

    if(!file.is_open()){    // When file cannot be read
        std::cout << "Error: Could not find file '"<< fileName << "'." << std::endl;
        return 0;
    }

    while(file >> word) {    // read in file word by word
       int position;    // marker/count

        for(int x = 0; x < word.size(); x++) {
            if (isalpha(word[x])) { // char is letter
                position = x;   // set marker at x

                while (isalpha(word[x])) {  // count letters after initial letter
                    x++;
                }
                std::string temp = word.substr(position, x - position); // put word into a string

                if (isUpperCase(temp)) {    // Keyword must be uppercase
                    if(temp == "FOR" || temp == "BEGIN" || temp == "END") { // Keyword must be FOR, BEGIN, or END
                        keywords.push(temp);

                        if (temp == "FOR") {    // count loop depth
                            if (keywords.top() == "FOR" || keywords.top() == "BEGIN") { // Only count nested FOR's
                                loopCount++;
                            }
                            forCount++;
                        }
                        else if(temp == "BEGIN"){
                            numBegin++;
                        }
                        else{
                            numEnd++;
                        }
                    }
                    else{
                        errors.push(temp);

                        if(temp[0] == 'F') {    // Assumes FOR is misspelled
                            if(keywords.top()[0] == 'F' || keywords.top()[0] == 'B') {
                                loopCount++;
                            }
                            forCount++;
                        }
                        if(temp[0] == 'B') {    // Assumes BEGIN is misspelled
                            numBegin++;
                        }
                        if (temp[0] == 'E') {   // Assumes End is misspelled
                            numEnd++;
                        }
                    }
                }
                else { // Identifiers are lowercase
                    identifiers.push(temp);
                }
            }

            if(isNumber(word)){
                position = x;

                while (isdigit(word[x])){
                    x++;
                }
                constants.push(word.substr((position), (x - position)));
            }

            if(word[x] == ',' || word[x] == ';') {
                delimiters.push(word.substr(x, 1));

                if(word[x] == ',') {
                    commas++;
                }
                else{
                    semicolons++;
                }
            }

            if(word[x] == '(' || word[x] == ')'){
                if(word[x] == '(') {
                    openParenthesis++;
                }
                else{
                    closeParenthesis++;
                }
            }

            if (word[x] == '=' || word[x] == '+' || word[x] == '-' || word[x] == '*' || word[x] == '/'){
                if(word[x + 1] == '+' || word[x + 1] == '-' || word[x + 1] == '='){
                    operators.push(word.substr(x, 2));
                }
                else {
                    operators.push(word.substr(x, 1));

                    if(word[x] == '='){
                        equals++;
                    }
                }
            }

        }
    }

    // Match tokens to make sure there are no unexpected or missing tokens
    if(openParenthesis < closeParenthesis) {
        errors.push(")");
    }
    if(openParenthesis > closeParenthesis) {
        errors.push("(");
    }

    if(commas > forCount * 2 || commas < forCount * 2) {  // Must be two commas in parenthesis ie ( , , )s
        if(openParenthesis == closeParenthesis) {   // Make sure there are no unexpected or missing parenthesis
            errors.push(",");
        }
    }

    if(forCount == numBegin) { // If number of FOR's equals BEGIN's
        if (numBegin > numEnd || numBegin < numEnd) {   // Missing or unexpected END
            errors.push("END");
        }
    }
    else {
        errors.push("BEGIN");   // Missing BEGIN
    }
    if (forCount == numEnd){
        if (numEnd > numBegin || numEnd < numBegin) {   // Missing or unexpected BEGIN
            errors.push("BEGIN");
        }
    }
    else{
        errors.push("END"); // Missing END
    }

    if(equals > semicolons) {
        errors.push(";");
    }
    if(equals < semicolons) {
        errors.push("=");
    }

    // Print analysis results
    std::cout << "\nThe depth of nested loop(s) is " << loopCount;

    std::cout << "\n\nKeywords: ";
    printStack(keywords);

    std::cout << "\nIdentifier: ";
    printStack(identifiers);

    std::cout << "\nConstant: ";
    printStack(constants);

    std::cout << "\nOperators: ";
    printStack(operators);

    std::cout << "\nDelimiter: ";
    printStack(delimiters);

    std::cout << "\n\nSyntax Error(s): ";
    printStack(errors);

    std::cout << std::endl;

    file.close();
    return 0;
}

bool isUpperCase(std::string word){
    /*
     * Checks whether characters are uppercase
     * Used to check identifiers and keywords
     * Parameters - word
     * Output - isUpper
     * Returns - isUpper
     */

    bool isUpper = false;
    for(int i = 0; i < word.length(); i++){
        if(word[i] >= 'A' && word[i] <= 'Z'){
            isUpper = true;
        }
    }
    return isUpper;
}   // Returns true if uppercase letter is found

bool isNumber(std::string word) {
    return (word.find_first_of("0123456789") != std::string::npos);
}   //If a digit is found, returns true

std::string getFileName() {
    /*
     * Gets name of file to be read from
     * input - filename
     * return - filename
     */

    std::string fileName;
    std::cout << "\nPlease enter the name of the input file: ";
    std::cin >> fileName;   // file name
    return fileName;
}

std::string Stack::top(){
    return stack.back();
}   // returns reference to element at the top of the stack

void Stack::pop() {
    stack.pop_back();
}   // remove element at top of stack

void Stack::push(std::string word) {
    for(int x = 0; x < stack.size(); x++) {
        if (stack[x] == word) {
            return;
        }
    }
    stack.push_back(word);
}   // add word to stack if not already in stack

bool Stack::isEmpty() {
    return stack.empty();
}   // return true if stack is empty

void printStack(Stack stack) {
    if(stack.isEmpty()) {
        std::cout << "NA";
    }

    while(!stack.isEmpty()){
        std::cout << stack.top() << " ";
        stack.pop();
    }
}   // Prints elements