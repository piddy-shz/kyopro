#include <vector>

struct union_find {
private :
    std::vector<int> v;

public :
    union_find(int n) noexcept : v(n, -1) { }

    int root(int i) noexcept {
        return v[i] < 0 ? i : v[i] = root(v[i]);
    }
    
    int size(int i) noexcept {
        return -v[root(i)];
    }

    bool is_united(int i, int j) noexcept {
        return root(i) == root(j);
    }

    void unite(int i, int j) noexcept {
        i = root(i); j = root(j);
        if (i == j) return;
        if (size(i) < size(j)) std::swap(i, j);
        v[i] += v[j];
        v[j] = i;
    }
};
