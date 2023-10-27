lexer grammar GazpreaLexer;

// Keywords
AND: 'and';
AS: 'as';
BOOLEAN: 'boolean';
BREAK: 'break';
BY: 'by';
CALL: 'call';
CHARACTER: 'character';
COLUMNS: 'columns';
CONST: 'const';
CONTINUE: 'continue';
ELSE: 'else';
FALSE: 'false';
FUNCTION: 'function';
IDENTITY: 'identity';
IF: 'if';
IN: 'in';
INTEGER: 'integer';
INTERVAL: 'interval';
LENGTH: 'length';
LOOP: 'loop';
NOT: 'not';
NULL_: 'null';
OR: 'or';
PROCEDURE: 'procedure';
REAL: 'real';
RETURN: 'return';
RETURNS: 'returns';
REVERSE: 'reverse';
ROWS: 'rows';
STD_INPUT: 'std_input';
STD_OUTPUT: 'std_output';
STREAM_STATE: 'stream_state';
STRING: 'string';
TRUE: 'true';
TUPLE: 'tuple';
TYPEDEF: 'typedef';
VAR: 'var';
WHILE: 'while';
XOR: 'xor';

// Punctuation
LEFT_BRACKET: '(';
RIGHT_BRACKET: ')';
LEFT_SQUARE: '[';
RIGHT_SQUARE: ']';
LEFT_BRACE: '{';
RIGHT_BRACE: '}';
LEFT_COMMENT: '/*' -> pushMode(INSIDE_MULTI_COMMENT);
RIGHT_COMMENT: '*/';
LEFT_ARROW: '<-';
RIGHT_ARROW: '->';
SEMI: ';';
COMMA: ',';
BAR: '|';
UNDERSCORE: '_';
COMMENT: '//' -> pushMode(INSIDE_COMMENT);
QUOTE_OPEN: '"' -> pushMode(INSIDE_QUOTE);
APOSTROPHE_OPEN: '\'' -> pushMode(INSIDE_APOSTROPHE);
SLASH: '\\';

// Operators
MUL: '*';
DIV: '/';
MOD: '%';
EXP: '^';
ADD: '+';
SUB: '-';
CAT: '||';
DOT_PROD: '**';
LT: '<';
GT: '>';
LE: '<=';
GE: '>=';
EQ: '==';
NE: '!=';
SET: '=';
RANGE: '..';
DOT: { _input->LA(2) != '.' }? '.';
FILTER: '&';

FLOAT_LITERAL
    : DECIMAL ('e' (ADD | SUB)? INT_LITERAL)?
    | INT_LITERAL 'e' (ADD | SUB)? INT_LITERAL
    ;

// IDs and INTs
IDENTIFIER: (UPPER | LOWER | UNDERSCORE) (UPPER | LOWER | NUMBER | UNDERSCORE)*;
INT_LITERAL: NUMBER+;
TUPLE_ACCESS: IDENTIFIER DOT (IDENTIFIER | INT_LITERAL);
DECIMAL
    : NUMBER* DOT NUMBER+
    | NUMBER+ DOT NUMBER*
    ;

fragment UPPER: [A-Z];
fragment LOWER: [a-z];
fragment NUMBER: [0-9];

// Skip whitespace and comments
WS : [ \t\r\n]+ -> skip ;
CM: ((COMMENT (COMMENT_OTHER | COMMENT_ESCAPE)*? COMMENT_CLOSE) | (LEFT_COMMENT (MULTI_OTHER | MULTI_ESCAPE)*? MULTI_CLOSE)) -> skip;

mode INSIDE_QUOTE;
QUOTE_CLOSE: '"' -> popMode;
// should \ always escape character 
// should you be able to escape ' in double quotes?
QUOTE_ESCAPE: ESCAPE_NULL | ESCAPE_BELL | ESCAPE_BACK | ESCAPE_TAB | ESCAPE_LF | ESCAPE_CR | ESCAPE_QUOTE | ESCAPE_SLASH;
QUOTE_OTHER: .;

mode INSIDE_COMMENT;
COMMENT_CLOSE: '\n' -> popMode;
// should \ always escape character 
COMMENT_ESCAPE: ESCAPE_NULL | ESCAPE_BELL | ESCAPE_BACK | ESCAPE_TAB | ESCAPE_APOSTROPHE | ESCAPE_CR | ESCAPE_QUOTE | ESCAPE_SLASH;
COMMENT_OTHER: .;

mode INSIDE_MULTI_COMMENT;
MULTI_CLOSE: RIGHT_COMMENT -> popMode;
// should \ always escape character 
MULTI_ESCAPE: ESCAPE_NULL | ESCAPE_BELL | ESCAPE_BACK | ESCAPE_TAB | ESCAPE_APOSTROPHE | ESCAPE_CR | ESCAPE_QUOTE | ESCAPE_SLASH;
MULTI_OTHER: .;

mode INSIDE_APOSTROPHE;

APOSTROPHE_CLOSE: '\'' -> popMode;

APOSTROPHE_ESCAPE: ESCAPE_NULL | ESCAPE_BELL | ESCAPE_BACK | ESCAPE_TAB | ESCAPE_LF | ESCAPE_CR | ESCAPE_QUOTE | ESCAPE_APOSTROPHE | ESCAPE_SLASH;
APOSTROPHE_OTHER: .;

fragment ESCAPE_NULL: '\\0';
fragment ESCAPE_BELL: '\\a';
fragment ESCAPE_BACK: '\\b';
fragment ESCAPE_TAB: '\\t';
fragment ESCAPE_LF: '\\n';
fragment ESCAPE_CR: '\\r';
fragment ESCAPE_QUOTE: '\\"';
fragment ESCAPE_APOSTROPHE: '\\\'';
fragment ESCAPE_SLASH: '\\\\';
