#include "reverse_polish_notation.h"
#include <gtest/gtest.h>
 
class CalculatorTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		rpn = std::make_unique<ReversePolishNotation>();
		result = 0.;
	}
	std::unique_ptr<ReversePolishNotation> rpn;
	double result;
	static constexpr auto ACCURACY = 0.5;
};

TEST_F( CalculatorTest, TestFromTask )
{
	ASSERT_TRUE( rpn->calc( "-1 + 5 - 3", result ) );
	ASSERT_NEAR( 1, result, ACCURACY );
	
	ASSERT_TRUE( rpn->calc( "-10 + (8 * 2.5) - (3 / 1,5)", result ) );
	ASSERT_NEAR( 8, result, ACCURACY );

	ASSERT_TRUE( rpn->calc( "1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)", result ) );
	ASSERT_NEAR( 11, result, ACCURACY );

	ASSERT_FALSE( rpn->calc( "1.1 + 2.1 + abc", result ) );
}

TEST_F( CalculatorTest, TestSpace )
{
	ASSERT_TRUE( rpn->calc( "                                    -1 +                           80", result ) );
	ASSERT_NEAR( 79, result, ACCURACY );

	ASSERT_TRUE( rpn->calc( "      -8                                   +                           80 + 1.5 - 2.5", result ) );
	ASSERT_NEAR( 71, result, ACCURACY );

	ASSERT_TRUE( rpn->calc( "(      -200 + 20000    ) - (    6000 + 100000    )", result ) );
	ASSERT_NEAR( -86200, result, ACCURACY );

}

TEST_F( CalculatorTest, TestDelimeter )
{
	ASSERT_TRUE( rpn->calc( "12,4 - 12.4 + 10.3 - 10,3", result ) );
	ASSERT_NEAR( 0, result, ACCURACY );

	ASSERT_TRUE( rpn->calc( "1 + 2,5 - 1.5 + 15.3 - 12,3", result ) );
	ASSERT_NEAR( 5, result, ACCURACY );

	ASSERT_TRUE( rpn->calc( " -3 / 1,5 * 1.5 / 12", result ) );
	ASSERT_NEAR( -0.25, result, ACCURACY );
}

TEST_F( CalculatorTest, TestBracket )
{
	ASSERT_TRUE( rpn->calc( " ( -8 ) + ( 8 ) ", result ) );
	ASSERT_NEAR( 0, result, ACCURACY );

	ASSERT_TRUE( rpn->calc( " ( (((((((((((((((-8 ))))))))))))))) ) + ( 8 ) ", result ) );
	ASSERT_NEAR( 0, result, ACCURACY );

	ASSERT_TRUE( rpn->calc( " ( (((((((((((((((-5 + 3 ) - 20) + 12) -12) *3) /2) *100) -111 + 12) + 201.5) - 211.1) + 10) -1123) + 200000) / 2) + 23) -0)", result ) );
	ASSERT_NEAR( 97762.2, result, ACCURACY );
}

TEST_F( CalculatorTest, DivZero )
{
	ASSERT_FALSE( rpn->calc( " ( -8 ) + ( 8 ) * 10 / 0 ", result ) );

	ASSERT_FALSE( rpn->calc( " 0 / 0 ", result ) );

	ASSERT_FALSE( rpn->calc( " ( (((((((((((((((-5 + 3 ) - 20) + 12) -12) *3) /2) *100) -111 + 12) + 201.5) - 211.1) + 10) -1123) + 200000) / 2) + 23) -0) / 0", result ) );
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
