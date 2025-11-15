#include "core/impl/calc.hpp"

#include "variables.hpp"

#include <iostream>
#include <string>

std::string calc_chars = "+-*/";

int interpret( std::string instruction ) {
    size_t operation_pos = instruction.find_first_of(calc_chars);
    if (operation_pos == std::string::npos) {
        return 0;
    }

    size_t secondStartPos = instruction.find_first_of(calc_chars) + 1;
    if (secondStartPos == std::string::npos) {
        return 0;
    }

    size_t secondEndPos = instruction.find_first_of(calc_chars, secondStartPos);
    if (secondEndPos == std::string::npos) {
        secondEndPos = instruction.length();
    }

    std::string instructionBuffer   = instruction.substr( 0, secondEndPos );

    std::string firstStr      = instructionBuffer.substr(0, operation_pos);
    std::string secondStr     = instructionBuffer.substr(operation_pos + 1, secondEndPos);

    int first;
    int second;

    if ( Variables::instance().isDeclaredVariable(firstStr) ) {
        first                 = Variables::instance().getInt(firstStr);
    } else {
        first                 = stoi( firstStr );
    }

    if ( Variables::instance().isDeclaredVariable(secondStr) ) {
        second                = Variables::instance().getInt(secondStr);
    } else {
        second                = stoi( secondStr );
    }

    char op = instruction[operation_pos];

    int result = 0;

    switch ( op ) {
        case '+':
            result = first + second;
            break;

        case '-':
            result = first - second;
            break;

        case '*':
            result = first * second;
            break;

        case '/':
            result = first / second;
            break;
    }

    if ( secondEndPos != instruction.length() ) {
        std::string instructionAfter = std::to_string( result ) + instruction.substr(secondEndPos);
    
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