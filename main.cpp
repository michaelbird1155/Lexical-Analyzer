//
//  main.cpp
//  Project1
//
//  Created by Michael Bird on 6/25/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include "LexicalAnalysis.h"

using namespace std;

string convertToken(int t) {
    switch (t) {
        case SPACE:  return "SPACE";
        //case LETTER: return "LETTER";
        //case DIGIT:  return "DIGIT";
        //case PLUS_CODE:  return "PLUS_CODE";
        case IDENT:  return "ID";
        case INT_LIT:return "INT_LIT";
        case ERROR:  return "ERROR";
        case STOP:  return "STOP";
        case COMMA:  return "COMMA";
        case PERIOD:  return "PERIOD";
        case Q_MARK:  return "Q_MARK";
        case LEFT_PAREN:  return "LEFT_PAREN";
        case RIGHT_PAREN:  return "RIGHT_PAREN";
        case COLON:  return "COLON";
        case COLON_DASH:  return "COLON_DASH";
        case SCHEMES:  return "SCHEMES";
        case FACTS:  return "FACTS";
        case RULES:  return "RULES";
        case QUERIES:  return "QUERIES";
        case ID:  return "ID";
        case STRING:  return "STRING";
        case QUOTATION: return "QUOTATION";
        case COMMENT: return "COMMENT";
        default:  return "UNKNOWN";
    }
}

int main (void)
{
    ofstream outputFile("/Users/birdman/Documents/Project1/Project1/output.txt");
    ifstream inputFile("/Users/birdman/Documents/Project1/Project1/input.txt");
    string line;
    long long length;
    
    inputFile.seekg(0, ios::end); // put the "cursor" at the end of the file
    length = inputFile.tellg(); // find the position of the cursor
    inputFile.seekg(0, ios::beg); //return the "cursor" at the beginning of the file
    
    if ( length == 0 ) {
        cout << "Failure: The file is empty!" << endl;
    }
    else {
        
        int token=SPACE;
        int linecount = 0;
        int tokencount = 0;
        
        
        while(getline(inputFile, line)) {
            
            linecount++;
            
            LexAn *LA;
            LA = new LexAn(line);
            
            while (token != STOP) {
                
                tokencount++;
                token = LA->lex();
                
                if (token == STOP)
                    break; //do not show any end of line (STOP) tokens
                else if(token == PLUS_CODE) {
                    outputFile << "Input error on line " << linecount << endl;
                    return 0;
                }
                else if (token == ERROR)
                    outputFile << "Input error on line " << linecount << endl;
                else {
                    outputFile << "(" << convertToken(token) << ", \"" << LA->lexeme << "\", " << linecount << ")" << endl;
                }
            }
            token = 0; //resets the token so that the getline while loop doesnt stop at the STOP.
        }
        outputFile << "Total Tokens: " << tokencount - linecount << endl;
    }
}


