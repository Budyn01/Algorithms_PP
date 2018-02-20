#ifndef _LIST_H
#define _LIST_H


#include "stdafx.h"


typedef struct tagList {
	LIST_DATA *data;
	tagList *next;
} LIST;

LIST *MakeEmptyList();
void Insert(LIST *afterElement, LIST_DATA *data);
void InsertFront(LIST *list, LIST_DATA *data);
int isEmpty(LIST *list);
void FreeList(LIST *list);
void Remove(LIST *afterElement);
void RemoveFront(LIST *list);
LIST *Front(LIST *list);
void DeleteList(LIST *list);
int Compare(const void* value1, const void* value2);
LIST* Find(LIST* list, const void* tmpItem, LIST** pPrev, int(_cdecl *Compare)(const void*, const void*));
void Sort(LIST* list, int(__cdecl*Compare)(const void*, const void*));

#endif	
