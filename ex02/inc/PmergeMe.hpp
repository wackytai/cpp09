#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
# include <climits>
# include <ctime>
# include <math.h>
# include <numeric>
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
		void mergeInsertion( void );
		void inPairComparison( void );
		void orderPairs( std::vector<std::pair<int, int> > pairs );
		static bool compare( const std::pair<int,int> &a, const std::pair<int,int> &b );
		void dividePairs( void );
		std::vector<int> merge( std::vector<int> &main, std::vector<int> &left );
		class InvalidInputException : public std::exception
		{
			public:
				const char *what() const throw();
		};
};

#endif