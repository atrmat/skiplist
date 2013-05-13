#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__

#define SKIPLIST_MAXLEVEL 32
#define SKIPLIST_P 0.25 // p=1/4

// make key and value int, as simple as it can be since it is just an example
typedef struct skiplistNode {
    int key;
    int value;
    struct skiplistNode* forwards[];
} skiplistNode;

typedef struct skiplist {
    struct skiplistNode* header;
    int level;
} skiplist;

skiplist* skiplistCreate(void);
skiplistNode* skiplistCreateNode(int level, int key, int value);
int skiplistSearch(skiplist* l, int key);
skiplistNode* skiplistInsert(skiplist* l, int key, int value);
void skiplistDelete(skiplist* l, int key);
void skiplistFree(skiplist* l);
void skiplistFreeNode(skiplistNode* node);

#endif
