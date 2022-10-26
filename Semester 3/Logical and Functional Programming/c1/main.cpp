#include <iostream>

struct Node {
    int val;
    Node *next;
};

bool arec(Node* node, Node* nx = nullptr) {
    if (node == nullptr) return true;
    if (nx == nullptr) return true;
    else {
        if (node->val == nx->val) {
            return false;
        }
        if (!arec(node, nx->next)) {
            return false;
        }
    }
    return arec(node->next, node->next->next);
}
//// 1 2 3 4 2 2 4 5 5
//// 5
int brec(Node* node, Node* nx = nullptr) {
    if (node->next == nullptr) return 1;
    if (nx == nullptr) return brec(node->next, node->next->next)+1;
    else {
        if (node->val == nx->val) {
            return brec(node->next, node->next->next)+0;
        }
        return brec(node, nx->next);
    }
}

int main()
{
    Node* root = new Node;
    Node* l = root;
    l->val = 1;
    l->next = new Node;
    l = l->next;
    l->val = 2;
    l->next = new Node;
    l = l->next;
    l->val = 2;
    l->next = new Node;
    l = l->next;
    l->val = 1;
    l->next = nullptr;
    std::cout << brec(root, root->next);

}
