#include "pch.h"
#include "..\mp2-lab5-list\TList.h"

TEST(TList, CanCreateNewList)
{
	ASSERT_NO_THROW(TList<int> t);
}

TEST(TList, NewCreatedListIsEmpty)
{
	TList<int> t;
	ASSERT_TRUE(t.IsEmpty());
}

TEST(TList, NotEmptyListIsNotEmpty)
{
	TList<int> t;
	t.InsFirst(10);

	ASSERT_TRUE(!t.IsEmpty());
	ASSERT_TRUE(t.IsNotEmpty());
}

TEST(TList, CanInsertFirstElement)
{
	TList<int> t;
	ASSERT_NO_THROW(t.InsFirst(1));
	std::cout << "\t     " << t << '\n';
}

TEST(TList, CanInsertLastElement)
{
	TList<int> t;
	t.InsFirst(1);
	ASSERT_NO_THROW(t.InsLast(2));
	std::cout << "\t     " << t << '\n';
}

TEST(TList, CanInsertCurrentElementWhenFirst)
{
	TList<int> t;
	t.InsFirst(1); t.InsFirst(2);
	t.InsFirst(3); t.InsFirst(4);

	t.Reset();
	ASSERT_NO_THROW(t.InsCurr(100));
	std::cout << "\t     " << t << '\n';
}

TEST(TList, CanInsertCurrentElementWhenSecond)
{
	TList<int> t;
	t.InsFirst(1); t.InsFirst(2);
	t.InsFirst(3); t.InsFirst(4);

	t.Reset(); t.GoNext();
	ASSERT_NO_THROW(t.InsCurr(100));
	std::cout << "\t     " << t << '\n';
}

TEST(TList, CanInsertCurrentElementWhenPenultimate)
{
	TList<int> t;
	t.InsLast(1); t.InsLast(2);
	t.InsLast(3); t.InsLast(4);

	t.Reset();
	t.GoNext(); t.GoNext();
	t.GoNext();

	ASSERT_NO_THROW(t.InsCurr(100));

	std::cout << "\t     " << t << '\n';
}

TEST(TList, CanInsertCurrentElementWhenLast)
{
	TList<int> t;
	t.InsLast(1); t.InsLast(2);
	t.InsLast(3); t.InsLast(4);

	t.Reset();
	t.GoNext(); t.GoNext();
	t.GoNext(); t.GoNext();

	ASSERT_NO_THROW(t.InsCurr(100));

	std::cout << "\t     " << t << '\n';
}

TEST(TList, CanDeleteFirstElement)
{
	TList<int> t;
	t.InsLast(1); t.InsLast(2);
	t.InsLast(3); t.InsLast(4);

	ASSERT_NO_THROW(t.DelFirst());

	std::cout << "\t     " << t << '\n';
}

TEST(TList, CanDelete2CurrentElementsWhenFirst)
{
	TList<int> t;
	t.InsLast(1); t.InsLast(2);
	t.InsLast(3); t.InsLast(4);

	t.Reset();

	ASSERT_NO_THROW(t.DelCurr());
	ASSERT_NO_THROW(t.DelCurr());

	std::cout << "\t     " << t << '\n';
}

TEST(TList, CanDeleteCurrentElementWhenSecond)
{
	TList<int> t;
	t.InsLast(1); t.InsLast(2);
	t.InsLast(3); t.InsLast(4);

	t.Reset();
	t.GoNext();

	ASSERT_NO_THROW(t.DelCurr());

	std::cout << "\t     " << t << '\n';
}

TEST(TList, CanDeleteCurrentElementWhenPenultimate)
{
	TList<int> t;
	t.InsLast(1); t.InsLast(2);
	t.InsLast(3); t.InsLast(4);

	t.Reset();
	t.GoNext(); t.GoNext();

	ASSERT_NO_THROW(t.DelCurr());

	std::cout << "\t     " << t << '\n';
}

TEST(TList, CanDeleteCurrentElementWhenLast)
{
	TList<int> t;
	t.InsLast(1); t.InsLast(2);
	t.InsLast(3); t.InsLast(4);

	t.Reset();
	t.GoNext(); t.GoNext();
	t.GoNext();

	ASSERT_NO_THROW(t.DelCurr());

	std::cout << "\t     " << t << '\n';
}