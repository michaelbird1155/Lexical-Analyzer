

#include "LexicalAnalysis.h"



LexAn::LexAn(string in) : input(in), charClass(ERROR), nextChar(' '), lexeme("")
{
	getChar();
}

LexAn::~LexAn()
{

}

void LexAn::setNewInput(string in) 
{
	input=in;
	getChar();

}

void LexAn::getChar()
{
	if (input.size()>0) {
	  nextChar = input[0];
	  input.erase(0,1);
	}
	else nextChar = '$';

	charClass = ERROR;

	if ( (nextChar > 64 && nextChar <91) || (nextChar > 96 && nextChar <123) )
		charClass = LETTER;

	if ( nextChar > 47 && nextChar <58 )
		charClass = DIGIT;

	if (nextChar == ' ') charClass = SPACE;
	if (nextChar == '$') charClass = STOP;
	if (nextChar == '+') charClass = PLUS_CODE;
    if (nextChar == '?') charClass = Q_MARK;
    if (nextChar == ',') charClass = COMMA;
    if (nextChar == '.') charClass = PERIOD;
    if (nextChar == '(') charClass = LEFT_PAREN;
    if (nextChar == ')') charClass = RIGHT_PAREN;
    if (nextChar == ':') charClass = COLON;
    if (nextChar == ';') charClass = SEMI_COLON;
    if (nextChar == '-') charClass = DASH;
    if (nextChar == '#') charClass = COMMENT;
    if (nextChar == 39)  charClass = QUOTATION;
   
}

void LexAn::addChar()
{
	lexeme+=nextChar;
}

int LexAn::lex()
{

  lexeme="";

  while (charClass == SPACE)
      getChar();

  if (charClass == ERROR) {
      addChar();
      getChar();
      return ERROR;
  }
  if (charClass == STOP)
      return STOP;

  switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
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
            return IDENT;
	  break;
	case DIGIT: 
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        return INT_LIT;
        break;
    case PLUS_CODE:
        addChar();
        getChar();
        return PLUS_CODE;
        break;
    case COMMA:
        addChar();
        getChar();
        return COMMA;
        break;
    case PERIOD:
        addChar();
        getChar();
        return PERIOD;
        break;
    case Q_MARK:
        addChar();
        getChar();
        return Q_MARK;
        break;
    case LEFT_PAREN:
        addChar();
        getChar();
        return LEFT_PAREN;
        break;
    case RIGHT_PAREN:
        addChar();
        getChar();
        return RIGHT_PAREN;
        break;
    case COLON:
        addChar();
        getChar();
        while(charClass == DASH) {
            addChar();
            getChar();
        }
        if (lexeme == ":-") 
            return COLON_DASH;
        else
            return COLON;
        break;
    case DASH:
        addChar();
        getChar();
        return DASH;
        break;
    case COLON_DASH:
        addChar();
        getChar();
        return COLON_DASH;
        break;
    case SEMI_COLON:
        addChar();
        getChar();
        return SEMI_COLON;
        break;
    case COMMENT:
        addChar();
        getChar();
        return STOP;
        break;
    case QUOTATION:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT || charClass == QUOTATION || charClass  == SPACE) {
            addChar();
            getChar();
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
