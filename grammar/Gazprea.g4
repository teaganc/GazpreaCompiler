grammar Gazprea;

options { tokenVocab = GazpreaLexer; }

file: (decl | function | procedure | typedef )*;

qualifier: CONST | VAR;

/* Type Block */
type: sized_type | size_inferred_type;

// Sizes are known without an assignment
sized_type
    : string_type
    | vector_type
    | matrix_type
    | tuple_type
    | interval_type
    | simple_type
    ;
// Sizes must be infered from assignment
size_inferred_type
    : simple_type LEFT_SQUARE MUL RIGHT_SQUARE              #vectorInferred
    | simple_type LEFT_SQUARE MUL COMMA expr RIGHT_SQUARE   #matrixFirstInferred
    | simple_type LEFT_SQUARE expr COMMA MUL RIGHT_SQUARE   #matrixSecondInferred
    | simple_type LEFT_SQUARE MUL COMMA MUL RIGHT_SQUARE    #matrixInferred
    | STRING LEFT_SQUARE MUL RIGHT_SQUARE                   #stringInferred
    ;
string_type: STRING (LEFT_SQUARE expr RIGHT_SQUARE)?;
vector_type: simple_type LEFT_SQUARE expr RIGHT_SQUARE;
matrix_type: simple_type LEFT_SQUARE expr COMMA expr RIGHT_SQUARE;
tuple_type: TUPLE LEFT_BRACKET tuple_member (COMMA tuple_member)+ RIGHT_BRACKET;
interval_type: INTEGER INTERVAL;
simple_type: BOOLEAN | INTEGER | CHARACTER | REAL | IDENTIFIER;
/* End Type Block */

tuple_member: type IDENTIFIER?;

// Typedef
typedef: TYPEDEF type IDENTIFIER SEMI;

// Statements
decl
    : qualifier? sized_type IDENTIFIER (SET expr)? SEMI         #declare
    | qualifier? size_inferred_type IDENTIFIER SET expr SEMI    #declareSize
    | qualifier IDENTIFIER SET expr SEMI                        #declareInferred
    ;
assign: id (COMMA id)* SET expr SEMI;
comp
    : LEFT_BRACKET expr RIGHT_BRACKET
    | expr
    ;
conditional: IF comp block (ELSE block)?;
loop
    : LOOP block                        #loopInfinite
    | LOOP WHILE comp block             #loopPrePredicate
    | LOOP domain (COMMA domain)* block #loopIterator
    | LOOP block WHILE comp SEMI        #loopPostPredicate
    ;
breaks: BREAK SEMI;
continues: CONTINUE SEMI;
return_statement
    : RETURN expr SEMI
    | RETURN SEMI
    ;
output: expr RIGHT_ARROW STD_OUTPUT SEMI;
input: id LEFT_ARROW STD_INPUT SEMI;

domain: IDENTIFIER IN expr;
id
    : IDENTIFIER                                                #varId
    | IDENTIFIER LEFT_SQUARE expr RIGHT_SQUARE                  #vectorId
    | IDENTIFIER LEFT_SQUARE expr COMMA expr RIGHT_SQUARE       #matrixId
    | TUPLE_ACCESS                                              #tupleId
    | TUPLE_ACCESS LEFT_SQUARE expr RIGHT_SQUARE                #tupleVectorAccess
    | TUPLE_ACCESS LEFT_SQUARE expr COMMA expr RIGHT_SQUARE     #tupleMatrixAccess
    ;

// Function declaration
function
    : FUNCTION IDENTIFIER LEFT_BRACKET (function_param (COMMA function_param)*)? RIGHT_BRACKET RETURNS type SEMI            #functionForward
    | FUNCTION IDENTIFIER LEFT_BRACKET (function_param (COMMA function_param)*)? RIGHT_BRACKET RETURNS type SET expr SEMI   #functionSingle
    | FUNCTION IDENTIFIER LEFT_BRACKET (function_param (COMMA function_param)*)? RIGHT_BRACKET RETURNS type block           #functionBlock
    ;
function_param: type IDENTIFIER?;

// Procedure declaration
procedure
    : PROCEDURE IDENTIFIER LEFT_BRACKET (procedure_param (COMMA procedure_param)*)? RIGHT_BRACKET SEMI                  #procedureForward
    | PROCEDURE IDENTIFIER LEFT_BRACKET (procedure_param (COMMA procedure_param)*)? RIGHT_BRACKET RETURNS type SEMI     #procedureFowardReturn
    | PROCEDURE IDENTIFIER LEFT_BRACKET (procedure_param (COMMA procedure_param)*)? RIGHT_BRACKET block                 #procedureNoReturn
    | PROCEDURE IDENTIFIER LEFT_BRACKET (procedure_param (COMMA procedure_param)*)? RIGHT_BRACKET RETURNS type block    #procedureReturn
    ;
procedure_param: qualifier? type IDENTIFIER?;

// Calls
proc_call
    : CALL IDENTIFIER LEFT_BRACKET (expr (COMMA expr)*)? RIGHT_BRACKET SEMI
    | CALL STREAM_STATE LEFT_BRACKET STD_INPUT RIGHT_BRACKET SEMI
    ;
call
    : IDENTIFIER LEFT_BRACKET (expr (COMMA expr)*)? RIGHT_BRACKET
    | STREAM_STATE LEFT_BRACKET STD_INPUT RIGHT_BRACKET
    | (LENGTH | ROWS | COLUMNS | REVERSE) LEFT_BRACKET expr RIGHT_BRACKET
    ;
non_decl_statement: assign | conditional | loop | breaks | continues | return_statement
    | proc_call | input | output;
block
    : LEFT_BRACE (decl)* (non_decl_statement | block)* RIGHT_BRACE
    | non_decl_statement
    ;

// Casting
cast: AS LT cast_type GT LEFT_BRACKET expr RIGHT_BRACKET;
cast_type
    : matrix_type
    | tuple_type
    | string_type
    | vector_type
    | simple_type
    ;

// Expressions
expr
    : LEFT_BRACKET expr RIGHT_BRACKET                           #parenExpr
    | cast                                                      #castExpr
    | call                                                      #callExpr
    | expr RANGE expr                                           #intervalLiteral
    | LEFT_SQUARE domain (COMMA domain)? BAR expr RIGHT_SQUARE  #generatorExpr
    | LEFT_SQUARE domain FILTER expr (COMMA expr)* RIGHT_SQUARE #filterExpr
    | <assoc=right> op=(ADD | SUB | NOT) expr                   #unaryExpr
    | <assoc=right> expr EXP expr                               #binaryExpr
    | expr op=(MUL | DIV | MOD | DOT_PROD) expr                 #binaryExpr
    | expr op=(ADD | SUB) expr                                  #binaryExpr
    | expr BY expr                                              #binaryExpr
    | expr op=(LT | GT | LE | GE) expr                          #binaryExpr
    | expr op=(EQ | NE) expr                                    #binaryExpr
    | expr AND expr                                             #binaryExpr
    | expr op=(OR | XOR) expr                                   #binaryExpr
    | expr CAT expr                                             #binaryExpr
    | NULL_                                                     #nullLiteral
    | IDENTITY                                                  #identityLiteral
    | id                                                        #idExpr
    | tuple_literal                                             #tupleLiteral
    | vector_literal                                            #vectorLiteral
    | boolean_literal                                           #booleanLiteral
    | character_literal                                         #characterLiteral
    | string_literal                                            #stringLiteral
    | float_literal                                             #floatLiteral
    | INT_LITERAL                                               #intLiteral
    ;

// Literals
tuple_literal: LEFT_BRACKET expr (COMMA expr)* RIGHT_BRACKET;
vector_literal: LEFT_SQUARE (expr (COMMA expr)*)? RIGHT_SQUARE;
boolean_literal: TRUE | FALSE;
character_literal: APOSTROPHE_OPEN (APOSTROPHE_OTHER | APOSTROPHE_ESCAPE) APOSTROPHE_CLOSE;
string_literal: QUOTE_OPEN (QUOTE_OTHER | QUOTE_ESCAPE)* QUOTE_CLOSE;
float_literal: FLOAT_LITERAL;
