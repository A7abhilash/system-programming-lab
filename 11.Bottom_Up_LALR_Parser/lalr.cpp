#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <utility>

using namespace std;

#define TOKEN_CASE(chr, tkn) \
	case chr: \
		cur = lookahead + 1; \
		return tkn;


enum class Token {
	A, B, C, D, EOI, ERR
};

string token_to_str(const Token& token) {
	switch(token) {
		case Token::A:
			return "<A>";
		case Token::B:
			return "<B>";
		case Token::C:
			return "<C>";
		case Token::D:
			return "<D>";
		case Token::EOI:
			return "<$>";
		case Token::ERR:
			return "<ERROR>";
		default:
			return "unrecognized token";
	}
}

class Lexer {
public:
	Lexer(const string input) {
		input_buffer = input;
	}
	
	Token next() {
		if (cur >= input_buffer.size()) {
			// No more input to read, return end of input token
			return Token::EOI;
		}
		
		// Ignore whitespace
		while (input_buffer[cur] == ' ' || input_buffer[cur] == '\t') cur++;

		int lookahead = cur;
		switch(input_buffer[lookahead]) {
			TOKEN_CASE('a', Token::A)
			TOKEN_CASE('b', Token::B)
			TOKEN_CASE('c', Token::C)
			TOKEN_CASE('d', Token::D)
			TOKEN_CASE('\0', Token::EOI)
			// case 'i':
			// 	if (input_buffer[++lookahead] == 'd') {
			// 		cur = lookahead + 1;
			// 		return Token::ID;
			// 	}
			// 	error();
			// 	return Token::ERR;
			default:
				error();
				return Token::ERR;
		}
	}
	
	void display_current_state(const string& msg) {
		cout << input_buffer << endl;
		for(int i = 0; i < cur; i++) cout << ' ';
		cout << "^ " << msg << endl;
	}

private:
	void error() {
		cout << "Lex error: " << endl << input_buffer << endl;
		for(int i = 0; i < cur; i++) cout << ' ';
		cout << "^ error occurred while trying to lex." << endl;
	}

	int cur = 0;
	string input_buffer;
};

class Action {
public:
	enum ActionType {
		Shift,
		Reduce,
		Accept,
		Error
	};

	ActionType type;
};

class ShiftAction : public Action {
public:
	ShiftAction(int shiftState)
		:shift_state(shiftState)  {
		type = Action::Shift;
	}
	int shift_state;
};

class ReduceAction : public Action {
public:
	ReduceAction(const string& productionLhs, const string& productionRhs)
		:production_lhs(productionLhs), production_rhs(productionRhs), pop_amt(productionRhs == "id" ? 1 : productionRhs.size())  {
		type = Action::Reduce;
	}
	int pop_amt;
	string production_lhs;
	string production_rhs;
};

class Parser {
public:
	Parser(map<pair<int, Token>, Action*> actionMap, map<pair<int, string>, int> gotoMap)
		:action_map(actionMap), goto_map(gotoMap) {
		parse_stack.push(0);
	}

	bool parse(const string& input) {
		cout << "Parse Stack\tAction" << endl;
		cout << "-------------------------------------------" << endl;
		display();
		cout << "\t\tInitially" << endl;
		Lexer lex(input);
		Token a = lex.next();
		while (true) {
			if (a == Token::ERR) return false;
			int s = parse_stack.top();
			if (action_map[{s, a}]->type == Action::Shift) {
				ShiftAction* sa = reinterpret_cast<ShiftAction*>(action_map[{s, a}]);
				parse_stack.push(sa->shift_state);
				display();
				cout << "\t\tShift " << sa->shift_state<< endl;
				a = lex.next();
			} else if (action_map[{s, a}]->type  == Action::Reduce) {
				ReduceAction* ra = reinterpret_cast<ReduceAction*>(action_map[{s, a}]);
				for (int i = 0; i < ra->pop_amt; i++) parse_stack.pop();
				int t = parse_stack.top();
				if (goto_map[{t, ra->production_lhs}] == -1) {
					error(a, lex);
					return false;
				}
				parse_stack.push(goto_map[{t, ra->production_lhs}]);
				display();
				cout << "\t\tReduce using production " << ra->production_lhs << " -> " << ra->production_rhs << endl;
			} else if (action_map[{s, a}]->type == Action::Accept) {
				return true;
			} else {
				error(a, lex);
				return false;
			}
		}
	}
private:
	stack<int> parse_stack;
	map<pair<int, Token>, Action*> action_map;
	map<pair<int, string>, int> goto_map;

	void error(Token cur_token, Lexer& lex) {
		cout << "Encountered error while parsing : Unexpected token " << token_to_str(cur_token) << endl;
		lex.display_current_state("Parse error");
	}

	void display(){
		int n = parse_stack.size();
		int arr[n];
		for (int i = n - 1; i >= 0;i--){
			arr[i]=parse_stack.top();
			parse_stack.pop();
		}
		for (int i = 0; i <n ;i++){
			cout << arr[i];
			parse_stack.push(arr[i]);
		}
		// cout << endl;
	}
};

#define ERROR_ACTION new Action {.type = Action::Error}
#define ACCEPT_ACTION new Action {.type = Action::Accept}
#define SHIFT_ACTION(i) new ShiftAction(i)
#define REDUCE_ACTION(i) new ReduceAction(productions[i][0], productions[i][1])

int main() {
	string productions[7][2] = {
		{"S'", "S"},
		{"S" , "Pa"},
		{"S" , "bPc"},
		{"S" , "dc"},
		{"S" , "bda"},
		{"P" , "d"}
	};

	map<pair<int, Token>, Action*> action_map;
	map<pair<int, string>, int> goto_map;

	// initialize goto_map
	for (int i = 0; i < 7; i++)
		for (int j = 0; j <= 21; j++)
			goto_map[{j, productions[i][0]}] = -1;

	// Define parse table : Action
	action_map[{0, Token::A}]  = ERROR_ACTION     ; action_map[{0, Token::B}]  = SHIFT_ACTION(3)  ; action_map[{0, Token::C}]  = ERROR_ACTION     ; action_map[{0, Token::D}]  = SHIFT_ACTION(4)  ; action_map[{0, Token::EOI}]  = ERROR_ACTION      ;
	action_map[{1, Token::A}]  = ERROR_ACTION 	  ; action_map[{1, Token::B}]  = ERROR_ACTION     ; action_map[{1, Token::C}]  = ERROR_ACTION     ; action_map[{1, Token::D}]  = ERROR_ACTION     ; action_map[{1, Token::EOI}]  = ACCEPT_ACTION     ;
	action_map[{2, Token::A}]  = SHIFT_ACTION(5)  ; action_map[{2, Token::B}]  = ERROR_ACTION     ; action_map[{2, Token::C}]  = ERROR_ACTION     ; action_map[{2, Token::D}]  = ERROR_ACTION     ; action_map[{2, Token::EOI}]  = ERROR_ACTION      ;
	action_map[{3, Token::A}]  = ERROR_ACTION     ; action_map[{3, Token::B}]  = ERROR_ACTION     ; action_map[{3, Token::C}]  = ERROR_ACTION     ; action_map[{3, Token::D}]  = SHIFT_ACTION(7)  ; action_map[{3, Token::EOI}]  = ERROR_ACTION      ;
	action_map[{4, Token::A}]  = REDUCE_ACTION(5) ; action_map[{4, Token::B}]  = ERROR_ACTION     ; action_map[{4, Token::C}]  = SHIFT_ACTION(8)  ; action_map[{4, Token::D}]  = ERROR_ACTION     ; action_map[{4, Token::EOI}]  = ERROR_ACTION      ;
	action_map[{5, Token::A}]  = ERROR_ACTION     ; action_map[{5, Token::B}]  = ERROR_ACTION     ; action_map[{5, Token::C}]  = ERROR_ACTION     ; action_map[{5, Token::D}]  = ERROR_ACTION     ; action_map[{5, Token::EOI}]  = REDUCE_ACTION(1)  ;
	action_map[{6, Token::A}]  = ERROR_ACTION     ; action_map[{6, Token::B}]  = ERROR_ACTION     ; action_map[{6, Token::C}]  = SHIFT_ACTION(9)  ; action_map[{6, Token::D}]  = ERROR_ACTION     ; action_map[{6, Token::EOI}]  = ERROR_ACTION      ;
	action_map[{7, Token::A}]  = SHIFT_ACTION(10) ; action_map[{7, Token::B}]  = ERROR_ACTION     ; action_map[{7, Token::C}]  = REDUCE_ACTION(5) ; action_map[{7, Token::D}]  = ERROR_ACTION     ; action_map[{7, Token::EOI}]  = ERROR_ACTION      ;
	action_map[{8, Token::A}]  = ERROR_ACTION     ; action_map[{8, Token::B}]  = ERROR_ACTION     ; action_map[{8, Token::C}]  = ERROR_ACTION     ; action_map[{8, Token::D}]  = ERROR_ACTION     ; action_map[{8, Token::EOI}]  = REDUCE_ACTION(3)  ;
	action_map[{9, Token::A}]  = ERROR_ACTION     ; action_map[{9, Token::B}]  = ERROR_ACTION     ; action_map[{9, Token::C}]  = ERROR_ACTION     ; action_map[{9, Token::D}]  = ERROR_ACTION     ; action_map[{9, Token::EOI}]  = REDUCE_ACTION(2)  ;
	action_map[{10, Token::A}] = ERROR_ACTION     ; action_map[{10, Token::B}] = ERROR_ACTION     ; action_map[{10, Token::C}] = ERROR_ACTION     ; action_map[{10, Token::D}] = ERROR_ACTION     ; action_map[{10, Token::EOI}] = REDUCE_ACTION(4)  ;

	// Define parse table : Goto
	goto_map[{0, "S"}] = 1; goto_map[{0, "P"}] = 2;
	goto_map[{3, "P"}] = 6; 

	// Create parser
	Parser parser(action_map, goto_map);
	string input;
	cout << "Enter string to parse :";
	getline(cin, input);
	bool result=parser.parse(input);
	result ? cout << "\n***Valid input***\n" : cout << "\n***Invalid input***\n";
}