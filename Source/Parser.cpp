//
// Created by bambuchachkin on 7/19/25.
//

#include "Parser.h"
#include <iostream>

bool Parser::Check_Format(std::string File_Name) const{
    if (File_Name.substr(File_Name.size()-4, File_Name.size()-1) == ".txt") {
        return true;
    }
    throw "Choose a .txt file";
}

bool Parser::Work_File(std::string File_Name){
    try {
        Check_Format(File_Name); // В случае провала выбрасывает исключение
    }
    catch (const char* error_message) { // Перенести в window
        std::cout<<error_message;
        return false;
    }
    std::ifstream inputFile(File_Name);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            if (!line.empty() && line.back() == '\r') { // Удаление команды для возврата каретки на windows
                line.pop_back(); // Удаляем \r
            }
            if (line.size()) {
                std::cout<<line<<'\n';
            }
        }
        inputFile.close();
        return true;
    }
    throw "Can not open the file";
}


bool Parser::Pars_File_from_to(std::string from_File_Name, std::string to_File_Name) {
    try {
        Work_File(from_File_Name);
    }
    catch (const char* error_message) { // Перенести в window
        std::cout<<error_message;
        return false;
    }
    return true;
}
