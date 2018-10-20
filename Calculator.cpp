/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Calculator.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 11:50:10 by ggrybova          #+#    #+#             */
/*   Updated: 2018/09/01 11:50:39 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Calculator.hpp"

Calculator::Calculator(std::list<std::string> ins, std::list<std::string> typ, std::list<std::string> val) {
    while (ins.size() != 0 && typ.size() != 0 && val.size() != 0) {
        eOperandType type;
        if (typ.front() == "int8") {type = Int8;}
        else if (typ.front() == "int16") {type = Int16;}
        else if (typ.front() == "int32") {type = Int32;}
        else if (typ.front() == "float") {type = Float;}
        else {type = Double;}
        executeInstruction(ins.front(), type, val.front());
        ins.pop_front();
        typ.pop_front();
        val.pop_front(); }}

Calculator::Calculator(Calculator const &src) { *this = src; }

Calculator      &Calculator::operator=(Calculator const &src) {
    if(this != &src) {
        this->_stack = src._stack;
    }
    return *this; }

Calculator::~Calculator() {}

void            Calculator::executeInstruction(std::string ins, eOperandType typ, std::string val) {
    if (ins == "push") {
        check_flow(typ, std::stold(val));
        this->_stack.push(this->_factory.createOperand(typ, val)); }
    else if (ins == "assert") {
        if (this->_stack.empty())
            throw StackIsOverException();
        IOperand const  *Assert = this->_factory.createOperand(typ, val);
        if (Assert->getType() != this->_stack.top()->getType() || Assert->toString() != this->_stack.top()->toString())
            throw AssertFalseException(); }
    else if (ins == "pop") {
        if (this->_stack.empty())
            throw StackIsOverException();
        this->_stack.pop(); }
    else if (ins == "dump")
        this->printStack(0);
        else if (ins == "dump -t")
        this->printStack(1);
    else if (ins == "print") {
        if (this->_stack.empty())
            throw StackIsOverException();
        if (this->_stack.top()->getType() != Int8)
            throw AssertFalseException();
        char ascii = std::stoi(this->_stack.top()->toString());
        if (ascii > 32 && ascii < 127) { std::cout << ascii << std::endl; }
        else { std::cout << "I Can't interprets as an ASCII this value" << std::endl; }}
    else if (ins == "add" || ins == "sub" || ins == "mul" || ins == "div" || ins == "mod") {
        if (this->_stack.size() < 2)
            throw StackIsOverException();
        IOperand const    *B = this->_stack.top();
        this->_stack.pop();
        IOperand const    *A = this->_stack.top();
        this->_stack.pop();
        if (ins == "add") {
            check_flow_add(A->getType(), B->getType(), std::stod(A->toString()), std::stod(B->toString()));
            this->_stack.push(*A + *B); }
        else if (ins == "sub")
            this->_stack.push(*A - *B);
        else if (ins == "mul") {
            check_flow_mult(A->getType(), B->getType(), std::stod(A->toString()), std::stod(B->toString()));
            this->_stack.push(*A * *B); }
        else if (ins == "div") {
            if (std::stod(B->toString()) == 0)
                throw DivisionByNullException();
            this->_stack.push(*A / *B); }
        else if (ins == "mod") {
            if (std::stod(B->toString()) == 0)
                throw DivisionByNullException();
            this->_stack.push(*A % *B); }}}


void            Calculator::printStack(int flg) {
    std::stack<IOperand const *> stack = this->_stack;
    while (!stack.empty()) {
        if (flg == 0)
            std::cout << stack.top()->toString() << std::endl;
        else {
            eOperandType t = stack.top()->getType();
            std::string  type;
            if (t == 0) {type = "(INT8)";}
            else if (t == 1) {type = "(INT16)";}
            else if (t == 2) {type = "(INT32)";}
            else if (t == 3) {type = "(FLOAT)";}
            else {type = "(DOUBLE)";}
            std::cout << stack.top()->toString() << " " << type << std::endl;
        }
        stack.pop(); }}

void            Calculator::check_flow_add(eOperandType typA, eOperandType typB, double A, double B) {
    if (typA > typB) { check_flow(typA, A + B); }
    else { check_flow(typB, A + B); }}

void            Calculator::check_flow_mult(eOperandType typA, eOperandType typB, double A, double B) {
    if (typA > typB) { check_flow(typA, A * B); }
    else { check_flow(typB, A * B); }}

void            Calculator::check_flow(eOperandType typ, double i) {
    if ((typ == Int8 && i < -128) || (typ == Int16 && i < -8388608) ||
        (typ == Int32 && i < std::numeric_limits<int>::min()) ||
        (typ == Float && i < std::numeric_limits<float>::min()*(-1)) ||
        (typ == Double && i < std::numeric_limits<double>::min()*(-1)))
        throw OverflowException();
    if ((typ == Int8 && i > 127) || (typ == Int16 && i > 8388607) ||
        (typ == Int32 && i > std::numeric_limits<int>::max()) ||
        (typ == Float && i > std::numeric_limits<float>::max()) ||
        (typ == Double && i > std::numeric_limits<double>::max()))
        throw UnderflowException(); }

Calculator::OverflowException::OverflowException() {}
Calculator::OverflowException::OverflowException(OverflowException const &src) {*this = src;}
Calculator::OverflowException &Calculator::OverflowException::operator=(OverflowException const &src) {
    if (this != &src)
        *this = src;
    return *this;}
Calculator::OverflowException::~OverflowException() throw() {}
const char* Calculator::OverflowException::what() const throw() {return ("Wow, wow, easy! Overflow on a value");}

Calculator::UnderflowException::UnderflowException() {}
Calculator::UnderflowException::UnderflowException(UnderflowException const &src) {*this = src;}
Calculator::UnderflowException &Calculator::UnderflowException::operator=(UnderflowException const &src) {
    if (this != &src)
        *this = src;
    return *this;}
Calculator::UnderflowException::~UnderflowException() throw() {}
const char* Calculator::UnderflowException::what() const throw() {return ("Wow, wow, easy! Underflow on a value");}

Calculator::StackIsOverException::StackIsOverException() {}
Calculator::StackIsOverException::StackIsOverException(StackIsOverException const &src) {*this = src;}
Calculator::StackIsOverException &Calculator::StackIsOverException::operator=(StackIsOverException const &src) {
    if (this != &src)
        *this = src;
    return *this;}
Calculator::StackIsOverException::~StackIsOverException() throw() {}
const char* Calculator::StackIsOverException::what() const throw() {return ("Stop and think! How many operands is in the stack? Stack don't have enough operands!");}

Calculator::DivisionByNullException::DivisionByNullException() {}
Calculator::DivisionByNullException::DivisionByNullException(DivisionByNullException const &src) {*this = src;}
Calculator::DivisionByNullException &Calculator::DivisionByNullException::operator=(DivisionByNullException const &src) {
    if (this != &src)
        *this = src;
    return *this;}
Calculator::DivisionByNullException::~DivisionByNullException() throw() {}
const char* Calculator::DivisionByNullException::what() const throw() {return ("Are you kidding? Division/modulo by 0.");}

Calculator::AssertFalseException::AssertFalseException() {}
Calculator::AssertFalseException::AssertFalseException(AssertFalseException const &src) {*this = src;}
Calculator::AssertFalseException &Calculator::AssertFalseException::operator=(AssertFalseException const &src) {
    if (this != &src)
        *this = src;
    return *this;}
Calculator::AssertFalseException::~AssertFalseException() throw() {}
const char* Calculator::AssertFalseException::what() const throw() {return ("Gotcha! An assert/print instruction is not true;)");}
