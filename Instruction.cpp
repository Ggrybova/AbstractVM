/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instruction.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 11:55:45 by ggrybova          #+#    #+#             */
/*   Updated: 2018/09/01 11:55:47 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Instruction.hpp"


Instructions::Instructions() { this->stop = false; }

Instructions::Instructions(Instructions const &src) {*this = src;}

Instructions                    &Instructions::operator=(Instructions const &src) {
    if (this != &src) {
        this->_instructions = src._instructions;
        this->_type = src._type;
        this->_value = src._value;
        this->stop = src.stop; }
    return *this; }

Instructions::~Instructions() {}

void                            Instructions::lexer() {
    std::string                 instructionLine;
    char                        buf[101];
    std::fstream                file;
    if (this->fileName.size() != 0) {
        this->stop = true;
        file.open(this->fileName, std::fstream::in);
        if (file.is_open() == false) {
            std::cerr << "Could not open this stupid file: " << this->fileName << "!" << std::endl; exit(1);}
            file.getline(buf, 100);
            instructionLine = buf;
            std::cout << instructionLine << std::endl;
    }
    else
        instructionLine = this->getInstruction();
    if (instructionLine == ";;") {
        this->stop = true;
        return; }
    else {
        while (instructionLine != "exit") {
            if (instructionLine == ";;") {
                this->stop = true;
                this->_errors.push_back("Hey, buddy! The program doesn’t have an exit instruction(");
                return; }
            this->lexerValidation(instructionLine);
            if (this->fileName.size() != 0) {
                if (!file.getline(buf, 100)) {
                    this->_errors.push_back("Hey, buddy! The program doesn’t have an exit instruction(");
                    return; }
                instructionLine = buf;
                std::cout << instructionLine << std::endl;
            }
            else
                instructionLine = this->getInstruction(); }
        std::cout << "./avm" << std::endl; }}

void                            Instructions::lexerValidation(std::string str) {
    std::list<std::string>      split = this->mySplit(str, " ");

    if (str == "dump -t") {
        this->_instructions.push_back(str);
        this->_type.push_back("");
        this->_value.push_back("");
    }
    else if (str.front() != ';' && split.size() > 2 && split.back().front() != ';')
        this->_errors.push_back("Line has more then two commands or multispaces.");
    else if (split.size() == 1 && split.front() == "")
        this->_errors.push_back("Empty line commands? Seriously?");
    else if (str.front() != ';') {
        this->_instructions.push_back(split.front());
        split.pop_front();
        if (split.front() == "" || split.front().front() == ';') {
            this->_type.push_back("");
            this->_value.push_back("");}
        else {
            const std::string arg = split.front();
            std::regex type_rgx("(\\w+)\\(.*");
            std::regex value_rgx("[^\\(]*\\(([^\\)]*)\\)");
            std::smatch match_type;
            std::smatch match_value;
            if (std::regex_search(arg.begin(), arg.end(), match_type, type_rgx) &&
                std::regex_search(arg.begin(), arg.end(), match_value, value_rgx)) {
                this->_type.push_back(match_type[1]);
                this->_value.push_back(match_value[1]); }
            else
                this->_errors.push_back("Сan you stop doing this anymore? Do you known operand like " + arg + "?"); }}}

void                            Instructions::parser() {
    std::list<std::string>      ins = this->_instructions;
    std::list<std::string>      typ = this->_type;
    std::list<std::string>      val = this->_value;
    while (ins.size() != 0 && typ.size() != 0 && val.size() != 0) {
        if (ins.front() != "push" && ins.front() != "pop" && ins.front() != "dump" && ins.front() != "dump -t"
            && ins.front() != "assert" && ins.front() != "add" && ins.front() != "sub" && ins.front() != "mul"
            && ins.front() != "div" && ins.front() != "mod" && ins.front() != "print" && ins.front() != "exit" && ins.front() != ";;")
            this->_errors.push_back("\"" + ins.front() + "\"? No comments.");
        if (typ.front() != "int8" && typ.front() != "int16" && typ.front() != "int32" && typ.front() != "float" &&
            typ.front() != "double" && typ.front() != "")
            this->_errors.push_back("Interesting type: " + typ.front() + ", but no.");
        if (((ins.front() == "push" || ins.front() == "assert") && typ.front() == "") ||
            (!(ins.front() == "push" || ins.front() == "assert") && typ.front() != ""))
            this->_errors.push_back("Rate and go eat ice cream, you're confusing everything! Wrong argument \"" + typ.front() +
                "\" for instruction \"" + ins.front() + "\"");
    ins.pop_front();
    typ.pop_front();
    val.pop_front(); }}

std::string                     Instructions::getInstruction() {
    std::string buff;
    getline(std::cin, buff);
    return buff;
}

std::list<std::string>          Instructions::mySplit(std::string str, std::string sep) {
    std::list<std::string>      list;
    std::size_t                 found;

    while (!str.empty() && (found = str.find(sep)) != std::string::npos) {
        list.push_back(str.substr(0, found));
        str.erase (str.begin(), str.begin()+found+1); }
    list.push_back(str);
    return list; }

void                            Instructions::printErrors() {
    std::copy(this->_errors.begin(), this->_errors.end(), std::ostream_iterator<std::string>(std::cout,"\n") ); }
