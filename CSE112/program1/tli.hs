import Data.Char
import Data.Either
import System.IO
import Debug.Trace
import System.Environment   

-- maps labels line numbers and variables to values - uses float for line numbers for simplicity
type SymTable = [(String,Float)]



data Expr = Constant Float | 
            Var String     | 
            Str String     |
            Plus Expr Expr             | 
            Minus Expr Expr            | 
            Mult Expr Expr             | 
            Div Expr Expr              | 
            Lt Expr Expr               | 
            Gt Expr Expr               | 
            Lte Expr Expr              | 
            Gte Expr Expr              | 
            Equal Expr Expr            | 
            NotEqual Expr Expr         |
            ExprError String  deriving (Show)

data Stmt =
     Let String Expr  |
     -- If Expr Line Number of Jump
     If Expr String|
     Input String |
     Error String |
     NOP |
     Print [Expr] deriving (Show) 

-- dummy predicate that is supposed to check if a string is a label which is a string ending with ":"
isLabel :: String -> Bool
isLabel x = last x == ':'
-- isLabel _ = False -- there are no labels in this nano version of the tiny language

-- takes a list of tokens as strings and returns the parsed expression
parseExpr :: [String] -> Expr
parseExpr (e1:"+":e2:[]) = Plus (parseExpr [e1]) (parseExpr [e2])
parseExpr (e1:"-":e2:[]) = Minus (parseExpr [e1]) (parseExpr [e2])
parseExpr (e1:"*":e2:[]) = Mult (parseExpr [e1]) (parseExpr [e2])
parseExpr (e1:"/":e2:[]) = Div (parseExpr [e1]) (parseExpr [e2])
parseExpr (e1:"<":e2:[]) = Lt (parseExpr [e1]) (parseExpr [e2])
parseExpr (e1:">":e2:[]) = Gt (parseExpr [e1]) (parseExpr [e2])
parseExpr (e1:"<=":e2:[]) = Lte (parseExpr [e1]) (parseExpr [e2])
parseExpr (e1:">=":e2:[]) = Gte (parseExpr [e1]) (parseExpr [e2])
parseExpr (e1:"==":e2:[]) = Equal (parseExpr [e1]) (parseExpr [e2])
parseExpr (e1:"!=":e2:[]) = NotEqual (parseExpr [e1]) (parseExpr [e2])
parseExpr [x] = if (isAlpha ( head x)) then (Var x) else if (((head x ) == '"') && ((last x) == '"')) then (Str (tail (init x))) else  (Constant (read x))

splitCommaStringArray :: [String] -> [String] -> [[String]] -> [[String]]
splitCommaStringArray [] temp result = reverse (temp:result)
splitCommaStringArray (x:xs) temp res = if last x == ',' then splitCommaStringArray xs [] ((reverse ((init x):temp)):res) else splitCommaStringArray xs (x:temp) res 
-- takes the first token which should be a keyword and a list of the remaining tokens and returns the parsed Stmt
parseStmt :: String -> [String] -> Stmt
parseStmt "let" (v:"=":expr) = Let v (parseExpr expr)
parseStmt "print" exprs = Print (map parseExpr (splitCommaStringArray exprs [] []))
-- If there is more than one element in the [String] it is invalid code
parseStmt "input" [x] = Input x
-- "if expr goto label"
-- Split into [Expr, "goto", label]
--parseStmt "if" (expr:"goto":label) = If (parseExpr expr) label
      -- Doesn't work but will 
--parseStmt "if" arr = If (parseExpr (tail (tail (reverse arr)))) (last arr )-- else error for unparseable statement
parseStmt "if" arr
      | goto == "goto"  = If (parseExpr expr) label
      -- | otherwise = emit error
      -- label is last element of array
      where label = last arr
      -- goto is 2nd to last element of array
            goto = arr !! ((length arr) - 2 )
      -- expr is everything except the last two elements
            expr = ( init ( init arr ))
otherwise keyword expr = ExprError (unwords keyword ++ expr )
            -- parseStmt "if" (reverse arr)
-- we need "if"
-- takes a list of tokens and returns the parsed statement - the statement may include a leading label
-- EDIT: Changed to return a tuple of the statement and Label Name. If no label, the label name will be ""

parseLine :: [String] -> (Stmt, String)
parseLine (first:rest) =
      if (isLabel first) then (parseStmt (head rest) (tail rest), init first)
      else (parseStmt first rest, "")

-- takes a variable name and a ST and returns the value of that variable or zero if the variable is not in the ST
-- Returns True if error and False for no error
      -- variable -> Symtable -> LineNum -> value
lookupVar :: String -> SymTable  -> Float
lookupVar name []  = error ("Undefined variable " ++ name ++ " at line " )
lookupVar name ((id,v):rest) = if (id == name) then v else lookupVar name rest 

-- evaluates the given Expr with the variable values found in the given ST
eval :: Expr -> SymTable  -> Float
eval (Var v) env  =  (lookupVar v env )
eval (Constant v) _  =  v
eval (Plus e1 e2) env  =  (((eval e1 env )) + ( (eval e2 env )))
eval (Minus e1 e2) env  =  ( (eval e1 env ) - (eval e2 env ))
eval (Mult e1 e2) env  = (eval e1 env ) * (eval e2 env )
eval (Div e1 e2) env  = (eval e1 env ) / (eval e2 env )
eval (Lt e1 e2) env  = if (eval e1 env ) < (eval e2 env ) then 1 else 0
eval (Gt e1 e2) env  = if (eval e1 env ) > (eval e2 env ) then 1 else 0
eval (Lte e1 e2) env  = if (eval e1 env ) <= (eval e2 env ) then 1 else 0
eval (Gte e1 e2) env  = if (eval e1 env ) >= (eval e2 env ) then 1 else 0
eval (Equal e1 e2) env  = if (eval e1 env ) == (eval e2 env ) then 1 else 0
eval (NotEqual e1 e2) env  = if (eval e1 env ) /= (eval e2 env ) then 1 else 0

-- given a statement, a ST, line number, input and previous output, return an updated ST, input, output, and line number
-- this starter version ignores the input and line number
-- Stmt, SymTable, progCounter, input, output, programSize ,(SymTable', input', output', progCounter)
perform:: Stmt -> SymTable -> Float -> [String] ->String -> Int-> (SymTable, [String], String, Float)
perform (Print e) env lineNum input output  _ = (env, input, output++ (unlines (printEval e env [])), lineNum+1)
perform (Let id e) env lineNum input output _ = ((id,(eval e env )):env, input, output, lineNum+1)
-- perform (Input id) env lineNum [] output =  Error out
perform (Input id) env lineNum input output _ =  ((id,(read (head input))):env, (tail input), output, lineNum+1) 
perform (If e label) env lineNum input output size = if (eval e env ) /= 0 then  (if (floor (lookupVar label env )) > size then error ("illegal goto " ++ label ++ " at line " ++ (show (lookupVar label env ))) else (env, input, output, (lookupVar label env ) )) else (env, input, output, (lineNum+1) )

printEval:: [Expr] -> SymTable -> [String] -> [String]
printEval [] _ res = reverse res
printEval ((Str v):xs) env  res= printEval xs env (v:res) 
printEval (x:xs) env res= printEval xs env  ((show (eval x env )):res)
      

-- given a list of Stmts, a ST, EDIT: Program Counter and current output, perform all of the statements in the list and return the updated output String
-- EDIT: Changed to accept a tuple of ([Stmt], SymTable) so that processParsedLines can prepopulatae the symTable with Labels
-- Need to accept changing program counter
-- Currently run only executes statements in sequence 
-- TODO: Should probably change to pass around remaining input tokens array aswell
-- TODO: Check for out of bounds label goto
--  ([statements], Symtable) -> ProgramCounter -> input -> output -> outpu
run :: ([Stmt], SymTable) -> Float -> [String]-> String -> String
run (stmtList, env) lineNum input output 
      | (floor lineNum) >= (length stmtList) = output
      | True                            = let  (env1, input1, output1, newLineNum) = perform (stmtList !! (floor lineNum)) env lineNum input output (length stmtList) in run (stmtList, env1) newLineNum input1 output1

-- Debugging Functions to trace execution 
-- runTrace :: ([Stmt], SymTable) -> Float -> String -> String
-- runTrace (stmtList, env) lineNum output
-- -- | if floor(lineNum) == length stmtList = OK
--    -- | if floorLineNum > length stmtList = error  
--      | (floor lineNum) >= (length stmtList) = output
--      | otherwise                            = let  (env1, input1, output1, newLineNum) = performTrace (stmtList !! (floor lineNum)) env lineNum [] output in runTrace (stmtList, env1) newLineNum output1

-- performTrace :: Stmt -> SymTable -> Float -> [String] ->String -> (SymTable, [String], String, Float)
-- performTrace (Print e) env lineNum input output = traceShowId (env, input, output++(show (eval e env)++"\n"), lineNum+1)
-- -- perform (Let id e) env lineNum input output = ((id,22):env, input, output, lineNum+1)
-- performTrace (Let id e) env lineNum input output = traceShowId ((id, (eval e env)):env, input, output, lineNum+1)
-- -- if x is not an int this will cause the program to crash
-- performTrace (Input id) env lineNum (x:xs) output = traceShowId ((id, (read x)):env, xs, output, lineNum+1)
-- performTrace (If e label) env lineNum input output = if (eval e env) /= 0 then traceShowId (env, input, output, (lookupVar label env) ) else traceShowId (env, input, output, (lineNum+1) )


-- given list of list of tokens, a ST, and return the list of parsed Stmts and ST storing mapping of labels to line numbers
parseTest :: [[String]] -> SymTable -> ([Stmt], SymTable)
parseTest []  st = ([], st)
parseTest arr st = processParsedLines (map parseLine ( arr)) [] st 0
      
-- Works for print a, b but not for print a , b
-- Program specification does not match testing environment

--parseTest stmts table = processParsedLines (map parseLine stmts) table 
 -- where parsedLines = processParsedLines
-- parseTest (x:xs) st = if isLabel (head x) then Something (test stuff)
-- needs completing for partial credit
main = do
      (fileName:args) <- getArgs
      pfile <- openFile fileName ReadMode
      input <-  getContents
      
    --  pfile <- openFile "nano1.txt" ReadMode
      contents <- hGetContents pfile
      putStr (run (processParsedLines (map parseLine (map words (lines contents))) [] [] 0 ) 0 (words input) "")
      hClose pfile

   --  contents <- hGetContents pfile
    -- hClose pfile


-- Function to take in a list of tuples (Stmt, String) and store each statement in an array and each label in a SymTable with its corresponding line number.
processParsedLines :: [(Stmt, String)] -> [Stmt] -> SymTable -> Float -> ([Stmt], SymTable) 
processParsedLines [] stmts id _ = (reverse stmts, id) 
processParsedLines (x:xs) stmts id lineNum = if (snd x) /= "" then processParsedLines (xs) ((fst x):stmts) ((snd x, lineNum):id)  (lineNum+1)
                                                                               else processParsedLines (xs) ((fst x):stmts) id (lineNum+1)

