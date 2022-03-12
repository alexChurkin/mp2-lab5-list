#include "pch.h"
#include "..\mp2-lab5-list\TPolynom.h"

TEST(TPolynom, CanCreateNewPolynom)
{
	ASSERT_NO_THROW(TPolynom t);
}

TEST(TPolynom, NewCreatedPolynomIs0)
{
	TPolynom t;
	ASSERT_EQ(t.ToStr(), "0");
}

TEST(TPolynom, CanCreatePolynomCopy)
{
	TPolynom t;
	ASSERT_NO_THROW(TPolynom t2(t));
}

TEST(TPolynom, CanAddMonomToPolynom)
{
	TPolynom t;
	ASSERT_NO_THROW(t.AddMonom(1, 1, 1, 1));
	std::cout << "\t     " << t << '\n';
}

TEST(TPolynom, CanAddPolynomToPolynom)
{
	TPolynom t1;
	t1.AddMonom(1, 1, 0, 0);
	t1.AddMonom(1, 0, 0, 0);

	TPolynom t2;
	t2.AddMonom(-1, 1, 0, 0);
	t2.AddMonom(-1, 0, 0, 0);

	std::cout << "\t     t1 = " << t1 << '\n';
	std::cout << "\t     t2 = " << t2 << '\n';

	TPolynom sum = t1 + t2;

	ASSERT_NO_THROW(sum);
	std::cout << "\t     " << sum << '\n';
}