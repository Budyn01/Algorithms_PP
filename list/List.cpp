#include "stdafx.h"

LIST *MakeEmptyList() {
	LIST *list = (LIST*)calloc(1, sizeof(LIST));
	if (!list) {
		printf("ERROR: MakeEmptyList");
		return NULL;
	}
	return list;
};
void Insert(LIST *afterElement, LIST_DATA *data) {
	LIST *newListElement = MakeEmptyList();
	// sprawdzic null
	if (!newListElement) {
		printf("Error: can't insert element");
		return;
	}
	newListElement->data = data;
	newListElement->next = afterElement->next;
	afterElement->next = newListElement;
};
void InsertFront(LIST *list, LIST_DATA *data) {
	Insert(list, data);
};

int isEmpty(LIST *list) {
	return !(list->next);
};
void FreeList(LIST *list) {
	while (!isEmpty(list)) {
		RemoveFront(list);
	}
};
void Remove(LIST *elementAfter) {
	if (!isEmpty(elementAfter)) {
		LIST *temp = elementAfter->next;
		elementAfter->next = temp->next;
		free(temp->data);
		free(temp);
	}
	else {
		cout << "ERROR: Remove" << endl;
	}
};
void RemoveFront(LIST *list) {
	Remove(list);
};
LIST *Front(LIST *list) {
	return list->next;
};
void DeleteList(LIST *list) {
	if (list) {
		FreeList(list);
		free(list);
	}
};

LIST* Find(LIST* list, const void* searchingElement, LIST** pPrev, int(_cdecl *Compare)(const void*, const void*)) {
	LIST *temp = list->next;
	*pPrev = list;
	while (temp) {
		if (!Compare(temp->data, searchingElement)) {
			return temp;
		}
		*pPrev = temp;
		temp = temp->next;
	}
	return *pPrev = NULL;
}

void Sort(LIST* list, int(__cdecl*Compare)(const void*, const void*)) {
	LIST* sorted = list;

	while (sorted->next)
	{
		LIST* min = sorted;
		LIST* pListPointer = sorted->next;

		while (pListPointer->next)
		{
			if (Compare(min->next->data, pListPointer->next->data) == 1)
			{
				min = pListPointer;
			}

			pListPointer = pListPointer->next;
		}

		if (min != sorted)
		{
			LIST* temp = min->next->next;
			min->next->next = sorted->next;
			sorted->next = min->next;
			min->next = temp;

		}
		sorted = sorted->next;
	}

}
