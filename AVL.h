#ifndef AVL_H
#define AVL_H

#include <memory>
#include "json.hpp"

using json = nlohmann::json;

class AVLTree {
public:
    AVLTree(int key);
    AVLTree();
    void insert(int key);
    json toJSON();
private:
    std::shared_ptr<AVLTree> root;
    int size;
    void updateBalanceFactors(std::shared_ptr<AVLTree> node);
    void balance(std::shared_ptr<AVLTree> node);
    void leftRotate(std::shared_ptr<AVLTree> node);
    void rightRotate(std::shared_ptr<AVLTree> node);
    void leftRightRotate(std::shared_ptr<AVLTree> node);
    void rightLeftRotate(std::shared_ptr<AVLTree> node);
    int key;
    int height;
    int balanceFactor;
    std::weak_ptr<AVLTree> parent;
    std::shared_ptr<AVLTree> left;
    std::shared_ptr<AVLTree> right;
};

#endif /* AVL_H */