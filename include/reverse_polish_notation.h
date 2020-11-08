#pragma once
#include <string>
#include <stack>
#include <sstream>
#include <vector>
#include <cctype>

class ReversePolishNotation
{
	std::vector<std::string>		expr_;
	std::string						out_;

	template<class T>
	T pop_( std::stack<T> & st )
	{
		auto tmp = st.top();
		st.pop();
		return tmp;
	}
	const int getPriority_( const char s ) const
	{
		switch ( s )
		{
			case '(': return 0;
			case ')': return 1;
			case '+': return 2;
			case '-': return 3;
			case '*': return 4;
			case '/': return 4;
		}
		return -1;
	}
	const bool isDummy_( const char s )  const
	{
		switch ( s )
		{
			case ' ': return true;
		}
		return false;
	}
	const bool isDelimiter_( const char s ) const
	{
		switch ( s )
		{
			case '.': return true;
			case ',': return true;
		}
		return false;
	}

	const bool getRpnExpresion_( std::string expression )
	{
		std::stack<char>	operands;
		bool succes = true;
		for ( size_t i = 0; i < expression.length(); ++i )
		{
			auto ch = expression[i];
			if ( std::isdigit( ch ) ||
				expr_.empty() && ch == '-' )
			{
				auto start = i;
				while ( ++i < expression.length() )
				{
					if ( std::isdigit( expression[i] ) )
						continue;
					else if ( isDelimiter_( expression[i] ) )
					{
						expression[i] = '.';
						continue;
					} else
						break;
				}
				expr_.push_back( expression.substr( start, i - start ) );
				i--;
			} else if ( auto priority = getPriority_( ch ); priority >= 0 )
			{
				if ( ch == ')' )
				{
					while ( !operands.empty() && operands.top() != '(' )
						expr_.push_back( std::string( 1, pop_( operands )) );
					if ( !operands.empty() )
						operands.pop();

					continue;
				} else if ( ch != '(' && !operands.empty() &&
					getPriority_( operands.top() ) >= priority )
				{
					expr_.push_back( std::string( 1, pop_( operands ) ) );
				}

				operands.push( ch );
			} else if ( isDummy_( ch ) )
				continue;
			else
			{
				out_ += ch;
				succes = false;
			}
		}

		while ( succes && !operands.empty() )
			expr_.push_back( std::string( 1, pop_( operands ) ) );

		if ( !succes )
			out_ = "Некорректный ввод, строка содержит недопустимое выражение " + out_;

		return succes;
	}

	const bool calcFromExpretion_( double & ret )
	{
		std::stack<double> result;
		for ( auto &it : expr_ )
		{
			std::stringstream ss( it.data() );
			if ( double val = 0; ss >> val )
			{
				result.push( val );
			} else
			{
				if ( result.empty() )
					return false;
				auto right = pop_( result );
				if ( result.empty() )
					return false;
				auto left = pop_( result );
				auto ch = it.at( 0 );
				switch ( ch )
				{
					case '+': val = left + right;  break;
					case '-': val = left - right;  break;
					case '*': val = left * right;  break;
					case '/':
					{
						if ( right == 0 )
						{
							out_ = "Деление на ноль невозможно";
							return false;
						}
						val = left / right;
						break;
					}
				}
				result.push( val );
			}
		}
		if ( result.size() != 1 )
			return false;

		ret = pop_( result );

		return true;
	}

public:
	ReversePolishNotation() {};
	~ReversePolishNotation() {};

	bool calc( std::string expression, double & result )
	{
		expr_.clear();
		out_.clear();
		auto succes = getRpnExpresion_( std::move( expression ) );
		succes = succes && calcFromExpretion_( result );
		return succes;
	}

	const std::string getOut() const noexcept
	{
		return out_.empty() ? "Неккоректный ввод" : out_;
	}
};