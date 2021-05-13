#include <iostream>
#include <cinttypes>
#include <string>
 
using namespace std;
 
// Reversing string
string reverse(string str)
{
  string result = "";
  for (int i = str.length() - 1; i >= 0; i--)
  {
    result += str[i];
    result += " ";
  }
 
  return result;
}
 
// Structure for node
struct Node
{
  int data;
  Node *npx;
};
 
// XOR
Node *XOR(Node *a, Node *b)
{
  return reinterpret_cast<Node *>(
      reinterpret_cast<uintptr_t>(a) ^
      reinterpret_cast<uintptr_t>(b));
}
 
void insertBeg(Node **head_ref, int data, Node **actual_ref)
{
  Node *new_node = new Node();
  new_node->data = data;
  new_node->npx = *head_ref;
 
  if (*head_ref != NULL)
    (*head_ref)->npx = XOR(new_node, (*head_ref)->npx);
  else
    *actual_ref = new_node; // Adding Init actual node
  *head_ref = new_node;
}
 
void insertEnd(Node *head, int data, Node **head_ref, Node **actual_ref)
{
  // If list is empty
  if (*head_ref == NULL)
  {
    Node *new_node = new Node();
    new_node->data = data;
    new_node->npx = *head_ref;
    *actual_ref = new_node;
    *head_ref = new_node;
 
    return;
  }
 
  // List is not empty
  Node *prevPrev = NULL;
  Node *prev = NULL;
  Node *curr = head;
  Node *next;
 
  while (curr != NULL)
  {
    next = XOR(prev, curr->npx);
    prevPrev = prev;
    prev = curr;
    curr = next;
  }
 
  Node *new_node = new Node();
  new_node->data = data;
  new_node->npx = XOR(prev, NULL);
  prev->npx = XOR(prevPrev, new_node);
}
 
// Printing list 1 2 3 -> 1 2 3
void printForward(Node *head)
{
  Node *curr = head;
  Node *prev = NULL;
  Node *next;
 
  while (curr != NULL)
  {
    cout << curr->data << " ";
 
    next = XOR(prev, curr->npx);
    prev = curr;
    curr = next;
  }
  cout << endl;
}
 
// Printing list backwards 1 2 3 -> 3 2 1
void printBackward(Node *head)
{
  Node *curr = head;
  Node *prev = NULL;
  Node *next;
 
  string result = "";
 
  while (curr != NULL)
  {
    int data = curr->data;
    result += to_string(data);
 
    next = XOR(prev, curr->npx);
    prev = curr;
    curr = next;
  }
  cout << reverse(result) << endl; // Reversing nodes
}
 
// Printing value in ACTUAL node, if there is no node, printing "NULL"
void printActual(Node *head, Node *actual)
{
  if (head == NULL || actual == NULL)
    cout << "NULL" << endl;
  else
    cout << actual->data << endl;
}
 
// Searching for neighbors of ACTUAL, and making next neighbour new ACTUAL
void actualNext(Node *head, Node *actual, Node **actual_ref)
{
  Node *prev = NULL;
  Node *curr = head;
  Node *next;
 
  while (curr != actual)
  {
    next = XOR(prev, curr->npx);
    prev = curr;
    curr = next;
  }
 
  next = XOR(prev, curr->npx);
 
  if (next == NULL) // It's the end of the list
  {
    cout << head->data << endl;
    *actual_ref = head;
    return;
  }
 
  // It's not the end of the list
  cout << next->data << endl;
  *actual_ref = next;
}
 
void actualPrev(Node *head, Node *actual, Node **actual_ref)
{
  Node *prev = NULL;
  Node *curr = head;
  Node *next;
 
  while (curr != actual)
  {
    next = XOR(prev, curr->npx);
    prev = curr;
    curr = next;
  }
  if (prev == NULL)
  {
    prev = NULL;
    curr = head;
    while (curr != NULL)
    {
      next = XOR(prev, curr->npx);
      prev = curr;
      curr = next;
    }
    cout << prev->data << endl;
    *actual_ref = prev;
  }
  else
  {
    cout << prev->data << endl;
    *actual_ref = prev;
  }
}
 
void addBeforePrev(Node *head, Node *actual, Node **actual_ref, int data)
{
  Node *prevPrev = NULL;
  Node *prev = NULL;
  Node *curr = head;
  Node *next;
 
  while (curr != actual)
  {
    next = XOR(prev, curr->npx);
    prevPrev = prev;
    prev = curr;
    curr = next;
  }
 
  if (prev == NULL)
  {
  }
 
  // prevPrev prev | curr next
  //               <= here we insert new_node
  next = XOR(prev, curr->npx);
  Node *new_node = new Node();
  new_node->data = data;
  prev->npx = XOR(prevPrev, new_node);
  new_node->npx = XOR(prev, curr);
  curr->npx = XOR(new_node, next);
}

void deleteBeg(Node **head_ref) {
  if(*head_ref != NULL) {
    Node* temp = *head_ref;
    *head_ref = XOR(NULL, temp->npx);
    if (*head_ref != NULL) {
          // Update head node address
          (*head_ref)->npx = XOR(NULL, XOR(temp, (*head_ref)->npx));
        }
    free(temp);
  }
}
 
void deleteEnd(Node **head_ref) {
{
  Node *curr = *head_ref;
  Node *prev = NULL;
  Node *next;

    if (*head_ref != NULL)
        while (XOR(curr->npx, prev) != NULL) {
            next = XOR(prev, curr->npx);
            prev = curr;
            curr = next;
        }
        if (prev != NULL)
            prev->npx = XOR(XOR(prev->npx, curr), NULL);
        else
            *head_ref = NULL;
        free(curr);
    }
}

void deleteVal(Node **head_ref, int data) {
  Node *curr = *head_ref;
  Node *prev = NULL;
  Node *next;
  
  if(*head_ref != NULL) {
    while (XOR(curr->npx, prev) != NULL) {
      next = XOR(prev, curr->npx);
      if(curr->data == data) {
        Node* temp = curr;
        if(temp == *head_ref) {
          *head_ref = next;
          if (*head_ref != NULL) {
            // Update head node address
            (*head_ref)->npx = XOR(NULL, XOR(temp, (*head_ref)->npx));
          }
          curr = *head_ref;
          prev = NULL;
          free(temp);
        }
        else {
          
        }
      }

      prev = curr;
      curr = next;
    }
  }
}

int main()
{
  Node *head = NULL;
  Node *actual = head;
 
  string command;
  while (cin >> command)
  {
 
    if (command.compare("ADD_BEG") == 0)
    {
      int data;
      cin >> data;
      insertBeg(&head, data, &actual);
    }
    else if (command.compare("ADD_END") == 0)
    {
      int data;
      cin >> data;
      insertEnd(head, data, &head, &actual);
    }
    else if (command.compare("PRINT_FORWARD") == 0)
      printForward(head);
    else if (command.compare("PRINT_BACKWARD") == 0)
      printBackward(head);
    else if (command.compare("ACTUAL") == 0)
      printActual(head, actual);
    else if (command.compare("NEXT") == 0)
      actualNext(head, actual, &actual);
    else if (command.compare("PREV") == 0)
      actualPrev(head, actual, &actual);
    else if (command.compare("ADD_ACT") == 0)
    {
      int data;
      cin >> data;
      addBeforePrev(head, actual, &actual, data);
    }
    else if (command.compare("DEL_BEG") == 0)
      deleteBeg(&head);
    else if (command.compare("DEL_END") == 0)
      deleteEnd(&head);
  }
}