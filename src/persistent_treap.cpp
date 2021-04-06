#include "persistent_treap.hpp"


namespace base {
using ptr_node = std::shared_ptr<Node>;

std::random_device rd;
std::mt19937 rand_number(rd());

int PersistentTreap::CntUpperSegments(int x, int y) {
    if (root.empty()) {
        return 0;
    }
  int idx =
      std::lower_bound(segments_info.begin(), segments_info.end(), x,
                       [](const std::pair<int, int> &a, const int b) {
                           return a.first < b;
                       }) -
      segments_info.begin();


  // std::cout << "Segments info:\n";
  // for (auto a: segments_info) {
  //     std::cout << a.first << ' ' << a.second << std::endl;
  // } std::cout << std::endl;

  std::cout << "idx " << idx << "  root size " << root.size() << std::endl;
  // std::cout << "Enter search " << y << " in treap\n";

  if (idx >= static_cast<int>(root.size())) {
      idx -= 1;
  }
  if (segments_info[idx].first > x) {
      idx -= 1;
  }

  return CntUpperSegments(root[idx], y);
}

int PersistentTreap::CntUpperSegments(ptr_node &node, int height) {
    if (node == nullptr) {
        return 0;
    }
    std::cout << "node size " << Size(node) << std::endl;
    std::cout << "node height " << node->height << std::endl;
    if (node->height == height) {
        return Size(node->right) + 1;
    }
    else if (node->height < height) {
        return CntUpperSegments(node->right, height);
    }
    else {
        return CntUpperSegments(node->left, height) + Size(node->right) + 1;
    }
}

void PersistentTreap::Insert(int height) {
  if (root.empty()) {
    root.push_back(std::shared_ptr<Node>(new Node(height)));
    return;
  }

  ptr_node left;
  ptr_node right;
  ptr_node new_node = std::shared_ptr<Node>(new Node(height));
  SplitHeight(root.back(), left, right, height);

  root.resize(root.size() + 1);
  ptr_node tmp;
  Merge(tmp, left, new_node);
  Merge(root.back(), tmp, right);
}

void PersistentTreap::Remove(int height) {
  if (root.empty()) {
    return;
  }

  ptr_node left;
  ptr_node right;
  ptr_node mid;
  SplitHeight(root.back(), left, right, height);
  SplitSize(right, mid, right, 1);

  root.resize(root.size() + 1);
  Merge(root.back(), left, right);
}

ptr_node PersistentTreap::CopyNode(ptr_node &prev) {
  if (prev == nullptr) {
    return nullptr;
  }

  ptr_node new_node = std::shared_ptr<Node>(new Node(*prev));
  return new_node;
}

int PersistentTreap::Size(const ptr_node &node) {
  if (node == nullptr) {
    return 0;
  }
  return node->size;
}

void PersistentTreap::UpdateNode(ptr_node &node) {
  if (node == nullptr) {
    return;
  }
  node->size = Size(node->left) + Size(node->right) + 1;
}

bool PersistentTreap::GoLeft(int left, int right) {
  return static_cast<int>(rand_number()) % (left + right) < left;
}

void PersistentTreap::Merge(ptr_node &node, ptr_node &left, ptr_node &right) {
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
  } else {
    node = CopyNode(right);
    Merge(node->left, left, right->left);
  }

  UpdateNode(node);
}

void PersistentTreap::SplitHeight(ptr_node &node, ptr_node &left,
                                  ptr_node &right, int key) {
  if (node == nullptr) {
    left = nullptr;
    right = nullptr;
    return;
  }

  if (node->height < key) {
    left = CopyNode(node);
    SplitHeight(node->right, left->right, right, key);
    UpdateNode(left);
  } else {
    right = CopyNode(node);
    SplitHeight(node->left, left, right->left, key);
    UpdateNode(right);
  }
}

void PersistentTreap::SplitSize(ptr_node &node, ptr_node &left, ptr_node &right,
                                int key) {
  if (node == nullptr) {
    left = nullptr;
    right = nullptr;
    return;
  }

  if (Size(node->left) + 1 <= key) {
    left = CopyNode(node);
    SplitSize(left->right, left->right, right, key - Size(node->left) - 1);
    UpdateNode(left);
  } else {
    right = CopyNode(node);
    SplitSize(right->left, left, right->left, key);
    UpdateNode(right);
  }
}

} // namespace base
