/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:15:31 by zsyyida           #+#    #+#             */
/*   Updated: 2023/12/22 00:18:19 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <deque>
#include <stdexcept>
#include <cstdlib> // for atoi

# define RED "\033[0;31m"
# define GREEN "\033[38:5:2m"
# define BLUE    "\033[34m"
# define YELLOW  "\033[33m"
# define RESET "\033[0m"

class RPN
{
	std::deque<int> _RPN_Database;
	std::string _input;
	public:
		RPN();
		RPN(std::string input);
		RPN(const RPN &object);
		RPN &operator=(const RPN &object);
		~RPN();
		bool checkValidInput(std::string input);
		void calculate(std::string inputFile);
		class BadInputException : public std::exception
		{
			public:
				virtual const char * what () const throw ();
		};
		class DivisionByZeroException: public std::exception
		{
			public:
				const char *what() const throw();
		};
};
#endif