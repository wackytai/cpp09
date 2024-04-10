#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <iostream>
# include <sstream>
# include <fstream>
# include <string>
# include <map>

class BitcoinExchange
{
	private:
		std::map<std::string, float> _exchangeRate;
	
	public:
		BitcoinExchange();
		BitcoinExchange( BitcoinExchange const &object );
		~BitcoinExchange();
		BitcoinExchange 				&operator=( BitcoinExchange const &object );
		bool							checkFile( std::string const &infile );
		void							setExchangeRate( std::string const &filename );
		bool							checkValue( float value ) const;
		bool							checkDate( std::string date ) const;
		std::map<std::string, float>	BitcoinExchange::getExchangeRate( void ) const;
		class BadFileException : public std::exception
		{
			public:
				const char *what( void ) const throw();
		};
};

std::ostream	&operator<<(std::ostream &out, BitcoinExchange const &object);

#endif