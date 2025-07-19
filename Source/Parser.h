//
// Created by bambuchachkin on 7/19/25.
//



#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <fstream>

class Parser {
    bool Check_Format(std::string File_Name) const;
    bool Work_File(std::string File_Name);
public:
    bool Pars_File_from_to(std::string from_File_Name,
        std::string to_File_Name);
};



#endif //PARSER_H
