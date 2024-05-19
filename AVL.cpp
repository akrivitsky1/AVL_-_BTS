#include "AVL.h"

AVLTree::AVLTree(int key) { //Constructor for AVL Tree
    this->key = key; // assigning key value
    this->height = 0; //assigning height value
    this->balanceFactor = 0; //assigning balance factor value
    this->parent.reset(); // reseting parents
    this->left = nullptr; //no children
    this->right = nullptr;
}

AVLTree::AVLTree() {
    this->root = nullptr; //if no first key given
    this->size = 0; //size is 0
}

void AVLTree::insert(int key) {
    std::shared_ptr<AVLTree> node(new AVLTree(key)); // new shared ptr
    if (this->root == nullptr) { // if null pointer
        this->root = node; //root is now node
        this->size++; //increase size
        return;
    }
    std::shared_ptr<AVLTree> current = this->root; //shared pointer 
    while (true) {
        if (key < current->key) { //if the key is less than current key
            if (current->left == nullptr) { //if left node is null pointer
                current->left = node; // current node is now has a left child
                node->parent = current; //parent node is current
                this->size++; //increase the size
                this->updateBalanceFactors(node); //update the balance factor
                this->balance(node); //balance the node
                break;
            }
            current = current->left; //now has a new left node
        } else if (key > current->key) { //if new key is bigger than current key
            if (current->right == nullptr) { // if it is null pointer
                current->right = node; //node is now right pointer
                node->parent = current; //parent is now current
                this->size++; //increase the size
                this->updateBalanceFactors(node); //update the balance factor
                this->balance(node); //balance the node
                break;
            }
            current = current->right;
        } else {
            break;
        }
    }
}

json AVLTree::toJSON() {
    json j; //json object
    j["height"] = this->root->height; //height is root height
    j["root"] = this->root->key; //key value
    j["size"] = this->size; //size
    std::function<void(std::shared_ptr<AVLTree>, json&)> traverse = [&](std::shared_ptr<AVLTree> node, json& j) {
        json nodeJson; //new json object
        nodeJson["height"] = node->height; //node height
        nodeJson["balance factor"] = node->balanceFactor; //balance factor of the node
        if (node->parent.lock() != nullptr) {
            nodeJson["parent"] = node->parent.lock()->key; //parent of node
        }
        if (node->left != nullptr) {
            nodeJson["left"] = node->left->key; //left child of node
        }
        if (node->right != nullptr) {
            nodeJson["right"] = node->right->key; //right child of node
        }
        if (node == this->root) {
            nodeJson["root"] = true; // check if there is root
        }
        j[std::to_string(node->key)] = nodeJson; //converts key value to string
        if (node->left != nullptr) { // check if there is a left node
            traverse(node->left, j);
        }
        if (node->right != nullptr) { //check if there is a right node
            traverse(node->right, j);
        }
    };
    traverse(this->root, j); //traverse the root
    return j;
}

void AVLTree::updateBalanceFactors(std::shared_ptr<AVLTree> node) {
    while (node != nullptr) { //check if node is not null
        int leftHeight = (node->left != nullptr) ? node->left->height : -1; //find left height
        int rightHeight = (node->right != nullptr) ? node->right->height : -1; //find right height
        node->height = std::max(leftHeight, rightHeight) + 1; //find max of height
        node->balanceFactor = rightHeight - leftHeight; //balance factor calculation
        node = node->parent.lock();
    }
}

void AVLTree::balance(std::shared_ptr<AVLTree> node) {
    while (node != nullptr) { //node is not null
        if (node->balanceFactor == 2) { //check if balance factor is 2
            if (node->right->balanceFactor == -1) { //if right child balance factor is negative 1
                this->rightLeftRotate(node); //right left rotation
            } else {
                this->leftRotate(node); //left left rotation
            }
        } else if (node->balanceFactor == -2) { //unbalanced
            if (node->left->balanceFactor == 1) {
                this->leftRightRotate(node); //left right rotation
            } else {
                this->rightRotate(node); //right right rotation
            }
        }
        node = node->parent.lock();
    }
}

void AVLTree::leftRotate(std::shared_ptr<AVLTree> node) {
    std::shared_ptr<AVLTree> pivot = node->right;
    pivot->parent = node->parent;
    if (node->parent.lock() == nullptr) {
        this->root = pivot;
    } else if (node == node->parent.lock()->left) {
        node->parent.lock()->left = pivot;
    } else {
        node->parent.lock()->right = pivot;
    }
    node->right = pivot->left;
    if (pivot->left != nullptr) {
        pivot->left->parent = node;
    }
    node->parent = pivot;
    pivot->left = node;
    this->updateBalanceFactors(node);
    this->updateBalanceFactors(pivot);
}

void AVLTree::rightRotate(std::shared_ptr<AVLTree> node) {
    std::shared_ptr<AVLTree> pivot = node->left; //shared pointer
    pivot->parent = node->parent; //pivot parent
    if (node->parent.lock() == nullptr) { //null then root is parent
        this->root = pivot;
    } else if (node == node->parent.lock()->left) { // if equal to left then it is pivot
        node->parent.lock()->left = pivot;
    } else {
        node->parent.lock()->right = pivot; //if equal to right then it is pivot
    }
    node->left = pivot->right;
    if (pivot->right != nullptr) { //not null make the right child parent a node
        pivot->right->parent = node;
    }
    node->parent = pivot; //node parent is pivot
    pivot->right = node; //pivot right child is new node
    this->updateBalanceFactors(node); //update balance factors
    this->updateBalanceFactors(pivot);
}

void AVLTree::leftRightRotate(std::shared_ptr<AVLTree> node) {
    this->leftRotate(node->left); //rotate left
    this->rightRotate(node); //rotate right
}

void AVLTree::rightLeftRotate(std::shared_ptr<AVLTree> node) {
    this->rightRotate(node->right); //rotate right
    this->leftRotate(node); //rotate left
}