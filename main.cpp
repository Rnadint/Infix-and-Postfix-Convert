// Shibo Cong, 2021/4/1

#include <iostream>
#include <stack>
using namespace std;

bool contain(char array[], int arrayLength, char character){
    for (int i=0; i<arrayLength; i++){
        if (array[i]==character){
            return true;
        }
    }
    return false;
}

/**
 * print an infix in postfix form
 * @param input an string expression with left parenthesis and right parenthesis for every operation
 */

void in2post(string input){

    /* Examples For Input:
     * ((A*B)+(C/D)) -> AB*CD/+
     * ((A*(B+C))/D) -> ABC+*D/
     * (A*(B+(C/D))) -> ABCD/+*
     *
     * Warning:
     * The input must have an left parenthesis and right parenthesis around every operation
     * (Including the beginning and the end)
     */

    string expression = std::move(input); //initialize the expression

    stack<char> postfix; //initialize the postfix stack

    char operands[] = {'+','-','*','/'}; // add your custom operands here

    char operandsLength = 4; // change length if add custom operands

    size_t i = 0;

    do{
        if (expression[i]=='('){
            // top is (
            postfix.push(expression[i]);
        }
        else if (isdigit(expression[i])||isalpha(expression[i])){
            // top is a digit or a letter
            cout << expression[i];
        }
        else if (contain(operands,operandsLength,expression[i])){
            // top is an operation symbol
            postfix.push(expression[i]);
        }
        else{
            if (not (postfix.empty())){
                cout << postfix.top();
                postfix.pop();
            }
            else {
                cout << "error: too few operations in the infix expression";
            }
            postfix.pop();
        }
        i ++;
    }
    while (i < expression.length());

    if (not postfix.empty()){
        cout << "error: expression was not fully parenthesized";
    }

    cout  << endl;

}

/**
 * print an postfix in infix form
 * @param input an string of postfix expression
 */

void post2in(string input){

    /* Examples For Input:
     * AB*CD/+ -> ((D/C)+(B*A))
     * ABC+*D/ -> ((A*(B+C))/D)
     * ABCD/+* -> (A*(B+(C/D)))
     */

    string expression = input; //initialize the expression

    stack<string> infix; //initialize the infix stack

    char operands[] = {'+','-','*','/'}; // add your custom operands here

    char operandsLength = 4; // change length if add custom operands

    size_t i = 0; //iterator though the expression

    do {
        if (isdigit(expression[i])||isalpha(expression[i])){
            // top is operand
            string temp(1, expression[i]);
            infix.push(temp);
        }
        else if (contain(operands,operandsLength,expression[i])){
            // is an operator
            string preExpression = infix.top();
            infix.pop();
            string postExpression = infix.top();
            infix.pop();

            string wholeExpression = "("+postExpression+expression[i]+preExpression+")";
            // the post and pre will usually get reversed. It will mess up the denominator.
            // so the post and pre need to be reversed again

            infix.push(wholeExpression);
        }
        i ++;
    }
    while (i < expression.length());


    cout << infix.top() << endl;
    infix.pop();

    if (not infix.empty()){
        cout << "error: expression was not fully parenthesized";
    }

}



int main(){

    /* Dictionary:
     * AB*CD/+ -> ((D/C)+(B*A))
     * ABC+*D/ -> ((A*(B+C))/D)
     * ABCD/+* -> (A*(B+(C/D)))
     *
     * ((A*B)+(C/D)) -> AB*CD/+
     * ((A*(B+C))/D) -> ABC+*D/
     * (A*(B+(C/D))) -> ABCD/+*
     */
    in2post("((A*B)+(C/D))"); // AB*CD/+
    in2post("((A*(B+C))/D)"); // ABC+*D/
    in2post("(A*(B+(C/D)))"); // ABCD/+*

    post2in("AB*CD/+");; // ((A*B)+(C/D))
    post2in("ABC+*D/");; // ((A*(B+C))/D)
    post2in("ABCD/+*");; // (A*(B+(C/D)))

    /*
     * expecting:
     * AB*CD/+
     * ABC+*D/
     * ABCD/+*
     *
     * ((D/C)+(B*A))
     * ((A*(B+C))/D)
     * (A*(B+(C/D)))
     */

    return 0;
}

