#ifndef	RPN_HPP
# define RPN_HPP
# include <iostream>
# include <stack>
# include <limits>

class RPN
{
	private:
		std::stack<int> _stack;

	public:
		RPN();
		RPN( const RPN &object );
		~RPN();
		RPN			&operator=( const RPN &object );
		void		calculate( const char *str );
		int			multiply( int a, int b );
		int			divide( int a, int b );
		int			add( int a, int b );
		int			subtract( int a, int b );
		void		checkInput( const std::string &input );
		void		updateStack ( const char *str );
		class InvalidExpression : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};
};

#endif