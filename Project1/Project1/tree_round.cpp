/*문제 설명
 트리를 입력받아 전위 순회(preorder traversal), 중위 순회(inorder traversal), 
 후위 순회(postorder traversal)한 결과를 출력하는 프로그램을 작성하시오.

 입력   첫째 줄에는 이진 트리의 노드의 개수 N(1 ≤ N ≤ 26)이 주어진다. 
        둘째 줄부터 N개의 줄에 걸쳐 각 노드와 그의 왼쪽 자식 노드, 오른쪽 자식 노드가 주어진다. 
        노드의 이름은 A부터 차례대로 알파벳 대문자로 매겨지며, 항상 A가 루트 노드가 된다. 
        자식 노드가 없는 경우에는 .으로 표현한다.

 출력     첫째 줄에 전위 순회, 둘째 줄에 중위 순회, 셋째 줄에 후위 순회한 결과를 출력한다. 
          각 줄에 N개의 알파벳을 공백 없이 출력하면 된다.

 input
 7
 A B C
 B D .
 C E F
 E . .
 F . G
 D . .
 G . .

 output
 ABDCEFG
 DBAECFG
 DBEGFCA
*/ 

#include <iostream>
#include <vector>
using namespace std;

class Node {
private:
    string element;
    Node* parent;
    vector<Node*> child_v;
public:
    Node(string s) {
        this->element = s;
        this->parent = nullptr;
    }

    friend class Tree;
};

class Tree {
public:
    Node* root;
    vector<Node*> node_v; // 모든 노드를 저장할 벡터

    Tree(string); // 루트노드 설정
    void insert(string, string, string); // 부모노드, left자식, right자식
    void preorder(Node*);
    void postorder(Node*);
    // void inorder(Node*);
};

Tree::Tree(string r) {
    Node* node = new Node(r);
    this->root = node;
    this->node_v.push_back(node);
}
void Tree::insert(string parent_elem, string left_elem, string right_elem) {
    // 전체 노드 순회하면서 parent_data찾기
    for (int i = 0; i < node_v.size(); i++) {
        if (node_v[i]->element == parent_elem) {
            if (left_elem == ".") { 
                if (right_elem != ".") {
                    Node* node_r = new Node(right_elem);
                    node_r->parent = node_v[i];
                    node_v[i]->child_v.push_back(node_r);
                    node_v.push_back(node_r);
                    continue;
                }
                continue;
            }
            else if (right_elem == ".") { 
                Node* node_l = new Node(left_elem);
                node_l->parent = node_v[i];
                node_v[i]->child_v.push_back(node_l);
                node_v.push_back(node_l);
                continue; 
            }
            Node* node_l = new Node(left_elem);
            node_l->parent = node_v[i];
            node_v[i]->child_v.push_back(node_l);
            node_v.push_back(node_l);
            Node* node_r = new Node(right_elem);
            node_r->parent = node_v[i];
            node_v[i]->child_v.push_back(node_r);
            node_v.push_back(node_r);
            return;
        }
    }
}
void Tree::preorder(Node* node) {
    if (!node)return;
    cout << node->element << " ";
    for (int i = 0; i < node->child_v.size(); i++) {
        preorder(node->child_v[i]);
    }
    cout << endl;
}
void Tree::postorder(Node* node) {
    if (!node)return;
    for (int i = 0; i < node->child_v.size(); i++) {
        postorder(node->child_v[i]);
    }
    cout << node->element << " ";
}
int main() {
    int N;
    cin >> N;
    Tree t("a");
    for (int i = 0; i < N; i++) {
        string cur, l, r;
        cin >> cur >> l >> r;
        t.insert(cur, l, r);
    }
    cout << "preorder" << endl;
    t.preorder(t.node_v[0]);
    t.postorder(t.node_v[0]);
    return 0;
}