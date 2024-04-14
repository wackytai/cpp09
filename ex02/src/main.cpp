#include "../inc/PmergeMe.hpp"

int	main (int argc, char **argv)
{
	PmergeMe pm;

	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " < positive sequence of integers>" << std::endl;
		return 1;
	}
	try
	{
		pm.validateInput(++argv);
	}
	catch (PmergeMe::InvalidInputException &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
