#include <stdio.h>
#include "skiplist.h"

int getNodeLevel(skiplistNode* forwards[]) {
    return sizeof(forwards) / sizeof(forwards[0]);
}

void printSkipListNode(int value) {
    printf("node value:%d\n", value);
}

int main(int argc, char** srgv) {
    skiplist* l = skiplistCreate();
    if (NULL == l) {
        fprintf(stderr, "create skiplist error\n");
        return -1;
    }
    skiplistNode* node = NULL;
    int i;
    for (i=0; i<20; i++) {
        skiplistInsert(l, i, i*2);
    }
    printSkipListNode(skiplistSearch(l, 10));
    printSkipListNode(skiplistSearch(l, 5));
    printSkipListNode(skiplistSearch(l, 15));
    printSkipListNode(skiplistSearch(l, 16));
    printSkipListNode(skiplistSearch(l, 17));
    skiplistDelete(l, 11);
    printSkipListNode(skiplistSearch(l, 11));
    skiplistFree(l);
    return 0;
}
