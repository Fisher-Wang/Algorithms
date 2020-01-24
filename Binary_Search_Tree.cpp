#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

struct Node{
    int val, ct;
    Node *left, *right;
    Node(int v = -1):val(v), ct(1), left(NULL), right(NULL){}
};
Node* root = NULL;

int size(Node* p){
    if(p == NULL) return 0;
    else return p->ct;
}

void put(int v, Node*& p){//注意：但凡修改Node*本身（而非仅仅访问），必须加引用
    if(p == NULL){
        p = new Node(v);
        return;
    }
    if(v < p->val) put(v, p->left);
    else if(v > p->val) put(v, p->right);
    p->ct = size(p->left) + 1 + size(p->right);//我们之所以用递归，就是因为它在回溯的过程中自动提供了路径，无需人为记录，比较方便
}

int myrank(int v, Node* p){
    if(p == NULL){
        cout << "error in rank: not exist" << endl;
        return -1000;
    }
    if(v == p->val) return size(p->left);
    else if(v < p->val) return myrank(v, p->left);
    else return size(p->left) + 1 + myrank(v, p->right);
}

Node* select(int r, Node* p){
    int tmp = size(p->left);
    if(r == tmp) return p;
    else if(r < tmp) return select(r, p->left);
    else return select(r-tmp-1, p->right);
}

void prt(Node* p){
    if(p->left != NULL) prt(p->left);
    cout << p->val <<" " << p->ct << endl;
    if(p->right != NULL) prt(p->right);
}

Node* findMin(Node* p){
    if(p == NULL) return NULL;
    Node* u = p;
    while(u->left != NULL) u = u->left;
    return u;
}

Node* removeMin(Node* p){
    if(p == NULL){
        cout << "error in removeMin: empty tree" << endl;
        return NULL;
    }
    if(p->left != NULL){
        p->left = removeMin(p->left);
        p->ct = size(p->left) + 1 + size(p->right);
        return p;
    }
    else{
        /*【1】这是错误的
        Node* tmp = p;
        delete p;           //delete p是删除p对应地址下记录的值，即使用tmp记下了p的地址也没用
        return tmp->right;*/
        /*【2】这也是错误的
        delete p;
        return NULL;        //应该返回右子树
        */
        Node* tmp = p->right;
        delete p;
        return tmp;
    }
}

Node* remove(int v, Node* p){
    if(p == NULL){
        cout << "error in remove: empty tree / not exist" <<endl;
        return NULL;
    }
    if(v < p->val) p->left = remove(v, p->left);
    else if(v > p->val) p->right = remove(v, p->right);
    else{
        if(p->left == NULL){
            Node* tmp = p->right;
            delete p;
            return tmp;
        }
        else if(p->right == NULL){
            Node* tmp = p->left;
            delete p;
            return tmp;
        }
        else{
            Node* u = findMin(p->right);
            p->val = u->val;
            removeMin(p->right);
        }
    }
    p->ct = size(p->left) + 1 + size(p->right);
    return p;
}

//仅用于测试，与二叉树实现无关
int main()
{
    int n; cin >> n;
    int t;
    for(int i = 0; i < n; ++i){
        cin >> t;
        put(t, root);
    }
    remove(5, root); prt(root);
    for(int i = 0; i < 9; ++i) cout << select(i, root)->val << endl;
    
    system("pause");
    return 0;
}