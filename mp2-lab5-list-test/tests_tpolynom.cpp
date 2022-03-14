#include "pch.h"
#include "..\mp2-lab5-list\TPolynom.h"

TEST(TPolynom, CanCreateNewPolynom)
{
	ASSERT_NO_THROW(TPolynom t);
}

TEST(TPolynom, CanCreatePolynomFromString)
{
	TPolynom t("2xyz+0.5xz");

	TPolynom correct;
	correct.AddMonom(2, 1, 1, 1);
	correct.AddMonom(0.5, 1, 0, 1);

	EXPECT_EQ(t, correct);
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
	std::cout << "\t     t2 = t1 = " << t2 << '\n';
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

	std::cout << "\t     t1 + t2 = " << sum << '\n';

	TPolynom correct;

	EXPECT_EQ(sum, correct);
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

	std::cout << "\t     t1 + t2 = " << sum << '\n';

	TPolynom correct;
	correct.AddMonom(1, 0, 0, 0);

	EXPECT_EQ(sum, correct);
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

	std::cout << "\t     t1 + t2 = " << sum << '\n';

	TPolynom correct;
	correct.AddMonom(1, 1, 0, 0);

	EXPECT_EQ(sum, correct);
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

	std::cout << "\t     t1 + t2 = " << sum << '\n';

	TPolynom correct;
	correct.AddMonom(6, 1, 1, 1);
	correct.AddMonom(2, 0, 1, 1);

	EXPECT_EQ(sum, correct);
}

TEST(TPolynom, CanAddPolynomToPolynom_5)
{
	TPolynom t1;
	t1.AddMonom(1, 2, 2, 2);
	t1.AddMonom(3, 0, 0, 2);

	TPolynom t2;
	t2.AddMonom(1, 2, 2, 1);
	t2.AddMonom(-2, 0, 0, 2);
	t2.AddMonom(1, 0, 0, 1);

	std::cout << "\t     t1 = " << t1 << '\n';
	std::cout << "\t     t2 = " << t2 << '\n';

	TPolynom sum;
	ASSERT_NO_THROW(sum = t1 + t2);

	std::cout << "\t     t1 + t2 = " << sum << '\n';

	TPolynom correct;
	correct.AddMonom(1, 2, 2, 2);
	correct.AddMonom(1, 2, 2, 1);
	correct.AddMonom(1, 0, 0, 2);
	correct.AddMonom(1, 0, 0, 1);

	EXPECT_EQ(sum, correct);
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

	TPolynom difference;
	ASSERT_NO_THROW(difference = t1 - t2);

	std::cout << "\t     t1 - t2 = " << difference << '\n';

	TPolynom correct;
	correct.AddMonom(4, 1, 0, 1);

	EXPECT_EQ(difference, correct);
}

TEST(TPolynom, CanMultiplyPolynomByZeroDouble)
{
	TPolynom t;
	t.AddMonom(1, 0, 1, 1);
	t.AddMonom(2, 1, 0, 1);
	t.AddMonom(3, 1, 1, 1);

	std::cout << "\t     t = " << t << '\n';

	TPolynom result;
	ASSERT_NO_THROW(result = 0 * t);

	std::cout << "\t     0 * t = " << result << '\n';

	EXPECT_EQ(result, TPolynom());
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
	std::cout << "\t     (-10) * t = " << result << '\n';

	TPolynom correct;
	correct.AddMonom(-10, 0, 1, 1);
	correct.AddMonom(-20, 1, 0, 1);
	correct.AddMonom(-30, 1, 1, 1);

	EXPECT_EQ(result, correct);
}

TEST(TPolynom, CanMultiplyPolynomByMonom)
{
	TPolynom t;
	t.AddMonom(1, 0, 1, 0);
	t.AddMonom(1, 1, 0, 0);

	TMonom m(2, 1, 0, 1);

	std::cout << "\t     t = " << t << '\n';

	TPolynom result;
	ASSERT_NO_THROW(result = t * m);

	std::cout << "\t     t * 2*xz = " << result << '\n';

	TPolynom correct;
	correct.AddMonom(2, 2, 0, 1);
	correct.AddMonom(2, 1, 1, 1);

	EXPECT_EQ(result, correct);
}

TEST(TPolynom, CanMultiplyPolynomByPolynom)
{
	TPolynom t1;
	t1.AddMonom(1, 1, 0, 0);

	TPolynom t2;
	t2.AddMonom(2, 0, 1, 1);
	t2.AddMonom(0.5, 0, 0, 1);

	std::cout << "\t     t1 = " << t1 << '\n';
	std::cout << "\t     t2 = " << t2 << '\n';

	TPolynom result;
	ASSERT_NO_THROW(result = t1 * t2);

	std::cout << "\t     t1 * t2 = " << result << '\n';

	TPolynom correct;
	correct.AddMonom(2, 1, 1, 1);
	correct.AddMonom(0.5, 1, 0, 1);

	EXPECT_EQ(result, correct);
}