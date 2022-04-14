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
    bool left_check = true;
    bool right_check = true;
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
    int left_check = 0;
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
            if (left == ".") {
                node_v[i]->left_check == false;
            }
            if (right == ".") {
                node_v[i]->right_check == false;
            }
            return;
        }
    }
}
string Tree::recursion(Node* curNode) {
    // 노드에게 left_child값이 있는지 확인
    cout << "recursion에 들어온 값: " << curNode->element << endl;
    // left,right child가 없는 애들은 못들어옴
    if (curNode->left_check) {
            k += curNode->left_child->element;
            cout << "left_k값 : " << k << endl;
            // left node를 읽었다고 check해주기
            Node* cur = curNode->left_child;
            if (cur->left_check) {
                cur->left_check = false; // 현재 노드의 left노드는 이제 불어올거니 이젠 안읽어도 됌
                return recursion(cur->left_child);
            }
        }
    if (curNode->right_check) {
        k += curNode->right_child->element;
        cout << "right_k값 : " << k << endl;
        Node* cur = curNode->right_child;
        if (cur->right_child) {
            cur->right_check = false;
            return recursion(cur->right_child);
        }
    }
    else {
        // 그냥 leaf node 라면
        if(curNode->element)
    }
    k += curNode->element;
    if (curNode->element == "F") {
        return k;
    }
    cout << "leaf node" << endl;
        // leaf node에서 right_child가 존재하는 부모노드로 올라가는 법만 더하면 됌
        // leaf node의 부모노드로 한칸 올라가서 확인 없으면(else) 또 확인
    return recursion(curNode->parent);
    
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