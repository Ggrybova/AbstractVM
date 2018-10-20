/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 11:56:30 by ggrybova          #+#    #+#             */
/*   Updated: 2018/09/01 11:56:32 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOperand.hpp"
#include "Operand.hpp"
#include "Instruction.hpp"
#include "CreateFactory.hpp"
#include "Calculator.hpp"
#include <iostream>
#include <regex>

int main(int argc, char **argv) {
    if (argc <= 2) {
        Instructions    instr;
        while (!instr.stop) {
            if (argc == 2) {
                instr.fileName = argv[1]; }
            instr.lexer();
            instr.parser();
            if (instr._errors.size() != 0) {
                if (!(instr._errors.empty()))
                    instr.printErrors();
                return 0; }
            try {
                Calculator  calc(instr._instructions, instr._type, instr._value);
                instr._instructions.clear();
                instr._type.clear();
                instr._value.clear();}
            catch (Calculator::OverflowException &e) {
                std::cout << e.what() << std::endl;
                instr.printErrors();
                return 0; }
            catch (Calculator::UnderflowException &e) {
                std::cout << e.what() << std::endl;
                instr.printErrors();
                return 0; }
            catch (Calculator::StackIsOverException &e) {
                std::cout << e.what() << std::endl;
                instr.printErrors();
                return 0; }
            catch (Calculator::DivisionByNullException &e) {
                std::cout << e.what() << std::endl;
                instr.printErrors();
                return 0; }
            catch (Calculator::AssertFalseException &e) {
                std::cout << e.what() << std::endl;
                instr.printErrors();
                return 0; }
            catch (const std::invalid_argument &oor) {
                std::cerr << "Type error. Go home!"  << std::endl;
                return 0; }
            catch (const std::out_of_range &oor) {
                std::cerr << "Wow, wow, easy! Out of Range error!" << std::endl;
                return 0; }}
        return 0; }
    else {
        std::cout << "Maybe you'll try again?\nusage:\t./avm\n\t./avm <file>" << std::endl;
        return 0;
    }
}


/* ++++++++++++++++++++++++++ *
------------
push int32(10)
push int32(42)
div
dump
exit
------------
push int32(42)
dump
pop
exit
------------
push int32(42)
push int32(10)
add
dump
exit
-----------
push double(42)
push int32(10)
div
dump
exit
-----------
push int32(42)
push int8(8)
print
exit
-----------
push double(4.2)
push int32(10)
push int32(42)
push float(0.42)
dump
exit
------------
push double(4.2)
push int32(10)
pop
push int32(42)
push float(0.42)
dump
exit
------------
push int32(42)
push int32(10)
; comment
dump
exit
------------
push int16(543)
assert int16(543)
exit
------------
push float(1)
push double(2.09)
assert double(2.09)
dump
exit
------------
push float(1)
push double(2.09)
assert double(2.09)
;comment bla bla
exit
------------
push int32(42)
push int32(33)
add
push float(44.55)
mul
push double(42.42)
push int32(42)
dump
pop
assert double(42.42)
exit
------------
push int16(-8388608)
dump
exit
------------
exit
------------
push int32(42)
push int32(42)
add ;poney
push float(44.55)
mul
push double(42.42)
;commentaire de ouf
push int32(42)
dump
pop
assert double(42.42)
exit
------------
push int32(42)
push int32(42)
add
dump
exit
------------
push int8(42)
push double(42)
add
dump -t
exit
 * - - - - - - - - - - - - - - *
------------
push int32(10)
push int16(0)
div
dump
exit
------------
push int32(11)
push int32(1)
push int16(1)
sub
div
dump
exit
------------
push int32(0)
push int16(10)
mod
dump
exit
------------
push int32(blabla)
dump
pop
exit
------------
pop
exit
------------
push int16(543)
pop
pop
exit
------------
push int32(42)
push int32(1)
print
exit
-----------
push int16(543)
assert int16(54)
exit
------------
push int16(543)
assert int8(543)
exit
------------
push int16(543)
assert int16(54)
push int32(1) int8(11)
exit
------------
push float(1.0)
add
push
assert double(2.09)
;comment bla bla
exit
------------
push int32(42)
push int32(10)
;;
------------
push int32(42)
push int32(10)
div int8(11)
exit
------------
push int32(1) int8(11)
push int32(10)

exit
------------
key1 val1
key2 val2
;;
------------
push int32(-2147483649)
dump
exit
------------
push float(3.40283e+38)
dump
exit
------------
push double(2.22507e-308)
dump
exit
-----------
push double(1.7977e+308)
dump
exit
-----------
push int8(127)
push int8(1)
add
exit
-----------
push int16(32;)
pu int(32))
exit
----------
pop
exit
----------
push int32(42)
assert int32(0)
exit
---------
push int32(42)
add
exit
---------
push int16(erfder)
exit
----------- */
