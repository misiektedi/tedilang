#include "core/impl/condition.hpp"

#include <iostream>
#include <string>

std::string condition_chars = "><";
std::string condition_numbers = "0123456789";

int condition( std::string instruction ) {
    size_t operation_pos = instruction.find_first_of(condition_chars);
    if (operation_pos == std::string::npos) {
        return 0;
    }

    size_t secondcondition_numberstartPos = instruction.find_first_of(condition_numbers, operation_pos);
    if (secondcondition_numberstartPos == std::string::npos) {
        return 0;
    }

    size_t secondNumberEndPos = instruction.find_first_of(condition_chars, secondcondition_numberstartPos);
    if (secondNumberEndPos == std::string::npos) {
        secondNumberEndPos = instruction.length();
    }

    std::string instructionBuffer = instruction.substr( 0, secondNumberEndPos );

    int firstNumber         = stoi( instructionBuffer.substr(0, operation_pos) );
    int secondNumber        = stoi( instructionBuffer.substr(secondcondition_numberstartPos, secondNumberEndPos) );

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
    
        result = condition( instructionAfter );
    }

    return result;
}

bool get_condition(std::string instruction) {
    instruction.erase(remove(instruction.begin(), instruction.end(), ' '), instruction.end());
    
    // if (instruction.find_first_of(condition_chars) == std::string::npos) {
    //     return stoi(instruction);
    // }
    
    bool final = false;

    final = condition( instruction );

    return final;
}