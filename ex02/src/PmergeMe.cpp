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
	orderPairs();
}

void PmergeMe::orderPairs( void )
{
	bool isSwapped = true;

	while (isSwapped)
	{
		isSwapped = false;
		for (std::vector<int>::iterator it = _seq.begin(); it < _seq.end() - 3; it += 2)
        {
            if (it + 3 < _seq.end() && *(it + 3) < *(it + 1))
            {
                std::iter_swap(it, it + 2);
                std::iter_swap(it + 1, it + 3);
                isSwapped = true;
            }
        }
	}
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
	_seq = merge(main, left);
}

std::vector<int> PmergeMe::merge( std::vector<int> &main, std::vector<int> &left )
{
	for (std::vector<int>::iterator itL = left.begin(); itL != left.end(); ++itL)
    {
        std::vector<int>::iterator itM = std::upper_bound(main.begin(), main.end(), *itL);
        main.insert(itM, *itL);
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
