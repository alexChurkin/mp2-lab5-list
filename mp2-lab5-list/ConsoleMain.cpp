#include <iostream>
#include "TListAndMonom.h"

using namespace std;

int main()
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
	for (l.Revert(); !l.IsEnd(); l.GoNext())
	{
		cout << l.GetCurr() << ' ';
	}
	cout << "\n";

	l.Revert();
	l.InsCurr(0);

	//0 1 2 3 4
	for (l.Revert(); !l.IsEnd(); l.GoNext())
	{
		cout << l.GetCurr() << ' ';
	}
	cout << "\n";

	l.InsCurr(5);

	//0 1 2 3 4 5
	for (l.Revert(); !l.IsEnd(); l.GoNext())
	{
		cout << l.GetCurr() << ' ';
	}
	cout << "\n";

	l.Revert();
	l.GoNext();
	l.InsCurr(777);

	//0 777 1 2 3 4 5
	for (l.Revert(); !l.IsEnd(); l.GoNext())
	{
		cout << l.GetCurr() << ' ';
	}
	cout << "\n";

	l.DelFirst();

	//777 1 2 3 4 5
	for (l.Revert(); !l.IsEnd(); l.GoNext())
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

	l.Revert();
	l.DelCurr();
	
	//1 2 3 4 5
	for (l.Revert(); !l.IsEnd(); l.GoNext())
	{
		cout << l.GetCurr() << ' ';
	}
	cout << "\n";

	l.DelFirst();

	//1 2 3 4 5
	for (l.Revert(); !l.IsEnd(); l.GoNext())
	{
		cout << l.GetCurr() << ' ';
	}
	cout << "\n";
}