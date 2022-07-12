#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
    this->relation = r;
    this->root = nullptr;
    this->_size = 0;
}

void SortedBag::add(TComp e) {
    if (this->root == nullptr) {
        this->root = new Node;
        this->root->info = e;
        this->root->left = nullptr;
        this->root->right = nullptr;
        ++this->_size;
    } else {
        Node *prev = this->root;
        Node *current = this->root;
        bool dir; // true = right, false = left
        while (current != nullptr) {
            if (this->relation(e, current->info)) {
                // left
                dir = false;
                prev = current;
                current = current->left;
            } else {
                // right
                dir = true;
                prev = current;
                current = current->right;
            }
        }
        current = new Node;
        current->info = e;
        current->right = nullptr;
        current->left = nullptr;
        if (dir) {
            prev->right = current;
        } else {
            prev->left = current;
        }
        ++this->_size;
    }
}


bool SortedBag::remove(TComp e) {
    if (this->root == nullptr) {
        return false;
    }

    Node *curr = this->root;
    Node *prev = nullptr;

    while (curr != nullptr && curr->info != e) {
        prev = curr;
        if (this->relation(e, curr->info))
            curr = curr->left;
        else
            curr = curr->right;
    }

    if (curr == nullptr) {
        return false;
    }

    if (curr->left == nullptr || curr->right == nullptr) {
        Node *newCurr;

        if (curr->left == nullptr)
            newCurr = curr->right;
        else
            newCurr = curr->left;

        if (prev == nullptr) {  // root
            if (curr->left == nullptr) {
                Node *del = this->root;
                this->root = this->root->right;
                delete del;
            } else if (curr->right == nullptr) {
                Node *del = this->root;
                this->root = this->root->left;
                delete del;
            } else { // root has 2 children
                Node *p = nullptr;
                Node *temp;

                temp = curr->right;

                while (temp->left != nullptr) {
                    p = temp;
                    temp = temp->left;
                }

                if (p != nullptr) {
                    p->left = temp->right;
                } else {
                    curr->right = temp->right;
                }

                curr->info = temp->info;
                this->root->info = temp->info;

                delete temp;
            }

            --this->_size;
            return true;
        }

        if (curr == prev->left)
            prev->left = newCurr;
        else
            prev->right = newCurr;

        --this->_size;
        delete curr;
    } else { // node to be deleted has two children.
        Node *p = nullptr;
        Node *temp;

        temp = curr->right;
        while (temp->left != nullptr) {
            p = temp;
            temp = temp->left;
        }

        if (p != nullptr)
            p->left = temp->right;
        else
            curr->right = temp->right;

        curr->info = temp->info;
        --this->_size;
        delete temp;
    }
    return true;
}


bool SortedBag::search(TComp elem) const {
    if (this->root == nullptr) {
        return false;
    } else {
        Node *current = this->root;
        while (current != nullptr) {
            if (current->info == elem) {
                return true;
            } else if (this->relation(elem, current->info)) {
                current = current->left;
            } else if (this->relation(current->info, elem)) {
                current = current->right;
            }
        }
        return false;
    }
}


int SortedBag::nrOccurrences(TComp elem) const {
    int nrOccurrences = 0;
    if (this->root == nullptr) {
        return 0;
    }

    bool found = false;
    SortedBagIterator it = this->iterator();
    it.first();
    while (it.valid()) {
        if (it.getCurrent() == elem) {
            ++nrOccurrences;
            found = true;
        } else if (found) {
            break;
        }
        it.next();
    }


    return nrOccurrences;
}


int SortedBag::size() const {
    return this->_size;
}


bool SortedBag::isEmpty() const {
    return (this->_size == 0);
}


SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
    if (this->_size == 0) {
        return;
    } else {
        deleteTree(this->root);
    }
}

void SortedBag::deleteTree(struct Node *node) {
    if (node == nullptr)
        return;

    deleteTree(node->right);
    deleteTree(node->left);

    delete node;
}

void SortedBag::filter(Condition cond) {
    auto *newBag = new SortedBag(this->relation);
    SortedBagIterator it = this->iterator();
    it.first();
    while (it.valid()) {
        if (cond(it.getCurrent())) {
            newBag->add(it.getCurrent());
        }
        it.next();
    }

    this->deleteTree(this->root);
    this->root = newBag->root;
}
