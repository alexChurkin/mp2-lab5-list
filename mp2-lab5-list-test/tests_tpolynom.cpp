#include "pch.h"
#include "..\mp2-lab5-list\TPolynom.h"

TEST(TPolynom, CanCreateNewPolynom)
{
	ASSERT_NO_THROW(TPolynom t);
}

TEST(TPolynom, NewCreatedPolynomIsZero)
{
	TPolynom t;
	ASSERT_EQ(t.ToStr(), "0");
}

TEST(TPolynom, CanCreateCopiedPolynom)
{
	TPolynom t;
	ASSERT_NO_THROW(TPolynom t2(t));
}

TEST(TPolynom, CanAssignPolynoms)
{
	TPolynom t1;
	t1.AddMonom(2, 0, 0, 0);

	TPolynom t2;

	ASSERT_NO_THROW(t2 = t1);
	std::cout << "\t     t1 = " << t1 << '\n';
	std::cout << "\t     t2 = " << t2 << '\n';
	EXPECT_EQ(t1.ToStr(), t2.ToStr());
}

TEST(TPolynom, CanAssignPolynomToItself)
{
	TPolynom t;
	t.AddMonom(2, 0, 0, 0);

	ASSERT_NO_THROW(t = t);
	std::cout << "\t     t = " << t << '\n';
	EXPECT_EQ(t.ToStr(), t.ToStr());
}

TEST(TPolynom, CanAddMonomToPolynom)
{
	TPolynom t;
	ASSERT_NO_THROW(t.AddMonom(1, 1, 1, 1));
	std::cout << "\t     t = " << t << '\n';
}

TEST(TPolynom, CanAddPolynomToPolynom_1)
{
	TPolynom t1;
	t1.AddMonom(1, 1, 0, 0);
	t1.AddMonom(1, 0, 0, 0);

	TPolynom t2;
	t2.AddMonom(-1, 1, 0, 0);
	t2.AddMonom(-1, 0, 0, 0);

	std::cout << "\t     t1 = " << t1 << '\n';
	std::cout << "\t     t2 = " << t2 << '\n';

	TPolynom sum;	
	ASSERT_NO_THROW(sum = t1 + t2);

	std::cout << "\t     sum = " << sum << '\n';
}

TEST(TPolynom, CanAddPolynomToPolynom_2)
{
	TPolynom t1;
	t1.AddMonom(1, 1, 0, 0);
	t1.AddMonom(1, 0, 0, 0);

	TPolynom t2;
	t2.AddMonom(-1, 1, 0, 0);

	std::cout << "\t     t1 = " << t1 << '\n';
	std::cout << "\t     t2 = " << t2 << '\n';

	TPolynom sum;
	ASSERT_NO_THROW(sum = t1 + t2);

	std::cout << "\t     sum = " << sum << '\n';
}

TEST(TPolynom, CanAddPolynomToPolynom_3)
{
	TPolynom t1;
	t1.AddMonom(1, 1, 0, 0);
	t1.AddMonom(1, 0, 0, 0);

	TPolynom t2;
	t2.AddMonom(-1, 0, 0, 0);

	std::cout << "\t     t1 = " << t1 << '\n';
	std::cout << "\t     t2 = " << t2 << '\n';

	TPolynom sum;
	ASSERT_NO_THROW(sum = t1 + t2);

	std::cout << "\t     sum = " << sum << '\n';
}

TEST(TPolynom, CanAddPolynomToPolynom_4)
{
	TPolynom t1;
	t1.AddMonom(1, 0, 1, 1);
	t1.AddMonom(2, 1, 0, 1);
	t1.AddMonom(3, 1, 1, 1);

	TPolynom t2;
	t2.AddMonom(1, 0, 1, 1);
	t2.AddMonom(-2, 1, 0, 1);
	t2.AddMonom(3, 1, 1, 1);

	std::cout << "\t     t1 = " << t1 << '\n';
	std::cout << "\t     t2 = " << t2 << '\n';

	TPolynom sum;
	ASSERT_NO_THROW(sum = t1 + t2);

	std::cout << "\t     sum = " << sum << '\n';
}

TEST(TPolynom, CanAddPolynomToPolynom_5)
{
	TPolynom t1;
	t1.AddMonom(1, 2, 2, 2);
	t1.AddMonom(-4, 2, 2, 1);
	t1.AddMonom(5, 2, 1, 1);
	t1.AddMonom(-1, 1, 1, 0);
	t1.AddMonom(1, 0, 0, 1);

	TPolynom t2;
	t2.AddMonom(1, 0, 1, 1);
	t2.AddMonom(-2, 1, 0, 1);
	t2.AddMonom(3, 1, 1, 1);

	std::cout << "\t     t1 = " << t1 << '\n';
	std::cout << "\t     t2 = " << t2 << '\n';

	TPolynom sum;
	ASSERT_NO_THROW(sum = t1 + t2);

	std::cout << "\t     sum = " << sum << '\n';
}

TEST(TPolynom, CanSubstractPolynomFromPolynom)
{
	TPolynom t1;
	t1.AddMonom(1, 0, 1, 1);
	t1.AddMonom(2, 1, 0, 1);
	t1.AddMonom(3, 1, 1, 1);

	TPolynom t2;
	t2.AddMonom(1, 0, 1, 1);
	t2.AddMonom(-2, 1, 0, 1);
	t2.AddMonom(3, 1, 1, 1);

	std::cout << "\t     t1 = " << t1 << '\n';
	std::cout << "\t     t2 = " << t2 << '\n';

	TPolynom result;
	ASSERT_NO_THROW(result = t1 - t2);

	std::cout << "\t     result = " << result << '\n';
}

TEST(TPolynom, CanMultiplyPolynomByZeroDouble)
{
	TPolynom t;
	t.AddMonom(1, 0, 1, 1);
	t.AddMonom(2, 1, 0, 1);
	t.AddMonom(3, 1, 1, 1);

	TPolynom result;
	ASSERT_NO_THROW(result = 0 * t);

	std::cout << "\t     t = " << t << '\n';
	std::cout << "\t     result = t * 0 = " << result << '\n';
}

TEST(TPolynom, CanMultiplyPolynomByDouble)
{
	TPolynom t;
	t.AddMonom(1, 0, 1, 1);
	t.AddMonom(2, 1, 0, 1);
	t.AddMonom(3, 1, 1, 1);

	TPolynom result;
	ASSERT_NO_THROW(result = -10 * t);

	std::cout << "\t     t = " << t << '\n';
	std::cout << "\t     result = (-10) * t = " << result << '\n';
}

TEST(TPolynom, CanMultiplyPolynomByMonom)
{
	TPolynom t;
	t.AddMonom(1, 0, 1, 0);

	TPolynom result;

	TMonom m(1, 1, 0, 1);

	ASSERT_NO_THROW(result = t * m);

	std::cout << "\t     t = " << t << '\n';
	std::cout << "\t     result = " << result << '\n';
}

TEST(TPolynom, CanMultiplyPolynomByPolynom)
{
	TPolynom t1;
	t1.AddMonom(1, 1, 0, 0);

	TPolynom t2;
	t2.AddMonom(2, 0, 1, 1);
	t2.AddMonom(0.5, 0, 0, 1);

	TPolynom result;

	TMonom m(1, 1, 0, 1);

	ASSERT_NO_THROW(result = t1 * t2);

	std::cout << "\t     t1 = " << t1 << '\n';
	std::cout << "\t     t2 = " << t2 << '\n';
	std::cout << "\t     result = " << result << '\n';
}