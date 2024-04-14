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
	std::vector<int> vec;
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
		if (std::find(vec.begin(), vec.end(), value) != vec.end())
			throw InvalidInputException();
		else if (value < 1)
			throw InvalidInputException();
		vec.push_back(value);
		i++;
	}
	std::cout << "Valid input." << std::endl;
	return true;
}

const char *PmergeMe::InvalidInputException::what() const throw()
{
	return "Invalid input: not a positive sequence of unique integers separated by a single space each.";
}
