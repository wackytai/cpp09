#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <list>
# include <ctime>
# include <vector>
# include <math.h>
# include <climits>
# include <numeric>
# include <iterator>
# include <iostream>
# include <exception>
# include <algorithm>

class PmergeMe
{
	private:
		std::vector<int>	_seq;
		std::list<int>		_lst;
		static int64_t		groups[];

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &object);
		~PmergeMe();
		PmergeMe			&operator=(const PmergeMe &object);
		bool 				validateInput(char **input);
		void 				mergeInsertion( void );
		void 				inPairComparison( void );
		void 				orderPairs( std::vector<std::pair<int, int> > pairs );
		static bool 		compare( const std::pair<int,int> &a, const std::pair<int,int> &b );
		void 				dividePairs( void );
		std::vector<int> 	merge( std::vector<int> &main, std::vector<int> &left );
		void				check_sorted(std::vector<int> final);
		void 				inPairComparisonLst( void );
		void 				orderPairsLst( std::list<std::pair<int, int> > pairs );
		static bool 		compareLst( const std::pair<int,int> &a, const std::pair<int,int> &b );
		void 				dividePairsLst( void );
		std::list<int> 		mergeLst( std::list<int> &main, std::list<int> &left );
		void				check_sortedLst(std::list<int> final);
		class InvalidInputException : public std::exception
		{
			public:
				const char *what() const throw();
		};
};

#endif
