#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

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

bool isOperator(string str)
{
    if (str == "+" || str == "-" || str == "*" || str == "/") {
        return true;
    } else {
        return false;
    }
}

//convert the input to tokens and store in a vector<string>
void tokenize(string& str, vector<string>& expression)
{
    split(str, " ", expression);
}

float compute(string oper, float val1, float val2)
{
    if (oper == "+") {
        return val1 + val2;
    } else if (oper == "-") {
        if (val1 >= val2) {
            return val1 - val2;
        } else {
            return (-1) * (val2 - val1);
        }
    } else if (oper == "*") {
        return val1 * val2;
    } else if (oper == "/") {
        return val1 / val2;
    } else {
        return 0;
    }
}
void evalPrefix(vector<string>& expression)
{
    vector<float> nums;
    float num1, num2;
    for (int i = expression.size() - 1; i >= 0; --i) {
        if (isOperator(expression[i])) {
            num1 = nums.back();
            nums.pop_back();
            num2 = nums.back();
            nums.pop_back();
            nums.push_back(compute(expression[i], num1, num2));
        } else {
            nums.push_back(atof(expression[i].c_str()));
        }
    }
    int res = (int)(nums[0]);
    cout << res << endl;
}

int main()
{
    cout << "Please enter instruction (enter \"QUIT\" to quit):" << endl;
    string str = "";
    vector<string> expression;
    getline(cin, str);
    while (true) {
        //check if the input is legal
        if (str == "QUIT") {
            break;
        } else if (str.size() == 0) {
            continue;
        } else {
            if (str.size() < 3) {
                cout << "WRONG EXPRESSION, PLEASE TRY AGAIN!" << endl;
            } else {
                //eval the correct input
                expression.clear();
                tokenize(str, expression);
                evalPrefix(expression);
            }
            getline(cin, str);
        }
    }
    return 0;
}