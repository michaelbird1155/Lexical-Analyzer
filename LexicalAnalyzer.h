
//
//  LexicalAnalyzer.h
//  Project1
//
//  Created by Michael Bird on 6/25/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.

#include <iostream>
#include <string>


using namespace std;

//  list of enum types

enum tokens {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, SEMI_COLON, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, DASH, QUOTATION, COMMENT, BACK_SLASH, DIGIT, UNDERSCORE, TAB, LETTER, INTEGER, ERROR, SPACE, STOP, PLUS_CODE, EPSILON};

//  the class and its public and private methods and values

class LexAn  
{

public:
	char next_char;
	int char_class;
    int char_everything;
	string lexeme;
    
    int lex();
    int rule1();
    int rule2();
    int rule3();
	void new_input(string in);
	LexAn(string in="");
	virtual ~LexAn();

private:
	string input;
    
    void add_char();
	void get_char();


};
