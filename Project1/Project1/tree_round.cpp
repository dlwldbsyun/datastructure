/*���� ����
 ���� Ʈ���� �Է¹޾� ���� ��ȸ(preorder traversal), ���� ��ȸ(inorder traversal), 
 ���� ��ȸ(postorder traversal)�� ����� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.

 �Է�   ù° �ٿ��� ���� Ʈ���� ����� ���� N(1 �� N �� 26)�� �־�����. 
        ��° �ٺ��� N���� �ٿ� ���� �� ���� ���� ���� �ڽ� ���, ������ �ڽ� ��尡 �־�����. 
        ����� �̸��� A���� ���ʴ�� ���ĺ� �빮�ڷ� �Ű�����, �׻� A�� ��Ʈ ��尡 �ȴ�. 
        �ڽ� ��尡 ���� ��쿡�� .���� ǥ���Ѵ�.

 ���     ù° �ٿ� ���� ��ȸ, ��° �ٿ� ���� ��ȸ, ��° �ٿ� ���� ��ȸ�� ����� ����Ѵ�. 
          �� �ٿ� N���� ���ĺ��� ���� ���� ����ϸ� �ȴ�.

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
    vector<Node*> node_v; // ��� ��带 ������ ����
    string k = "";
public:
    Tree(string); // ��Ʈ��� ����
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
    //��ȸ�ϸ鼭 �ڽĳ�尡 �ִ��� Ȯ��
    for (int i = 0; i < node_v.size(); i++) {
        if (node_v[i]->element == left || node_v[i]->element == right) {
            cout << "�����ϴ� �ڽĳ���� ���Դϴ�." << endl;
            return;
        }
    }
    //��ȸ�ϸ鼭 ���س�尡 �ִ��� Ȯ��
    for (int i = 0; i < node_v.size(); i++) {
        if (node_v[i]->element == standard) { // ���� ��尡 �ִٸ�
            // leftȮ��
            cout << "find standard node" << endl;
            Node* curNode = node_v[i];
            if (left != ".") {
                // left ��尡 .�� �ƴ϶�� ���ο� ��带 ����
                Node* v = new Node(left);
                // left���� standard��带 ����
                v->parent = curNode;
                curNode->left_child = v;
                // ��ü Ʈ�� ����ҿ� v(left)�߰�
                node_v.push_back(v);
                cout << "insert left" << endl;
            }
            // right Ȯ��
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
    // ��忡�� left_child���� �ִ��� Ȯ��
    cout << "recursion�� ���� ��: " << curNode->element << endl;
    if (curNode->left_child) {
        k += curNode->left_child->element;
        cout << "left_k�� : " << k << endl;
        Node* cur = curNode->left_child;
        if (cur->left_child) {
            return recursion(cur->left_child);
        }
    }
    else if (curNode->right_child) {
        k += curNode->right_child->element;
        cout << "right_k�� : " << k << endl;
        Node* cur = curNode->right_child;
        if (cur->right_child) {
            return recursion(cur->right_child);
        }
    }
    else {
        k += curNode->element;
        // leaf node���� right_child�� �����ϴ� �θ���� �ö󰡴� ���� ���ϸ� ��
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