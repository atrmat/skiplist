#include <math.h>
#include "skiplist.h"

skiplist* skiplistCreate(void) {
    int i;
    skiplist* l = (skiplist*)malloc(sizeof(*l));
    if (NULL == l) return NULL;
    l->level = 1;
    l->header = skiplistCreateNode(SKIPLIST_MAXLEVEL, -1);
    if (NULL == l->header) {
        free(l);
        return NULL;
    }
    for (i=0; i<SKIPLIST_MAXLEVEL; i++) {
        l->header->forwards[i] = NULL;
    }
    return l;
}

void skiplistFree(skiplist* l) {
    if (NULL == l) return;
    skiplistNode *p = l->header, *next;
    while (p) {
        next = p->forwards[0];
        skiplistFreeNode(p);
        p = next;
    }
    free(l);
    l = NULL;
}

skiplistNode* skiplistCreateNode(int level, int value) {
    skiplistNode* node = (skiplistNode*)malloc(sizeof(*node) + level*sizeof(node));
    if (NULL == node) return NULL;
    node->value = value;
    return node;
}

void skiplistFreeNode(skiplistNode* node) {
    if (NULL != node) {
        free(node);
        node = NULL;
    }
}

/* Returns a random level for the new skiplist node we are going to create.
 * The return value of this function is between 1 and ZSKIPLIST_MAXLEVEL
 * (both inclusive), with a powerlaw-alike distribution where higher
 * levels are less likely to be returned. */
int skiplistRandomLevel(void) {
    int level = 1;
    while ((random()&0xFFFF) < (SKIPLIST_P * 0xFFFF))
        level += 1;
    return (level<SKIPLIST_MAXLEVEL) ? level : SKIPLIST_MAXLEVEL;
}

skiplistNode* skiplistInsert(skiplist* l, int value) {
    skiplistNode *update[SKIPLIST_MAXLEVEL], *p = l->header;
    int i;
    for (i=l->level-1; i>=0; i--) {
        while (p && p->forwards[i]->value < value)
            p = p->forwards[i];
        update[i] = p;
    }
    int level = skiplistRandomLevel();
    if (level > l->level) {
        for (i=l->level; i<level; i++)
            update[i] = l->header;
        l->level = level;
    }
    p = skiplistCreateNode(level, value);
    if (NULL == p) return NULL;
    // insert the new node in all the level lists 
    for (i=0; i<level; i++) {
        p->forwards[i] = update[i]->forwards[i];
        update[i]->forwards[i] = p;
    }
    return p;
}

void skiplistDelete(skiplist* l, int value) {
    skiplistNode *update[SKIPLIST_MAXLEVEL], *p = l->header;
    int i;
    for (i=l->level-1; i>=0; i--) {
        while (p && p->forwards[i]->value < value)
            p = p->forwards[i];
        update[i] = p;
    }
    if (!p || p->forwards[0]->value != value) // not found
        return;
    p = p->forwards[0];
    for (i=0; i<l->level; i++) {
        if (update[i]->forwards[i] == p)
            update[i]->forwards[i] = p->forwards[i];
    }
    while (l->level > 1 && NULL == l->header->forwards[i])
        l->level --;
    skiplistFreeNode(p);
}

