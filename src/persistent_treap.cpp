#include "persistent_treap.hpp"

namespace base {
using ptr_node = std::unique_ptr<Node>;

ptr_node PersistentTreap::CopyNode(ptr_node& prev) {
    if (prev == nullptr) {
        return nullptr;
    }

    ptr_node new_node = std::make_unique<Node>(new Node(*prev));
    return new_node;
}

int Size(const ptr_node& node) {
    if (node == nullptr) {
        return 0;
    }
    return node->size;
}


void UpdateNode(ptr_node& node) {
    if (node == nullptr) {
        return;
    }
    node->size = Size(node->left) + Size(node->right) + 1;
}

bool GoLeft(int left, int right) {
    return static_cast<int>(rand_number()) % (left + right) < left;
}

void Merge(ptr_node& node, ptr_node& left, ptr_node& right) {
    if (left == nullptr) {
        node = CopyNode(right);
        return;
    }
    if (right == nullptr) {
        node = CopyNode(left);
        return;
    }

    if (GoLeft(Size(left), Size(right))) {
        node = CopyNode(left);
        Merge(node->right, left->right, right);
    }
    else {
        node = CopyNode(right);
        Merge(node->left, left, right->left);
    }

    UpdateNode(node);
}

void SplitHeight(ptr_node& node, ptr_node& left, ptr_node& right, int key) {
    if (node == nullptr) {
        left = nullptr;
        right = nullptr;
        return;
    }

    if (node->height <= key) {
        left = CopyNode(node);
        SplitHeight(node->right, left->right, right, key);
        UpdateNode(left);
    }
    else {
        right = CopyNode(node);
        SplitHeight(node->left, left, right->left, key);
        UpdateNode(right);
    }
}

void SplitSize(ptr_node& node, ptr_node& left, ptr_node& right, int key) {
    if (node == nullptr) {
        left = nullptr;
        right = nullptr;
        return;
    }

    if (Size(node->left) + 1 <= key) {
        left = CopyNode(node);
        SplitSize(node->right, left->right, right, key - Size(node->left) - 1);
        UpdateNode(left);
    }
    else {
        right = CopyNode(node);
        SplitSize(node->left, left, right->left, key );
        UpdateNode(right);
    }
}

} // namespace base
