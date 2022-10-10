#include "calc.h"
#include <iostream>
#include <ostream>
#include <string>
#include <sstream>
using namespace std; 

// Constructor: no parameters
Calc::Calc() : error{false}, display{0}, oper{' '}, result{0}, memory{0} {}

// Constructor: with parameter
Calc::Calc(const Calc &other)
    : error{other.error}, display {other.display}, oper{other.oper}, result{other.result}, memory{other.memory} {}

// Addding between 0 and 9 to the end of dispaly
void Calc::digit(int digit){
    if (digit >= 0 && digit <= 9) display = (display * 10) + digit; 
}

// Executing operator or setting operator field if no operator
void Calc::op(char newOper){
    switch (oper) {

        // If no operator set, display contents are result
        case ' ':
            result = display;
            error = false;
            break;
        
        // If operator set, result is combining operator with display
        case '+':
            result += display;
            error = false;
            break;
        case '-':
            result -= display;
            error = false;
            break;
        case '*':
            result *= display;
            error = false;
            break;

        // If division by 0, error flag set, result is 0
        case '/':
            if (display == 0) {
                error = true;
                result = 0; 
            } else {
                result /= display;
                error = false;
            }
            break;
    }

    // Reset display and set new operator field
    display = 0; 
    oper = newOper; 
}

// Combining result and display using operator
void Calc::equals(){
    switch (oper) {

        // If no operator set, display contents are result
        case ' ':
            result = display;
            error = false;
            break;

        // If operator set, result is combining operator with display
        case '+':
            result += display;
            error = false;
            break;
        case '-':
            result -= display;
            error = false;
            break;
        case '*':
            result *= display;
            error = false;
            break;
        
        // If division by 0, error flag set, result is 0
        case '/':
            if (display == 0) {
                error = true;
                result = 0; 
            } else {
                result /= display;
                error = false;
            }
            break;
    }

    // Reset operator and set new display
    oper = ' ';
    display = result;
}

// Adding displayed value to contents of memory
void Calc::memPlus(){
    memory += display; 
}

// Clearing contents of memory
void Calc::memClear(){
    memory = 0;
}

// Copying contents of memory to the display
void Calc::memRecall(){
    display = memory; 
}

// Returning whether or not the error flag is set
bool Calc::isError() const {
    return error; 
}

// Resetting all memory to 0, clearing operator, resetting error flag
void Calc::allClear() {
    memory = 0; 
    result = 0;
    display = 0; 
    error = false;
    oper = ' ';
}

// Output operator
ostream & operator<<(ostream &out, const Calc &c) {
    
    // If nothing in memory, print just display
    if (c.memory == 0) out << c.display;
    
    // If something in memory, print display M: and memory
    else out << c.display << " M: " << c.memory;
    
    // If error flag is set, append E
    if (c.isError()) out << " E";
    
    return out; 
}

