//
// Created by bambuchachkin on 7/19/25.
//

#include "Parser.h"
#include <iostream>
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

Parser::Parser() {}

Parser::~Parser() {}

bool Parser::Number_or_not(char simbol) const {
    if (int(simbol) >= int('0') && int(simbol) <= int('9')) {
        return true;
    }
    return false;
}


bool Parser::Check_Format(std::string File_Name) const{
    if (File_Name.substr(File_Name.size()-4, File_Name.size()-1) == ".txt") {
        return true;
    }
    throw "Choose a .txt file";
}

std::string Parser::Standart_Numbers(std::string Line) {
    if (!Tasks["Standart_Numbers"]) return Line;
    std::string New_Line = Line + ' '; // Во избидание выхода за границу
    Why_not:
        for (int i=0; i != New_Line.size(); i++) {
            if (New_Line[i] == '.') {
                if (!Number_or_not(New_Line[i-1])) {
                    New_Line.insert(i, "0");
                    goto Why_not;
                }
                if (!Number_or_not(New_Line[i+1])) {
                    New_Line.insert(i+1, "0");
                    goto Why_not;
                }
            } else if (New_Line[i] == ' ' && i<New_Line.size()-1) {
                if (New_Line[i+1] == ' ') {
                    New_Line.erase(i+1, 1);
                    goto Why_not;
                }
            }
        }
    New_Line.pop_back(); // Удаляем лишний пробел
    return New_Line;
}

std::string Parser::Semicolon_Point(std::string Line) {
    if (!Tasks["Semicolon_Point"]) return Line;
    return Line+';';
}

std::string Parser::From_G1_to_G01(std::string Line) {
    if (!Tasks["From_G1_to_G01"]) return Line;
    int G_Pos = 0;
    int Space_Pos = 0;

    for (int i =0; i!= Line.size(); i++) {
        if (Line[i] == 'G') {
            G_Pos = i;
            Space_Pos = i;
            while (Line[Space_Pos]!=' ') {
                Space_Pos++;
            }
            Last_G_Number = Line.substr(G_Pos+1,Space_Pos-G_Pos-1);

            if (Last_G_Number.size() == 1) {
                Last_G_Number.insert(0,"0");
            }

            Line.replace(G_Pos+1, Space_Pos - G_Pos, Last_G_Number+' ');
            return Line;
        }
    }
    for (int i =0; i!= Line.size(); i++) {
        if (Line[i] == ' ') {
            Line.insert(i," G");
            Line.insert(i+2, Last_G_Number);
            return Line;
        }
    }
    return Line;
}

std::string Parser::The_Ending_Symbol(std::string Line) {
    if (!Tasks["The_Ending_Symbol"] && Line.substr(0,4) == "END_") return "";
    if (!Tasks["The_Ending_Symbol"]) return Line;
    if (Line.substr(0,4) == "END_") {
        std::cout<<YELLOW << "Введите желаемый символ окончания вашей программы: "<<RESET;
        std::string symbol;
        std::cin >> symbol;
        std::string substr= Line.substr(4);
        substr.pop_back();
        return "N"+substr+" "+symbol+";";
    }
    return Line;
}

void Parser::String_Analis(std::string Line) { // Добавить вариации преобразованиея через оператор switch в зависимости от выбора пользователя
    std::cout<<GREEN;

    std::string New_Line = Line;
    New_Line = Standart_Numbers(New_Line);
    New_Line = Semicolon_Point(New_Line);
    New_Line = From_G1_to_G01(New_Line);
    New_Line = The_Ending_Symbol(New_Line);

    std::cout<<New_Line<<'\n';
    outputFile << New_Line<<'\n';
    std::cout<<RESET;
}


bool Parser::Work_File(std::string File_Name){
    Check_Format(File_Name);
    inputFile.open(File_Name);
    outputFile.open(File_Name.substr(0, File_Name.size()-4)+"_MODIFIED.txt");

    if (inputFile.is_open() && outputFile.is_open()) {
        std::string line;
        int Line_Number = 0;
        while (std::getline(inputFile, line)) {
            if (!line.empty() && line.back() == '\r') { // Удаление команды для возврата каретки на windows
                line.pop_back(); // Удаляем \r
            }
            if (line.size()) {
                String_Analis(line);
                Line_Number++;
                std::cout<<line<<'\n'; // Убрать вывод в консоль
            }
        }
        String_Analis("END_" + std::to_string(Line_Number));
        outputFile.close();
        inputFile.close();
        std::cout << "Новый файл сохранен по адресу: " << File_Name.substr(0,File_Name.size()-4)+"_MODIFIED.txt";
        return true;
    }
    throw "Can not open or create the file";
}

bool Parser::Add_New_Task(std::string New_Task) {
    Tasks[New_Task] = true;
    return true;
}

bool Parser::Delete_Task(std::string New_Task) {
    Tasks[New_Task] = false;
    return true;
}

bool Parser::Pars_File(std::string File_Name) {
    Work_File(File_Name);
    return true;
}
