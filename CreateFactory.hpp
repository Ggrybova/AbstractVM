/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateFactory.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 11:54:28 by ggrybova          #+#    #+#             */
/*   Updated: 2018/09/01 11:54:32 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATEFACTORY_HPP
#define CREATEFACTORY_HPP
#include "IOperand.hpp"
# include <array>

class CreateFactory {

public:
    CreateFactory();
    CreateFactory(CreateFactory &src);
    CreateFactory               &operator=(CreateFactory const &src);
    ~CreateFactory();

    IOperand const              *createOperand(eOperandType type, std::string const &value) const;
    std::array<IOperand const   *(CreateFactory::*)(std::string const &value) const, 5> fun;

private:
    IOperand const              *createInt8( std::string const &value ) const;
    IOperand const              *createInt16( std::string const &value ) const;
    IOperand const              *createInt32( std::string const &value ) const;
    IOperand const              *createFloat( std::string const &value ) const;
    IOperand const              *createDouble( std::string const &value ) const;

};

#endif //CREATEFACTORY_HPP
