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
	inPairComparison();
	return true;
}

void PmergeMe::inPairComparison( void )
{
	std::vector<int>::iterator it = _seq.begin();

	while (it != _seq.end())
	{
		if (it == _seq.end() - 1)
			break ;
		else if (*it > *(it + 1))
		{
			std::iter_swap(it, it + 1);
			it = _seq.begin();
		}
		else
			it += 2;
	}
	std::cout << "#1 Step: ";
	for (it = _seq.begin(); it != _seq.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	orderPairs();
}

void PmergeMe::orderPairs( void )
{
	std::vector<int>::iterator it = _seq.begin();

	while (it != _seq.end())
	{
		if (it == _seq.end() - 1)
			break ;
		else if (it + 3 < _seq.end() && *(it + 3) < *(it + 1))
		{
			std::iter_swap(it, it + 2);
			std::iter_swap(it + 1, it + 3);
			it = _seq.begin();
		}
		else
			it += 2;
	}
	std::cout << "#2 Step: ";
	for (it = _seq.begin(); it != _seq.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	dividePairs();
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
	it = main.begin();
	std::cout << "Main chain: ";
	for (it = main.begin(); it != main.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	it = left.begin();
	std::cout << "Left: ";
	for (it = left.begin(); it != left.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	_seq = merge(main, left);
}

std::vector<int> PmergeMe::merge( std::vector<int> &main, std::vector<int> &left )
{
	bool isOdd = left.size() % 2 != 0;
	std::vector<int>::iterator itM = main.begin();
	std::vector<int>::iterator itL = left.begin();

	while (itL != left.end() && itM != main.end())
	{
		if (*itL < *itM)
			if ((isOdd && itL < left.end() - 1) || !isOdd)
				itM = main.insert(itM, *itL++);
		itM++;
	}
	if (isOdd)
	{
		while (itL != left.end())
		{
			itM = main.begin();
			while (*itM < *itL)
				itM++;
			main.insert(itM, *itL++);
		}
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
