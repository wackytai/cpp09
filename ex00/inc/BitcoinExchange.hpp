#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <iostream>
# include <iomanip>
# include <sstream>
# include <fstream>
# include <limits>
# include <cfloat>
# include <climits>
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
		bool								checkValue( std::string value ) const;
		bool								validateValue( std::string value ) const;
		bool								checkDate( std::string date ) const;
		std::string							getClosestDate( std::string date ) const;
		bool								getAmount( std::string str, std::string date ) const;
		std::map<std::string, std::string>	getExchangeRate( void ) const;
		std::map<std::string, std::string>	getBAmount( void ) const;
		void								printer( void );
		class CantOpenFileException : public std::exception
		{
			public:
				const char *what( void ) const throw();
		};
		class BadFileException : public std::exception
		{
			public:
				const char *what( void ) const throw();
		};
};

#endif
