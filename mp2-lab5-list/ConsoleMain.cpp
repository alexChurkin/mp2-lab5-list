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

void LaunchTPolinomDemo()
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

	TPolinom result = p1 + p2;
	//Не работает
	//cout << "P1 + P2 = " << p1 + p2 << '\n';
	//Работает
	cout << "P1 + P2 = " << result << '\n';

	TPolinom p3;
	p3.AddMonom(TMonom(1, 0, 0, 0));
	cout << "P3 = " << p3 << '\n';

	TPolinom p4 = result * (-100);
	cout << "P4 = " << p4 << '\n';
}

int main()
{
	//LaunchTListDemo();
	LaunchTPolinomDemo();
}