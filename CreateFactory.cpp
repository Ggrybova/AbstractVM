/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateFactory.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 11:54:38 by ggrybova          #+#    #+#             */
/*   Updated: 2018/09/01 11:54:40 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CreateFactory.hpp"
#include "Operand.hpp"

CreateFactory::CreateFactory() {
    fun[Int8] = &CreateFactory::createInt8;
    fun[Int16] = &CreateFactory::createInt16;
    fun[Int32] = &CreateFactory::createInt32;
    fun[Float] = &CreateFactory::createFloat;
    fun[Double] = &CreateFactory::createDouble; }

CreateFactory::CreateFactory(CreateFactory &src) { static_cast<void>(src); }

CreateFactory       &CreateFactory::operator=(CreateFactory const &src) {
    static_cast<void>(src);
    return *this; }

CreateFactory::~CreateFactory() {}

IOperand const      *CreateFactory::createOperand(eOperandType type, std::string const &value) const {
    IOperand const *(CreateFactory::*f)(std::string const & value) const;
    f = fun.at(type);
    return ((*this.*f)(value)); }

IOperand const      *CreateFactory::createInt8( std::string const &value ) const {
    return new Operand<int8_t>(Int8, value, std::stoi(value), 1); }

IOperand const      *CreateFactory::createInt16( std::string const &value ) const {
    return new Operand<int16_t>(Int16, value, std::stoi(value), 2); }

IOperand const      *CreateFactory::createInt32( std::string const &value ) const {
    return new Operand<int32_t>(Int32, value, std::stoi(value), 3); }

IOperand const      *CreateFactory::createFloat( std::string const &value ) const {
    return new Operand<float>(Float, value, std::stof(value), 4); }

IOperand const      *CreateFactory::createDouble( std::string const &value ) const {
    return new Operand<double>(Double, value, std::stod(value), 5); }
