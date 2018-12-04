#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;
#define MAX_DEQUE_SIZE 9999

//create deque struct and some default function
typedef struct
{
    int key;
} element;
element deque[MAX_DEQUE_SIZE];
int front = -1, rear = -1;
void deque_empty()
{
    cout << "The deque is empty." << endl;
}
void deque_full()
{
    cout << "The deque is full." << endl;
}
bool isEmpty()
{
    if (front == -1 && rear == -1) {
        return true;
    }
    return false;
}
bool isFull()
{
    if (front < rear) {
        if (front == 0 && rear == MAX_DEQUE_SIZE - 1) {
            return true;
        }
    } else if (front > rear) {
        if (rear == front - 1) {
            return true;
        }
    }
    return false;
}

//the function to split a big string
//can exclude designated small string
//use a vector<string> to store the splited string
void split(string req, string tar, vector<string>& vec)
{
    string str = req;
    int pos = 0;
    while (true) {
        pos = str.find_first_of(tar, 0);
        if (pos != 0) {
            string tmp = str.substr(0, pos);
            if (tmp.size() != 0) {
                if (!(vec.empty() || vec.size() == 1)) {
                    vec.pop_back();
                }
                vec.push_back(tmp);
                if (pos == str.size() - 1) {
                    break;
                } else {
                    string tmp2 = str.substr(pos + 1, (str.size() - pos));
                    if (tmp2.size() == 0) {
                        break;
                    } else {
                        vec.push_back(tmp2);
                        str = tmp2;
                    }
                }
            }
        }
        if (pos == string::npos) {
            if (!vec.empty()) {
                vec.pop_back();
            }
            break;
        }
    }
}

void push_front(element item)
{
    if (isEmpty()) {
        front = 0;
        rear = 0;
        deque[front] = item;
    } else if (isFull()) {
        deque_full();
    } else if (front == 0) {
        front = MAX_DEQUE_SIZE - 1;
        deque[front] = item;
    } else {
        --front;
        deque[front] = item;
    }
}
void push_back(element item)
{
    if (isEmpty()) {
        front = 0;
        rear = 0;
        deque[rear] = item;
    } else if (isFull()) {
        deque_full();
    } else if (rear == MAX_DEQUE_SIZE - 1) {
        rear = 0;
        deque[rear] = item;
    } else {
        ++rear;
        deque[rear] = item;
    }
}
void pop_front()
{
    if (isEmpty()) {
        deque_empty();
    } else if (front == rear) {
        front = -1;
        rear = -1;
        deque_empty();
    } else if (front == MAX_DEQUE_SIZE - 1) {
        front = 0;
    } else {
        ++front;
    }
}
void pop_back()
{
    if (isEmpty()) {
        deque_empty();
    } else if (front == rear) {
        front = -1;
        rear = -1;
        deque_empty();
    } else if (rear == 0) {
        rear = MAX_DEQUE_SIZE - 1;
    } else {
        --rear;
    }
}
void show()
{
    if (isEmpty()) {
        deque_empty();
    } else if (front > rear) {
        for (int i = front; i < MAX_DEQUE_SIZE; ++i) {
            cout << deque[i].key << " ";
        }
        for (int i = 0; i <= rear; ++i) {
            cout << deque[i].key << " ";
        }
        cout << endl;
    } else {
        for (int i = front; i <= rear; ++i) {
            cout << deque[i].key << " ";
        }
        cout << endl;
    }
}

int main()
{
    cout << "Please enter instruction (enter \"QUIT\" to quit):" << endl;
    string str = "";
    getline(cin, str);
    while (true) {
        if (str == "QUIT") { //designed instruction to end the program
            break;
        } else if (str == "pop_front") { //delete from front
            pop_front();
        } else if (str == "pop_back") { //delete from back
            pop_back();
        } else if (str == "show") { //output the deque
            show();
        } else { //to add element to the deque
            vector<string> vec;
            split(str, " ", vec);
            if (vec.empty() || vec.size() != 2) { //check if the instruction is legal
                cout << "WRONG INSTRUCTION, PLEASE TRY AGAIN!" << endl;
            } else {
                if (vec[0] == "push_front") {
                    int n = atoi(vec[1].c_str());
                    element tmp;
                    tmp.key = n;
                    push_front(tmp);
                } else if (vec[0] == "push_back") {
                    int n = atoi(vec[1].c_str());
                    element tmp;
                    tmp.key = n;
                    push_back(tmp);
                } else {
                    cout << "WRONG INSTRUCTION, PLEASE TRY AGAIN!" << endl;
                }
            }
        }
        getline(cin, str);
    }

    return 0;
}