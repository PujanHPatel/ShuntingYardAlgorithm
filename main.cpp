#include <iostream>
#include <cstring>
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

void push(Stack *& stack, char newValue, int & stackSize);
void pop(Stack *& stack, int & stackSize);
char peek(Stack * stack);
void enqueue(Queue *& queue, char newValue, int & queueSize);
void dequeue(Queue *& queue, int & queueSize);

char shuntingYardPostFix(Stack * stack, Queue * queue, int & stackSize, int & queueSize, char input[]);

int main() {
    Queue * queue = new Queue;
    Stack * stack = new Stack;
    int queueSize = 0;
    int stackSize = 0;
    char input[80];
    cout << "Please input expression";
    cin >> input;
    shuntingYardPostFix(stack, queue, stackSize, queueSize, input);

    return 0;
}
void enqueue(Queue *& queue, char newValue, int & queueSize) {
    Node * queueHead = queue -> array;
    Node * current = queueHead;
    Node * tempNode = new Node;
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
    queue -> top = tempNode -> value;
    queue -> bottom = queueHead -> value;
    queue -> array = queueHead;
    queueSize++;
}
void dequeue(Queue *& queue, int & queueSize) {
    Node * head = queue -> array;
    Node * previous = head;
    if(queueSize > 1) {
        head = head->next;
        previous -> value = '\0';
        delete previous -> next;
        queue -> array = head;
        queue -> bottom = head -> value;
        queueSize--;
    }
    else {
        queue -> top = '\0';
        queue -> bottom = '\0';
        delete queue -> array;
        queueSize = 0;
    }
    
}
void push(Stack *& stack, char newValue, int & stackSize) {
    Node * stackHead = stack -> array;
    Node * current = stackHead;
    Node * tempNode = new Node;
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
    stack -> top = tempNode -> value;
    stackSize++;
}
void pop(Stack *& stack, int & stackSize) {
    Node* stackHead = stack -> array;
    Node * current = stackHead;
    Node * previous = current;
    while(current -> next != NULL) {
        previous = current;
        current = current -> next;
    }
    previous -> next = NULL;
    current -> value = '\0';
    delete current -> next;
    stack -> array = stackHead;
    stack -> top = previous -> value;
    stackSize--;
}
char peek(Stack * stack) {
    return stack -> top;
}
char shuntingYardPostFix(Stack * stack, Queue * queue, int & stackSize, int & queueSize, char input[]) {
    for(int i = 0; i < strlen(input); i++) {
        if(isdigit(input[i])) {
            enqueue(queue, input[i], queueSize);
        }
        else if(input[i] == '(') {
            push(stack, '(', stackSize);
        }
        else if(input[i] == '^' && stack -> top != '^') {
            push(stack, '^', stackSize);
        }
        else if(input[i] == 'x' && stack -> top != '^' && stack -> top != 'x' && stack -> top != '/') {
            push(stack, 'x', stackSize);
        }
        else if(input[i] == '/' && stack -> top != '^' && stack -> top != 'x' && stack -> top != '/') {
            push(stack, '/', stackSize);
        }
        else if(input[i] == '+' && stack -> top != '^' && stack -> top != 'x' && stack -> top != '/' && stack -> top != '+' && stack -> top != '-')  {
            push(stack, '+', stackSize);
        }
        else if(input[i] == '-' && stack -> top != '^' && stack -> top != 'x' && stack -> top != '/' && stack -> top != '+' && stack -> top != '-') {
            push(stack, '-', stackSize);
        }
        else if(input[i] == ')') {
            while(stack -> top != '(') {
                enqueue(queue, peek(stack), queueSize);
                pop(stack, stackSize);
            }
            pop(stack, stackSize);
        }
        else if(input[i] == '^' && stack -> top == '^') {
            while(stack -> top == '^') {
                enqueue(queue, peek(stack), queueSize);
                pop(stack, stackSize);
            }
            push(stack, '^', stackSize);
        }
        else if(input[i] == 'x' && (stack -> top == '^' || stack -> top == 'x' || stack -> top == '/')) {
            while(stack -> top == '^' || stack -> top == 'x' || stack -> top == '/') {
                enqueue(queue, peek(stack), queueSize);
                pop(stack, stackSize);
            }
            push(stack, 'x', stackSize);
        }
        else if(input[i] == '/' && (stack -> top == '^' || stack -> top == 'x' || stack -> top == '/')) {
            while(stack -> top == '^' || stack -> top == 'x' || stack -> top == '/') {
                enqueue(queue, peek(stack), queueSize);
                pop(stack, stackSize);
            }
            push(stack, '/', stackSize);
        }
        else if(input[i] == '+' && (stack -> top == '^' || stack -> top == 'x' || stack -> top == '/' || stack -> top == '+' || stack -> top == '-')) {
            while(stack -> top == '^' || stack -> top == 'x' || stack -> top == '/' || stack -> top == '+' || stack -> top == '-') {
                enqueue(queue, peek(stack), queueSize);
                pop(stack, stackSize);
            }
            push(stack, '+', stackSize);
        }
        else if(input[i] == '-' && (stack -> top == '^' || stack -> top == 'x' || stack -> top == '/' || stack -> top == '+' || stack -> top == '-')) {
            while(stack -> top == '^' || stack -> top == 'x' || stack -> top == '/' || stack -> top == '+' || stack -> top == '-') {
                enqueue(queue, peek(stack), queueSize);
                pop(stack, stackSize);
            }
            push(stack, '-', stackSize);
        }
    }
    while(stackSize != 0) {
        enqueue(queue, peek(stack), queueSize);
        pop(stack, stackSize);
    }
    Node * head = queue -> array;
    while(head -> next != NULL) {
        cout << head -> value; 
        head = head -> next;
    }
    cout << queue -> top;
    return ' ';
}