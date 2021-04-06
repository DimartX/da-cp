#pragma once
#include <vector>
#include <algorithm>
#include <memory>
#include <random>

namespace base {
std::random_device rd;
std::mt19937 rand_number(rd());

struct Segment {
    int l, r, h;
};

struct Node {
  Node() = delete;
  int size;
  int height;

  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;

  Node(int height_) { this->height = height_; }

  Node(Node &other) {
    this->size = other.size;
    this->height = other.height;

    *this->left = *other.left;
    *this->right = *other.right;
  }

  Node &operator=(Node &other) {
    this->size = other.size;
    this->height = other.height;

    *this->left = *other.left;
    *this->right = *other.right;
    return *this;
  }
};
using ptr_node = std::unique_ptr<Node>;

struct PersistentTreap {
private:


public:
    PersistentTreap() = delete;
    PersistentTreap(const std::vector<Segment>& segments_,
                    const std::vector<std::pair<int, std::vector<int>>>& segments_info_) {
        this->segments = segments_;
        this->segments_info = segments_info_;
    }

    void Insert(int height) {
        if (root.empty()) {
            root.push_back(std::make_unique<Node>(Node(height)));
            return;
        }

        ptr_node left;
        ptr_node right;
        ptr_node new_node = std::make_unique<Node>(new Node(height));
        SplitHeight(root.back(), left, right, height);

        root.resize(root.size() + 1);
        Merge(root.back(), left, new_node);
        Merge(root.back(), left, right);
    }

    void Remove(int height) {
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

    int CntUpperSegments(int x, int y) {

        return ;
    }

private:


    ptr_node CopyNode(ptr_node& prev);

    int Size(const ptr_node& node);

    void UpdateNode(ptr_node& node);

    bool GoLeft(int left, int right);

    void Merge(ptr_node& node, ptr_node& left, ptr_node& right);

    void SplitHeight(ptr_node& node, ptr_node& left, ptr_node& right, int key);

    void SplitSize(ptr_node& node, ptr_node& left, ptr_node& right, int key);

    std::vector<Segment> segments;
    std::vector<std::pair<int, std::vector<int>>> segments_info;
    std::vector<ptr_node> root;
};

} // namespace base
