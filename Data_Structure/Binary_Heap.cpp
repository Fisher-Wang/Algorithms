#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

template <typename T>
class BinaryHeap{
    private:
    int N;
    T a[10005];
    void swim(int p){
        while(p > 1 && a[p] < a[p/2]){
            swap(a[p], a[p/2]);
            p /= 2;
        }
    }
    void sink(int p){
        while(2*p <= N){
            int t = 2*p;
            if(t < N && a[t+1] < a[t]) ++t;
            if(a[p] > a[t]) swap(a[p], a[t]);
            else break;
            p = t;
        }
    }

    public:
    BinaryHeap(){
        N = 0;
    }
    bool empty(){
        return N == 0;
    }
    int top(){
        return a[1];
    }
    void insert(int x){
        a[++N] = x;
        swim(N);
    }
    int pop(){
        T rt = a[1];
        a[1] = a[N];
        a[N--] = 0;
        sink(1);
        return rt;
    }
};

int main()
{
    BinaryHeap<int> bh;
    int n; cin >> n;
    for(int i = 1; i <= n; ++i){
        int t; cin >> t;
        bh.insert(t);
    }
    while(!bh.empty()){
        cout << bh.pop() << endl;
    }
    system("pause");
    return 0;
}
