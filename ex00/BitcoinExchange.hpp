/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:12:17 by zsyyida           #+#    #+#             */
/*   Updated: 2023/12/14 18:31:28 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream> //for ifstream
#include<sstream> // for sstream
#include <cstring>
#include<cstdlib> //for atof

# define RED "\033[0;31m"
# define GREEN "\033[38:5:2m"
# define BLUE    "\033[34m"
# define YELLOW  "\033[33m"
# define RESET "\033[0m"

class BitcoinExchange 
{
	std::string _inputFile;
	std::map<std::string, float> _BitcoinValueDatabase;
	std::map<std::string, float> _BitcoinRateDatabase;
	public:
		BitcoinExchange();
		BitcoinExchange(std:: string inputFile);
		BitcoinExchange(const BitcoinExchange &object);
		BitcoinExchange &operator=(const BitcoinExchange &object);
		~BitcoinExchange();
		void makeDatabase();
		void makeDatabase(std::string inputFile);
		bool   check_date(std::string date);
		// struct BitcoinRateDatabaseHash
		// {
		//     size_t operator()(const  BitcoinExchange& object)
		//     // {
		//     //     return hash<:;string()(key.date);
		//     // }
		// }
		class CouldNotOpenFileException : public std::exception
		{
			public:
				virtual const char * what () const throw ();
		};
		class BadInputException : public std::exception
		{
			public:
				virtual const char * what () const throw ();
		};
		class TooLargeNumberException : public std::exception
		{
			public:
				virtual const char * what () const throw ();
		};
		class NotPositiveNumberException : public std::exception
		{
			public:
				virtual const char * what () const throw ();
		};
		class OutOfRangeException : public std::exception
		{
			public:
				virtual const char * what () const throw ();
		};
		class NotNumberException : public std::exception
		{
			public:
				virtual const char * what () const throw ();
		};
};

#endif