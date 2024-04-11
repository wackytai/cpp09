#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <iostream>
# include <sstream>
# include <fstream>
# include <limits>
# include <string>
# include <map>

class BitcoinExchange
{
	private:
		std::map<std::string, float> _exchangeRate;
		std::map<std::string, float> _bAmount;
	
	public:
		BitcoinExchange();
		BitcoinExchange( BitcoinExchange const &object );
		~BitcoinExchange();
		BitcoinExchange 				&operator=( BitcoinExchange const &object );
		bool							checkFile( std::string const &infile );
		void							setExchangeRate( std::string const &filename );
		void							setBitcoinAmount( std::string const &filename );
		bool							validateValue( float value ) const;
		bool							checkDate( std::string date ) const;
		bool							checkValue( std::string value ) const;
		void							getAmount( float value, float rate) const;
		std::map<std::string, float>	BitcoinExchange::getExchangeRate( void ) const;
		class BadFileException : public std::exception
		{
			public:
				const char *what( void ) const throw();
		};
};

std::ostream	&operator<<(std::ostream &out, BitcoinExchange const &object);

#endif