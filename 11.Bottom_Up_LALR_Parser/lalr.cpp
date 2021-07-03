#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <sstream>
#include <algorithm>
#include <functional>

using namespace std;

// FOR TREE DRAWING
class TextBox {
public:
    struct xy {
        TextBox& tb;
        int x, y;

        xy operator<< (const string& s) const {
            return {tb, x + tb.puts(x, y, s), y};
        }

        xy operator<< (const int i) const {
            string s = to_string(i);
            return {tb, x + tb.puts(x, y, s), y};
        }

        xy operator<< (const char c) const {
            tb.putc(x, y, c);
            return {tb, x + 1, y};
        }

        xy operator<< (const TextBox& _tb) const {
            tb.puttb(x, y, _tb);
            return {tb, x + _tb.width(), y};
        }
    };

    string str() const {
        stringstream ss;
        for (auto& s : m_buffer) {
            //ss << s << '\n';
            for (char c : s) {
                if (c > 0b1111)
                    ss << c;
                else {
                    switch (static_cast<int>(c) & 0b1111) {
                        case 0b01:
                            ss << '-';
                            break;
                        case 0b10:
                            ss << '|';
                            break;
                        case 0b11:
                            ss << '.';
                            break;
                        default:
                            ss << c;
                    }
                }
            }
            ss << '\n';
        }
        return ss.str();
    }
    
    TextBox::xy operator() (int x, int y) const {
        return {const_cast<TextBox&>(*this), x, y};
    }
    

    int width() const {
        int w = -1;
        for (auto& s : m_buffer) 
            w = max(w, static_cast<int>(s.size()));
        return w;
    }

    int height() const {
        return m_buffer.size();
    }

    void hline(int x, int y, int width) {
        if (y >= m_buffer.size())
            m_buffer.resize(y+1);
        if (x+width >= m_buffer[y].size())
            m_buffer[y].resize(x+width, ' ');

        for (int i = 0; i < width; i++) {
            if (m_buffer[y][x+i] > 0b1111)
                m_buffer[y][x+i] = 0;
            m_buffer[y][x+i] |= 0b1;
        }
    }

    void vline(int x, int y, int height) {
        if (y+height >= m_buffer.size())
            m_buffer.resize(y+height);
        for (int i = 0; i < height; i++) {
            if (x >= m_buffer[y+i].size())
                m_buffer[y+i].resize(x+1, ' ');
            if (m_buffer[y+i][x] > 0b1111)
                m_buffer[y+i][x] = 0;
            m_buffer[y+i][x] |= 0b10;
        }
    }

private:

    void putc(int x, int y, char c) {
        if (y >= m_buffer.size())
            m_buffer.resize(y+1);
        if (x >= m_buffer[y].size())
            m_buffer[y].resize(x+1, ' ');
        m_buffer[y][x] = c;
    }
    
    int puts(int x, int y, const string& s) {
        if (s.empty()) return x;
        for (int i = 0; i < s.size(); i++)
            putc(x+i, y, s[i]);
        return x + s.size();
    }
    
    void puttb(int x, int y, const TextBox& tb) {
        for (int i = 0; i < tb.height(); i++) {
            puts(x, y+i, tb.m_buffer[i]);
        }
    }

private:
    vector<string> m_buffer;
};


struct Tree {
    struct TreeNode {
        string data;
        vector<TreeNode> children;
        
        TreeNode(string _data) : data(_data)  {}

        void add_child(string c) {
            children.emplace_back(c);
        }
    };

	bool rightmost_add(string& lhs, string& rhs) {
		bool added = false;
		_rightmost_add(root, lhs, rhs, added);
		return added;
	}

	void _rightmost_add(TreeNode& n, string& lhs, string& rhs, bool& added) {
		if (added) return;

		if (n.children.size() == 0) {
			if (n.data == lhs) {
				if (rhs != "id") {
					for (char c : rhs) n.children.emplace_back(string(1, c));
				} else {
					n.children.emplace_back("id");
				}
				added = true;
			}
		}

		for (auto i = n.children.rbegin(); i < n.children.rend(); i++) {
			_rightmost_add(*i, lhs, rhs, added);
		}
	}

    TreeNode root;

    Tree(string _root) : root(_root) {}
    
    friend ostream& operator<< (ostream& os, Tree& tree) {
        TextBox tb = create_tree_textbox(tree.root);
        os << tb.str();
        return os;
    }
private:
    static TextBox create_tree_textbox(const TreeNode& node) {
        TextBox tb;
        constexpr int padding = 2;
        tb(0, 0) << node.data;
        if (node.children.empty())
            return tb;

        vector<TextBox> child_tbs;
        for (auto child : node.children)
            child_tbs.push_back(create_tree_textbox(child));
        
        tb.vline(0, 1, 1);
        int i = 0;
        for (auto child : child_tbs) {
            tb.vline(i, 2, 2);
            tb(i, 4) << child;
            i += child.width() + padding;
        }
        tb.hline(0, 2, i - child_tbs[child_tbs.size() - 1].width() - padding + 1);

        return tb;
    }
};

// TREE DRAWING END


#define TOKEN_CASE(chr, tkn) \
	case chr: \
		cur = lookahead + 1; \
		return tkn;

template <class T, class Container = deque<T>>
class printable_stack : public stack<T, Container> {
	friend ostream& operator<<(ostream& os, const printable_stack<T, Container>& stk) {
		stringstream ss;
		ss << "[";
		for (auto i : stk.c)
			ss << " " << i;
		ss << " ]";
		os << ss.str();
		return os;
	}
};

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
			default:
				error();
				return Token::ERR;
		}
	}

	friend ostream& operator<<(ostream& os, const Lexer& lex) {
		stringstream ss;
		for (int i = (lex.input_buffer[lex.cur] == ' ')? lex.cur + 1 : lex.cur; i < lex.input_buffer.size(); i++) ss << lex.input_buffer[i];
		ss << " $";
		os << ss.str();
		return os;
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
	ReduceAction(const string& productionLhs, const string& productionRhs, int i)
		:production_lhs(productionLhs), production_rhs(productionRhs), pop_amt(productionRhs == "id" ? 1 : productionRhs.size()), production_id(i)  {
		type = Action::Reduce;
	}
	int production_id;
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
		Lexer lex(input);
		cout << left << setw(25) << "Stack"     << setw(25) << "Current Token" << setw(25) << "Input" << setw(25) << "Action" << endl;
		cout << left << setw(25) << parse_stack << setw(25) << "- "            << setw(25) << lex     << setw(25) << "-"<< endl;
		Token a = lex.next();
		while (true) {
			if (a == Token::ERR) return false;
			int s = parse_stack.top();
			if (action_map[{s, a}]->type == Action::Shift) {
				ShiftAction* sa = reinterpret_cast<ShiftAction*>(action_map[{s, a}]);
				parse_stack.push(sa->shift_state);
				cout << left << setw(25) << parse_stack << setw(25) << token_to_str(a) << setw(25) << lex << setw(25) << "Shift to " + to_string(sa->shift_state) << endl;
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
				cout << left << setw(25) << parse_stack << setw(25) << token_to_str(a) << setw(25) << lex << setw(25) << "Reduce by " + ra->production_lhs + " -> " + ra->production_rhs << endl;
				//cout << "Using production " << ra->production_lhs << " -> " << ra->production_rhs << endl;
				production_stack.push({ra->production_lhs, ra->production_rhs});
			} else if (action_map[{s, a}]->type == Action::Accept) {
				cout << left << setw(25) << parse_stack << setw(25) << token_to_str(a) << setw(25) << lex << setw(25) << "Accepted" << endl;
				Tree pt = create_parse_tree();
				cout << "\nThe parse tree for the string is : \n" << pt << "\n";
				return true;
			} else {
				error(a, lex);
				return false;
			}
		}
	}
private:
	printable_stack<int> parse_stack;
	map<pair<int, Token>, Action*> action_map;
	map<pair<int, string>, int> goto_map;
	stack<pair<string, string>> production_stack;

	void error(Token cur_token, Lexer& lex) {
		cout << "Encountered error while parsing : Unexpected token " << token_to_str(cur_token) << endl;
		lex.display_current_state("Parse error");
	}

	void print_state() {
		cout << "This is test string, this string is supposed to be very big, lets see";
		cout << endl;
	}

	Tree create_parse_tree() {
		Tree parse_tree("S");
		while (!production_stack.empty()) {
			auto prod = production_stack.top(); production_stack.pop();
			parse_tree.rightmost_add(prod.first, prod.second);
		}
		return parse_tree;
	}
};

#define ERROR_ACTION new Action {.type = Action::Error}
#define ACCEPT_ACTION new Action {.type = Action::Accept}
#define SHIFT_ACTION(i) new ShiftAction(i)
#define REDUCE_ACTION(i) new ReduceAction(str_productions[i][0], str_productions[i][1],i)

typedef pair<string, string> production;

struct Item {
	Item(string l, string r, string la = "$") : lhs(l), rhs(r), dot_idx(0), lookahead(la) {}
	Item(string l, string r, int di, string la = "$") : lhs(l), rhs(r), dot_idx(di), lookahead(la) {}
    Item(production p, string la = "$") : lhs(p.first), rhs(p.second), dot_idx(0), lookahead(la) {}
    Item(production p, int di, string la = "$") : lhs(p.first), rhs(p.second), dot_idx(di), lookahead(la) {}

    bool operator==(const Item& other) const {
        return (lhs == other.lhs) && (rhs == other.rhs) && (dot_idx == other.dot_idx) && (lookahead == other.lookahead);
    }

    bool operator<(const Item& other) const {
        return (lhs < other.lhs) && (rhs < other.rhs) && (dot_idx < other.dot_idx) && (lookahead < other.lookahead);
    }

    friend ostream& operator<<(ostream& os, const Item& i) {
        int idx = i.dot_idx;
        os << "[" << i.lhs << " -> " << i.rhs.substr(0, idx) << "." << i.rhs.substr(idx) << " , " << i.lookahead << "]";
        return os; 
    }

	string lhs;
	string rhs;
    string lookahead = "$";
	int dot_idx;
};

string str_productions[7][2] = {
	{"S'", "S"},
	{"S" , "Pa"},
	{"S" , "bPc"},
	{"S" , "dc"},
	{"S" , "bda"},
	{"P" , "d"}
};

struct Grammar {

    Grammar(vector<production> p) : productions(p) {
        for (auto& i : p)
            non_terminals.insert(i.first);
        generate_lr1_items();
    }

    set<string> first(string s) {
        set<string> first_set;
        for (char c : s) {
            if (non_terminals.find(string(1, c)) == non_terminals.end()) {
                first_set.insert(string(1,c));
                break;
            } else {
                string nt = string(1, c);
                for (auto p : productions) if (p.first == nt && p.second[0] != nt[0]) {
                    auto tmp = first(p.second);
                    first_set.insert(tmp.begin(), tmp.end());
                }
            }
        }
        return first_set;
    }

    vector<Item> closure(vector<Item> I) {
        bool done = false;
        while (!done) {
            done = true;
            for (int i = 0; i < I.size(); i++) {
                Item item = I[i];
                if (non_terminals.find(item.rhs.substr(item.dot_idx, 1)) != non_terminals.end()) {
                    string nt = item.rhs.substr(item.dot_idx, 1);
                    string remaining = item.rhs.substr(item.dot_idx+1) + item.lookahead;
                    for (auto p : productions) if (p.first == nt) {
                        auto s = first(remaining);
                        for (auto k : s) {
                            auto u = Item(p, k);
                            bool exists = false;
                            for (auto& x : I) {
                                if (x.dot_idx == u.dot_idx && x.lhs == u.lhs && x.rhs == u.rhs && x.lookahead == u.lookahead) {
                                    exists = true;
                                    break;
                                }
                            }
                            if (!exists) {
                                I.push_back(u);
                                done = false;
                            }
                        }
                    }
                }
            }
        }
        return I;
    }

    vector<Item> Goto(vector<Item> I, string X) {
        vector<Item> J;
        for (auto i : I) {
            if (i.rhs[i.dot_idx] == X[0]) J.push_back(Item(i.lhs, i.rhs,  i.dot_idx+1, i.lookahead));
        }
        return closure(J);
    }

    bool is_in_item_set(vector<Item> set) {
        for (auto soi : item_set) {
            if (set == soi) return true;
        }
        return false;
    }

    void generate_lr1_items() {
        item_set.push_back(closure({Item(productions[0])}));
        vector<string> grammar_symbols = {"S", "P", "F", "a", "b", "c", "d",};
        bool done = false;
        while (!done) {
            done = true;
            for (int i = 0; i < item_set.size(); i++) {
                for (auto symb : grammar_symbols) {
                    auto g = Goto(item_set[i], symb);
                    if (g.size() != 0 && !is_in_item_set(g)) {
                        goto_history.push_back({i, symb});
                        item_set.push_back(g);
                        done = false;
                    } else if (g.size() != 0) {
						int k;
						for (k = 0; k < item_set.size() && item_set[k] != g; k++);
						existing_goto_history.push_back({{i, symb}, k});
					}
                }
            }
        }
        clean_item_set();
    }

    void clean_item_set() {
        for (auto& x : item_set) {
			vector<Item> cleaned;
			for (auto i : x) {
				bool exists = false;
				for (auto k : cleaned) {
					if (k.lhs == i.lhs && k.rhs == i.rhs && k.dot_idx == i.dot_idx) {
						exists = true;
						break;
					}
				}
				if (exists) continue;
				Item ni(i.lhs, i.rhs, i.dot_idx, "");
				set<string> lookaheads;
				for (auto tmp : x) {
					if (tmp.lhs == ni.lhs && tmp.rhs == ni.rhs && tmp.dot_idx == ni.dot_idx) {
						lookaheads.insert(tmp.lookahead);
					}
				}
				ni.lookahead = *(lookaheads.begin());
				for (auto i : lookaheads)
					if (i != *lookaheads.begin()) ni.lookahead = ni.lookahead + "/" + i;
				cleaned.push_back(ni);
			}

			x = cleaned;
		}
    }

	map<pair<int, Token>, Action*> action_map() {
		map<pair<int, Token>, Action*> action_map;

		// init action map
		for (auto token : {Token::A, Token::B, Token::C, Token::D, Token::EOI}) {
			for (int i = 0; i < item_set.size(); i++)
				action_map[{i, token}] = nullptr;
		}

		// add shift actions
		for (int i = 0; i < existing_goto_history.size(); i++) {
			if (non_terminals.find(existing_goto_history[i].first.second) == non_terminals.end()) {
				if (action_map[{existing_goto_history[i].first.first, token_map[existing_goto_history[i].first.second]}] == nullptr)
					action_map[{existing_goto_history[i].first.first, token_map[existing_goto_history[i].first.second]}] = SHIFT_ACTION(existing_goto_history[i].second); 
			}
		}

		// add reduce actions
		map<string, int> reduction_map = {
			{"S", 0}, {"Pa", 1}, {"bPc", 2}, {"dc", 3}, {"bda", 4}, {"d", 5}
		};
		for (int i = 2; i < item_set.size(); i++) {
			for (auto item : item_set[i]) {
				if (item.dot_idx == item.rhs.size()) {
					for (char c : item.lookahead) if (c != '/') {
						string lah(1, c);
						action_map[{i, token_map[lah]}] = REDUCE_ACTION(reduction_map[item.rhs]);
					}
				}
			}
		}

		// add accept action
		action_map[{1, Token::EOI}] = ACCEPT_ACTION;

		// add err actions
		for (auto token : {Token::A, Token::B, Token::C, Token::D, Token::EOI}) {
			for (int i = 0; i < item_set.size(); i++) if (action_map[{i, token}] == nullptr) {
				action_map[{i, token}] = ERROR_ACTION;
			}
		}

		
		return action_map;
	}

	map<pair<int, string>, int> goto_map() {
		map<pair<int, string>, int> goto_map;

		// initialize goto_map
		for (int i = 0; i < productions.size(); i++)
			for (int j = 0; j <= item_set.size(); j++)
				goto_map[{j, str_productions[i][0]}] = -1;
		
		for (int i = 0; i < existing_goto_history.size(); i++) {
			if (non_terminals.find(existing_goto_history[i].first.second) != non_terminals.end()) {
				if (goto_map[{existing_goto_history[i].first.first, existing_goto_history[i].first.second}] == -1)
					goto_map[{existing_goto_history[i].first.first, existing_goto_history[i].first.second}] = existing_goto_history[i].second; 
			}
		}

		return goto_map;
	}

	bool has_same_core(vector<Item>& i1, vector<Item>& i2) {
		if (i1.size() != i2.size()) return false;
		for (auto p : i1) {
			bool exists = false;
			for (auto op : i2) if(p.lhs == op.lhs && p.rhs == op.rhs && p.dot_idx == op.dot_idx) {
				exists = true;
				break;
			}
			if (exists == false) return false;
		}
		return true;
	}

	vector<pair<int, vector<int>>> lalr_grouping() {
		int idx = 0;
		set<int> used_states;
		vector<pair<int, vector<int>>> ans;
		for (int i = 0; i < item_set.size(); i++) {
			if (used_states.find(i) != used_states.end()) continue;
			vector<int> grouping {i};
			used_states.insert(i);
			for (int j = i + 1; j < item_set.size(); j++) {
				if (used_states.find(j) != used_states.end()) continue;
				if (has_same_core(item_set[i], item_set[j])) {
					grouping.push_back(j);
					used_states.insert(j);
				}
			}
			ans.push_back({idx++, grouping});
		}
		return ans;
	}

	map<pair<int, Token>, Action*> lalr_action_map(map<pair<int, Token>, Action*>& clr_action_map) {
		auto grouping = lalr_grouping();
		map<int, int> old_to_new;
		for (auto g : grouping) for (auto i : g.second) old_to_new[i] = g.first;
		map<pair<int, Token>, Action*> new_action_map;
		for (auto token : {Token::A, Token::B, Token::C, Token::D, Token::EOI}) {
			for(int i = 0; i < item_set.size(); i++) {
				if (new_action_map.find({old_to_new[i], token}) == new_action_map.end() || new_action_map[{old_to_new[i], token}]->type == Action::Error) {
					if (clr_action_map[{i, token}]->type == Action::Shift) {
						ShiftAction* a = reinterpret_cast<ShiftAction*>(clr_action_map[{i, token}]);
						new_action_map[{old_to_new[i], token}] = SHIFT_ACTION(old_to_new[(a->shift_state)]);
					} else {
						new_action_map[{old_to_new[i], token}] = clr_action_map[{i, token}];
					}
				}
			}
		}

		return new_action_map;
	}

	map<pair<int, string>, int> lalr_goto_map(map<pair<int, string>, int>& clr_goto_map) {
		auto grouping = lalr_grouping();
		map<int, int> old_to_new;
		for (auto g : grouping) for (auto i : g.second) old_to_new[i] = g.first;
		map<pair<int, string>, int> new_goto_map;

		for (int i = 0; i < productions.size(); i++)
			for (int j = 0; j <= grouping.size(); j++)
				new_goto_map[{j, str_productions[i][0]}] = -1;

		for (auto kp : clr_goto_map) {
			int os = kp.first.first;
			if (old_to_new.find(os) == old_to_new.end() || old_to_new.find(kp.second) == old_to_new.end()) continue;
			int ns = old_to_new[os];
			int ngs = old_to_new[kp.second];
			string nt = kp.first.second;
			if (new_goto_map.find({ns, nt}) != new_goto_map.end()) {
				new_goto_map[{ns, nt}] = ngs;
			}
		}

		return new_goto_map;
	}

	void print_items() const {
		int i = 0;
		for (auto items : item_set) {
			cout << "State I" << i << endl;
			for (auto item : items) {
				cout << "[" << item << "]" << endl;
			}
			cout << "-------" << endl << endl;
			i++;
		}
	}

	void print_parse_table(map<pair<int, Token>, Action*> action_map, map<pair<int, string>, int> goto_map) {
		cout << "state\t+\t*\t(\t)\tid\t$\tE\tT\tF\n";
		for (int i = 0; i < item_set.size(); i++) {
			if (action_map.find({i, Token::EOI}) == action_map.end()) return;
			cout << i << "\t";
			for (auto token : {Token::A, Token::B, Token::C, Token::D, Token::EOI}) {
				switch(action_map[{i, token}]->type) {
					case Action::Shift: {
						ShiftAction* a = reinterpret_cast<ShiftAction*>(action_map[{i, token}]);
						cout << "s" << a->shift_state << "\t";
						break;
					}
					case Action::Reduce: {
						ReduceAction* a = reinterpret_cast<ReduceAction*>(action_map[{i, token}]);
						cout << "r" << a->production_id << "\t";
						break;
					}
					case Action::Accept: {
						cout << "acc\t"; 
						break;
					}
					case Action::Error: {
						cout << "\t";
						break;
					}
				}
			}

			for (auto nt : {"S", "P"}) {
				if (goto_map[{i, nt}] != -1) {
					cout << goto_map[{i, nt}] << "\t";
				} else {
					cout << "\t";
				}
			}
			cout << "\n";
		}
	}

	map<string, Token> token_map = {
		{"a", Token::A}, {"b", Token::B}, {"c", Token::C}, {"d", Token::D}, {"$", Token::EOI}
	};
    vector<pair<int, string>> goto_history;
	vector<pair<pair<int, string>, int>> existing_goto_history;
    set<string> non_terminals;
    vector<vector<Item>> item_set;
    vector<production> productions;
};

int main() {
	Grammar grammar({{"S'", "S"},
		{"S" , "Pa"},
		{"S" , "bPc"},
		{"S" , "dc"},
		{"S" , "bda"},
		{"P" , "d"}});

	cout << "Generated LR(1) Items: " << endl;
	grammar.print_items();

	map<pair<int, Token>, Action*> action_map = grammar.action_map();
	map<pair<int, string>, int> goto_map = grammar.goto_map();

	cout << "CLR Parse table :" << endl;
	grammar.print_parse_table(action_map, goto_map);

	auto tmp =  grammar.lalr_grouping();
	cout << endl << "LALR Groupings from CLR Items: " << endl;
	for (auto p : tmp) {
		cout << p.first << " = ";
		for (auto pt : p.second)
			cout << pt << " ";
		cout << endl;
	}
	cout << endl;

	map<pair<int, Token>, Action*> lalr_action_map = grammar.lalr_action_map(action_map);
	map<pair<int, string>, int> lalr_goto_map = grammar.lalr_goto_map(goto_map);

	cout << "LALR Parse table:" << endl;
	grammar.print_parse_table(lalr_action_map, lalr_goto_map);
	cout << endl;

	// Create parser
	Parser parser(lalr_action_map, lalr_goto_map);
	string input;
	cout << "Enter string to parse: ";
	getline(cin, input);
	parser.parse(input);
}
