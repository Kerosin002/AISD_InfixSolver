#include <iostream>
#include "Stack.h"
#include "String.h"
#include "Stack.cpp"


using namespace std;



String intToString(int num) {
    String res = "";

    if (num == 0)
        return "0";



    while (num > 0) {
        char digit = '0' + (num % 10);
        res.appendChar(digit);
        num /= 10;
    }
    res.reverse();
    return res;

}


int stringToInt(String num) {
    int res = 0;
    if (num == "0")
        return 0;

    for (int i = 0; i < num.length(); i++) {
        res *= 10;
        int digit = num[i] - '0';
        res += digit;


    }
    return res;
}


int funIF(int a, int b, int c) {
    if (a > 0)
        return b;
    return c;
}


int funN(int a) {
    return -1 * a;
}

int Max(int q, int* args) {
    int max = args[0];
    for (int i = 1; i < q; i++) {
        if (max < args[i])
            max = args[i];
    }
    return max;
}

int Min(int q, int* args) {
    int min = args[0];
    for (int i = 1; i < q; i++) {
        if (min > args[i])
            min = args[i];
    }
    return min;
}


bool isFunction(String* token) {
    return (*token)[0] == 'M' || (*token)[0] == 'I' || (*token)[0] == 'N';
}

bool isMaxMin(String* token) {
    return (*token)[0] == 'M';
}



bool isOperatorHigh(String* token) {
    return (*token)[0] == '*' || (*token)[0] == '/';
}

bool isOperatorLow(String* token) {
    return (*token)[0] == '+' || (*token)[0] == '-';
}



String infixToPostfix() {
    Stack<String> stos;
    Stack<int> comaStos;
    String postFix = "";
    String token = "";
    char c = -1;
    for (int i = 0; c != '.'; i++) {
        c = getchar();
        if (c == '\n')
            continue;
        if (c == ' ') {
            if (token.isNum()) {
                postFix += token;
                postFix.appendChar(' ');
            }
            else if (token[0] == '(' || isFunction(&token)) {
                stos.push(token);
                if (token[1] == 'A' || token[1] == 'I' || token[0] == 'I') {
                    int newComaC = 0;
                    comaStos.push(newComaC);
                }
            }
            else if (token[0] == ')') {
                while (!stos.isEmpty() && stos.top()[0] != '(') {


                    postFix += stos.top();
                    postFix.appendChar(' ');
                    //postFix = updPostfix(postFix, &stos, &comaStos);   

                    stos.pop();
                }
                stos.pop();
                String comas = "";
                if (!stos.isEmpty() && isFunction(&stos.top()) && !comaStos.isEmpty()) {
                    if (isMaxMin(&stos.top())) {
                        comas = intToString(comaStos.top() + 1);
                        comaStos.pop();
                    }
                    if (stos.top()[0] == 'I')
                        comaStos.pop();
                    postFix += stos.top() + comas;
                    postFix.appendChar(' ');
                    stos.pop();

                }

            }
            else if (isOperatorHigh(&token)) {
                while (!stos.isEmpty() && !isOperatorLow(&stos.top()) && stos.top() != "(") {

                    postFix += stos.top();
                    postFix.appendChar(' ');
                    //postFix = updPostfix(postFix, &stos, &comaStos);
                    stos.pop();
                }
                stos.push(token);
            }
            else {
                while (!stos.isEmpty() && stos.top()[0] != '(') {
                    postFix += stos.top();
                    postFix.appendChar(' ');
                    //postFix = updPostfix(postFix, &stos, &comaStos);
                    stos.pop();
                }
                if (token[0] != ',' && token[0] != ' ')
                    stos.push(token);
                else if (token[0] = ',') {
                    int temp = comaStos.top();
                    comaStos.pop();
                    temp++;
                    comaStos.push(temp);
                }
            }
            token = "";
        }
        else
            token.appendChar(c);
    }
    while (!stos.isEmpty()) {
        String comas = "";
        if (isMaxMin(&stos.top()) && !comaStos.isEmpty()) {
            comas = intToString(comaStos.top() + 1);
            comaStos.pop();
        }
        postFix += stos.top() + comas;
        postFix.appendChar(' ');
        //postFix = updPostfix(postFix, &stos, &comaStos);
        stos.pop();
    }
    //String cleanedPostfix = clearSpaces(postFix);
    return postFix;
}


void solvePostfix(String postFix) {
    cout << postFix << endl;
    String token = "";
    Stack<int> argumentStack;
    Stack<String> operandStack;
    for (int i = 0; i < postFix.length(); i++) {
        if (postFix[i] == '\n')
            continue;
        if (postFix[i] == ' ' && postFix[i - 1] != ' ') {
            if (token.isNum()) {
                argumentStack.push(stringToInt(token));
            }
            else {
                cout << token << " ";
                argumentStack.showStos();
                cout << endl;
                if (token[0] == 'M' && token[2] == 'X') {
                    int sizeOfArgs = 0;
                    for (int j = 3; j < token.length(); j++) {
                        sizeOfArgs = token[j] - '0' + sizeOfArgs * 10;
                    }
                    int* args = new int[sizeOfArgs];
                    for (int j = 0; j < sizeOfArgs; j++) {
                        args[j] = argumentStack.top();
                        argumentStack.pop();
                    }
                    argumentStack.push(Max(sizeOfArgs, args));
                    delete[] args;
                }
                else if (token[0] == 'M' && token[2] == 'N') {
                    int sizeOfArgs = 0;
                    for (int j = 3; j < token.length(); j++) {
                        sizeOfArgs = token[j] - '0' + sizeOfArgs * 10;
                    }
                    int* args = new int[sizeOfArgs];
                    for (int j = 0; j < sizeOfArgs; j++) {
                        args[j] = argumentStack.top();
                        argumentStack.pop();
                    }
                    argumentStack.push(Min(sizeOfArgs, args));
                    delete[] args;
                }
                else if (token[0] == 'N') {
                    int arg = argumentStack.top();
                    argumentStack.pop();
                    argumentStack.push(funN(arg));
                }
                else if (token[0] == 'I') {
                    int arg1 = argumentStack.top();
                    argumentStack.pop();
                    int arg2 = argumentStack.top();
                    argumentStack.pop();
                    int arg3 = argumentStack.top();
                    argumentStack.pop();
                    argumentStack.push(funIF(arg3, arg2, arg1));
                }
                else if (token[0] == '/') {
                    int arg1 = argumentStack.top();
                    argumentStack.pop();
                    int arg2 = argumentStack.top();
                    argumentStack.pop();
                    if (arg1 != 0)
                        argumentStack.push(arg2 / arg1);
                    else {
                        cout << "ERROR" << endl;
                        return;
                    }


                }
                else if (token[0] == '-') {
                    int arg1 = argumentStack.top();
                    argumentStack.pop();
                    int arg2 = argumentStack.top();
                    argumentStack.pop();
                    argumentStack.push(arg2 - arg1);
                }
                else if (token[0] == '+') {
                    int arg1 = argumentStack.top();
                    argumentStack.pop();
                    int arg2 = argumentStack.top();
                    argumentStack.pop();
                    argumentStack.push(arg2 + arg1);
                }
                else if (token[0] == '*') {
                    int arg1 = argumentStack.top();
                    argumentStack.pop();
                    int arg2 = argumentStack.top();
                    argumentStack.pop();
                    argumentStack.push(arg2 * arg1);
                }

            }
            token = "";
        }
        else if (postFix[i] != ' ')
            token.appendChar(postFix[i]);
    }
    cout << argumentStack.top() << endl;
}




int main() {
    int n;
    cin >> n;
    cin.ignore();
    
    for (int i = 0; i < n; ++i) {
        //String infix;
        //infix.getline();
        
        solvePostfix(infixToPostfix());
        cin.ignore();
    }

    return 0;
}