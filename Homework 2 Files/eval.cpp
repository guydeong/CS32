#include <stack>
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int evaluate_precedence(char c);
int evaluate(string infix, string& postfix, bool& result);
char apply_operation(char operand1, char operand2, char op);
bool evaluate_postfix(string post_fix);
void infix_to_postfix(string infix, string& postfix);
bool valid_string(const string infix);
void remove_spaces(string& infix);

int evaluate(string infix, string& postfix, bool& result) {
    
    remove_spaces(infix);
    string test_postfix = infix;
    //If infix is a syntactically valid infix boolean expression,
    if (valid_string(test_postfix)) {
        //then set postfix to the postfix form of that expression, set
        //result to the value of the expression, and return zero.    
        infix_to_postfix(infix, postfix);
        result = evaluate_postfix(postfix);

        return 0;

    }

    //If infix is not a syntactically valid expression, return 1; in
    //that case, postfix may or may not be changed, but result must be unchanged
    return 1;
}

//Helper functions:

void remove_spaces(string& infix) {
    if (infix != "") {
        string temp = "";
        for (int i = 0; i < infix.size(); i++) {
            char c = infix[i];
            if (c != ' ') {
                temp += c;
            }
        }
        infix = temp;
    }
}
void infix_to_postfix(string infix, string& postfix) {
    //Initialize postfix to empty
    postfix = "";

    //Initialize the operator stack to empty
    stack <char> op_stack;
    
    //For each character ch in the infix string
    for (int i = 0; i < infix.length(); i++) {
        
        char ch = infix[i];
        switch (ch) {
                //Case operand
            case 'F':
            case 'T':
                //append ch to end of postfix
                postfix += ch;
                break;

            //Case '('
            case '(':
                //push ch onto the operator stack
                op_stack.push(ch);
                break;

            //Case ')'
            case ')':
                //pop stack until matching '('
                while (op_stack.top() != '(') {
                    //Append the stack top to postfix
                    postfix += op_stack.top();
                    //Pop the stack
                    op_stack.pop();
                }
                //remove the '('
                op_stack.pop();
                break;

            //Case operator
            case '!':
                op_stack.push(ch);
                break;
            case '&':   
            case '^':
                //While the stack is not empty and the stack top is not '(' and precedence of ch <= precedence of stack top
                while (!op_stack.empty() && op_stack.top() != '(' && evaluate_precedence(ch) <= evaluate_precedence(op_stack.top())) {
                    //append the stack top to postfix
                    postfix += op_stack.top();
                    op_stack.pop();
                }
                //Push ch onto the stack
                op_stack.push(ch);
                break;
            }
        }
        
    while (!op_stack.empty()) {
        postfix += op_stack.top();
        op_stack.pop();
    }
    

}


bool evaluate_postfix(string post_fix) {
    //Initialize the operand stack to empty
    stack <char> op_stack;

    for (int i = 0; i < post_fix.size(); i++) {
        char ch = post_fix[i];
        //If ch is an operand
        if (ch == 'T' || ch == 'F') {
            op_stack.push(ch);
        }
        //elseif ch is NOT operator
        else if (ch == '!') {
            char temp1 = op_stack.top();
            op_stack.pop();

            if (temp1 == 'T') {
                //Change temp2 to opposite operand
                op_stack.push('F');
            }
            else if (temp1 == 'F') {
                //Change temp2 to opposite operand
                op_stack.push('T');
            }
        }
        //Check here to evaluate validity of the operation
        //Otherwise, ch is a binary operator
        else {
            char operand2 = op_stack.top();
            op_stack.pop();
            char operand1 = op_stack.top();
            op_stack.pop();
            op_stack.push(apply_operation(operand1, operand2, ch));
            
        }
    }

    char result = op_stack.top();
    if (result == 'T' && op_stack.size() == 1) {
        return true;
    }
    
    return false;
}

char apply_operation(char operand1, char operand2, char op) {
    //'N' indicates that operation is not valid
    char c = 'N';

    //T&F = F
    if (operand1 == 'T' && operand2 == 'F' && op == '&') {
        c = 'F';
    }
    //F&T = F
    else if (operand1 == 'F' && operand2 == 'T' && op == '&') {
        c = 'F';
    }
    //T&T = T
    else if (operand1 == 'T' && operand2 == 'T' && op == '&') {
        c = 'T';
    }
    //F&F = F
    else if (operand1 == 'F' && operand2 == 'F' && op == '&') {
        c = 'F';
    }


    //T^T = F
    else if (operand1 == 'T' && operand2 == 'T' && op == '^') {
        c = 'F';
    }
    //F^T = T
    else if (operand1 == 'F' && operand2 == 'T' && op == '^') {
        c = 'T';
    }
    //T^F = F
    else if (operand1 == 'T' && operand2 == 'F' && op == '^') {
        c = 'T';
    }
    //F^F = T
    else if (operand1 == 'F' && operand2 == 'F' && op == '^') {
        c = 'F';
    }

    return c;
}

int evaluate_precedence(char c) {
    switch (c) {
        case '!':
            return 3;
        case '&':
            return 2;
        case '^':
            return 1;
        default:
            exit(1);
    }
}

bool valid_string(const string infix) {

    string postfix = "";

    //Check 1: If string is empty
    if (infix.size() == 0) {
        return false;
    }

    //Check 2: Check end of the infix string
    char end = infix[infix.size() - 1];
    if (end == '(' || end == '!' || end == '&' || end == '^') {
        return false;
    }

    //Check 3: Check if all characters are valid
    for (int i = 0; i < infix.size(); i++) {
        char ch = infix[i];
        if (ch == ')' || ch == '(' || ch == '&' || ch == '!' || ch == '^' || ch == 'T' || ch == 'F') {
            continue;
        }
        else {
            return false;
        }
    }
    
    //Check 5: Check beginning
    if (infix[0] == '&' || infix[0] == '^') {
        return false;
    }

    //Check 4: Check if paranthesis are valid
    stack <char> p_stack;

    for (int i = 0; i < infix.size(); i++) {
        char c = infix[i];
        //Push if '(' found
        if (c == '(') {
            p_stack.push(c);
        }
        //Otherwise, check if paranthesis match
        else {
            //Case 1 Error: p_stack is empty and current examination is ')'
            if (p_stack.empty() && c == ')') {
                return false;
            }

            //If '(' matches with ')', then continue
            if (!p_stack.empty()) {
                if (!p_stack.empty() && infix[i] == ')' && p_stack.top() == '(') {
                    p_stack.pop();
                    continue;
                }
            }
            //Otherwise, c is an operator or operand and continue
            else {
                continue;
            }
        }
    }
    
    if (!p_stack.empty()) {
        return false;
    }

    //Examine every item in the string, and check if there are invalid characters after the item examined
    for (int i = 0; i < infix.size(); i++) {
        char ch = infix[i];
        switch (ch) {
            case 'T':
            case 'F':
                if (i + 1 < infix.size()) {
                    if (infix[i + 1] == 'T' || infix[i + 1] == 'F' || infix[i + 1] == '(' || infix[i + 1] == 'F' || infix[i + 1] == '!') {
                        return false;
                    }
                }
                break;
            case '!':
            case '(':
                if (i + 1 < infix.size()) {
                    if (infix[i + 1] == ')' || infix[i + 1] == '&' || infix[i + 1] == '^') {
                        return false;
                    }
                }
                break;
            case ')':
                if (i + 1 < infix.size()) {
                    if (infix[i + 1] == '(' || infix[i + 1] == 'T' || infix[i + 1] == 'F') {
                        return false;
                    }
                }
                break;
            case '^':
            case '&':
                if (i + 1 < infix.size()) {
                    if (infix[i + 1] == ')' || infix[i + 1] == '&' || infix[i + 1] == '^') {
                        return false;
                    }
                }
                break;
                
        }   
        
    }
    return true;
}

int main() {
    

}