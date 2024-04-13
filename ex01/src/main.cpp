#include "../inc/RPN.hpp"

void testCalculation( std::string expression );

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./ex01 \"<expression>\"" << std::endl;
		return 1;
	}
	testCalculation(argv[1]);
}

void testCalculation( std::string expression )
{
	RPN rpn;

	try
	{
		rpn.checkInput(expression);
		rpn.getResult();
	}
	catch (RPN::InvalidExpression &e)
	{
		std::cout << e.what() << std::endl;
	}
}
