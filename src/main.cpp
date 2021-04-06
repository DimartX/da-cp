#include <iostream>
#include "persistent_treap.hpp"


int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<Segment> segments(n);


    using vec_i_v = std::vector<std::pair<int, std::vector<int>>>;
    vec_i_v segments_info(n * 2);

    for (int i = 0; i < n; i++) {
        std::cin >> segments[i].l >> segments[i].r >> segments[i].h;

        segments_info[i * 2].first = segments[i].l;
        segments_info[i * 2].second.push_back(i);
        segments_info[i * 2 + 1].first = segments[i].r + 1; // delete after point
        segments_info[i * 2 + 1].second.push_back(i);
    }

    std::sort(segments_info.begin(), segments_info.end());

    PersistentTreap tree(segments, segments_info);

    for (const std::pair<int, std::vector<int>>& point: segments_info) {
        for (const int segment_id: point.second) {
            Segment current = segments[segment_id];
            if (current.l == point.first) {
                tree.Insert(current.h);
            }
            else {
                tree.Remove(current.h);
            }
        }
    }

    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        std::cout << tree.CntUpperSegments(x, y);
    }
}
