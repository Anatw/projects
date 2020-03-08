#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

DLL_t *DLLCreate();

void DLLDestroy(DLL_t *list);

void *DLLGetData(const iter_t node);

void DLLSetData(const iter_t node, const void *data);

iter_t DLLNext(const iter_t));

iter_t DLLPrev(DLL_t *list);

int DLLIsEmpty(const DLL_t *list);

iter_t DllRemove(iter_t to_remove);

iter_t DLLInsert(DLL_t *list, void *data);

size_t DLLSize(const DLL_t *list);

iter_t *DLBegine(const DLL_t *list);

iter_t *DLEnd(const DLL_t *list);

DLLIsSameIter(const iter_t iter1, const iter_t iter2);

iter_t *DLLFind(const iter_t from, const iter_t to, const void *data,
			   int (*match_func)(const void *, const void *));

DLLForEach(iter_t from, iter_t to, void *param, int
			   (*action_func)(void *param, void *data));

DLLPopBack(DLL_t *list);

DLLPushBack(DLL_t *list);

DLLPopFront(DLL_t *list);

DLLSplice(DLL_t *list);

DLL_t *DLLMultiFind(const iter_t from, const iter_t to, const void *data,
			 int (*match_func)(const void *, const void *));

#endif /* DOUBLY_LINKED_LIST_H */
