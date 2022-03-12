#include <iostream>
#include "TPolynom.h"

using namespace std;

void LaunchTListDemo()
{
	cout << "TList demo\n";
	cout << "==================\n";
	TList<int> l;
	l.InsFirst(3);
	l.InsFirst(2);
	l.InsFirst(1);

	cout << l << "\n";

	l.InsLast(4);

	cout << l << '\n';

	l.Reset();
	l.InsCurr(0);

	cout << l << '\n';

	l.InsCurr(5);

	cout << l << '\n';

	l.Reset();
	l.GoNext();
	l.InsCurr(777);

	cout << l << '\n';

	l.DelFirst();

	cout << l << '\n';

	l.Reset();
	l.DelCurr();

	cout << l << '\n';

	l.DelFirst();

	cout << l << '\n';
}

void LaunchTPolynomPrintDemo()
{
	cout << "TPolynom print demo\n";
	cout << "==================\n";
	//P1 = 1
	TPolynom p1;
	p1.AddMonom(TMonom(1, 0, 0, 0));
	cout << "P1 = " << p1 << '\n';

	//P1 = -1
	TPolynom p2;
	p2.AddMonom(TMonom(-1, 0, 0, 0));
	cout << "P2 = " << p2 << '\n';

	//P3 = 5
	TPolynom p3;
	p3.AddMonom(TMonom(5, 0, 0, 0));
	cout << "P3 = " << p3 << '\n';

	//P4 = x + 1
	TPolynom p4;
	p4.AddMonom(TMonom(1, 1, 0, 0));
	p4.AddMonom(TMonom(1, 0, 0, 0));
	cout << "P4 = " << p4 << '\n';

	//P5 = x - 1
	TPolynom p5;
	p5.AddMonom(TMonom(1, 1, 0, 0));
	p5.AddMonom(TMonom(-1, 0, 0, 0));
	cout << "P5 = " << p5 << '\n';

	//P6 = x2 + x + 1
	TPolynom p6;
	p6.AddMonom(TMonom(1, 2, 0, 0));
	p6.AddMonom(TMonom(1, 1, 0, 0));
	p6.AddMonom(TMonom(1, 0, 0, 0));
	cout << "P6 = " << p6 << '\n';

	//P7 = 2*x2 - 4*x + 10
	TPolynom p7;
	p7.AddMonom(TMonom(2, 2, 0, 0));
	p7.AddMonom(TMonom(-4, 1, 0, 0));
	p7.AddMonom(TMonom(10, 0, 0, 0));
	cout << "P7 = " << p7 << '\n';

	//P8 = xyz
	TPolynom p8;
	p8.AddMonom(TMonom(1, 1, 1, 1));
	cout << "P8 = " << p8 << '\n';

	//P9 = -x2y
	TPolynom p9;
	p9.AddMonom(TMonom(-1, 2, 1, 0));
	cout << "P9 = " << p9 << '\n';

	//P10 = -10*x3y2z + 5*yz - 3*y + 3
	TPolynom p10;
	p10.AddMonom(TMonom(-10, 3, 2, 1));
	p10.AddMonom(TMonom(5, 0, 1, 1));
	p10.AddMonom(TMonom(-3, 0, 1, 0));
	p10.AddMonom(TMonom(3, 0, 0, 0));
	cout << "P10 = " << p10 << '\n';
}

void LaunchTPolynomDemo()
{
	cout << "TPolynom sum demo\n";
	cout << "==================\n";

	TPolynom p3;
	p3.AddMonom(TMonom(1, 1, 0, 0));
	p3.AddMonom(TMonom(2, 0, 0, 0));
	cout << "P3 = " << p3 << '\n';

	TPolynom p4;
	p4.AddMonom(TMonom(-1, 1, 0, 0));
	p4.AddMonom(TMonom(-2, 0, 0, 0));
	cout << "P4 = " << p4 << '\n';

	cout << "P4 + P3 = " << p4 + p3 << '\n';
}

int main()
{
	LaunchTListDemo();
	cout << '\n';
	LaunchTPolynomPrintDemo();
	cout << '\n';
	LaunchTPolynomDemo();

	return 0;
}