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
    vector<Node*> node_v; // ��� ��带 ������ ����
    string k = "";
    int left_check = 0;
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
    // ��忡�� left_child���� �ִ��� Ȯ��
    cout << "recursion�� ���� ��: " << curNode->element << endl;
    // left,right child�� ���� �ֵ��� ������
    if (curNode->left_check) {
            k += curNode->left_child->element;
            cout << "left_k�� : " << k << endl;
            // left node�� �о��ٰ� check���ֱ�
            Node* cur = curNode->left_child;
            if (cur->left_check) {
                cur->left_check = false; // ���� ����� left���� ���� �Ҿ�ðŴ� ���� ���о ��
                return recursion(cur->left_child);
            }
        }
    if (curNode->right_check) {
        k += curNode->right_child->element;
        cout << "right_k�� : " << k << endl;
        Node* cur = curNode->right_child;
        if (cur->right_child) {
            cur->right_check = false;
            return recursion(cur->right_child);
        }
    }
    else {
        // �׳� leaf node ���
        if(curNode->element)
    }
    k += curNode->element;
    if (curNode->element == "F") {
        return k;
    }
    cout << "leaf node" << endl;
        // leaf node���� right_child�� �����ϴ� �θ���� �ö󰡴� ���� ���ϸ� ��
        // leaf node�� �θ���� ��ĭ �ö󰡼� Ȯ�� ������(else) �� Ȯ��
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