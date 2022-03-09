#include <iostream>
#include "TPolinom.h"

using namespace std;

void LaunchTListDemo()
{
	cout << "Console TList demo\n";
	cout << "==================\n";
	TList<int> l;
	l.InsFirst(3);
	l.InsFirst(2);
	l.InsFirst(1);

	//1 2 3
	cout << l << "\n";

	l.InsLast(4);

	//1 2 3 4
	for (l.Reset(); !l.IsEnd(); l.GoNext())
	{
		cout << l.GetCurr() << ' ';
	}
	cout << "\n";

	l.Reset();
	l.InsCurr(0);

	//0 1 2 3 4
	for (l.Reset(); !l.IsEnd(); l.GoNext())
	{
		cout << l.GetCurr() << ' ';
	}
	cout << "\n";

	l.InsCurr(5);

	//0 1 2 3 4 5
	for (l.Reset(); !l.IsEnd(); l.GoNext())
	{
		cout << l.GetCurr() << ' ';
	}
	cout << "\n";

	l.Reset();
	l.GoNext();
	l.InsCurr(777);

	//0 777 1 2 3 4 5
	for (l.Reset(); !l.IsEnd(); l.GoNext())
	{
		cout << l.GetCurr() << ' ';
	}
	cout << "\n";

	l.DelFirst();

	//777 1 2 3 4 5
	for (l.Reset(); !l.IsEnd(); l.GoNext())
	{
		cout << l.GetCurr() << ' ';
	}
	cout << "\n";

	//Trying to delete current when it's == end
	try
	{
		l.DelCurr();
	}
	catch (TLException e)
	{
		cout << e;
	}

	l.Reset();
	l.DelCurr();

	//1 2 3 4 5
	for (l.Reset(); !l.IsEnd(); l.GoNext())
	{
		cout << l.GetCurr() << ' ';
	}
	cout << "\n";

	l.DelFirst();

	//1 2 3 4 5
	for (l.Reset(); !l.IsEnd(); l.GoNext())
	{
		cout << l.GetCurr() << ' ';
	}
	cout << "\n";
}

void LaunchTPolinomCoutTest()
{
	//P1 = 1
	TPolinom p1;
	p1.AddMonom(TMonom(1, 0, 0, 0));
	cout << "P1 = " << p1 << '\n';

	//P1 = -1
	TPolinom p2;
	p2.AddMonom(TMonom(-1, 0, 0, 0));
	cout << "P2 = " << p2 << '\n';

	//P3 = 5
	TPolinom p3;
	p3.AddMonom(TMonom(5, 0, 0, 0));
	cout << "P3 = " << p3 << '\n';

	//P4 = x + 1
	TPolinom p4;
	p4.AddMonom(TMonom(1, 1, 0, 0));
	p4.AddMonom(TMonom(1, 0, 0, 0));
	cout << "P4 = " << p4 << '\n';

	//P5 = x - 1
	TPolinom p5;
	p5.AddMonom(TMonom(1, 1, 0, 0));
	p5.AddMonom(TMonom(-1, 0, 0, 0));
	cout << "P5 = " << p5 << '\n';

	//P6 = x2 + x + 1
	TPolinom p6;
	p6.AddMonom(TMonom(1, 2, 0, 0));
	p6.AddMonom(TMonom(1, 1, 0, 0));
	p6.AddMonom(TMonom(1, 0, 0, 0));
	cout << "P6 = " << p6 << '\n';

	//P7 = 2*x2 - 4*x + 10
	TPolinom p7;
	p7.AddMonom(TMonom(2, 2, 0, 0));
	p7.AddMonom(TMonom(-4, 1, 0, 0));
	p7.AddMonom(TMonom(10, 0, 0, 0));
	cout << "P7 = " << p7 << '\n';

	//P8 = xyz
	TPolinom p8;
	p8.AddMonom(TMonom(1, 1, 1, 1));
	cout << "P8 = " << p8 << '\n';

	//P9 = -x2y
	TPolinom p9;
	p9.AddMonom(TMonom(-1, 2, 1, 0));
	cout << "P9 = " << p9 << '\n';

	//P10 = -10*x3y2z + 5*yz - 3*y + 3
	TPolinom p10;
	p10.AddMonom(TMonom(-10, 3, 2, 1));
	p10.AddMonom(TMonom(5, 0, 1, 1));
	p10.AddMonom(TMonom(-3, 0, 1, 0));
	p10.AddMonom(TMonom(3, 0, 0, 0));
	cout << "P10 = " << p10 << '\n';
}

void LaunchTPolinomDemo1()
{
	TPolinom p1;
	p1.AddMonom(TMonom(5, 1, 1, 1));
	p1.AddMonom(TMonom(1, 2, 2, 2));
	p1.AddMonom(TMonom(-4, 1, 1, 2));
	p1.AddMonom(TMonom(3, 1, 2, 1));
	p1.AddMonom(TMonom(2, 1, 2, 2));
	cout << "P1 = " << p1 << '\n';

	TPolinom p2;
	p2.AddMonom(TMonom(5, 1, 1, 1));
	p2.AddMonom(TMonom(1, 2, 2, 2));
	p2.AddMonom(TMonom(-4, 1, 1, 2));
	p2.AddMonom(TMonom(3, 1, 2, 1));
	p2.AddMonom(TMonom(2, 1, 2, 2));

	p2.AddMonom(TMonom(1.5, 4, 1, 1));
	p2.AddMonom(TMonom(777, 1, 1, 0));
	cout << "P2 = " << p2 << '\n';

	TPolinom result1(p1 + p2);
	cout << "P1 + P2 = " << result1 << '\n';

	TPolinom result2 = p1 + p2;
	cout << "P1 + P2 = " << result2 << '\n';

	TPolinom p3;
	p3.AddMonom(TMonom(1, 0, 0, 0));
	cout << "P3 = " << p3 << '\n';

	TPolinom p4 = result1 * (-100);
	cout << "P4 = " << p4 << '\n';

	TPolinom p5 = p4;
	cout << "P5 = " << p5 << '\n';

	TPolinom p6 = p2 - p1;
	cout << "P6 = P2 - P1 = " << p6 << '\n';
}

void LaunchTPolinomDemo2()
{
	/*TPolinom p1;
	p1.AddMonom(TMonom(1, 0, 0, 0));
	cout << "P1 = " << p1 << '\n';

	TPolinom p2;
	p2.AddMonom(TMonom(-1, 0, 0, 0));
	cout << "P2 = " << p2 << '\n';

	TPolinom s1 = p2 + p1;
	cout << "P2 + P1 = " << s1 << "\n\n";*/

	TPolinom p3;
	p3.AddMonom(TMonom(1, 1, 0, 0));
	p3.AddMonom(TMonom(2, 0, 0, 0));
	cout << "P3 = " << p3 << '\n';

	TPolinom p4;
	p4.AddMonom(TMonom(-1, 1, 0, 0));
	p4.AddMonom(TMonom(-2, 0, 0, 0));
	cout << "P4 = " << p4 << '\n';

	TPolinom s2 = p3 + p4;
	cout << "P3 + P4 = " << s2 << '\n';

	TPolinom p7;
	p7.AddMonom(TMonom(2, 2, 0, 0));
	p7.AddMonom(TMonom(-4, 1, 0, 0));
	p7.AddMonom(TMonom(10, 0, 0, 0));
	cout << "P7 = " << p7 << '\n';

	TPolinom p6 = p7;
	cout << "P6 = " << p6 << '\n';
}

int main()
{
	//LaunchTListDemo();
	//LaunchTPolinomCoutTest();

	//LaunchTPolinomDemo1();
	LaunchTPolinomDemo2();
	
}

//Не работает
//cout << "P1 + P2 = " << (p1 + p2) << '\n';