#include "../inc/BitcoinExchange.hpp"

int	exchanger( std::string filename )
{
	BitcoinExchange	exchange;

	if (!exchange.checkFile(filename))
		throw BitcoinExchange::BadFileException();
	exchange.setExchangeRate(filename);
	return 0;

}

int	main( int argc, char **argv )
{
	try
	{
		if (argc != 2)
			exchanger( "" );
		else
			exchanger( argv[1] );
	}
	catch(const BitcoinExchange::BadFileException& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}
