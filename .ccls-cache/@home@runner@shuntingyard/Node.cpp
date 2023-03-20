#include "Node.h"
#include <iostream>
#include <cstring>

using namespace std;

BinaryTreeNode::BinaryTreeNode(char* charnNew, int numberNew) {
  charn = charnNew;
  number = numberNew;
  left = nullptr;
  right = nullptr;
  next = nullptr;
}