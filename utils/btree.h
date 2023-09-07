

typedef struct {
    int __type__;
    int value;
    void *left;
    void *right;
} __attribute__((packed)) BTreeNode;

typedef struct {
    void (*insert)(void *self, int value);
    void (*remove)(void *self, int value);
    int (*contains)(void *self, int value);
    int (*size)(void *self);
    void (*print)(void *self);
    void (*destroy)(void *self);
} __attribute__((packed)) BTreeNodeVtable;

typedef struct {
    void (*insert)(void *self, int value);
    void (*remove)(void *self, int value);
    int (*contains)(void *self, int value);
    int (*size)(void *self);
    void (*print)(void *self);
    void (*destroy)(void *self);
} __attribute__((packed)) BTreeVtable;

typedef struct {
    int __type__;
    BTreeNode *root;
    int size;
    BTreeVtable *vtable;
} __attribute__((packed)) BTree;

BTree *newBTree();
void btree_insert(void *self, int value);
void btree_remove(void *self, int value);
int btree_contains(void *self, int value);
int btree_size(void *self);
void btree_print(void *self);
void btree_destroy(void *self);

BTreeNode *newBTreeNode(int value);
void btree_node_insert(void *self, int value);
void btree_node_remove(void *self, int value);
int btree_node_contains(void *self, int value);
int btree_node_size(void *self);
void btree_node_print(void *self);
void btree_node_destroy(void *self);





#define BTREE 0x00000002
#define BTREE_NODE 0x00000003

