/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:17:45 by zsyyida           #+#    #+#             */
/*   Updated: 2023/12/25 23:07:53 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(): _unsortedNbrList(), _unsortedNbrVector(), _input()
{
    // std::cout << "Default constructor called" << std::endl;
}

PmergeMe::PmergeMe(std::string input): _unsortedNbrList(), _unsortedNbrVector(), _input(input)
{
    // std::cout << "Parametric constructor called" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &object): _unsortedNbrList(), _unsortedNbrVector(), _input()
{
    this->_unsortedNbrList = object._unsortedNbrList;
    this->_unsortedNbrVector = object._unsortedNbrVector;
    *this = object;
    // std::cout << "Copy constructor called" << std::endl;
}
PmergeMe &PmergeMe::operator=(const PmergeMe &object)
{
    if (this != &object)
    {
        _unsortedNbrList.clear();
        _unsortedNbrVector.clear();
        this->_unsortedNbrList = object._unsortedNbrList;
        this->_unsortedNbrVector = object._unsortedNbrVector;
    }
    // std::cout << "Copy Assignment operator called" << std::endl;
    return (*this);
}

PmergeMe::~PmergeMe()
{
    // std::cout << "Destructor called" << std::endl;
}

void PmergeMe::makeUnsortedVector(char **av, int ac)
{
    try
    {
        for (int i = 1; i < ac; i++)
        {
            int a = atoi(av[i]);
            if (a < 0)
                throw PmergeMe::BadInputException();
            _unsortedNbrVector.push_back(a);
        }
        if (_unsortedNbrVector.size() < 2) 
            throw BadInputException();
        if (_unsortedNbrVector.size() > 4000)
            throw BadInputException();
        std::cout << YELLOW << "Before for vector: ";
        for (int i = 0; i < ac - 1; i++)
        {
            std::cout << " " << _unsortedNbrVector[i];
        }
        std::cout << "\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void PmergeMe::makeUnsortedList(char **av, int ac)
{
    try
    {
        std::cout << YELLOW << "Before for List: ";
        for (int i = 1; i < ac; i++)
        {
            int a = atoi(av[i]);
            if (a < 0)
                throw PmergeMe::BadInputException();
            _unsortedNbrList.push_back(a);
        }
        if (_unsortedNbrList.size() < 2) 
            throw BadInputException();
        if (_unsortedNbrList.size() > 4000)
            throw BadInputException();
        std::list<int>::iterator it;
        for (it = _unsortedNbrList.begin(); it != _unsortedNbrList.end(); ++it) 
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void PmergeMe::mergeInsertVector()
{
    // Create a vector of sorted pairs
    std::vector<std::pair<int, int> > _myPairedVector;
    for (size_t i = 0; i < _unsortedNbrVector.size() - 1; i+=2)
    {
        if (_unsortedNbrVector[i] < _unsortedNbrVector[i + 1])
            _myPairedVector.push_back(std::make_pair(_unsortedNbrVector[i], _unsortedNbrVector[i + 1]));
        else
            _myPairedVector.push_back(std::make_pair(_unsortedNbrVector[i + 1], _unsortedNbrVector[i]));
    }
    // sorting the pairs in ascending order based on second in pair .Using stable sort for handling duplicates
    std::stable_sort(_myPairedVector.begin(), _myPairedVector.end(), myCompare);
    int jacobsthalSequence[] = {3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731};
    std::vector<std::pair<int, int> >::iterator myPairedVectorIt;
    int pair_number = static_cast<int>(_myPairedVector.size());
    for (int i = 0; i < pair_number; i++)
    {
        // put in first pair and larger of subsequent pairs
        if (i == 0)
        {
            _sortedNbrVector.push_back(_myPairedVector[i].first);
            _sortedNbrVector.push_back(_myPairedVector[i].second);
        }
        else
            _sortedNbrVector.push_back(_myPairedVector[i].second);
    }
    int sortedIndex = 0;
	for (int j = 0; jacobsthalSequence[j] - 1 < pair_number; j++)
	{
		int index = jacobsthalSequence[j];
		int length = index + sortedIndex;
		for (int i = index - 1; i > sortedIndex; i--)
		{
			myPairedVectorIt = _myPairedVector.begin();
			_sortedNbrVector.insert(std::lower_bound(_sortedNbrVector.begin(),_sortedNbrVector.begin() + length, (myPairedVectorIt + i)->first), (myPairedVectorIt + i)->first);
		}
		sortedIndex = index - 1;
	}
    // sortedIndex++ makes it 1
	while (sortedIndex++ < pair_number - 1)
	{
		myPairedVectorIt = _myPairedVector.begin();
		_sortedNbrVector.insert(std::lower_bound(_sortedNbrVector.begin(), _sortedNbrVector.end(), (myPairedVectorIt + sortedIndex)->first), (myPairedVectorIt + sortedIndex)->first);
	}
	if (_myPairedVector.size() * 2 != _unsortedNbrVector.size())
        _sortedNbrVector.insert(std::lower_bound(_sortedNbrVector.begin(), _sortedNbrVector.end(), _unsortedNbrVector[_unsortedNbrVector.size() - 1]),_unsortedNbrVector[_unsortedNbrVector.size() - 1]);
    std::cout << BLUE << "After for vector: ";
    for (size_t i = 0; i < _sortedNbrVector.size(); i++)
    {
        std::cout << _sortedNbrVector[i] << " ";
    }
    std::cout << "\n";
}

bool PmergeMe::myCompare(const std::pair<int, int> &p1, const std::pair<int, int> &p2)
{
	return (p1.second < p2.second);
}


void PmergeMe::mergeInsertList()
{
    // Create a list of pairs
    std::list<std::pair<int, int> > myPairedList;
    // Populate the list with pairs using iterator
    std::list<int>::iterator it = _unsortedNbrList.begin();
    while (it != _unsortedNbrList.end())
    {
        int FirstElement = *it;
        ++it;
        if (it != _unsortedNbrList.end())
        {
            int SecondElement = *it;
            if (FirstElement < SecondElement)
                myPairedList.push_back(std::make_pair(FirstElement, SecondElement));
            else
                myPairedList.push_back(std::make_pair(SecondElement, FirstElement));
            ++it;
        }
    }
    // stable_sort doesnt work for list as sort itself handles equivqlent values
    myPairedList.sort(myCompare);
    std::list<std::pair<int,int> >::iterator myPairedListIt;
    for (myPairedListIt = myPairedList.begin(); myPairedListIt != myPairedList.end(); ++myPairedListIt)
    {
        // put in first pair and larger of subsequent pairs
        if (myPairedListIt == myPairedList.begin())
        {
            _sortedNbrList.push_back(myPairedListIt->first);
            _sortedNbrList.push_back(myPairedListIt->second);
        }
        else
            _sortedNbrList.push_back(myPairedListIt->second);
    }
    size_t jacobsthalSequence[] = {3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731};
    size_t sortedIndex = 0;
    for (size_t j = 0; jacobsthalSequence[j] - 1 < myPairedList.size(); j++)
    {
        size_t index = jacobsthalSequence[j];
        for (size_t i = index - 1; i > sortedIndex; i--)
        {
        // std::cout << "hello\n";
            // advance advances the iterator it3 by n element positions.
            // next does the same but doesn't move iterator. Instead returns a new one
            std::list<std::pair<int,int> >::iterator it3 = myPairedList.begin();
            std::advance(it3, i);
            // Find the position to insert the element
            std::list<int>::iterator insertPosition = std::lower_bound(_sortedNbrList.begin(), _sortedNbrList.end(), it3->first);
            // using insert the container is extended by inserting new elements before the element at the specified position.
            // lower_bound returns an iterator pointing to the first element in the range [first,last) which does not compare less than val.
            // takes forward iterators to the initial and final positions of a sorted sequence and value of the lower bound to search for in the range.
            _sortedNbrList.insert(insertPosition, it3->first);
            std::advance(it3, -i);
        }
        sortedIndex = index - 1;
    }
    // for when jacobthal is > pairedlists size
    while (sortedIndex++ < myPairedList.size() - 1)
    {
        std::list<std::pair<int,int> >::iterator it3 =  myPairedList.begin();
        std::advance(it3, sortedIndex);
        std::list<int>::iterator insertPosition = std::lower_bound(_sortedNbrList.begin(), _sortedNbrList.end(), it3->first);
        _sortedNbrList.insert(insertPosition, it3->first);
    }

    if (myPairedList.size() * 2 != _unsortedNbrList.size())
    {
        std::list<int>::iterator insertPosition = std::lower_bound(_sortedNbrList.begin(), _sortedNbrList.end(), _unsortedNbrList.back());
        _sortedNbrList.insert(insertPosition, _unsortedNbrList.back());
    }
    std::cout << GREEN << "After for list: ";
    for (std::list<int>::iterator it2 = _sortedNbrList.begin(); it2 != _sortedNbrList.end(); ++it2)
    {
        std::cout << *it2 << " ";
    }
    std::cout << "\n";
}

const char	*PmergeMe::BadInputException::what() const throw()
{
	return ("\033[0;31m Error");
}
