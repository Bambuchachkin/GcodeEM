//
// Created by bambuchachkin on 7/19/25.
//



#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <fstream>
#include <map>

class Parser {

    std::string Last_G_Number;
    std::ifstream inputFile;
    std::ofstream outputFile;
    std::map<std::string, bool> Tasks;

    bool Check_Format(std::string File_Name) const;
    bool Work_File(std::string File_Name);
    bool Number_or_not(char simbol) const;

    void String_Analis(std::string Line);

    std::string Standart_Numbers(std::string Line);
    std::string Semicolon_Point(std::string Line);
    std::string From_G1_to_G01(std::string Line);
    std::string The_Ending_Symbol(std::string Line);

public:
    Parser();
    ~Parser();
    bool Pars_File(std::string File_Name);
    bool Add_New_Task(std::string New_Task);
    bool Delete_Task(std::string New_Task);
};



#endif //PARSER_H
