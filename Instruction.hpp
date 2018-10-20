/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instruction.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 11:55:52 by ggrybova          #+#    #+#             */
/*   Updated: 2018/09/01 11:55:54 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP
#include "IOperand.hpp"
#include <iostream>
#include <list>
#include <stack>
#include <map>
#include <regex>
#include <sstream>
#include <fstream>

class Instructions {

public:
    Instructions();
    Instructions(Instructions const &src);
    Instructions                        &operator=(Instructions const &src);
    ~Instructions();

    void                                lexer();
    void                                lexer(std::string str);
    void                                lexerValidation(std::string str);
    void                                parser();
    void                                parserValidation(std::string inst, std::string arg);

    std::string                         getInstruction();
    std::list<std::string>              mySplit(std::string str, std::string sep);

    std::list<std::string>              _errors;
    std::list<std::string>              _instructions;
    std::list<std::string>              _type;
    std::list<std::string>              _value;

    void                                printErrors();
    std::string                         fileName;
    std::fstream                        file;
    bool                                stop;

private:
};

#endif //INSTRUCTIONS_HPP
