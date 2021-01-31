// Author: Natalie Petrosian
// CSE 112 Comparative Programming Languages 
// Program 4: Tiny Language Interpreter in Scala
// Professor McDowell

import scala.collection.mutable.Map
import scala.io.Source


abstract class Expr
case class Var(name: String) extends Expr
case class Str(name: String) extends Expr
case class Constant(num: Double) extends Expr
case class BinOp(operator: String, left: Expr, right: Expr) extends Expr

abstract class Stmt
case class Let(variable: String, expr: Expr) extends Stmt
case class If(expr: Expr, label: String) extends Stmt
case class Input(variable: String) extends Stmt
case class Print(exprList: List[Expr]) extends Stmt

object TLI {
    def eval(expr: Expr, symTab: Map[String, Double]): Double = expr match {
        case BinOp("+",e1,e2) => eval(e1,symTab) + eval(e2,symTab) 
        case BinOp("-",e1,e2) => eval(e1,symTab) - eval(e2,symTab)
        case BinOp("*",e1,e2) => eval(e1,symTab) * eval(e2,symTab)
        case BinOp("/",e1,e2) => eval(e1,symTab) / eval(e2,symTab)
        case BinOp("==", e1, e2) => if (eval(e1,symTab) == eval(e2,symTab)) {1} else {0}
        case BinOp("!=", e1, e2) => if (eval(e1,symTab) != eval(e2,symTab)) {1} else {0}
        case BinOp(">", e1, e2) => if (eval(e1,symTab) > eval(e2,symTab)) {1} else {0}
        case BinOp(">=", e1, e2) => if (eval(e1,symTab) >= eval(e2,symTab)) {1} else {0}
        case BinOp("<", e1, e2) => if (eval(e1,symTab) < eval(e2,symTab)) {1} else {0}
        case BinOp("<=", e1, e2) => if (eval(e1,symTab) <= eval(e2,symTab)) {1} else {0}
        case Var(name) => symTab(name)
        case Constant(num) => num
		case _ => 0 // should really throw an error
    }

    // This routine returns True if the operator in the TLI code matches a legal operator
    // otherwise it returns False
    def validOperator(operator: String): Boolean = {

    	// println("received this operator: " + operator)

    	operator == "+"  ||
    	operator == "-"  ||
    	operator == "*"  ||
    	operator == "/"  ||
    	operator == "==" ||
    	operator == "!=" ||
    	operator == ">"  ||
    	operator == ">=" ||
    	operator == "<"  ||
    	operator == "<="


    }

    // this routine parses the expression in the TLI code and returns an
    // expression obkect that can be evaluated by the eval method
    def constructExpression(line: String, lineNum: Double, symTab: Map[String, Double]): Expr = {


            // println("constructing expression for " + ">>>>" + line + "<<<<<")

            // initialize mutable expressions to constant 0
    		var e: Expr = Constant(0)
    		var e1: Expr = Constant(0)
    		var e2: Expr = Constant(0)

    		// Constant(25)
    		val tokens = (line.trim).split(" ")

    		if (tokens.length == 1) {

    			if (scala.util.Try(line.toDouble).isSuccess) {
    				e = Constant(line.toDouble)
    			} else {
                    if (symTab.exists(x => x._1 == line)) {
                        e = Var(line)
                    } else {
    				    println("Undefined variable " + line + " at line " + (lineNum+1).toInt + ".")
                        System.exit(-1)
                    }
    			}

    		} else if (tokens.length == 3) {

    			if (!(validOperator(tokens(1)))) {
    				println("Syntax error on line " + (lineNum+1).toInt + ".")
    				System.exit(-1)
    			}

   
    			if (scala.util.Try(tokens(0).toDouble).isSuccess) {
    				e1 = Constant(tokens(0).toDouble)
    			} else {
                    if (symTab.exists(x => x._1 == tokens(0))) {
    				    e1 = Var(tokens(0))
                    } else {
                        println("Undefined variable " + tokens(0) + " at line " + (lineNum+1).toInt + ".")
                        System.exit(-1)
                    }
    			}

    			if (scala.util.Try(tokens(2).toDouble).isSuccess) {
    				e2 = Constant(tokens(2).toDouble)
    			} else {
                    if (symTab.exists(x => x._1 == tokens(2))) {
    				    e2 = Var(tokens(2))
                    } else {
                        println("Undefined variable " + tokens(2) + " at line " + (lineNum+1).toInt + ".")
                        System.exit(-1)
                    }
    			}

    			e = BinOp(tokens(1), e1, e2)

              

    		} else {
    			println("Syntax error on line " + (lineNum+1).toInt + ".")
    			System.exit(-1)
    		}
    		// This is the expression that is returned to caller
    		e

    }


    // this routine processes the Let statements
    def processLetStatement(myStatement: Let, lineNum: Double, symTab: Map[String, Double]) = {
    	
    	symTab += (myStatement.variable -> eval(myStatement.expr, symTab))
    }

	// this routine processes the If statements
    def processIfStatement(myStatement: If, lineNum: Double, symTab: Map[String, Double]) = {


    	if (symTab.exists(x => x._1 == myStatement.label)) {

    		// if the boolean expression in the if-goto statement is true
    		if (eval(myStatement.expr,symTab) == 1.0) {

    				// Get the line number associated with the label
    				var nl = eval(Var(myStatement.label), symTab)
		
    				// set the nexLineNum value in the symbol table to nl
    				symTab += ("nextLineNum" -> nl)
    		}

    	} else {
    		println("Illegal goto label at line " + (lineNum+1).toInt + "." )
            System.exit(-1)
    	}

    }

    // this routine processes the print statements
    def processPrintStatement(arguments: Array[String], lineNum: Double, symTab: Map[String, Double]) = {

    	var argCount = 0

    	for (arg <- arguments) {

    		var argument = arg.trim

    		if (argument.startsWith("\"") && argument.endsWith("\"")) {
    			print(argument.replace("\"",""))
    		} else if (scala.util.Try(argument.toDouble).isSuccess) {
    			print(argument.trim)
    		} else {

                // It's either a variable or an expression.
                // Either way constructExpression() will handle it
                val theExpression = constructExpression(argument, lineNum, symTab)
                print(eval(theExpression, symTab))


    		}
    		argCount += 1
    		if (argCount < arguments.length) {
    			print(" ")
    		} else {
    			println(" ")
    		}
    	}
    }


    // parses a line of TLI code and handles the let, input, if-goto and print
    // statements 
    def processLine(line: String, lineNum: Double, symTab: Map[String, Double]) = {
    	var currentLine = line.trim

    	val lineTokens = (line.trim).split(" ")

        // handle let statement in the TLI code
    	if (lineTokens(0) == "let") {
    		if (!(line contains " = ")) {
    			println("Syntax error on line " + (lineNum+1).toInt + ".")
    			System.exit(-1)
    		} else {

    			
    			// determine what is at the right of the equal sign
    			val equalTokens = (line.trim).split(" = ")

    			val rightSideOfEqualSign = equalTokens(1).trim
    			var myExpression: Expr = constructExpression(rightSideOfEqualSign, lineNum, symTab)

    			val leftSideOfEqualSign = equalTokens(0).trim
    			val tokens = leftSideOfEqualSign.split(" ")
    			val variable = tokens(1).trim
    			
    			val myLetStatement = new Let(variable,myExpression)

    			processLetStatement(myLetStatement, lineNum, symTab)


    		}

    	// handle input statements in TLI code
    	} else if (lineTokens(0) == "input") {


    		if (lineTokens.length != 2) {
    			println("Illegal or missing input.")
    			System.exit(-1)
    		}

    		val inputValue = scala.io.StdIn.readLine()

    		if (scala.util.Try(inputValue.toDouble).isSuccess) {
    			symTab += ((lineTokens(1).trim) -> inputValue.toDouble)
    		} else {
    			println("Illegal or missing input.")
    			System.exit(-1)
    		}		
    		
    	// handle print statements in TLI code
    	} else if (lineTokens(0) == "print") {

    		val tokens = (line.trim).split("print ")
    		
    		val arguments = (tokens(1).trim).split(",")
    		
    		processPrintStatement(arguments, lineNum, symTab)


        // handle if-goto statments in TLII code
    	} else if (lineTokens(0) == "if") {

    		
    		// extract the name of the label from the if-goto line
    		// it should be after goto
    		var gotoLabel = line.substring(line.indexOf("goto ") + 5)

    		// extract the boolean condition from the if-goto line
    		// it should be between if and goto
    		var booleanCondition = line.substring(line.indexOf("if ") + 3, line.indexOf(" goto"))
    		booleanCondition = booleanCondition.trim
    		val myExpression = constructExpression(booleanCondition, lineNum, symTab)

    		val myIfStatement = new If(myExpression, gotoLabel)

    		processIfStatement(myIfStatement, lineNum, symTab)



    	} else {
    		println("Syntax error on line " + (lineNum+1).toInt + ".")
    		System.exit(-1)
    	}

    }

    // processes all labels and writes them into the symbol table
    def processLabels(tliCode: Array[String], symTab: Map[String, Double]) = {

        var lineNum = 0
    	for (line <- tliCode) {
    		val lineTokens = (line.trim).split(" ")
    		val firstWord = lineTokens(0).trim
    		// see if first word is a label
    		// if it is add it and lineNum to symbol table
    		// and remove the label from the line for 
    		// easy parsing afterwards
    		
    		if (firstWord contains ":") {
    			val breakLine = line.split(":")
    			var label = breakLine(0).trim
    			// put label and corresponding lineNum in symTab
    			symTab += (label -> lineNum)
    			// replace the line in tliCode with the portion following
    			// the colon : 
    			var labelFree = breakLine(1).trim
    			tliCode(lineNum) = labelFree
    		}
    		lineNum += 1
    		
    	}
    }

    // main routine reads the TLI input file into an array, processed the labels
    // and runs the code line by line
    def main(args: Array[String]) = {

    	val symTable = Map("nextLineNum" -> 0.0)

    

        // Read the TLI input txt file into an array of strings
    	val tliCode = Source.fromFile(args(0)).getLines.toArray

        // Call process Labels to put all the labels and their
        // associated line numbers into the symbol table
    	processLabels(tliCode, symTable)
    	

        var numberOfLines = tliCode.length
        var lineNum = 0.0
        // Uodate the next line number in the symbol table
        symTable += ("nextLineNum" -> lineNum)

        // Run the tliCode line by line
        // note that nextLineNum in the symbol table is incremented by 1 here
        // but may also be changed by an if-goto
		while ( lineNum < numberOfLines) {


			if (tliCode(lineNum.toInt).length > 1) {

				// retrieve line number from the symbol table
				lineNum = eval(Var("nextLineNum"), symTable)

    			processLine(tliCode(lineNum.toInt), lineNum, symTable)
    			
    		}

    		// increment the next-line number in the
    		// symbol table UNLESS an if-goto has altered it
    		// in which case make the if-goto line number the
    		// active one in this while loop
    		var symTblLineNum = eval(Var("nextLineNum"), symTable)
    		if (symTblLineNum == lineNum) {
    				lineNum += 1
    				symTable += ("nextLineNum" -> lineNum)
    		} else {
    				lineNum = symTblLineNum
    		}

    	}

    	
    }
}
