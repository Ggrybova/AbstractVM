/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Calculator.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 11:50:52 by ggrybova          #+#    #+#             */
/*   Updated: 2018/09/01 11:52:08 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP
#include <climits>
#include <exception>
#include <stack>
#include <list>
#include <iostream>
#include "IOperand.hpp"
#include "CreateFactory.hpp"

class Calculator {

public:
    Calculator(std::list<std::string> ins, std::list<std::string> typ, std::list<std::string> val);
    Calculator(Calculator const &src);
    Calculator  &operator=(Calculator const &);
    ~Calculator();

    void        executeInstruction(std::string ins, eOperandType typ, std::string val);
    void        printStack(int flg);
    void        check_flow(eOperandType typ, double val);
    void        check_flow_add(eOperandType typA, eOperandType typB, double A, double B);
    void        check_flow_mult(eOperandType typA, eOperandType typB, double A, double B);

    class OverflowException : public std::exception {
    public:
        OverflowException();
        OverflowException(OverflowException const &src);
        OverflowException           &operator=(OverflowException const &);
        ~OverflowException() throw();
        virtual const char          *what() const throw(); };

    class UnderflowException : public std::exception {
    public:
        UnderflowException();
        UnderflowException(UnderflowException const &src);
        UnderflowException          &operator=(UnderflowException const &);
        ~UnderflowException() throw();
        virtual const char          *what() const throw(); };

    class StackIsOverException : public std::exception {
    public:
        StackIsOverException();
        StackIsOverException(StackIsOverException const &src);
        StackIsOverException        &operator=(StackIsOverException const &);
        ~StackIsOverException() throw();
        virtual const char          *what() const throw(); };

    class DivisionByNullException : public std::exception {
    public:
        DivisionByNullException();
        DivisionByNullException(DivisionByNullException const &src);
        DivisionByNullException     &operator=(DivisionByNullException const &);
        ~DivisionByNullException() throw();
        virtual const char          *what() const throw(); };

    class AssertFalseException : public std::exception {
    public:
        AssertFalseException();
        AssertFalseException(AssertFalseException const &src);
        AssertFalseException        &operator=(AssertFalseException const &);
        ~AssertFalseException() throw();
        virtual const char          *what() const throw(); };

private:
    std::stack<IOperand const *>    _stack;
    CreateFactory                   _factory;

};

#endif //CALCULATOR_HPP
