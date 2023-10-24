#include <vector>

template<class F, typename T>
struct segtree {
private :
    int n, last_referenced;
    std::vector<T> v;
    F f;
    T e, buffer;

void update() noexcept {
    v[last_referenced] = buffer;
    while (last_referenced >>= 1) {
        v[last_referenced] = f(v[last_referenced << 1], v[last_referenced << 1 | 1]);
    }
}

public :
    segtree(F f_, T e_) noexcept : f(f_), e(e_), buffer(e_) { }

    template<class Iterator>
    void build(Iterator first, Iterator last) noexcept {
        n = last - first;
        last_referenced = 0;
        v.resize(n * 2, e);
        for (int i = 0; i < n; i++) v[i + n] = *(first++);
        for (int i = n - 1; i; i--) v[i] = f(v[i << 1], v[i << 1 | 1]);
    }

    T& operator[](int i) noexcept {
        update();
        return buffer = v[last_referenced = i + n];
    }

    T fold(int l, int r) noexcept {
        update();
        l += n; r += n;
        T res_l = e, res_r = e;
        while (l < r) {
            if (l & 1) res_l = f(res_l, v[l++]);
            if (r & 1) res_r = f(v[--r], res_r);
            l >>= 1; r >>= 1;
        }
        return f(res_l, res_r);
    }
};
