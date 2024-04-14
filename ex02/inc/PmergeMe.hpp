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
		std::vector<int> _seq;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &object);
		~PmergeMe();
		PmergeMe &operator=(const PmergeMe &object);
		bool validateInput(char **input);
		void inPairComparison( void );
		void orderPairs( void );
		void dividePairs( void );
		std::vector<int> merge( std::vector<int> &main, std::vector<int> &left );
		class InvalidInputException : public std::exception
		{
			public:
				const char *what() const throw();
		};
};

#endif