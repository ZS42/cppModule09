/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:12:11 by zsyyida           #+#    #+#             */
/*   Updated: 2023/12/16 23:30:46 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange():_inputFile(), _BitcoinValueDatabase(), _BitcoinRateDatabase()
{
    std::cout << "Default constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(std:: string inputFile):_inputFile(inputFile), _BitcoinValueDatabase(), _BitcoinRateDatabase()
{
    std::cout << "Parametric constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &object):_inputFile(), _BitcoinValueDatabase(), _BitcoinRateDatabase()
{
    *this = object;
    std::cout << "Copy constructor called" << std::endl;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &object)
{
    if (this != &object)
    {
        _BitcoinValueDatabase.clear();
        _BitcoinRateDatabase.clear();
        this->_inputFile = object._inputFile;
        this->_BitcoinValueDatabase = object._BitcoinValueDatabase;
        this->_BitcoinRateDatabase = object._BitcoinRateDatabase;
    }
    std::cout << "Copy Assignment operator called" << std::endl;
    return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << "Destructor called" << std::endl;
}

bool   BitcoinExchange::check_date(std::string date)
{
    std::istringstream	iss(date);
    std::string token;
    int year, month, day;
    
    std::getline(iss,  token, '-');
    year = atof(token.c_str());
    // if (year > 2022 || year < 2009)
    //     return (1);
    std::getline(iss,  token, '-');
    month = atof(token.c_str());
    if (month > 12 || month < 1)
        return (1);
    std::getline(iss,  token, '-');
    day = atof(token.c_str());
    if (day > 31 || day < 1)
        return (1);
    if ((month == 4 || month == 6 || month == 9 || month == 11)  && day > 30)
        return (1);
    if (month == 2 && !(year % 4) && day > 28)
    {
        if (!(year % 400) && (year % 100))
            return (1);
    }
    if ((year == 2022 && month > 3) || (year == 2022 && month == 3 && day > 29) ||
        (year == 2009 && month == 1 && day < 2) || (year > 2022 || year < 2009))
        return (1);
    if (date.empty())
        return (1);
    return (0);
} 

void   BitcoinExchange::makeDatabase(std::string inputFile)
{
    std::string filename = inputFile;
    std::string line;
    std::string date;
    std::string bitcoin_value;
    std::map<std::string, float>::iterator it;

    
    std::ifstream	ifs;
    ifs.open(filename.c_str());
    if (!ifs.is_open())
        throw CouldNotOpenFileException();
    while (std::getline(ifs, line))
    {
        if (line.empty() || line == "date | value")
            continue ;
        std::istringstream	iss(line);
        //if input is string getline can split with a delimiter(third parameter) into the second parameter
        if (std::getline(iss, date , '|') && std::getline(iss, bitcoin_value , '\n'))
        {
            try
            {
                if (check_date(date) == 1)
                {
                    std::cerr << "Error: bad input =>" << date <<std::endl;
                    continue ;
                }
                // why does i need to be 1 and not 0??
                    
                //bc atof requires pointer to string use c_str
                float value = atof(bitcoin_value.c_str());
                if (value < 0)
                    throw (NotPositiveNumberException());
                if (value > 1000)
                    throw (TooLargeNumberException());
                _BitcoinValueDatabase[date] = value;
                // find Searches the container for an element with a key equivalent to k and returns an iterator to it 
                // if found, otherwise it returns an iterator to map::end.
                it = _BitcoinRateDatabase.find(date);
                // in case date is not in database we want to return the closest lower date
                // lowerbound Returns an iterator pointing to the first element in the container whose key is not 
                // considered to go before k (i.e., either it is equivalent or goes after).
                if (it ==_BitcoinRateDatabase.end())
                {
                    // check if lower_bound is the beginning bc can't go less than that
                    if( _BitcoinRateDatabase.lower_bound(date) == _BitcoinRateDatabase.begin())
                        std::cerr << "Error: bad input =>" << date <<std::endl;
                    else
                        // go one less than lower_bound
                        it = --_BitcoinRateDatabase.lower_bound(date);
                }
                std::cout << date << " => " << value << " = " << (value * (it->second)) << std::endl;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else
            std::cerr << "Error: bad input =>" << date <<std::endl;
    }
    ifs.close();
}

void   BitcoinExchange::makeDatabase()
{
    std::string filename = "data.csv";
    std::string line;
    std::string date;
    std::string rate;
    
    std::ifstream	ifs;
    ifs.open(filename.c_str());
    if (!ifs.is_open())
        throw CouldNotOpenFileException();
    while (std::getline(ifs, line))
    {
        if (line.empty() || line == "date,exchange_rate")
            continue ;
        std::istringstream	iss(line);
        //if input is string getline can split with a delimiter(third parameter) into the second parameter
        if (std::getline(iss, date , ',') && std::getline(iss, rate , '\n'))
        {
            try
            {
               //bc atof requires pointer to string use c_str
               float exchange_rate = atof(rate.c_str());
               _BitcoinRateDatabase[date] = exchange_rate;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }
    ifs.close();
}

const char	*BitcoinExchange::CouldNotOpenFileException::what() const throw()
{
	return ("Error: could not open file.");
}

const char	*BitcoinExchange::NotPositiveNumberException::what() const throw()
{
	return ("Error: not a positive number.");
}

const char	*BitcoinExchange::BadInputException::what() const throw()
{
	return ("Error: bad input =>" );
}

const char	*BitcoinExchange::TooLargeNumberException::what() const throw()
{
	return ("Error: too large a number.");
}

const char	*BitcoinExchange::OutOfRangeException::what() const throw()
{
	return ("Error: Value out of range.");
}

const char	*BitcoinExchange::NotNumberException::what() const throw()
{
	return ("Error: value not a number.");
}