/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:48:55 by zsyyida           #+#    #+#             */
/*   Updated: 2023/12/18 23:55:10 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(): _RPN_Database(), _input()
{
    // std::cout << "Default constructor called" << std::endl;
}

RPN::RPN(std:: string input): _RPN_Database(), _input(input)
{
    // std::cout << "Parametric constructor called" << std::endl;
}

RPN::RPN(const RPN &object): _RPN_Database(), _input()
{
    *this = object;
    // std::cout << "Copy constructor called" << std::endl;
}

RPN &RPN::operator=(const RPN &object)
{
    if (this != &object)
    {
        _RPN_Database.clear();
        this->_RPN_Database = object._RPN_Database;
    }
    // std::cout << "Copy Assignment operator called" << std::endl;
    return (*this);
}

RPN::~RPN()
{
    // std::cout << "Destructor called" << std::endl;
}

bool RPN::checkValidInput(std::string input)
{
    if (input.length() < 5)
        return(true);
    for(size_t i = 0; i < input.length(); i+=2)
    {
        if (!(std::isdigit(input[i])) && input[i] != '+'  && input[i] != '-' && input[i] != '*' && input[i] != '/')
            return(true);
    }
    for(size_t j = 1; j < input.length() - 1; j+=2)
    {
        if (input[j] != ' ')
            return(true);
    }
    int last = input[input.length() - 1];
    if (last != '+'  && last != '-'&& last != '*' && last != '/') 
        return(true);
    return(false);  
}

void RPN::calculate(std::string input)
{
    if (checkValidInput(input))
    {
        throw BadInputException();
    }
    for(int i = 0; i < (int)input.length(); i += 2)
    {
        if (std::isdigit(input[i]))
        {
            // _RPN_Database.push_back(std::atoi(&input[i]));
            _RPN_Database.push_back(input[i] - '0');
        }
        else
        {
            if (_RPN_Database.size() < 2)
                throw BadInputException();
            int second = _RPN_Database.back();
            _RPN_Database.pop_back();
            int first = _RPN_Database.back();
            _RPN_Database.pop_back();
            if (input[i] == '/' && second == 0)
                throw DivisionByZeroException();
            char c = input[i];
            switch(c)
            {
                case '+':
                {
                    _RPN_Database.push_back(first + second);
                    break;
                }
                case '-':
                {
                    _RPN_Database.push_back(first - second);
                    break;
                }
                case '*':
                {
                    _RPN_Database.push_back(first * second);
                    break;
                }
                case '/':
                {
                    _RPN_Database.push_back(first / second);
                    break;
                 }
            }
        }
    }
    if (_RPN_Database.size() != 1)
        throw BadInputException();
    int answer = _RPN_Database.back();
    _RPN_Database.pop_back();
    std::cout << RED << answer << RESET << std::endl;
}

const char	*RPN::BadInputException::what() const throw()
{
	return ("Error" );
}

const char	*RPN::DivisionByZeroException::what() const throw()
{
	return ("Error: Can't divide by zero" );
}