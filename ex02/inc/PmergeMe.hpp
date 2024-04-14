#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
# include <climits>
# include <vector>
# include <algorithm>
# include <iterator>
# include <exception>

class PmergeMe
{
	private:
		std::vector<std::pair<int, int> > _seq;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &object);
		~PmergeMe();
		PmergeMe &operator=(const PmergeMe &object);
		bool validateInput(char **input);
		class InvalidInputException : public std::exception
		{
			public:
				const char *what() const throw();
		};
};

#endif