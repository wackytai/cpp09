#include "../inc/PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &object)
{
	*this = object;
}

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &object)
{
	if (this != &object)
		_seq = object._seq;
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
	clock_t start = clock();

	inPairComparison();
	for (std::vector<int>::iterator it = _seq.begin(); it < _seq.end(); it += 2)
	{
		if (it + 1 < _seq.end())
			pairs.push_back(std::make_pair(*it, *(it + 1)));
		else
			pairs.push_back(std::make_pair(*it, INT_MAX));
	}
	orderPairs(pairs);
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
}

std::vector<int> PmergeMe::merge( std::vector<int> &main, std::vector<int> &left )
{
	std::vector<int> g;

	while (static_cast<size_t>(std::accumulate(g.begin(), g.end(), 0)) < left.size())
	{
		if (g.size() < 2)
			g.push_back(2);
		else
		{
			int next_value = static_cast<int>(pow(2, g.size() + 1)) - g.back();
           	g.push_back(next_value);
			//std::vector<int>::iterator it = g.end() - 1;
			//g.push_back(static_cast<int>(pow(2, g.size() + 1)) - *it);
		}
	}
	std::vector<int>::iterator itM = main.begin();
    std::vector<int>::iterator itG = g.begin();
    std::vector<int>::iterator it = left.begin();
    std::advance(it, *itG - 1);
    std::vector<int>::iterator it1 = left.begin();
	std::cout << "it: " << *it << " | it1: " << *it1 << " | itG: " << *itG << std::endl;

    while (it != left.end())
	{
	    while (it >= left.begin() && ((itG == g.begin()) || (it != it1)))
	    {
	        itM = std::upper_bound(main.begin(), main.end(), *it);
	        main.insert(itM, *it);
	        std::cout << "Pushed: " << *it << std::endl;
            it--;
	    }
	    if (itG != g.end())
			++itG;
	    if (it1 != left.end() && itG != g.end())
		{
			/* it = left.begin();
	        std::advance(it, std::distance(it, it1) + 1);
	        it1 = it - 1; */
			//std::advance(it, (std::accumulate(g.begin(), (itG + 1), 0) - 1));
			it1 += (std::accumulate(g.begin(), itG, 0) - 1);
			it = it1 + *itG;
			std::cout << "it: " << *it << " | it1: " << *it1 << " | itG: " << *itG << std::endl;
	    }
		if (itG == g.end() && it1 == it)
			break;
	}

	std::cout << "After: ";
	for (std::vector<int>::iterator it = main.begin(); it != main.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	return main;
}

const char *PmergeMe::InvalidInputException::what() const throw()
{
	return "Invalid input: not a positive sequence of unique integers separated by a single space each.";
}
