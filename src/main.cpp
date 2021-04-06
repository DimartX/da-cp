#include "persistent_treap.hpp"
#include <iostream>
#include <limits>

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<base::Segment> segments(n + 1);
  segments.front() = {std::numeric_limits<int>::min(),
                     std::numeric_limits<int>::max(),
                     std::numeric_limits<int>::min()};

  std::vector<std::pair<int, int>> segments_info(n * 2 + 2);
  segments_info[0] = {segments.front().l, 0};
  segments_info[1] = {segments.front().r, 0};

  for (int i = 1; i < n + 1; i++) {
    std::cin >> segments[i].l >> segments[i].r >> segments[i].h;

    if (segments[i].l > segments[i].r) {
        std::swap(segments[i].l, segments[i].r);
    }

    segments_info[i * 2] = {segments[i].l, i};
    segments_info[i * 2 + 1] = {segments[i].r + 1, i}; // delete after point
  }

  std::sort(segments_info.begin(), segments_info.end());

  base::PersistentTreap tree(segments, segments_info);

  //int index = 0;

  for (const std::pair<int, int> &point : segments_info) {
    int segment_id = point.second;
    base::Segment current = segments[segment_id];
    std::cout << current.h << std::endl;
    if (current.l == point.first) {
        //std::cout << "Insert\n";
      tree.Insert(current.h);
    } else {
        //std::cout << "Remove " << current.h << "\n";
      tree.Remove(current.h);
    }

    //tree.print(index++);
  }

  std::cout << "Treap size: " << tree.Size() << std::endl;
  for (int i = 0; i < tree.Size(); i++) {
      std::cout << i << "-th version\n";
      tree.print(i);
  }
  

  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    std::cout << tree.CntUpperSegments(x, y) << std::endl;
  }
}
