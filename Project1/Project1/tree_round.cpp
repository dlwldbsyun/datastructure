/*���� ����
 Ʈ���� �Է¹޾� ���� ��ȸ(preorder traversal), ���� ��ȸ(inorder traversal), 
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
    vector<Node*> node_v; // ��� ��带 ������ ����

    Tree(string); // ��Ʈ��� ����
    void insert(string, string, string); // �θ���, left�ڽ�, right�ڽ�
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
    // ��ü ��� ��ȸ�ϸ鼭 parent_dataã��
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