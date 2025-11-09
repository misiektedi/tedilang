#include "core/impl/condition.hpp"

#include "core/tedilang_utils.hpp"

#include <iostream>
#include <string>

std::string condition_chars = "><=";
std::string condition_numbers = "0123456789";

bool condition( std::string instruction ) {
    size_t condition_startPos = instruction.find_first_of(condition_chars);
    if (condition_startPos == std::string::npos) {
        return 0;
    }
    size_t condition_endPos = instruction.find_last_of(condition_chars);

    size_t first_startPos = instruction.find_first_of(condition_numbers, condition_startPos);
    if (first_startPos == std::string::npos) {
        return 0;
    }

    size_t second_endPos = instruction.length();

    int first         = stoi( instruction.substr(0, condition_startPos) );
    int second        = stoi( instruction.substr(condition_endPos + 1, second_endPos) );

    std::string op = instruction.substr( condition_startPos, condition_endPos );
    
    int result = 0;

    if          (op == "<") return first < second;
    else if     (op == ">") return first > second;
    else if     (op == "==") return first == second;
    else if     (op == ">=") return first >= second;
    else if     (op == "<=") return first <= second;
    else        tedilang_exception("Invalid operator");

    if ( second_endPos != instruction.length() ) {
        std::string instructionAfter = std::to_string( result ) + instruction.substr(second_endPos);
    
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