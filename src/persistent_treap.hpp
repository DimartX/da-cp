#pragma once
#include <algorithm>
#include <memory>
#include <random>
#include <vector>


#include <iostream>

namespace base {

// структура для отрезков
struct Segment {
  int l, r, h;
};

//структура для узлов декартова дерева
struct Node {
  int size;
  int height;

  std::shared_ptr<Node> left;
  std::shared_ptr<Node> right;

public:
  Node() = delete;
  Node(const int height_)
      : size(1), height(height_), left(nullptr), right(nullptr) {}

  Node(const Node &other) {
    this->size = other.size;
    this->height = other.height;

    if (other.left != nullptr) {
      this->left = other.left;
    }
    if (other.right != nullptr) {
      this->right = other.right;
    }
  }

  Node &operator=(const Node &other) {
    this->size = other.size;
    this->height = other.height;

    if (other.left != nullptr) {
      *this->left = *other.left;
    }
    if (other.right != nullptr) {
      *this->right = *other.right;
    }
    return *this;
  }
};

using ptr_node = std::shared_ptr<Node>;

// структура декартова дерева
struct PersistentTreap {
  PersistentTreap() = delete;
  PersistentTreap(const std::vector<Segment> &segments_,
                  const std::vector<std::pair<int, int>> &segments_info_) {
    this->segments = segments_;
    this->segments_info = segments_info_;
  }

  void Insert(int height);
  void Remove(int height);
  int CntUpperSegments(int x, int y);
  int Size() { return root.size(); }

  void print(int ver) {
    if (ver > static_cast<int>(root.size()) - 1) {
      ver = root.size() - 1;
    }
    print(root[ver]);
    std::cout << std::endl;
  }

  void print(ptr_node& node) {
    if (node == nullptr) {
      return;
    }
    print(node->left);
    std::cout << node->height << " ";
    print(node->right);
  }

private:
  ptr_node CopyNode(ptr_node &prev);
  int Size(const ptr_node &node);
  void UpdateNode(ptr_node &node);
  bool GoLeft(int left, int right);
  void Merge(ptr_node &node, ptr_node &left, ptr_node &right);
  void SplitHeight(ptr_node &node, ptr_node &left, ptr_node &right, int key);
  void SplitSize(ptr_node &node, ptr_node &left, ptr_node &right, int key);
  int CntUpperSegments(ptr_node &node, int y);

  std::vector<Segment> segments;
  std::vector<std::pair<int, int>> segments_info;
  std::vector<ptr_node> root;
};

} // namespace base
