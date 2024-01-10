#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* insert(struct TreeNode* root, int value) {
    if (root == NULL) {
        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

int sum_nodes(struct TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->value + sum_nodes(node->left) + sum_nodes(node->right);
}

void replace(struct TreeNode* node) {
    if (node == NULL) {
        return;
    }
    int left_sum = sum_nodes(node->left);
    int right_sum = sum_nodes(node->right);
    replace(node->left);
    replace(node->right);
    node->value = left_sum + right_sum;
}

void print_tree1(struct TreeNode* node, int space) {
    if (node == NULL) {
        return;
    }
    space += 5;
    print_tree1(node->right, space);
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", node->value);
    print_tree1(node->left, space);
}

void print_tree(struct TreeNode* node) {
    print_tree1(node, 0);
}

int main() {
    int values[] = {2, 5, 7, 8, 11, 1, 4, 2, 3, 7};
    int n = sizeof(values) / sizeof(values[0]);
    struct TreeNode* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }
    printf("Initial binary tree:\n");
    print_tree(root);
    replace(root);
    printf("Binary tree after replacement:\n");
    print_tree(root);
    return 0;
}
