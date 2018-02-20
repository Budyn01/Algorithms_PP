#include "stdafx.h"

LIST_DATA *MakeListData(int value) {
	LIST_DATA *listData = (ListData*)calloc(1, sizeof(ListData));
	if (!listData) {
		printf("ERROR: MakeListData");
		return 0;
	}
	listData->value = value;
	return listData;
};