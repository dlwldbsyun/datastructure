/*문제 설명
 이진 트리를 입력받아 전위 순회(preorder traversal), 중위 순회(inorder traversal), 
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
    Node* left_child;
    Node* right_child;
public:
    Node(string s) {
        this->element = s;
        this->parent = nullptr;
    }

    friend class Tree;
};

class Tree {
private:
    Node* root;
    vector<Node*> node_v; // 모든 노드를 저장할 벡터
    string k = "";
public:
    Tree(string); // 루트노드 설정
    void insert(string, string, string);
    string recursion(Node*);
    void printPre();
};

Tree::Tree(string r) {
    Node* node = new Node(r);
    this->root = node;
    this->node_v.push_back(node);
}
void Tree::insert(string standard, string left, string right) {
    //순회하면서 자식노드가 있는지 확인
    for (int i = 0; i < node_v.size(); i++) {
        if (node_v[i]->element == left || node_v[i]->element == right) {
            cout << "존재하는 자식노드의 값입니다." << endl;
            return;
        }
    }
    //순회하면서 기준노드가 있는지 확인
    for (int i = 0; i < node_v.size(); i++) {
        if (node_v[i]->element == standard) { // 기준 노드가 있다면
            // left확인
            cout << "find standard node" << endl;
            Node* curNode = node_v[i];
            if (left != ".") {
                // left 노드가 .이 아니라면 새로운 노드를 만들어서
                Node* v = new Node(left);
                // left노드와 standard노드를 연결
                v->parent = curNode;
                curNode->left_child = v;
                // 전체 트리 저장소에 v(left)추가
                node_v.push_back(v);
                cout << "insert left" << endl;
            }
            // right 확인
            if (right != ".") {
                Node* u = new Node(right);
                u->parent = curNode;
                curNode->right_child = u;
                node_v.push_back(u);
                cout << "insert right" << endl;
            }
            return;
        }
    }
}
string Tree::recursion(Node* curNode) {
    // 노드에게 left_child값이 있는지 확인
    cout << "recursion에 들어온 값: " << curNode->element << endl;
    if (curNode->left_child) {
        k += curNode->left_child->element;
        cout << "left_k값 : " << k << endl;
        Node* cur = curNode->left_child;
        if (cur->left_child) {
            return recursion(cur->left_child);
        }
    }
    else if (curNode->right_child) {
        k += curNode->right_child->element;
        cout << "right_k값 : " << k << endl;
        Node* cur = curNode->right_child;
        if (cur->right_child) {
            return recursion(cur->right_child);
        }
    }
    else {
        k += curNode->element;
        // leaf node에서 right_child가 존재하는 부모노드로 올라가는 법만 더하면 됌
        return recursion(curNode->parent->right_child);
    }
    return k;
}
void Tree::printPre() {
    // pre-order
    string result = "A";
    result += recursion(root);
    cout << result << endl;
}

int main() {
    int N;
    cin >> N;
    Tree t("A");
    for (int i = 0; i < N; i++) {
        string cur, l, r;
        cin >> cur >> l >> r;
        t.insert(cur, l, r);
    }
    t.printPre();
    return 0;
}