
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <locale.h>
#include <iomanip>

//////////////////////////////////////////////////////////////////////////
#include "reverse_polish_notation.h"

int main()
{
	char *locale = setlocale( LC_ALL, "" );
	auto rpn = std::make_unique<ReversePolishNotation>();
	std::string input;
	while ( true )
	{
		std::cout << "Введите выражение:" << std::endl;
		std::getline( std::cin, input );
		auto result = 0.;
		auto succes = rpn->calc( input, result );
		if ( !succes )
			std::cout << rpn->getOut() << std::endl;
		else
			std::cout << "Результат выражения: " << std::fixed << std::setprecision( 2 ) << result << std::endl;

		std::cout << std::endl;
	}
}