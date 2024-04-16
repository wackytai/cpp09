#include "../inc/PmergeMe.hpp"

int64_t	PmergeMe::groups[] =
{
	2u, 2u, 6u, 10u, 22u, 42u, 86u, 170u, 342u, 682u, 1366u,
    2730u, 5462u, 10922u, 21846u, 43690u, 87382u, 174762u, 349526u, 699050u,
    1398102u, 2796202u, 5592406u, 11184810u, 22369622u, 44739242u, 89478486u,
    178956970u, 357913942u, 715827882u, 1431655766u, 2863311530u, 5726623062u,
    11453246122u, 22906492246u, 45812984490u, 91625968982u, 183251937962u,
    366503875926u, 733007751850u, 1466015503702u, 2932031007402u, 5864062014806u,
    11728124029610u, 23456248059222u, 46912496118442u, 93824992236886u, 187649984473770u,
    375299968947542u, 750599937895082u, 1501199875790165u, 3002399751580331u,
    6004799503160661u, 12009599006321322u, 24019198012642644u, 48038396025285288u,
    96076792050570576u, 192153584101141152u, 384307168202282304u, 768614336404564608u,
    1537228672809129216u, 3074457345618258432u, 6148914691236516864u
};

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &object)
{
	*this = object;
}

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &object)
{
	if (this != &object)
	{
		_seq = object._seq;
		_lst = object._lst;
	}
	return *this;
}

bool PmergeMe::validateInput(char **input)
{
	int i = 0;
	int value;

	while (input[i])
	{
		try
		{
			value = std::atoi(input[i]);
		}
		catch (std::invalid_argument &e)
		{
			throw InvalidInputException();
		}
		catch (std::out_of_range &e)
		{
			throw InvalidInputException();
		}
		if (std::find(_seq.begin(), _seq.end(), value) != _seq.end())
			throw InvalidInputException();
		else if (value < 1)
			throw InvalidInputException();
		_seq.push_back(value);
		_lst.push_back(value);
		i++;
	}
	if (i < 2)
		throw InvalidInputException();
	std::cout << "Before: ";
	for (std::vector<int>::iterator it = _seq.begin(); it != _seq.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	mergeInsertion();
	return true;
}

void PmergeMe::mergeInsertion( void )
{
	std::vector<std::pair<int, int> > pairs;
	std::list<std::pair<int, int> > pairsL;
	clock_t start = clock();

	inPairComparison();
	for (std::vector<int>::iterator it = _seq.begin(); it < _seq.end(); it += 2)
	{
		if (it + 1 < _seq.end())
			pairs.push_back(std::make_pair(*it, *(it + 1)));
		else
			pairs.push_back(std::make_pair(*it, INT_MAX));
	}
	for (std::list<int>::iterator itL = _lst.begin(); std::next(itL) != _lst.end();)
	{
		if (std::next(itL) != _lst.end())
			pairsL.push_back(std::make_pair(*itL, *std::next(itL)));
		else
			pairsL.push_back(std::make_pair(*itL, INT_MAX));
		++itL;
		if (itL == _lst.end())
			break ;
		++itL;
	}
	orderPairs(pairs);
	orderPairsLst(pairsL);
	dividePairs();

	clock_t end = clock();
	double time = double(end - start) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process a range of " << _seq.size() << " elements with std::vector<int> : " << time << " us" << std::endl;
}

void PmergeMe::inPairComparison( void )
{
	bool isSwapped = true;

	while (isSwapped)
	{
		isSwapped = false;
		for (std::vector<int>::iterator it = _seq.begin(); it < _seq.end() - 1; it += 2)
        {
            if (*it > *(it + 1))
            {
                std::iter_swap(it, it + 1);
                isSwapped = true;
            }
        }
	}
}

void PmergeMe::orderPairs( std::vector<std::pair<int, int> > pairs )
{
	int size = pairs.size();

	if (size < 2)
		return;
	size /= 2;

	std::vector<std::pair<int, int> > left(pairs.begin(), pairs.begin() + size);
	std::vector<std::pair<int, int> > right(pairs.begin() + size, pairs.end());

	orderPairs(left);
	orderPairs(right);

	std::vector<std::pair<int, int> > temp;

	std::sort(left.begin(), left.end(), compare);
	std::sort(right.begin(), right.end(), compare);

	std::merge(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(temp), compare);
	
	std::vector<int> res;
	std::vector<std::pair<int, int> >::iterator it;
	for (it = temp.begin(); it < temp.end() - 1; it++)
	{
		res.push_back(it->first);
		res.push_back(it->second);
	}
	res.push_back(it->first);
	if ((temp.end() - 1)->second != INT_MAX)
		res.push_back(it->second);
	_seq = res;
}

bool PmergeMe::compare(const std::pair<int,int> &a, const std::pair<int,int> &b)
{
	if (a.second < b.second)
		return true;
	return false;
}

void PmergeMe::dividePairs( void )
{
	std::vector<int>::iterator it = _seq.begin();
	std::vector<int> main;
	std::vector<int> left;

	while (it != _seq.end())
	{
		if (it == _seq.begin())
		{
			main.push_back(*it);
			it++;
			continue;
		}
		else if (it < _seq.end())
		{
			main.push_back(*it);
			if (it + 1 < _seq.end())
				left.push_back(*(it + 1));
		}
		else
			break;
		it += 2;
	}
	std::cout << "Left: ";
	for (std::vector<int>::iterator it = left.begin(); it != left.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	_seq = merge(main, left);
	check_sorted(_seq);
}

std::vector<int> PmergeMe::merge( std::vector<int> &main, std::vector<int> &left )
{
	std::vector<int>::iterator f = left.end() - 1;
	std::vector<int>::iterator b = left.begin();
	std::vector<int>::iterator e;


	for (int i = 0; b <= f; i++)
	{
		e = (groups[i] <= std::distance(b, f)) ? b + groups[i] - 1 : f;
		for (int j = 0; j <= groups[i]; j++)
		{
			main.insert(std::upper_bound(main.begin(), main.end(), *e), *e);
			if (e == b)
				break ;
			e--;
		}
		std::advance(b, (groups[i]));
	}

	std::cout << "After: ";
	for (std::vector<int>::iterator it = main.begin(); it != main.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	return main;
}

void	PmergeMe::check_sorted(std::vector<int> final)
{
	std::vector<int>::iterator	begin = ++final.begin();
	std::vector<int>::iterator	end = final.end();

	for (; begin != end; begin++)
	{
		if (*begin < *(begin - 1))
		{
			std::cout << "NOT SORTED\n";
			return;
		}
	}
	std::cout << "SORTED\n";
}

void 				PmergeMe::inPairComparisonLst( void )
{
	bool isSwapped = true;

	while (isSwapped)
	{
		isSwapped = false;
		for (std::list<int>::iterator it = _lst.begin(); std::next(it) != _lst.end();)
        {
            if (*it > *std::next(it))
            {
                std::iter_swap(it, std::next(it));
                isSwapped = true;
            }
			++it;
			if (it == _lst.end())
				break ;
			++it;
        }
	}
}

void 				PmergeMe::orderPairsLst( std::list<std::pair<int, int> > pairs )
{

}

bool	PmergeMe::compareLst( const std::pair<int,int> &a, const std::pair<int,int> &b )
{

}

void	PmergeMe::dividePairsLst( void )
{

}

std::list<int>	PmergeMe::mergeLst( std::list<int> &main, std::list<int> &left )
{

}

void	PmergeMe::check_sortedLst(std::list<int> final)
{
	std::list<int>::iterator	curr = ++final.begin();
	std::list<int>::iterator	prev = final.begin();
	std::list<int>::iterator	end = final.end();

	for (; curr != end; curr++)
	{
		if (*curr < *prev)
		{
			std::cout << "NOT SORTED\n";
			return;
		}
	}
	std::cout << "SORTED\n";
}


const char *PmergeMe::InvalidInputException::what() const throw()
{
	return "Invalid input: not a positive sequence of unique integers separated by a single space each.";
}
