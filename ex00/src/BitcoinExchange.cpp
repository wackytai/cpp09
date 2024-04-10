#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange( BitcoinExchange const &object )
{
	*this = object;
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=( BitcoinExchange const &object )
{
	if (this != &object)
	{
		this->_exchangeRate = object._exchangeRate;
	}
	return (*this);
}

bool	BitcoinExchange::checkFile( std::string const &infile )
{
	std::ifstream	file(infile.c_str());

	if (infile.empty() || !file.is_open())
		throw BitcoinExchange::BadFileException();
	return true;
}

void	BitcoinExchange::setExchangeRate( std::string const &filename )
{

}

bool	BitcoinExchange::checkValue( float value ) const
{
	if (value < 0)
	{
		std::cout << "Error: value is not positive.";
		return false;
	}
	else if (value > 1000)
	{
		std::cout << "Error: too large a number.";
		return false;
	}
	else
		return true;
}

bool	BitcoinExchange::checkDate( std::string date ) const
{
	if (date.length() != 10 || date[4] != '-' || date[6] != '-')
		return false;

	std::istringstream iss_y(date.substr(0, 4));
	std::istringstream iss_m(date.substr(5, 2));
	std::istringstream iss_d(date.substr(7, 2));
	float y, m, d;

	iss_y >> y;
	iss_m >> m;
	iss_d >> d;

	if (y < 2009 || y > 2024 || m < 1 || m > 12 || d < 1 || d > 31
		|| ((m == 2 && (y == 2008 || y == 2012 || y == 2016 || y == 2020 || y == 2024) && d > 29)
		|| (m == 2 && d > 28)) || ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30))
		return false;
	return true;
}

std::map<std::string, float>	BitcoinExchange::getExchangeRate( void ) const
{
	return (this->_exchangeRate);
}

const char	*BitcoinExchange::BadFileException::what() const throw()
{
	return ("Error: could not open file.");
}

std::ostream	&operator<<(std::ostream &out, BitcoinExchange const &object)
{
	out << "date | value\n";
	for (std::map<std::string, float>::const_iterator it = object.getExchangeRate().begin(); it != object.getExchangeRate().end(); it++)
	{
		if (object.checkDate(it->first))
			out << "Error: bad input => " << it->first << std::endl;
		else if (!object.checkValue(it->second))
			out << std::endl;
		else
			out << it->first << " | " << it->second << std::endl;
	}
	return out;
}
