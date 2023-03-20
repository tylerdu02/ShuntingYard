/* 
  * Tyler Du
  * 3/19/23
  * Shunting Yard. Create the prefix, infix, and postfix of an inputted equation.
  */

#include <iostream>
#include <cstring>
#include <vector>
#include "Node.h"

using namespace std;

struct Node {
  char* charn;
  Node* next = nullptr;
  int number;
};


// function prototypes
void infixToPostfix(char infix[20]);
void enqueue(Node* &tail, Node* n);
Node* dequeue(Node* &head);
void push(Node* &head, Node* n);
Node* pop(Node* &head);
Node* peek(Node* head);
int numNumber(char infix[20], int index);
void stack(Node* head);
void queue(Node* head);
void convertToTree(Node* headPrev);
void treePush(BinaryTreeNode* &head, BinaryTreeNode* &n);
void printTreeStack(BinaryTreeNode* head);
BinaryTreeNode* treePop(BinaryTreeNode* &head);
void infix(BinaryTreeNode* head);
void postfix(BinaryTreeNode* head);
void prefix(BinaryTreeNode* head);

int main() {

  //get the infix equation from the user with no spaces
  char input[20];
  cout << "Input your mathematical expression with no spaces." << endl;
  cin >> input;
  cin.get();
  cout << input << endl;
  infixToPostfix(input);
  return 0;
  
}

void infixToPostfix(char infix[20]) {
  
  // create the head pointer
  Node* headStack = nullptr;
  Node* headQueue = nullptr;
  Node* tailQueue = nullptr;
  //cycle through user input
  for(int a = 0; a < strlen(infix); a++) {
    int b = (int)infix[a];
    if(b==42 || b==40 || b==41 || b==43 || b==45 || b==47 || b==94) {
      // create a new node with the operator as the value
      Node* n = new Node;
      char* charn = new char[1];
      charn[0] = infix[a];
      n->charn = charn;
      n->number = 1;
      if(headStack==nullptr) {
	headStack = n;
      }
      else if(infix[a]=='+'|| infix[a]=='-') {
	if(headStack->charn[0]=='(') {
	  push(headStack,n);
	}
	else{
	  while(headStack!=nullptr && headStack->charn[0]!='(') {
	    enqueue(tailQueue,pop(headStack));
	  }
	  push(headStack,n);
	}
      }
      else if(infix[a]=='*' || infix[a]=='/') {
	if(headStack->charn[0]=='(' || headStack->charn[0]=='+' || headStack->charn[0]=='-') {
	  push(headStack,n);
	}
	else{
	  while(headStack!=nullptr && headStack->charn[0]!='(' && headStack->charn[0]!='+' && headStack->charn[0]!='-') {
	    enqueue(tailQueue, pop(headStack));
	  }
	  push(headStack,n);
	}
      }
      else if(infix[a]==')') {
	push(headStack, n);
	while(headStack->charn[0]!='(') {
	  if(headStack->charn[0]==')') {
	    pop(headStack);
	  }
	  else{
	    enqueue(tailQueue,pop(headStack));
	  }
	}
	pop(headStack);
      }
      else{
	push(headStack, n);
      }
    }
    else{
      // create a new node with the value
      int number = numNumber(infix, a);
      char* charn = new char[number];
      for(int c = 0; c < number; c++) {
	charn[c] = infix[a+c];
	if(c!=0) {
	  a++;
	}
      }
      Node* n = new Node;
      n->charn = charn;
      n->number = number;
      // add the new node to the queue
      if(headQueue==nullptr) {
	headQueue = n;
	tailQueue = n;
      }
      else{
	enqueue(tailQueue, n);
      }
    }
  }
  // pop everything from the stack to the output queue
  while(headStack!=nullptr) {
    enqueue(tailQueue,pop(headStack));
  }
  // print out stack and output queue 
  cout << "Stack: " << endl;
  stack(headStack);
  cout << "Queue: " << endl;
  queue(headQueue);
  convertToTree(headQueue);
}

void convertToTree(Node* headPrev) {
  
  // create a head pointer
  BinaryTreeNode* head = nullptr;
  while(headPrev!=nullptr) {
    Node* n = pop(headPrev);
    BinaryTreeNode* bn = new BinaryTreeNode(n->charn, n->number);
    char c = bn->getChar()[0];
    if(c==42 || c==43 || c==45 || c==47 || c==94) {
      bn->setLeft(treePop(head));
      bn->setRight(treePop(head));
    }
    treePush(head, bn);
  }
  // output the tree nodes 
  cout << "Tree: " << endl;
  printTreeStack(head);
  cout << "Would you like to see infix, prefix, or postfix?" << endl;
  char fix[20];
  cin >> fix;
  cin.get();
  if(fix[1]=='n') {
    infix(head);
  }
  else if(fix[1]=='r') {
    prefix(head);
  }
  else if(fix[1]=='o') {
    postfix(head);
  }
  else {
    cout << "Invalid type" << endl;
  }
}

// print out the current head before calling for left and right
void prefix(BinaryTreeNode* head) {
  if(head!=nullptr) {
    for(int a = 0; a < head->getNumber(); a++) {
      cout << head->getChar()[a];
    }
    prefix(head->getLeft());
    prefix(head->getRight());
  }
}

void infix(BinaryTreeNode* head) {
  if(head!=nullptr) {
    char c = head->getChar()[0];
    if(c==42 || c==43 || c==45 || c==47 || c==94) {
      cout << "(";
    }
    infix(head->getLeft());
    for(int a = 0; a < head->getNumber(); a++) {
      cout << head->getChar()[a];
    }
    infix(head->getRight());
    if(c==42 || c==43 || c==45 || c==47 || c==94) {
      cout << ")";
    }
  }
}

void postfix(BinaryTreeNode* head) {
  if(head!=nullptr) {
    postfix(head->getLeft());
    postfix(head->getRight());
    for(int a = 0; a < head->getNumber(); a++) {
      cout << head->getChar()[a];
    }
  }
}

BinaryTreeNode* treePop(BinaryTreeNode* &head) {
  BinaryTreeNode* temp = head;
  head = temp->getNext();
  temp->setNext(nullptr);
  return temp;
}

void printTreeStack(BinaryTreeNode* head) {
  if(head!=nullptr) {
    for(int a = 0; a < head->getNumber(); a++) {
      cout << head->getChar()[a];
    }
    cout << endl;
    printTreeStack(head->getNext());
  }
}

void treePush(BinaryTreeNode* &head, BinaryTreeNode* &n) {
  if(head==nullptr) {
    head = n;
  }
  else{
    BinaryTreeNode* temp = head;
    head = n;
    n->setNext(temp);
  }
}

void queue(Node* head) {
  if(head!=nullptr){
    for(int a = 0; a < head->number; a++) {
      cout << head->charn[a];
    }
    cout << endl;
    queue(head->next);
  }
}

void stack(Node* head) {
  if(head!=nullptr) {
    cout << head->charn[0] << endl;
    stack(head->next);
  }
}

int numNumber(char infix[20], int index) {
  int count = 0;
  for(int a = index; a < strlen(infix); a++) {
    int b = (int)infix[a];
    if(b==42 || b==41 || b==40 || b==43 || b==45 || b==47 || b==94) {
      break;
    }
    count++;
  }
  return count;
}

void enqueue(Node* &tail, Node* n) {
  Node* temp = tail;
  tail = n;
  temp->next = tail;
  tail->next = nullptr;
}

Node* dequeue(Node* &head) {
  Node* temp = head;
  head = temp->next;
  temp->next = nullptr;
  return temp;
}

void push(Node* &head, Node* n) {
  if(head==nullptr) {
    head = n;
  }
  else{
    Node* temp = head;
    n->next = temp;
    head = n;
  }
}

Node* pop(Node* &head) {
  Node* temp = head;
  head = temp->next;
  temp->next = nullptr;
  return temp;
}

// return the head
Node* peek(Node* head) {
  return head;
}