#include "../inc/BitcoinExchange.hpp"

int	exchanger( std::string filename )
{
	BitcoinExchange	exchange ( filename );
	return 0;

}

int	main( int argc, char **argv )
{
	try
	{
		if (argc != 2)
			throw BitcoinExchange::CantOpenFileException();
		else
			exchanger( argv[1] );
	}
	catch(const BitcoinExchange::CantOpenFileException& e)
	{
		std::cerr << e.what() << '\n';
	}
	catch(const BitcoinExchange::BadFileException& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}
