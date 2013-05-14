#include <stdio.h>
#include "skiplist.h"

int getNodeLevel(skiplistNode* forwards[]) {
    return sizeof(forwards) / sizeof(skiplistNode*);
}

void printSkipListNode(skiplistNode* node) {
    if (NULL == node) {
        printf("node is NULL\n");
        return;
    }
    int i, level = getNodeLevel(node->forwards);
    printf("key=%d,value=%d,level=%d:", node->key, node->value, level);
    for (i=0; i<level; i++) {
        printf("%d -> ", i);
        if (NULL == node->forwards[i]) {
            printf("NULL");
        } else {
            printf("key=%d,value=%d", node->forwards[i]->key, node->forwards[i]->value);
        }
    }
    printf("\n");
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
        printSkipListNode(skiplistInsert(l, i, i*2));
    }
    printSkipListNode(skiplistSearch(l, 10));
    printSkipListNode(skiplistSearch(l, 5));
    printSkipListNode(skiplistSearch(l, 15));
    skiplistDelete(l, 11);
    printSkipListNode(skiplistSearch(l, 10));
    printSkipListNode(skiplistSearch(l, 11));
    skiplistFree(l);
    return 0;
}
