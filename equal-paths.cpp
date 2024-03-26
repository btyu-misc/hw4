#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int help(Node* root, int l) {
    if (root != NULL && root->left == NULL && root->right == NULL) return l + 1;
    if (root == NULL) return -1;
    int left = help(root->left, l+1);
    int right = help(root->right, l+1);

    if (left == right || left == -1 || right == -1) {
        if (left > right) return left;
        else return right;
    }
    return 0;
}

bool equalPaths(Node * root)
{
    // Add your code below
    return help(root, 0) != 0;
}

