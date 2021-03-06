#include "stdafx.h"

void PrintList(List *list);

int main()
{
	List *list = MakeEmptyList();
	PrintList(list);
	ListData *element1 = MakeListData(1);
	ListData *element2 = MakeListData(2);
	ListData *element3 = MakeListData(3);
	ListData *element4 = MakeListData(4);
	ListData *element5 = MakeListData(5);
	InsertFront(list, element1);
	InsertFront(list, element2);
	InsertFront(list, element3);
	InsertFront(list, element4);
	InsertFront(list, element5);
	PrintList(list);
	RemoveFront(list);
	RemoveFront(list);
	PrintList(list);
	DeleteList(list);
	system("PAUSE");
	return 0;
}

// do main, poprawic nazwe listDATA
int Compare(const void* value1, const void* value2) {
	if (((ListData*)value1)->value < ((ListData*)value2)->value) {
		return -1;
	}
	else if (((ListData*)value1)->value >((ListData*)value2)->value) {
		return 1;
	}
	return 0;
}

void PrintList(List *list) {
	int empty = isEmpty(list);
	cout << "List: (";
	while (!isEmpty(list))
	{
		list = list->next;
		ListData* temp = list->data;
		cout << temp->value << ",";
	}
	cout << (empty ? "empty)" : "\b)") << endl;
}
