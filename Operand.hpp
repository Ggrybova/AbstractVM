/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 11:56:07 by ggrybova          #+#    #+#             */
/*   Updated: 2018/09/01 11:56:14 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
#define OPERAND_HPP
#include "CreateFactory.hpp"
#include "IOperand.hpp"
#include <cmath>

template<class T>
class Operand : public IOperand {

public:
    Operand(eOperandType type, std::string const & value, T nbr, int precision) {
        this->_type = type;
        this->_str = value;
        this->_nbr = nbr;
        this->_precision = precision; }

    Operand(Operand const &src) { *this = src; }

    Operand             &operator=(Operand const &src) {
        if(this != &src) {
            this->_type = src._type;
            this->_str = src._str;
            this->_nbr = src._nbr;
            this->_precision = src._precision; }
        return *this; }

    ~Operand() {}

    int                 getPrecision() const {return this->_precision;}
    eOperandType        getType() const {return this->_type;}

    IOperand const      *operator+(IOperand const &rhs) const {
        if (this->getType() >= rhs.getType()) {
            T sum =  this->_nbr + static_cast<T>(std::stod(rhs.toString()));
            CreateFactory sumOperator;
            return sumOperator.createOperand(this->_type, std::to_string(sum)); }
        return (rhs + *this); }

    IOperand const      *operator-(IOperand const &rhs) const {
        IOperand const    *opposite = rhs * (-1);
        if (this->getType() >= rhs.getType())
            return *this + *opposite;
        else
            return (*opposite + *this); }

    IOperand const      *operator*(IOperand const &rhs) const {
        if (this->getType() >= rhs.getType()) {
            T prod =  this->_nbr * static_cast<T>(std::stod(rhs.toString()));
            CreateFactory sumOperator;
            return sumOperator.createOperand(this->_type, std::to_string(prod)); }
        return (rhs * *this); }

    IOperand const      *operator/(IOperand const &rhs) const {
        CreateFactory newOperator;
        if (this->getType() >= rhs.getType()) {
            T div = this->_nbr / static_cast<T>(std::stod(rhs.toString()));
            return newOperator.createOperand(this->_type, std::to_string(div)); }
        else {
            IOperand const   *tmp = newOperator.createOperand(rhs.getType(), this->_str);
            return (*tmp / rhs); }}

    IOperand const      *operator%(IOperand const &rhs) const {
        CreateFactory newOperator;
        if (this->getType() >= rhs.getType()) {
            T mod = fmod(this->_nbr, static_cast<T>(std::stod(rhs.toString())));
            return newOperator.createOperand(this->_type, std::to_string(mod)); }
        else {
            IOperand const   *tmp = newOperator.createOperand(rhs.getType(), this->_str);
            return (*tmp % rhs); }}

    IOperand const      *operator*(int scalar) const {
        CreateFactory     newOperator;
        IOperand const    *sc = newOperator.createOperand(this->_type, std::to_string(scalar));
        return *this * *sc; }

    std::string const   &toString()const { return this->_str; }

private:
    std::string         _str;
    T                   _nbr;
    int                 _precision;
    eOperandType        _type;

};

#endif //OPERAND_HPP
