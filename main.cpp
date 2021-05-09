#include <iostream>
using namespace std;

struct Node {
    char value;
    Node * next = NULL;
};
struct Stack {
    char top;
    Node * array;
};
struct Queue {
    char top;
    char bottom;
    Node * array;
};

void push(Stack *& stack, Node *& stackHead, char newValue, int & stackSize);
void pop(Stack *& stack, Node *& stackHead, int & stackSize);
void peek(Stack * stack);
void enqueue(Queue *& queue, Node *& queueHead, char newValue, int & queueSize);
void dequeue(Queue *& queue, int & queueSize);
void print(Node * head);

int main() {
    Queue * queue = new Queue;
    Stack * stack = new Stack;
    Node * queueHead = new Node;
    Node * stackHead = new Node;
    int queueSize = 0;
    int stackSize = 0;
    enqueue(queue, queueHead, 'a', queueSize);
    dequeue(queue, queueSize);
    return 0;
}
void enqueue(Queue *& queue, Node *& queueHead, char newValue, int & queueSize) {
    Node * tempNode = new Node;
    Node * current = queueHead;
    tempNode->value = newValue;
    if(queueSize == 0) {
        queueHead = tempNode;
    }
    else { 
        while(current -> next != NULL) {
            current = current -> next;
        }
        current -> next = tempNode;
    }
    queue -> top = newValue;
    queue -> array = queueHead;
    queueSize++;
}
void dequeue(Queue *& queue, int & queueSize) {
    Node * head = queue -> array;
    Node * previous = head;
    if(queueSize > 1) {
        head = head->next;
        delete previous;
        queue -> array = head;
        queue -> bottom = head -> value;
        queueSize--;
    }
    else {
        delete queue;
    }
}
void push(Stack *& stack, Node *& stackHead, char newValue, int & stackSize) {
    Node * tempNode = new Node;
    Node * current = stackHead;
    tempNode->value = newValue;
    if(stackSize == 0) {
        stackHead = tempNode;
    }
    else { 
        while(current -> next != NULL) {
            current = current -> next;
        }
        current -> next = tempNode;
    }
    stack -> array = stackHead;
    stackSize++;
}
void pop(Stack *& stack, Node *& stackHead, int & stackSize) {
    Node * current = stackHead;
    Node * previous = current;
    while(current -> next != NULL) {
        previous = current;
        current = current -> next;
    }
    previous -> next = NULL;
    delete current;
    stack -> array = stackHead;
    stackSize--;
}
void peek(Stack * stack) {
    Node * LL = stack -> array;
    while(LL -> next != NULL) {
        LL = LL -> next;
    }
    cout << LL -> value << endl;
}