#pragma once
typedef struct {
    void (*insert)(void *_self, int value);
    void (*remove)(void *_self, int value);
    int (*contains)(void *_self, int value);
    int (*size)(void *_self);
    void (*destroy)(void *_self);
    int (*empty)(void *_self);
    int (*sorted)(void *_self);
} __attribute__((packed)) BSTreeNodeVtable;


typedef struct BSTreeNode_s {
    int __type__;
    int value;
    struct BSTreeNode_s *left;
    struct BSTreeNode_s *right;
    BSTreeNodeVtable *vtable;
}  BSTreeNode;

typedef struct {
    void (*insert)(void *_self, int value);
    void (*remove)(void *_self, int value);
    int (*contains)(void *_self, int value);
    int (*size)(void *_self);
    void (*print)(void *_self);
    void (*destroy)(void *_self);
    int (*sorted)(void *_self);
} __attribute__((packed)) BSTreeVtable;

typedef struct {
    int __type__;
    BSTreeNode *root;
    int size;
    BSTreeVtable *vtable;
} __attribute__((packed)) BSTree;

BSTree *newBSTree();
void bstree_insert(void *_self, int value);
void bstree_remove(void *_self, int value);
int bstree_contains(void *_self, int value);
int bstree_size(void *_self);
void bstree_print(void *_self);
void bstree_destroy(void *_self);
int bstree_sorted(void *_self);

BSTreeNode *newBSTreeNode(int value);
void bstree_node_insert(void *_self, int value);
void bstree_node_remove(void *_self, int value);
int bstree_node_contains(void *_self, int value);
int bstree_node_size(void *_self);
void bstree_node_destroy(void *_self);
int bstree_node_empty(void *_self);
int bstree_node_sorted(void *_self);

#define BSTREE 0x00000002
#define BSTREE_NODE 0x00000003

