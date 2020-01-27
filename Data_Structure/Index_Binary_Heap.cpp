#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

template <typename T>
class IndexBinaryHeap{
    private:
    int N, pq[1005], qp[1005];
    T key[1005];
    void swim(int p){
        while(p > 1 && key[pq[p/2]] > key[pq[p]]){
            swap(pq[p/2], pq[p]);
            swap(qp[pq[p/2]], qp[pq[p]]);
            p /= 2;
        }
    }
    void sink(int p){
        while(p*2 <= N){
            int new_p = p*2;
            if(new_p < N && key[pq[new_p+1]] < key[pq[new_p]]) ++new_p;
            if(key[pq[new_p]] < key[pq[p]]){
                swap(pq[new_p], pq[p]);
                swap(qp[pq[new_p]], qp[pq[p]]);
                p = new_p;
            }
            else break;
        }
    }
    public:
    IndexBinaryHeap(){
        N = 0;
        // pq = new int[MAXN];
        // qp = new int[MAXN];
        // key = new T[MAXN];
    }
    bool empty(){ return N == 0; }
    int size(){ return N; }
    bool contain(int k){ return qp[k] != 0; }
    T top(){ return key[pq[1]]; }
    void insert(int k, T val){
        key[k] = val;
        ++N;
        qp[k] = N;
        pq[N] = k;
        swim(N);
    }
    void change(int k, T val){
        T old_val = key[k];
        key[k] = val;
        if(val < old_val) swim(qp[k]);
        else sink(qp[k]);
    }
    T delTop(){//返回Val;
        T rt = key[pq[1]];
        //注意：对于key，永远只删除，不修改，要改就改索引！
        key[pq[1]] = 0;
        //可以用链表的思维，修改完值了以后才可以丢掉地址
        qp[pq[1]] = 0;
        qp[pq[N]] = 1;
        pq[1] = pq[N];
        pq[N] = 0;
        --N;
        sink(1);
        return rt;
    }
    void del(int k){
        key[k] = 0;
        //实在想不清楚了，就把“地址”都记下来，总不会出错！
        int heapOrder_k = qp[k], index_N = pq[N];
        pq[heapOrder_k] = index_N;
        pq[N] = 0;
        qp[index_N] = heapOrder_k;
        qp[k] = 0;
        --N;
        sink(k);
    }
    void prt(){
        for(int i = 1; i <= N; ++i){
            cout << key[pq[i]] << " ";
        }
        cout << endl;
    }
};


int main()
{
    IndexBinaryHeap<int> ibh;
    int n; cin >> n;
    for(int i = 0; i < n; ++i){
        int t; cin >> t;
        ibh.insert(i, t);
        ibh.prt();
    }
    ibh.change(2, 10);
    ibh.del(3);
    while(!ibh.empty()){
        cout << ibh.delTop() << " ";
    }
    system("pause");
    return 0;
}
