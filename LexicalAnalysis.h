

#if !defined(_LA_)
#define _LA_

#include <iostream>
#include <string>


using namespace std;

enum {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, SEMI_COLON, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, DASH, QUOTATION, COMMENT, DIGIT, LETTER, IDENT, INT_LIT, ERROR, SPACE, STOP, PLUS_CODE};

class LexAn  
{

public:
	char nextChar;
	int charClass;
	string lexeme;

private:
	string input;

public:
	int lex();
	void setNewInput(string in);
	LexAn(string in="");
	virtual ~LexAn();

private:
	void addChar();
	void getChar();
};


#endif