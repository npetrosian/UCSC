#! /usr/bin/env python3

# Author: Natalie Petrosian
# CSE 112 Comparative Programming Languages 
# Program 3: Tiny Language Interpreter in Python
# Professor McDowell


import fileinput
from enum import Enum
import sys
import re

# used to store a parsed TL expressions which are
# constant numbers, constant strings, variable names, and binary expressions

symTable = {
        "nextLineNum" : 0.0
}


# used to store a parsed TL expressions which are
# constant numbers, constant strings, variable names, and binary expressions
class Expr :
        def __init__(self,op1,operator,op2=None):
                self.op1 = op1
                self.operator = operator
                self.op2 = op2

        def __str__(self):
                if self.op2 == None:
                        return str(self.operator) + " " + str(self.op1)
                else:
                        return str(self.op1) + " " + str(self.operator) + " " +  str(self.op2)

        # evaluate this expression given the environment of the symTable
        def eval(self, symTable):
                if self.operator == "var":
                        return symTable[self.op1]
                else:
                        return 0

# used to store a parsed TL statement
class Stmt :
        def __init__(self,keyword,exprs):
                self.keyword = keyword
                self.exprs = exprs

        def __str__(self):
                others = ""
                for exp in self.exprs:
                        others = others + " " + str(exp)
                return self.keyword + others

        # perform/execute this statement given the environment of the symTable
        def perform(self, symTable):
                print ("Doing: " + str(self))

def parseExpr(lineTokens):
        #TODO
        return Epr

# this subroutine looks for a label in the TLI code and if found
# it strips the label from the code and returns the code part of 
# a labeled line. If no labels are found the line is returned.
def parseLabelStatement(line, lineNum):

        tokens = line.split()
        returnStr = line
        if tokens[0].endswith(':'):
                
                # labels have already been processed and put
                # in the symbol table ny processAllLabels() early on/
                # All we are doing here is stripping the label
                # portion of the statement and sending the rest
                # back for processing

                # remove the label from the line strip leading spaces and tabs
                # and return it for processing
                tok = line.split(':')
                returnStr = tok[1].strip()
                
                
        return(returnStr)

# this subroutine processes the print statement by retrieving
# the value of the variable from the symbol table and printing it.
# It processes expressions too
def parsePrintStatement(line, lineNum):
    # ("in parsePrintStatement")

    # stript the word print from the line leaving arguments
    printArgs = line.split(' ', 1)[1]

    # split the arguments per comma
    argTokens = printArgs.split(',')
    
    # get number of tokens to be printed
    length = len(argTokens)

    #print("------ length is -------" + str(length))
    #print(length)

    i = 0
    while i < length:
        myStr = argTokens[i]
        myStr = myStr.strip()
        #print(">" + myStr + "<")
        if myStr.startswith('"') and myStr.endswith('"'):
            myStr = myStr.strip('\"')
        elif ' ' in myStr:
            #print("printing EXPRESSION")
            #print(myStr)
            exprTokens = myStr.split()
            if len(exprTokens) != 3:
                print("Illegal expression at line " + str(int(lineNum+1)) + ".")
                sys.exit()
            else:
                exprVal = evaluateExpression(exprTokens[0],exprTokens[1],exprTokens[2], lineNum)
                myStr = str(exprVal)
        else:
            
            if myStr not in symTable.keys():
                print("Undefined variable " + myStr + " at line " + str(int(lineNum+1)) + ".")
                sys.exit()

            e = Expr(myStr,"var")
            myStr = str(e.eval(symTable))

        if length - i == 1:
            print(myStr)
        else:
            print(myStr, end = ' ')

        i += 1

   
    #print("----- done -----")
    return


# this subroutine evaueates arithmetic and boolean expressions
def evaluateExpression(operand1, operator, operand2, lineNum):


    if is_number(operand1):
        val1 = float(operand1)
    else:
        # exit with error message if operand1 is not
        # in the symbol table
        if operand1 not in symTable.keys():
            print("Undefined variable " + operand1 + " at line " + str(int(lineNum+1)) + ".")
            sys.exit()

        e1 = Expr(operand1,"var")
        val1 = e1.eval(symTable)

    if is_number(operand2):
        val2 = float(operand2)
    else:
        if operand2 not in symTable.keys():
            print("Undefined variable " + operand2 + " at line " + str(int(lineNum+1)) + ".")
            sys.exit()

        e2 = Expr(operand2,"var")
        val2 = e2.eval(symTable)

    if operator=="+":
        retVal = val1 + val2
    elif operator=="-":
        retVal = val1 - val2
    elif operator=="*":
        retVal = val1 * val2
    elif operator=="/":
        retVal = val1 / val2

    # Boolean comparisons
    elif operator==">":
        if val1 > val2:
            retVal = 1
        else:
            retVal = 0
    elif operator==">=":
        if val1 >= val2:
            retVal = 1
        else:
            retVal = 0
    elif operator=="<":
        if val1 < val2:
            retVal = 1
        else:
            retVal = 0
    elif operator=="<=":
        if val1 <= val2:
            retVal = 1
        else:
            retVal = 0
    elif operator == "==":
        if val1 == val2:
            retVal = 1
        else:
            retVal = 0
    elif operator == "!=":
        if val1 != val2:
            retVal = 1
        else:
            retVal = 0
    else:
        print("Syntax error on line " + str(int(lineNum+1)) + ".")
        sys.exit()

    return retVal

# this subroutine processes the input statement by reading
# the user input from the terminal and puts the variable
# and the value entereed by the user in the symbol table
def parseInputStatement(lineTokens, lineNum):

    # only two words accepted for an input statement
    # example : input x
    if len(lineTokens)==2:
        line = input()
        # input must be a number otherwise issue error message
        if is_number(line):
            variable = lineTokens[1]
            value = float(line)
            symTable.update({variable:value})
        else:
            print("Illegal or missing input")
            sys.exit()
    else:
        print("Illegal or missing input")
        sys.exit()

# this ssubroutine evaluates the if statement to be true or false
# and if true it alters the nextLineNumber to match the value of
# the label specified in goto
def parseIfGotoStatement(line, lineNum):

    #print("in parseIfGotoStaement -----")

    tokens = line.split()

    # the label must be the last word
    label = tokens[-1]

    # the expression to be evaluated is between if and goto
    # so we extract what is between if and goto and strip any
    # leading and trailing spaces
    expression = re.search('if(.*)goto', line)
    expression = expression.group(1)
    expression = expression.strip() # strip leading and trailing spaces

    # break up the expression into an array of tokens
    tok = expression.split()

    # evaluate the resulting boolean expression of the form:
    # operand1 operator operand2
    result = evaluateExpression(tok[0], tok[1], tok[2], lineNum)

    #print(result)

    # if boolean expression is TRUE
    # and the label in goto label is in the symbol table
    # grab the value of that label from the symbol table and update
    # the nextLineNumber in symbol table to that value.
    # This will cause the loop in main() to run that line in its 
    # next iteration
    if result == 1:
        #print("Ok were doing it")
        if label in symTable.keys():
            #print("label found")
            e1 = Expr(label,"var")
            labelValue= e1.eval(symTable)
            #print(labelValue)
            symTable.update({"nextLineNum":labelValue})
            #print(symTable)
        else:
            # the label we were told to goto does not exist in
            # the symbol table. Print error message and exit
            print("Illegal goto label at line " + str(int(lineNum+1)) + ".")
            sys.exit()


    #print(label)
    #print(expression)



    return

# this subroutine handles the let statement. It calculates the 
# value of the variable and puts the variable and its value in 
# the symbol table
def parseLetStatement(lineTokens, lineNum):
    #print("in parseLetStatement")
    #print(lineTokens[0])
    #print(len(lineTokens))

    # get number of tokens
    tokenCount = len(lineTokens)

    # if number of tokens is 4 
    # its a let statment of the following type
    # let x = 4 OR
    # let x = z
    # so lets put the info in the symbol table
    if tokenCount==4:
                variable = lineTokens[1]
                # let variable = number
                if is_number(lineTokens[3]):
                    value = float(lineTokens[3])
                # let variable = variable
                else:
                    e = Expr(lineTokens[3],"var")
                    value = e.eval(symTable)
                #print ("variabele is")
                #print (variable)
                #print("value is")
                #print(value)
                symTable.update({variable:value})

    # if the number of tokens is 6
    # its a let statement of the following type
    # let x = y + z   OR
    # let x = 2 + y   Etc.
    elif tokenCount==6:
                variable = lineTokens[1]
                value = evaluateExpression(lineTokens[3], lineTokens[4], lineTokens[5], lineNum)
                #print ("variabele is")
                #print (variable)
                #print("value is")
                #print(value)
                symTable.update({variable:value})

    #print("----- done -----")
    return

# parses a line of TLI code, identifies the statement and calls the
# proper subroutine to process the line
def parseStatement(line, lineNum):

        # print("line before label remove:")
        #print(line)

        # if any labels exist let parseLabelStatement remove
        # it from the line after processing it
        labelFreeLine = parseLabelStatement(line, lineNum)
        #print("line after label remove:")
        #print(labelFreeLine)


        lineTokens = labelFreeLine.split()

        #print(lineTokens[0])
        #if lineTokens[0] == StatementType.LET:
        if lineTokens[0] == "let":
                
                parseLetStatement(lineTokens, lineNum)
                
                return(line)

        elif lineTokens[0] == "print":
                parsePrintStatement(labelFreeLine, lineNum)
                return(line)
        
        elif lineTokens[0] == "input":
                parseInputStatement(lineTokens, lineNum)
                return(line)

        elif lineTokens[0] == "if":
                parseIfGotoStatement(labelFreeLine, lineNum)
                return(line)

        else:
            print("Syntax error on line " + str(int(lineNum+1)) + ".")
            sys.exit()


# this function creates a list of lines from the input TLI program
# and returns it to the caller. This list will be used to parse each 
# line and jump to the pertinent next line or goto line
def parseText(inputFile):
        lineStmt = []
        for line in inputFile:
                # lineStmt.append(parseStatement(line.rstrip()))
                lineStmt.append(line.rstrip())
                #print("----------- parseText ------------")
                #print(line)
                #print(lineStmt)
                #print("----------- parseText exit -------")
        return lineStmt
        


# Googled this - it checks to see if a string is a float
def is_number(s):
        try:
                float(s)
                return True
        except ValueError:
                return False

# this soubroutinen goes through the entire tli code which 
# is in an array and puts any labels found along with their
# line number in the symbol table
def processAllLabels(tliCode):

    numOfLines = len(tliCode)
    lineNum = 0

    # go through all the lines of code
    # and when a label is encountered put it
    # and corresponding line number in symboll Table
    for line in tliCode:
        #print(str(lineNum) + " " + line)
        tok = line.split(':')
        if len(tok)==2:
            #print(tok[0])
            symTable.update({tok[0]:lineNum})
        lineNum += 1

# main subroutine which opens file, maintains next line of TLI code to be
# processed and calls a subroutine to parse the line
def main():

        
        # First argument should be filepath
        filePath = sys.argv[1]
        # print(filePath)
        f = open(filePath, 'r')
        tliCode = parseText(f)

        processAllLabels(tliCode)

        numOfLines = len(tliCode)


        lineNum = 0.0
        symTable.update({"nextLineNum":lineNum})
        while lineNum < numOfLines:

            #skip empty lines
            if len(tliCode[int(lineNum)]) > 1:

                    # get value of next line number of TLI code
                    e = Expr("nextLineNum","var")
                    lineNum = e.eval(symTable)


                    #print("======================================")
                    #print(tliCode[lineNum])
                    parseStatement(tliCode[int(lineNum)], lineNum)

                    

            #increment the line next line number
            # in the symbol table
            e = Expr("nextLineNum","var")
            symTblLineNum = e.eval(symTable)
            if symTblLineNum == lineNum:
                lineNum += 1
                symTable.update({"nextLineNum":lineNum})
            else:
                lineNum = symTblLineNum
                
            
        
        #print(symTable)

# Call the main subroutine to start the processing
main()
