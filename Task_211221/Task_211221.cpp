#include <iostream>
#include "TList.h"

using namespace std;

int main()
{
    cout << "TList demo\n";
    cout << "==================\n";

    TList<int> list;

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

    TList<int> list2 = list;


    for (int i = 1; i <= 5; i++)
    {
        cout << "Popped front: " << list.PopFront() << "\n";
        cout << list << "\n\n";
    }

    TList<int> list3(list);

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
    catch (TListException e)
    {
        cout << e;
    }

    try
    {
        list.PopBack();
    }
    catch (TListException e)
    {
        cout << e << '\n';
    }

    cout << "We copied this lists from some previous states of \"list\":\n\n";
    cout << "list2:\n" << list2 << "\n\n";
    cout << "list3:\n" << list3 << "\n\n";

    cout << "These 2 lists are not equal:\n";
    cout << "(list2 == list3) = " << (list2 == list3) << '\n';

    cout << "But their last elements are equal:\n";
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
    catch (TListException e)
    {
        cout << e << "\n\n";
    }

    /* ........ Task (21.12.21) ........ */

    cout << "Task (21.12.21):\n";
    cout << "===============\n";

    cout << "Test 1: \n\n";

    TList<int> l1;

    l1.PushBack(1);
    l1.PushBack(3);
    l1.PushBack(2);
    l1.PushBack(4);
    l1.PushBack(2);

    cout << l1 << "\n";
    l1.PushAfterMax(1024);
    cout << l1 << "\n\n";

    cout << "Test 2: \n\n";

    TList<int> l2;

    l2.PushBack(1);
    l2.PushBack(3);
    l2.PushBack(2);
    l2.PushBack(11);
    l2.PushBack(120);

    cout << l2 << "\n";
    l2.PushAfterMax(1024);
    cout << l2 << "\n\n";

    cout << "Test 3: \n\n";

    TList<int> l3;

    l3.PushBack(4);
    l3.PushBack(3);
    l3.PushBack(2);
    l3.PushBack(1);

    cout << l3 << "\n";
    l3.PushAfterMax(1024);
    cout << l3 << "\n\n";

    cout << "Test 4: \n\n";

    TList<int> l4;

    l4.PushBack(-12);

    cout << l4 << "\n";
    l4.PushAfterMax(1024);
    cout << l4 << "\n\n";

    cout << "Test 5: \n\n";

    TList<int> l5;

    cout << l5 << "\n";
    l5.PushAfterMax(1024);
    cout << l5 << "\n\n";

    cout << "Enter anything to finish...\n";
    int k;
    cin >> k;
}