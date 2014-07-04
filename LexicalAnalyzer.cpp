

//
//  LexicalAnalyzer.cpp
//  Project1
//
//  Created by Michael Bird on 6/25/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#include "LexicalAnalyzer.h"

//  initialize the constructor

LexAn::LexAn(string in) : input(in), char_class(ERROR), next_char(' '), lexeme("")
{
	get_char();
}

//  deconstruct the constructor

LexAn::~LexAn()
{
}

// gets the new input char

void LexAn::new_input(string in)
{
	input=in;
	get_char();
    
}

// gets the input char from new_input() and assigns its a character class

void LexAn::get_char()
{
	if (input.size()>0) {
        next_char = input[0];
        input.erase(0,1);
	}
	else
        next_char = '\n';
    
	char_class = ERROR;
    
    switch (next_char) {
        case 65 ... 90:
            char_class = LETTER;
            break;
        case 96 ... 123:
            char_class = LETTER;
            break;
        case 48 ... 57:
            char_class = DIGIT;
            break;
        case ' ':
            char_class = SPACE;
            break;
        case '\n':
            char_class = STOP;
            break;
        case '+':
            char_class = PLUS_CODE;
            break;
        case '?':
            char_class = Q_MARK;
            break;
        case ',':
            char_class = COMMA;
            break;
        case '.':
            char_class = PERIOD;
            break;
        case '(':
            char_class = LEFT_PAREN;
            break;
        case ')':
            char_class = RIGHT_PAREN;
            break;
        case ':':
            char_class = COLON;
            break;
        case ';':
            char_class = SEMI_COLON;
            break;
        case '-':
            char_class = DASH;
            break;
        case '#':
            char_class = COMMENT;
            break;
        case 39:
            char_class = QUOTATION;
            break;
        case 92:
            char_class = BACK_SLASH;
            break;
        case '_':
            char_class = UNDERSCORE;
            break;
        case 9:
            char_class = SPACE;
            break;
        default:
            char_class = ERROR;
            break;
    }
}

//  adds the character to the lexeme string

void LexAn::add_char()
{
	lexeme+=next_char;
}

//
int LexAn::rule1() {
    
    while (char_class == LETTER || char_class == DIGIT) {
        add_char();
        get_char();
    }
    
    if (lexeme == "Queries")
        return QUERIES;
    if (lexeme == "Schemes")
        return SCHEMES;
    if (lexeme == "Rules")
        return RULES;
    if (lexeme == "Facts")
        return FACTS;
    else
        return ID;
}

int LexAn::rule2() {
    
    while (char_class != QUOTATION && char_class != STOP) {
        add_char();
        get_char();
    }
    add_char();
    get_char();
    lexeme.erase( 0, 1 ); // erase the first character
    if (lexeme.back() == 39) {
        lexeme.erase( lexeme.size() - 1 ); // erase the last character
        return STRING;
    }
    else
        return ERROR;
} 

int LexAn::rule3() {
    
    while (char_class == LETTER || char_class == DASH) {
        add_char();
        get_char();
    }
    if (lexeme == "\n")
     return SPACE;
    else
     return ID;
}

int LexAn::lex()
{
    
    lexeme="";
    
    while (char_class == SPACE)   //  moves to the next character if there is a space. Does not add to the lexeme
        get_char();
    
    if (char_class == ERROR) {    //  simply throws an error if the character isnt recognized
        add_char();
        get_char();
        return ERROR;
    }
    if (char_class == STOP)       //  when line reaches the end, it produces a STOP token
        return STOP;
    
    switch (char_class) {         // switch statement for the other character classes.
        case LETTER:
            add_char();
            get_char();
            return rule1();
            break;
        case DIGIT:
            add_char();
            get_char();
            while (char_class == DIGIT) {
                add_char();
                get_char();
            }
            return INTEGER;
            break;
        case PLUS_CODE:
            add_char();
            get_char();
            return PLUS_CODE;
            break;
        case COMMA:
            add_char();
            get_char();
            return COMMA;
            break;
        case PERIOD:
            add_char();
            get_char();
            return PERIOD;
            break;
        case Q_MARK:
            add_char();
            get_char();
            return Q_MARK;
            break;
        case LEFT_PAREN:
            add_char();
            get_char();
            return LEFT_PAREN;
            break;
        case RIGHT_PAREN:
            add_char();
            get_char();
            return RIGHT_PAREN;
            break;
        case COLON:
            add_char();
            get_char();
            while(char_class == DASH) {
                add_char();
                get_char();
            }
            if (lexeme == ":-")
                return COLON_DASH;
            else
                return COLON;
            break;
        case DASH:
            add_char();
            get_char();
            return DASH;
            break;
        case COLON_DASH:
            add_char();
            get_char();
            return COLON_DASH;
            break;
        case SEMI_COLON:
            add_char();
            get_char();
            return SEMI_COLON;
            break;
        case COMMENT:
            add_char();
            get_char();
            return STOP;
            break;
        case QUOTATION:
            add_char();
            get_char();
            return rule2();
            //return STRING;
            break;
        case BACK_SLASH:
            add_char() ;
            get_char();
            return rule3();
            break;
        case UNDERSCORE:
            add_char() ;
            get_char();
            return ERROR;
            break;
        default:
            return ERROR;
    } 
    
}
