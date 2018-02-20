#ifndef _LIST_DATA_H
#define _LIST_DATA_H

typedef struct tagListData {
	int value;
} ListData;

ListData *MakeListData(int);

#define LIST_DATA ListData
#define LIST List

#endif
