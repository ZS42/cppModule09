/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:17:57 by zsyyida           #+#    #+#             */
/*   Updated: 2023/12/25 02:29:41 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <stdexcept>
#include <cstdlib> // for atoi
#include <sys/time.h> // for timeval
#include <algorithm>
#include <iterator>

# define RED "\033[0;31m"
# define GREEN "\033[38:5:2m"
# define BLUE    "\033[34m"
# define YELLOW  "\033[33m"
# define RESET "\033[0m"

class PmergeMe
{
	std::list<int> _unsortedNbrList;
	std::vector<int> _unsortedNbrVector;
	std::vector<std::pair<int, int> > _myPairedVector;
	std::list<int> _sortedNbrList;
	std::vector<int> _sortedNbrVector;
	std::string _input;
	public:
		PmergeMe();
		PmergeMe(std::string input);
		PmergeMe(const PmergeMe &object);
		PmergeMe &operator=(const PmergeMe &object);
		~PmergeMe();
		void makeUnsortedVector(char **av, int ac);
		void makeUnsortedList(char **av, int ac);
		void mergeInsertVector();
		void pairList();
		void mergeInsertList();
		// must be static so can be used in std::sort without instance of class
		static bool myCompare(const std::pair<int, int> &p1, const std::pair<int, int> &p2);
		class BadInputException : public std::exception
		{
			public:
				virtual const char * what () const throw ();
		};
};
