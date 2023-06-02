#include<iostream>
#include <string>
#include <stack>
#include <cctype>
using namespace std;
 struct NODE {
	 long  value;
	 NODE* left;
	 NODE* right;
};
 bool Operator(char c) {
	 return (c == '+' || c == '-' || c == '*' || c == '/');
}
 NODE* GetNode(int x) {
	 NODE* node = new NODE;
	 node->value = x;
	 node->left = node->right = nullptr;
	 return node;
}
long double calculate(long double left, long double  right, char op) {
	 switch (op) {
	 case '+': return left + right;
	 case '-': return left - right;
	 case '*': return left * right;
	 case '/': return left/right;
	 }
 }
long double evaluateTree(NODE* root) {
	 if (root == nullptr) return 0;
	 if (root->left == nullptr && root->right == nullptr) {
		 return root->value;
	 }
	 long double left = evaluateTree(root->left);
	 long double right = evaluateTree(root->right);
	 return calculate(left, right, root->value);
 }
NODE* createTree(string expression) {
	 stack<NODE*> operands;
	 stack<char> operators;
	 for (int i = 0; i < expression.length(); i++) {
		 char exp = expression[i]; 
		 if (isdigit(exp)) { 
			 int num = exp - '0';
			 while (i + 1 < expression.length() && isdigit(expression[i + 1])) { 
				 num = num * 10 + (expression[i + 1] - '0');
				 i++;
			 }
			 operands.push(GetNode(num)); 
		 }
		 else if (exp == '(') { 
			 operators.push(exp);
		 }
		 else if (Operator(exp)) { 
			 while (!operators.empty() && Operator(operators.top()) && ((operators.top() == '*' || operators.top() == '/') || (exp == '+' || exp == '-'))) {
				 char op = operators.top(); 
				 operators.pop();
				 NODE* temp_right = operands.top();
				 operands.pop();
				 NODE* temp_left = operands.top();
				 operands.pop();
				 NODE* node = GetNode(op);
				 node->left = temp_left;
				 node->right = temp_right;
				 operands.push(node);
			 }
			 operators.push(exp);
		 }

		 else if (exp == ')') { 
			 while (operators.top() != '(') { 
				 char op = operators.top();
				 operators.pop();
				 NODE* temp_right = operands.top();
				 operands.pop();
				 NODE* temp_left = operands.top();
				 operands.pop();
				 NODE* node = GetNode(op);
				 node->left = temp_left;
				 node->right = temp_right;
				 operands.push(node);
			 }
			 if (!operators.empty()) 
				 operators.pop();
		 }
	 }
	 while (!operators.empty()) {
		 char op = operators.top();
		 operators.pop();
		 NODE* temp_right = operands.top();
		 operands.pop();
		 NODE* temp_left = operands.top();
		 operands.pop();
		 NODE* node = GetNode(op);
		 node->left = temp_left; 
		 node->right = temp_right;
		 operands.push(node);
	 }
	 return operands.top();
 }
 void PreOrder(NODE* root) {
	 if (root != nullptr) {
		 if (Operator(root->value))cout << char(root->value) << ' ';
		 else cout << root->value << ' ';
		 PreOrder(root->left);
		 PreOrder(root->right);
	 }
	 else return;
 }
 void InOrder(NODE* root) {
	 if (root != nullptr) {
		 InOrder(root->left);
		 if (Operator(root->value)) cout << char(root->value) << ' ';
		 else cout << root->value << ' ';
		 InOrder(root->right);
	 }
	 else return;
 }
 void PostOrder(NODE* root) {
	 if (root != nullptr) {
		 PostOrder(root->left);
		 PostOrder(root->right);
		 if (Operator(root->value)) cout << char(root->value) << ' ';
		 else cout << root->value << ' ';
	 }
	 else return;
 }
 void printtree(NODE* q, int space) {
	 if (q != nullptr) {
		 space += 4;
		 printtree(q->right, space);
		 cout << endl;
		 for (int i = 4; i < space; i++) {
			 cout << "|" ;
		 }
		 if (Operator(q->value)) cout << char(q->value) << endl;
		 else cout << q->value << endl;
		 printtree(q->left, space);
	 }
	 else return;
 }

 int main() {
	 string expression;
	 cout << "Nhap mot bieu thuc: ";
	 cin >> expression;
	 NODE* root = createTree(expression);
	 long double result = evaluateTree(root);
	 printf("Ket qua la = %Lf", result);
	 cout << endl;
	 std::cout << "Duyet Pre-order (NLR):  ";
	 PreOrder(root);
	 std::cout << std::endl;

	 std::cout << "Duyet In-order (LNR): ";
	 InOrder(root);
	 std::cout << std::endl;

	 std::cout << "Duyet Post-order (LRN): ";
	 PostOrder(root);
	 std::cout << std::endl;
	 cout << "Trinh tu cay nhi phan thuc hien tinh toan: \n";
	 printtree(root,0);
 }
