

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
	else next_char = '$';

	char_class = ERROR;

	if ( (next_char > 64 && next_char <91) || (next_char > 96 && next_char <123) )
		char_class = LETTER;

	if ( next_char > 47 && next_char <58 )
		char_class = DIGIT;

	if (next_char == ' ') char_class = SPACE;
	if (next_char == '$') char_class = STOP;
	if (next_char == '+') char_class = PLUS_CODE;
    if (next_char == '?') char_class = Q_MARK;
    if (next_char == ',') char_class = COMMA;
    if (next_char == '.') char_class = PERIOD;
    if (next_char == '(') char_class = LEFT_PAREN;
    if (next_char == ')') char_class = RIGHT_PAREN;
    if (next_char == ':') char_class = COLON;
    if (next_char == ';') char_class = SEMI_COLON;
    if (next_char == '-') char_class = DASH;
    if (next_char == '#') char_class = COMMENT;
    if (next_char == 39)  char_class = QUOTATION;
   
}

//  adds the character to the lexeme string

void LexAn::add_char()
{
	lexeme+=next_char;
}

//

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
        while (char_class == LETTER || char_class == DIGIT || char_class == QUOTATION || char_class  == SPACE) {
            add_char();
            get_char();
        }
        if (lexeme.back() == ' ')
            lexeme.erase( lexeme.size() - 1 ); // erase the last character
          
        if (lexeme.front() == 39 && lexeme.back() == 39) { //erases the first and last ' in the lexeme
            lexeme.erase( 0, 1 ); // erase the first character
            lexeme.erase( lexeme.size() - 1 ); // erase the last character
        }
        else
            return ERROR;
        return STRING;
        break;
    default:
          return ERROR;
  } 

}
