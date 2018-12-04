#include <iostream>
#include <string>
#include <vector>
using namespace std;

// the function to split a big string
// can exclude designated small string
// use a vector<string> to store the splited string
void split(string req, string tar, vector<string>& vec) {
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
bool isOperator(string str) {
    if (str == "+" || str == "-" || str == "*" || str == "/" || str == "(" ||
        str == ")") {
        return true;
    } else {
        return false;
    }
}
int priority(string str) {
    if (str == "+" || str == "-") {
        return 1;
    } else if (str == "*" || str == "/") {
        return 2;
    } else {
        return 0;
    }
}

// the function to turn the stack into correct form prefix
void turnaway(vector<string>& vec) {
    vector<string> tmp;
    while (!vec.empty()) {
        tmp.push_back(vec.back());
        vec.pop_back();
    }
    for (int i = 0; i < tmp.size(); ++i) {
        vec.push_back(tmp[i]);
    }
}

void tokenize(string& str, vector<string>& infix) { split(str, " ", infix); }

// the function to convert infix to prefix
void toPrefix(vector<string>& infix, vector<string>& prefix) {
    vector<string> tmp;
    for (int i = infix.size() - 1; i >= 0; --i) {
        if (isOperator(infix[i])) {
            if (tmp.empty()) {
                tmp.push_back(infix[i]);
            } else {
                if (infix[i] == "(") {
                    while (tmp.back() != ")") {
                        prefix.push_back(tmp.back());
                        tmp.pop_back();
                    }
                    tmp.pop_back();
                } else if (infix[i] == ")") {
                    tmp.push_back(infix[i]);
                } else {
                    while (priority(tmp.back()) > priority(infix[i])) {
                        prefix.push_back(tmp.back());
                        tmp.pop_back();
                        if (tmp.empty()) {
                            break;
                        }
                    }
                    tmp.push_back(infix[i]);
                }
            }
        } else {
            prefix.push_back(infix[i]);
        }
    }
    while (!tmp.empty()) {
        prefix.push_back(tmp.back());
        tmp.pop_back();
    }
    turnaway(prefix);
}
void output(vector<string>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "Please enter instruction (enter \"QUIT\" to quit):" << endl;
    string str;
    vector<string> infix;
    vector<string> prefix;
    getline(cin, str);
    while (true) {
        if (str == "QUIT") {
            break;
        } else {
            infix.clear();
            prefix.clear();
            tokenize(str, infix);
            toPrefix(infix, prefix);
            output(prefix);
            getline(cin, str);
        }
    }
}