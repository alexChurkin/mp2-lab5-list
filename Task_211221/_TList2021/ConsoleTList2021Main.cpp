#include <iostream>
#include "TList2021.h"

using namespace std;

int main()
{
    cout << "Console TList2021 demo\n";
    cout << "==================\n";

    TList2021<int> list;

    cout << "list:\n" << list << "\n\n";


    cout << "Pushing back:\n";
    for (int i = 1; i <= 5; i++)
    {
        list.PushBack(i);
        cout << list << "\n";
    }

    cout << "\n";

    cout << "Pushing front:\n";
    for (int i = 6; i <= 10; i++)
    {
        list.PushFront(i);
        cout << list << "\n";
    }

    cout << "\n";

    TList2021<int> list2 = list;


    for (int i = 1; i <= 5; i++)
    {
        cout << "Popped front: " << list.PopFront() << "\n";
        cout << list << "\n\n";
    }

    TList2021<int> list3(list);

    for (int i = 1; i <= 5; i++)
    {
        cout << "Popped back: " << list.PopBack() << "\n";
        cout << list << "\n\n";
    }

    cout << "Let's try to pop back/front from \"list\" again:\n";

    try
    {
        list.PopFront();
    }
    catch (TList2021Exception e)
    {
        cout << e;
    }

    try
    {
        list.PopBack();
    }
    catch (TList2021Exception e)
    {
        cout << e << '\n';
    }

    
    cout << "We copied this lists from some states of \"list\":\n\n";
    cout << "list2:\n" << list2 << "\n\n";
    cout << "list3:\n" << list3 << "\n\n";

    cout << "These 2 lists are not equal:\n";
    cout << "(list2 == list3) = " << (list2 == list3) << '\n';

    cout << "But the last elements are equal:\n";
    cout << "list2.GetLast() = " << list2.GetLast() << "\n";
    cout << "list3.GetLast() = " << list3.GetLast() << "\n\n";

    cout << "We can make this lists equal with list2.PopFront():\n";
    for (int i = 1; i <= 5; i++)
    {
        list2.PopFront();
        cout << list2 << "\n\n";
    }

    cout << "list2:\n" << list2 << "\n\n";
    cout << "list3:\n" << list3 << "\n\n";

    cout << "(list2 == list3) = " << (list2 == list3) << "\n";

    cout << "list2[3] = " << list2[3] << "\n\n";

    cout << "Trying to get list2[20]:\n";
    try
    {
        int k = list2[20];
    }
    catch (TList2021Exception e)
    {
        cout << e << '\n';
    }
}