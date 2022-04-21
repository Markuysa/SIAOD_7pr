#pragma once
#include <iostream>
#include <string>
#include <map>
using namespace std;

map < char, int > dict = { {'+',1},{'-',1},{'*',2},{'/',2},{'^',3},{')',0},{'(',0} };

class Stack {
	struct Node
	{
		char data;
		Node* next_p;
	};
	Node* head = nullptr;
public:
	void push_front(int x);
	char pop_front();
	void print();
	bool Is_empty() { return head ? true : false; };
	int calculateExpression(string& str);
	int pop();
};
int Stack::pop() {
	return head->data;
}
char Stack::pop_front() {
	if (!this->Is_empty())
		return -1;
	char info = head->data;
	Node* temp = head;
	head = head->next_p;
	delete temp;
	return info;

}

void Stack::push_front(int x) {
	Node* pv = new Node;
	pv->data = x;
	pv->next_p = head;
	head = pv;
}
bool isdigit(char x) { if (int(x) <= 57 && int(x) >= 48) return true; return false; }
int operation(char op, Stack* operands) {
	int temp, temp2;
	char operation = char(op);
	temp = (operands->pop() >= 47 && operands->pop() <= 58) ? operands->pop_front() - 48 : operands->pop_front();
	temp2 = (operands->pop() >= 47 && operands->pop() <= 58) ? operands->pop_front() - 48 : operands->pop_front();
	int result = 0;
	switch (operation)
	{
	case '+':
		result = temp2 + temp;
		break;
	case '-':
		result = temp2 - temp;
		break;
	case '/':
		result = temp2 / temp;
		break;
	case '*':
		result = temp2 * temp;
		break;
	case '^':
		result = pow(temp2, temp);
	}
	return result;
}
int CalcuationBracket(Stack*& operations, Stack*& operands, string& str, int& i) {
	int result = 0;
	operations->push_front(str[i]);
	str.erase(str.find('('), 1);
	while (char(operations->pop()) != ')') {
		char key = char(str[i]);
		if ((isdigit(str[i])))
			operands->push_front(str[i]);
		else if (dict[key] < dict[char(operations->pop())]) {
			char op = operations->pop_front();
			result = operation(op, operands);
			operands->push_front(48 + result);
			operations->push_front(str[i]);
		}
		else {
			operations->push_front(key);
		}
		i++;
	}
	operations->pop_front();
	while (char(operations->pop() != '(' && char(operations->pop() != ')'))) {
		result = operation(operations->pop_front(), operands);

	}
	operations->pop_front();
	i--;
	return result;
}
int Stack::calculateExpression(string& str) {
	Stack* operands = new Stack;
	Stack* operations = new Stack;
	int result = 0;
	for (int i = 0; i < str.length(); i++) {
		char key = char(str[i]);
		if (isdigit(str[i])) {
			operands->push_front(str[i]); // Если встретили число - сразу записать в стек
		}
		else if (dict[key] == 0) { // Если встретили скобку (открывающую или закрывающую)
			if (key == '(')
				result += CalcuationBracket(operations, operands, str, i); // Выполнение вычисления выражения в скобках

		}
		else if (!(operations->Is_empty()) || dict[key] > dict[char(operations->pop())]) {  // Если текущий вычислительный знак больше по приоритету, чем предыдущий - запись в стек
			operations->push_front(str[i]);
		}
		else { // Если текущий вычислительный знак меньше предыдущего (по приоритету), то вычислить выражение для двух верхних элементво стека операндов
			char op = operations->pop_front();
			result = operation(op, operands);
			operands->push_front(result + 48);
			operations->push_front(str[i]);
		}
	}
	while (operations->Is_empty()) {
		result = operation(operations->pop_front(), operands);
		operands->push_front(result);
	}

	return result;
}
