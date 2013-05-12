#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__

#define SKIPLIST_MAXLEVEL 32;
#define SKIPLIST_P 0.25; // p=1/4

typedef struct skiplistNode {
    int value;
    struct skiplistNode* forwards[];
} skiplistNode;

typedef struct skiplist {
    struct skiplistNode* header;
    int level;
} skiplist;

skiplist* skiplistCreate(void);
skiplistNode* skiplistCreateNode(int level, int value);
int skiplistFind(skiplist* l, int value);
skiplistNode* skiplistInsert(skiplist* l, int value);
void skiplistDelete(skiplist* l, int value);
void skiplistFree(skiplist* l);
void skiplistFreeNode(skiplistNode* node);

#endif
