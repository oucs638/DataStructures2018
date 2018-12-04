#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

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

int count(int left, int right)
{
    if (left == -1) {
        return 0;
    } else {
        if (right == -1) {
            return 1;
        }
    }
    return 2;
}

int main()
{
    string str = "";
    vector<int> heap;
    vector<string> tmp;
    int tar = -1;
    getline(cin, str);
    split(str, " ", tmp);
    for (int i = 0; i < tmp.size(); ++i) {
        heap.push_back(atoi(tmp[i].c_str()));
    }
    tmp.clear();
    getline(cin, str);
    split(str, " ", tmp);
    for (int i = 0; i < heap.size(); ++i) {
        if (heap[i] == atoi(tmp[0].c_str())) {
            heap[i] = atoi(tmp[1].c_str());
            break;
        }
    }
    for (int i = 0; i < heap.size(); ++i) {
        int left = (i + 1) * 2 - 1;
        int right = (i + 1) * 2;
        if (left >= heap.size()) {
            left = -1;
            right = -1;
        } else {
            if (right >= heap.size()) {
                right = -1;
            }
        }
        switch (count(left, right)) {
        case 0:
            break;
        case 1:
            if (heap[i] < heap[left]) {
                int temp = heap[i];
                heap[i] = heap[left];
                heap[left] = temp;
            }
            break;
        case 2:
            if (!((heap[i] >= heap[left]) && (heap[i] >= heap[right]))) {
                if (heap[left] >= heap[right]) {
                    int temp = heap[i];
                    heap[i] = heap[left];
                    heap[left] = temp;
                } else {
                    int temp = heap[i];
                    heap[i] = heap[left];
                    heap[left] = temp;
                }
            }
            break;
        }
    }
    for (int i = 0; i < heap.size(); ++i) {
        cout << heap[i] << " ";
    }
    cout << endl;
    return 0;
}
