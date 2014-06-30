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
#include "LexicalAnalyzer.h"

using namespace std;

// function to returns enum values as strings.

string tokenizer(int token) {
    switch (token) {
        case SPACE:  return "SPACE";
        case INTEGER:return "INTEGER";
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

int main (int argc, char *argv[])
{
    ifstream inputFile(argv[4]);
    ofstream outputFile(argv[5]);
    string line;
    long long length;
    
    inputFile.seekg(0, ios::end);   //  put the "cursor" at the end of the file
    length = inputFile.tellg();     //  find the position of the cursor
    inputFile.seekg(0, ios::beg);   //  return the "cursor" at the beginning of the file
    
    if ( length == 0 ) {            //  checks for the file length
        outputFile << "Failure: The file is empty!" << endl;
    }
    else {
        
        int token=SPACE;
        int linecount = 0;
        int tokencount = 0;
        
        //  Use getline to handle the code line by line which will make it easy to get the line numbers
        
        while(getline(inputFile, line)) {
            
            linecount++;
            
            LexAn *LA;
            LA = new LexAn(line);
            
            //  keeps reading in characters until the endline STOP token appears
            
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
                    outputFile << "(" << tokenizer(token) << ", \"" << LA->lexeme << "\", " << linecount << ")" << endl;
                }
            }
            token = 0; //resets the token so that the getline while loop moves to the next line.
        }
        outputFile << "Total Tokens: " << tokencount - linecount << endl;
    }
}


