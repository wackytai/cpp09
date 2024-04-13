#include "../inc/RPN.hpp"

RPN::RPN() {}

RPN::RPN( const RPN &object )
{
	*this = object;
}

RPN::~RPN() {}

RPN&	RPN::operator=( const RPN &object )
{
	if (this != &object)
	{
		_stack = object._stack;
	}
	return *this;
}

void	RPN::calculate( const char *str )
{
	int a, b;

	a = _stack.top();
	_stack.pop();
	b = _stack.top();
	_stack.pop();
	switch (str[0])
	{
		case '+':
			_stack.push(add(a, b));
			break ;
		case '-':
			_stack.push(subtract(a, b));
			break ;
		case '*':
			_stack.push(multiply(a, b));
			break ;
		case '/':
			_stack.push(divide(a, b));
			break ;
		default:
			break ;
	}
	std::cout << "Calculating: " << b << str[0] << a << std::endl;
	std::cout << "Result: " << _stack.top() << std::endl;
	updateStack(++str);
}

int	RPN::multiply( int a, int b )
{
	long int	res = b * a;

	if (res < std::numeric_limits<int>::min() || res > std::numeric_limits<int>::max())
		throw InvalidExpression();
	return b * a;
}

int	RPN::divide( int a, int b )
{
	if (a == 0)
		throw InvalidExpression();
	long int	res = b / a;

	if (res < std::numeric_limits<int>::min() || res > std::numeric_limits<int>::max())
		throw InvalidExpression();
	return b / a;
}

int	RPN::add( int a, int b )
{
	long int	res = b + a;

	if (res < std::numeric_limits<int>::min() || res > std::numeric_limits<int>::max())
		throw InvalidExpression();
	return b + a;
}

int	RPN::subtract( int a, int b )
{
	long int	res = b - a;

	if (res < std::numeric_limits<int>::min() || res > std::numeric_limits<int>::max())
		throw InvalidExpression();
	return b - a;
}


void	RPN::updateStack ( const char *str )
{
	for (size_t i = 0; str[i]; i++)
	{
		if (isdigit(str[0]))
		{
			_stack.push(str[0] - '0');
			std::cout << "Pushed: " << str[0] << std::endl;
			str++;
		}
		else
			break ;
	}
	if (_stack.size() != 1)
		calculate(str);
}

void	RPN::checkInput( const std::string &input )
{
	int nb = 0;
	int opt = 0;
	std::string str;

	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == ' ')
			continue ;
		else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
			opt++;
		else if (isdigit(input[i]))
			nb++;
		else
			throw InvalidExpression();
	}
	if (opt != (nb - 1))
		throw InvalidExpression();
	for (size_t i = 0; i < input.length(); i++)
		if (input[i] != ' ')
			str += input[i];
	std::cout << "Valid expression: " << str << std::endl;
	updateStack(str.c_str());
}

const char	*RPN::InvalidExpression::what() const throw()
{
	return "Error";
}
