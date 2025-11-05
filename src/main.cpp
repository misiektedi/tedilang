#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <array>
#include <algorithm>
#include <cstring>
#include <variant>
#include <ranges>
#include <cctype>

#include "core/calc.h"

class Value {
public:
    enum class Type { INT, DOUBLE, STRING, BOOL };

private:
    Type type;
    std::variant<int, double, std::string, bool> data;

public:
    Value(int v) : type(Type::INT), data(v) {}
    Value(double v) : type(Type::DOUBLE), data(v) {}
    Value(const std::string& v) : type(Type::STRING), data(v) {}
    Value(bool v) : type(Type::BOOL), data(v) {}
    Value() : type(Type::INT), data(0) {}

    Type getType() const { return type; }

    int asInt() const { return std::get<int>(data); }
    double asDouble() const { return std::get<double>(data); }
    const std::string& asString() const { return std::get<std::string>(data); }
    bool asBool() const { return std::get<bool>(data); }
};

std::unordered_map<std::string, Value> variables;

bool check_function(std::string line, std::string function_name) {
    if ( line.starts_with(function_name + "(") && line.ends_with(")") ) return true;

    return false;
}

std::string function_content(std::string line, int name_length) {
    return line.substr(name_length + 1, line.length() - name_length - 2 );
}

std::string remove_qm(std::string text) {
    return text.substr(1, text.length() - 2 );
}

void interpreter(std::string line) {

    if ( check_function(line, "output") ) {

        std::string content = function_content(line, 6);

        if ( content.starts_with('"') && content.ends_with('"') ) {
            std::cout << remove_qm( content ) << std::endl;
        } 
        else
        {
            std::string type = content.substr( 0, content.find('@') );
            std::string varName = content.substr( content.find('@') + 1 );
            
            if ( type == "int" )            std::cout << variables[varName].asInt() << std::endl;
            else if ( type == "string" )    std::cout << variables[varName].asString() << std::endl;
            else std::cerr << "[ERROR] Nothing to output." << std::endl;
        }

    }

    if ( check_function(line, "shell") ) {

        std::string content = function_content(line, 5);

        if ( content.starts_with('"') && content.ends_with('"') ) {
            const char* contentChar = remove_qm( content ).data();

            int result = system(contentChar);

            std::cout << result << std::endl;
        }
    }

    if ( line.starts_with("let") ) {
        std::array<std::string, 2> types = {"int", "std::string"};

        std::string lineStriped = line.substr(4);

        std::string type = lineStriped.substr(0, 0 + lineStriped.find(' ') );

        std::string content = lineStriped.substr(1 + type.length());

        size_t pos = content.find('=');

        std::string key = content.substr(0, -1 + pos);
        std::string value = content.substr(pos + 2);
        
        if ( type == "int" ) {
            variables[key] = Value( calc(value) );
        } else if ( type == "string" ) {
            variables[key] = Value( remove_qm(value) );
        }
    }

    if ( check_function(line, "wait") ) {

        std::string content = function_content(line, 4);

        int contentInt = stoi(content);

        std::this_thread::sleep_for(std::chrono::seconds(contentInt));

    }

    if ( line.starts_with("exit") ) {
        exit(0);
    }

}

int main( int argc, char* argv[] ) {
    std::ifstream file( argv[1] );

    if (!file.is_open()) {
        std::cerr << "File not exist." << std::endl;
        return 1;
    }

    std::string line;
    bool main = false;

    while ( getline(file, line, ';') ) {

        if ( line.starts_with("#") ) continue;

        if ( line.starts_with("main {") ) {
            main = true;
            line = line.substr(6);
        }

        if ( main == false ) continue;


        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        
        auto view = line
            | std::views::drop_while([](unsigned char ch){ return std::isspace(ch); })
            | std::views::reverse
            | std::views::drop_while([](unsigned char ch){ return std::isspace(ch); })
            | std::views::reverse;

        std::string line(view.begin(), view.end());



        interpreter( line );

    }

    file.close();
    return 0;
}