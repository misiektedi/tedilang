#include "core/impl/calc.hpp"

#include "variables.hpp"

#include <iostream>
#include <string>

std::string calc_chars = "+-*/";
std::string calc_numbers = "0123456789";

int interpret( std::string instruction ) {
    size_t operation_pos = instruction.find_first_of(calc_chars);
    if (operation_pos == std::string::npos) {
        return 0;
    }

    size_t secondNumberStartPos = instruction.find_first_of(calc_chars) + 1;
    if (secondNumberStartPos == std::string::npos) {
        return 0;
    }

    size_t secondNumberEndPos = instruction.find_first_of(calc_chars, secondNumberStartPos);
    if (secondNumberEndPos == std::string::npos) {
        secondNumberEndPos = instruction.length();
    }

    std::string instructionBuffer   = instruction.substr( 0, secondNumberEndPos );

    std::string firstNumberStr      = instructionBuffer.substr(0, operation_pos);
    std::string secondNumberStr     = instructionBuffer.substr(operation_pos + 1, secondNumberEndPos);

    int firstNumber;
    int secondNumber;

    if ( Variables::instance().isDeclaredVariable(firstNumberStr) ) {
        firstNumber                 = Variables::instance().getInt(firstNumberStr);
    } else {
        firstNumber                 = stoi( firstNumberStr );
    }

    if ( Variables::instance().isDeclaredVariable(secondNumberStr) ) {
        secondNumber                = Variables::instance().getInt(secondNumberStr);
    } else {
        secondNumber                = stoi( secondNumberStr );
    }

    char op = instruction[operation_pos];

    int result = 0;

    switch ( op ) {
        case '+':
            result = firstNumber + secondNumber;
            break;

        case '-':
            result = firstNumber - secondNumber;
            break;

        case '*':
            result = firstNumber * secondNumber;
            break;

        case '/':
            result = firstNumber / secondNumber;
            break;
    }

    if ( secondNumberEndPos != instruction.length() ) {
        std::string instructionAfter = std::to_string( result ) + instruction.substr(secondNumberEndPos);
    
        result = interpret( instructionAfter );
    }

    return result;
}

int calc(std::string instruction) {
    instruction.erase(remove(instruction.begin(), instruction.end(), ' '), instruction.end());
    
    if (instruction.find_first_of(calc_chars) == std::string::npos) {
        return stoi(instruction);
    }
    
    int final = 0;

    final = interpret( instruction );

    return final;
}