#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::cout << "input.csv:" << std::endl;
	setMap("./dbs/input.csv", _exchangeRate);
	std::cout << "no input" << std::endl;
	setMap( "", _bAmount);
}

BitcoinExchange::BitcoinExchange( std::string const &filename )
{
	std::cout << "input.csv:" << std::endl;
	setMap("./dbs/input.csv", _exchangeRate);
	std::cout << filename << std::endl;
	setMap("./dbs/" + filename, _bAmount);
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
		this->_bAmount = object._bAmount;
	}
	return (*this);
}

bool	BitcoinExchange::checkFile( std::string const &infile )
{
	std::ifstream	file(infile.c_str());

	if (infile.empty() || !file.is_open())
		return false;
	return true;
}

void	BitcoinExchange::setMap( std::string const &filename, std::map<std::string, std::string> &map )
{
	std::ifstream	file(filename.c_str());
	std::string 	line;
	std::string		key;
	std::string		value;

	if (!checkFile(filename))
		throw BadFileException();
	while (std::getline(file, line))
	{
		if (line == "date | value")
			continue;
		if (line.length() < 10)
		{
			key = line;
			value = "";
		}
		else if (line.substr(10, 3) != " | " || (!isdigit(line[13]) && line[13] != '-'))
		{
			key = line.substr(0, 10);
			value = "";
		}
		else
		{
			key = line.substr(0, 10);
			value = line.substr(11, line.length() - 11);
		}
		map[key] = value;
		std::cout << key << " => " << value << std::endl;
 
	}
}


bool	BitcoinExchange::checkValue( std::string value ) const
{
	(void)value;
	/* if (value[value.length() -1] == 'f')
	{
		int dot = 0;
		for (int i = 0; i < value.length() - 1; i++)
		{
			if (value[i] == '.')
				dot++;
			if ((!isdigit(value[i]) && value[i] != '.') || dot > 1)
			{
				std::cout << "Error: value is not a number.";
				return false;
			}
		}
	}
	for (int i = 0; i < value.length(); i++)
	{
		if (!isdigit(value[i]))
		{
			std::cout << "Error: value is not a number.";
			return false;
		}
		//see if it's in int range
	} */
	return true;
}

bool	BitcoinExchange::validateValue( float value ) const
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
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	std::istringstream iss_y(date.substr(0, 4));
	std::istringstream iss_m(date.substr(5, 2));
	std::istringstream iss_d(date.substr(8, 2));
	float y, m, d;

	iss_y >> y;
	iss_m >> m;
	iss_d >> d;

	if (y < 2009 || y > 2024 || m < 1 || m > 12 || d < 1 || d > 31
		|| ((m == 2 && (y == 2008 || y == 2012 || y == 2016 || y == 2020 || y == 2024) && d > 29)
		|| (m == 2 && d > 28)) || ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30))
		return false;
	//make a validateDate() function that returns the closest date (it should get lower, not higher)?
	return true;
}

std::map<std::string, std::string>	BitcoinExchange::getExchangeRate( void ) const
{
	return (this->_exchangeRate);
}

void	BitcoinExchange::getAmount( float value, float rate ) const
{
	std::cout << value * rate;
	return ;
}

const char	*BitcoinExchange::BadFileException::what() const throw()
{
	return ("Error: could not open file.");
}

std::ostream	&operator<<(std::ostream &out, BitcoinExchange const &object)
{
	(void)object;
	out << "date | value" << std::endl;
	/* //iterate the map for the .txt file received at start of program
	for (std::map<std::string, float>::const_iterator it = object.getExchangeRate().begin(); it != object.getExchangeRate().end(); it++)
	{
		if (object.checkDate(it->first))
			out << "Error: bad input => " << it->first << std::endl;
		else if (!object.validateValue(it->second))
			out << std::endl;
		else
		{
			out << it->first << " => " << it->second;
			object.getAmount(it->second, it->second);
			out << std::endl;
		}
	} */
	return out;
}
