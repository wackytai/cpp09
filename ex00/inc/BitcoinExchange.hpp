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
		std::map<std::string, std::string> _exchangeRate;
		std::map<std::string, std::string> _bAmount;
	
	public:
		BitcoinExchange();
		BitcoinExchange(std::string const &filename);
		BitcoinExchange( BitcoinExchange const &object );
		~BitcoinExchange();
		BitcoinExchange 					&operator=( BitcoinExchange const &object );
		bool								checkFile( std::string const &infile );
		void								setMap( std::string const &filename, std::map<std::string, std::string> &map );
		bool								validateValue( float value ) const;
		bool								checkDate( std::string date ) const;
		bool								checkValue( std::string value ) const;
		void								getAmount( float value, float rate) const;
		std::map<std::string, std::string>	getExchangeRate( void ) const;
		class BadFileException : public std::exception
		{
			public:
				const char *what( void ) const throw();
		};
};

std::ostream	&operator<<(std::ostream &out, BitcoinExchange const &object);

#endif