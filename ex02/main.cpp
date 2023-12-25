/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:15:44 by zsyyida           #+#    #+#             */
/*   Updated: 2023/12/25 16:01:02 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 3)
        throw PmergeMe::BadInputException();
    else
    {
        try
        {
            for (int i = 1; i < ac; i++)
            {
                if (!isdigit(*av[i]))
                    throw PmergeMe::BadInputException();
            }
            // Declare timeval variables outside the timing block
            PmergeMe A;
            struct timeval start, end;
            // Capture start time
            gettimeofday(&start, NULL);
            A.makeUnsortedVector(av, ac);
            A.mergeInsertVector();
            gettimeofday(&end, NULL);
            long long elapsedTimeVector = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
            std::cout << BLUE << "Time to process a range of " << ac -1 << " elements with std::vector : " << elapsedTimeVector << "us" <<std::endl;
            gettimeofday(&start, NULL);
            A.makeUnsortedList(av, ac);
            A.mergeInsertList();
            gettimeofday(&end, NULL);
            long long elapsedTimeList = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
            std::cout << GREEN << "Time to process a range of " << ac -1 << " elements with std::list : " << elapsedTimeList << "us" << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

// expected output
// $> ./PmergeMe 3 5 9 7 4
// Before: 3 5 9 7 4
// After: 3 4 5 7 9
// Time to process a range of 5 elements with std::[..] : 0.00031 us
// Time to process a range of 5 elements with std::[..] : 0.00014 us
// $> ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
// Before: 141 79 526 321 [...]
// After: 79 141 321 526 [...]
// Time to process a range of 3000 elements with std::[..] : 62.14389 us
// Time to process a range of 3000 elements with std::[..] : 69.27212 us
// $> ./PmergeMe "-1" "2"
// Error
// $> # For OSX USER:
// $> ./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '`
// [...]
// $>
