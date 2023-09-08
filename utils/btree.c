#include "./btree.h"
#include "./macros.h"
#include "./logging.h"
#include <stdlib.h>

#pragma region find_and_pop_lowest_value

int find_and_pop_lowest_value(BSTreeNode *node, BSTreeNode *parent) {
    BSTreeNode *currentNode = node;
    BSTreeNode *prevNode = parent;

    while (1) {
        if (currentNode->left == NULL) {
            // we dont need to get into the whole removal process here
            // because if we've gotten here we already know that the
            // only possibilities are that either there are no child nodes
            // or only on the right, moving the pointer from the right to
            // the parent would work here, as it would either be a NULL,
            // which we would've done anyways, or the right node which is
            // something we want to preserve.

            // this is a special case for if we get in the loop and within one iteration we have to leave.
            // this only works the way it does because i know how im using this. unauthorized api usage might
            // might have ub, but idc for now.
            if (prevNode->right != NULL && prevNode->right->value == currentNode->value) {
                int val = currentNode->value;
                free(currentNode);
                prevNode->right = currentNode->right;
                return val;
            }
            prevNode->left = currentNode->right;
            int v = currentNode->value;
            free(currentNode);
            return v;
        }
        prevNode = currentNode;
        currentNode = currentNode->left;
    }
}

#pragma endregion

#pragma region premade vtables

BSTreeNodeVtable bstree_node_vtable = {
    .insert = bstree_node_insert,
    .remove = bstree_node_remove,
    .contains = bstree_node_contains,
    .size = bstree_node_size,
    .destroy = bstree_node_destroy,
    .empty = bstree_node_empty,
    .sorted = bstree_node_sorted
};

BSTreeVtable bstree_vtable = {
    .insert = bstree_insert,
    .remove = bstree_remove,
    .contains = bstree_contains,
    .size = bstree_size,
    .destroy = bstree_destroy,
    .sorted = bstree_sorted
};

#pragma endregion

#pragma region BSTree

BSTree* newBSTree() {
    BSTree* self = malloc(sizeof(BSTree));
    self->__type__ = BSTREE;
    self->root = NULL;
    self->vtable = &bstree_vtable;
    return self;
}

void bstree_insert(void *_self, int value) {
    FLASH_V(_self, self, BSTree, BSTREE)

    if (self->root == NULL) {
        self->root = newBSTreeNode(value);
        return;
    }
    self->root->vtable->insert(self->root, value);
    
}

void bstree_remove(void *_self, int value) {
    FLASH_V(_self, self, BSTree, BSTREE)

    if (self->root == NULL) {
        INFO("Tried to remove %d from an empty btree", value);
        return;
    }

    if (self->root->vtable->empty(self->root) && self->root->value == value) {
        self->root->vtable->destroy(self->root);
        self->root = NULL;
        return;
    } 
    if (self->root->value == value) {
        if (self->root->right == NULL) {
            BSTreeNode *next = self->root->left;
            free(self->root);
            self->root = next;
        } else if (self->root->left == NULL) {
            BSTreeNode *next = self->root->right;
            free(self->root);
            self->root = next;
        } else {
            // assume both nodes exist
            if (self->root->right->left == NULL) {
                self->root->value = self->root->right->value;
                BSTreeNode *drop = self->root->right;
                self->root->right = self->root->right->right;
                free(drop);
            }
            int lval = find_and_pop_lowest_value(self->root->right->left, self->root->right);
            self->root->value = lval; // this might be entirely wrong but i think this works correctly

        }
        return;
    }
    self->root->vtable->remove(self->root, value);

}

int bstree_contains(void *_self, int value) {
    FLASH(_self, self, BSTree, BSTREE)

    if (self->root == NULL) {
        return 0;
    }
    if (self->root->value == value) {
        return 1;
    }
    return self->root->vtable->contains(self->root, value);

}

int bstree_size(void *_self) {
    FLASH(_self, self, BSTree, BSTREE)

    if (self->root == NULL) {
        return 0;
    }
    if (self->root->vtable->empty(self->root)) {
        DEBUG("root EMPTY when checking size!")
        return 1;
    }
    return self->root->vtable->size(self->root);
}

void bstree_print(void *_self) {
    // this (will) use the btree printer found on geeksforgeeks as
    // inspiration
    ERROR("bstree_print not implemented");
}

void bstree_destroy(void *_self) {
    FLASH_V(_self, self, BSTree, BSTREE)

    if (!(self->root == NULL)) {
        self->root->vtable->destroy(self->root);
    }
    free(self);
    return;
}

int bstree_sorted(void *_self) {
    FLASH(_self, self, BSTree, BSTREE)

    if (!(self->root == NULL)) {
        return self->root->vtable->sorted(self->root);
    }
    return -2;
}


#pragma endregion

#pragma region BSTreeNode

BSTreeNode *newBSTreeNode(int value) {
    BSTreeNode *self = malloc(sizeof(BSTreeNode));
    self->__type__ = BSTREE_NODE;
    self->value = value;
    self->left = NULL;
    self->right = NULL;
    self->vtable = &bstree_node_vtable;
    return self;
}

void bstree_node_insert(void *_self, int value) {
    FLASH_V(_self, self, BSTreeNode, BSTREE_NODE)

    if (value == self->value) {
        return; // binary trees do not allow duplicates
    }
    if (value < self->value) {
        if (self->left == NULL) {
            self->left = newBSTreeNode(value);
        } else {
            FLASH_V(self->left, lnode, BSTreeNode, BSTREE_NODE)
            lnode->vtable->insert(lnode, value);
        }
        return;
    }
    if (value > self->value) {
        if (self->right == NULL) {
            self->right = newBSTreeNode(value);
        } else {
            FLASH_V(self->right, rnode, BSTreeNode, BSTREE_NODE)
            rnode->vtable->insert(rnode, value);
        }
        return;
    }
    FATAL("how did we get here? (default case in bstree_node_insert)");
    exit(1);
}

void bstree_node_remove(void *_self, int value) {

    FLASH_V(_self, self, BSTreeNode, BSTREE_NODE)
    
    if (value == self->value) {
        ERROR("we shouldn't be here! this shouldve been caught by our"
              "parent node!")
    }

    if (!(self->left == NULL)) {
        if (self->left->value == value) {
            if (self->left->right == NULL) {
                BSTreeNode *next = self->left->left;
                free(self->left);
                self->left = next;
            } else if (self->left->left == NULL) {
                BSTreeNode *next = self->left->right;
                free(self->left);
                self->left = next;
            } else {
                // assume both nodes exist
                if (self->left->right->left == NULL) {
                    self->left->value = self->left->right->value;
                    BSTreeNode *drop = self->left->right;
                    self->left->right = self->left->right->right;
                    free(drop);
                }
                int lval = find_and_pop_lowest_value(self->left->right->left, self->left->right);
                self->left->value = lval; // this might be entirely wrong but i think this works correctly

            }   
            return;
     
        } 
        if (value < self->value) {
            self->left->vtable->remove(self->left, value);
            return;
        }
    } 
    if (!(self->right == NULL)) {
        if (self->right->value == value) {
            if (self->right->right == NULL) {
                BSTreeNode *next = self->right->left;
                free(self->right);
                self->right = next;
            } else if (self->right->left == NULL) {
                BSTreeNode *next = self->right->right;
                free(self->right);
                self->right = next;
            } else {
                // assume both nodes exist
                if (self->right->right->left == NULL) {
                    self->right->value = self->right->right->value;
                    BSTreeNode *drop = self->right->right;
                    self->right->right = self->right->right->right;
                    free(drop);
                }
                int lval = find_and_pop_lowest_value(self->right->right->left, self->right->right);
                self->right->value = lval; // this might be entirely wrong but i think this works correctly

            }      
            return;  
        }
        if (value > self->value) {
            self->right->vtable->remove(self->right, value);
            return;
        }
    }
    INFO("%d did not exist in bstree!", value)
    
    return;
}

int bstree_node_contains(void *_self, int value) {
    FLASH(_self, self, BSTreeNode, BSTREE_NODE)

    int has = 0;
    if (self->value == value) {
        return 1;
    }
    if (!(self->left == NULL)) {
        has += self->left->vtable->contains(self->left, value);
    }
    if (!(self->right == NULL)) {
        has += self->right->vtable->contains(self->right, value);
    }
    if (has == 2) {
        ERROR("what (bstree_node_contains::has == 2)");
    }
    return has; 

}

int bstree_node_size(void *_self) {
    FLASH(_self, self, BSTreeNode, BSTREE_NODE)

    int len = 1;

    if (!(self->left == NULL)) {
        len += self->left->vtable->size(self->left);
    }
    if (!(self->right == NULL)) {
        len += self->right->vtable->size(self->right);
    }

    return len;
}

void bstree_node_destroy(void *_self) {
    FLASH_V(_self, self, BSTreeNode, BSTREE_NODE)

    if (!(self->left == NULL)) {
        self->left->vtable->destroy(self->left);
    }
    if (!(self->right == NULL)) {
        self->right->vtable->destroy(self->right);
    }
    free(self);

}

int bstree_node_empty(void *_self) {
    FLASH(_self, self, BSTreeNode, BSTREE_NODE)

    if (!(self->left == NULL) || !(self->right == NULL)) {
        return 0;
    }
    return 1;
}

int bstree_node_sorted(void *_self) {
    FLASH(_self, self, BSTreeNode, BSTREE_NODE)

    int sorted = 0;

    if (!(self->left == NULL)) {
        if (self->left->value > self->value) {
            DEBUG("!! UNSORTED, %d LEFT OF %d", self->left->value, self->value)
            return 0;
        }
        if (self->left->vtable->sorted(self->left) == 0) {
            return 0;
        }
    }
    if (!(self->right == NULL)) {
        if (self->right->value < self->value) {
            DEBUG("!! UNSORTED, %d RIGHT OF %d", self->right->value, self->value)
            return 0;
        }
        if (self->right->vtable->sorted(self->right) == 0) {
            return 0;
        }
    }


    return 1;
}

#pragma endregion