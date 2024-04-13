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
	std::istringstream iss(value);
	float f;

	if (!(iss >> f))
	{
		int dot = 0;
		for (int i = 0; i < value.length(); i++)
		{
			if (i == 0 && value[i] == '-')
				continue;
			if (value[i] == '.')
			{
				dot++;
				continue;
			}
			if (i == value.length() - 1 && value[i] == 'f')
			continue;
			if (!isdigit(value[i]) || dot > 1)
			{
				std::cout << "Error: value is not a number.";
				return false;
			}
		}
 		std::cout << "Error: number out of range.";
		return false;
	}
	return true;
}

bool	BitcoinExchange::validateValue( std::string value ) const
{
	std::istringstream iss(value);
	float val;

	if (!(iss >> val))
		val = 1001;
	if (val < 0)
	{
		std::cout << "Error: value is not positive.";
		return false;
	}
	else if (val > 1000)
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
	return true;
}

std::string	BitcoinExchange::getClosestDate( std::string date ) const
{
	std::map<std::string, std::string>::const_iterator it = _exchangeRate.find(date);
	if (it != _exchangeRate.end())
		return date;
	else
	{
		for (it = _exchangeRate.begin(); it != _exchangeRate.end(); it++)
		{
			if (it->first > date)
			{
				it--;
				return it->first;
			}
		}
		it--;
		return it->first;
	}
}

std::map<std::string, std::string>	BitcoinExchange::getExchangeRate( void ) const
{
	return (this->_exchangeRate);
}

std::map<std::string, std::string>	BitcoinExchange::getBAmount( void ) const
{
	return (this->_bAmount);
}

void	BitcoinExchange::getAmount( std::string date ) const
{
	std::map<std::string, std::string>::const_iterator it_1 = _exchangeRate.find(date);
	std::map<std::string, std::string>::const_iterator it_2 = _bAmount.find(date);
	std::istringstream issR(it_1->second);
	std::istringstream issV(it_2->second);
	float rate;
	float value;

	issR >> rate;
	issV >> value;
	std::cout << it_2->second << " * " << it_1->second << value * rate;
	return ;
}

const char	*BitcoinExchange::BadFileException::what() const throw()
{
	return ("Error: could not open file.");
}

std::ostream	&operator<<(std::ostream &out, BitcoinExchange const &object)
{
	out << "date | value" << std::endl;
	for (std::map<std::string, std::string>::const_iterator it_1 = object.getBAmount().begin(); it_1 != object.getBAmount().end(); it_1++)
	{
		if (object.checkDate(it_1->first))
			out << "Error: bad input => " << it_1->first << std::endl;
		else if (!object.checkValue(it_1->second) || !object.validateValue(it_1->second))
			out << std::endl;
		else
		{
			out << object.getClosestDate(it_1->first) << " => ";
			object.getAmount(object.getClosestDate(it_1->first));
			out << std::endl;
		}
	}
	return out;
}
