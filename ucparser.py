"""
ucparser.py.

A PLY specification for a uC lexer and parser. Constructs an AST from
uC source code.

Project UID c49e54971d13f14fbc634d7a0fe4b38d421279e7
"""

import importlib
from ucbase import *
from ucstmt import *
from ucexpr import *


#####################
# Lexical Structure #
#####################

# Reserved words
reserved = {
    'if': 'IF',
    'else': 'ELSE',
    'while': 'WHILE',
    'for': 'FOR',
    'struct': 'STRUCT',
    'break': 'BREAK',
    'continue': 'CONTINUE',
    'return': 'RETURN',
    'true': 'TRUE',
    'false': 'FALSE',
    'new': 'NEW',
    'null': 'NULL'
}


tokens = [
    # Literals (identifier, integer, float, string)
    'IDENT', 'INTEGER', 'FLOAT', 'STRING',

    # Operators (+, -, *, /, %, ||, &&, !, <, <=, >, >=, ==, !=, <<, >>)
    'PLUS', 'MINUS', 'TIMES', 'DIVIDE', 'MODULO',
    'LOR', 'LAND', 'LNOT',
    'LT', 'LE', 'GT', 'GE', 'EQ', 'NE',
    'PUSH', 'POP',

    # Assignment (=)
    'EQUALS',

    # Increment/decrement (++,--)
    'INCREMENT', 'DECREMENT',

    # ID operator (#)
    'ID',

    # Delimiters ( ) [ ] { } , . ;
    'LPAREN', 'RPAREN',
    'LBRACKET', 'RBRACKET',
    'LBRACE', 'RBRACE',
    'COMMA', 'PERIOD', 'SEMI'
]


tokens += reserved.values()


# Operators
t_PLUS = r'\+'
t_MINUS = r'-'
t_TIMES = r'\*'
t_DIVIDE = r'/'
t_MODULO = r'%'
t_LOR = r'\|\|'
t_LAND = r'&&'
t_LNOT = r'!'
t_LT = r'<'
t_GT = r'>'
t_LE = r'<='
t_GE = r'>='
t_EQ = r'=='
t_NE = r'!='
t_PUSH = r'<<'
t_POP = r'>>'


# Assignment operator
t_EQUALS = r'='


# Increment/decrement
t_INCREMENT = r'\+\+'
t_DECREMENT = r'--'


# ID operator
t_ID = r'\#'


# Delimiters
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_LBRACKET = r'\['
t_RBRACKET = r'\]'
t_LBRACE = r'\{'
t_RBRACE = r'\}'
t_COMMA = r','
t_PERIOD = r'\.'
t_SEMI = r';'


# Identifiers
def t_IDENT(t):
    r'[a-zA-Z][a-zA-Z_0-9]*'
    t.type = reserved.get(t.value, 'IDENT')  # Check for reserved words
    return t


# Integer literal
t_INTEGER = r'\d+([lL])?'


# Floating literal
t_FLOAT = r'(((\d*\.\d+)|(\d+\.))(e(\+|-)?(\d+))? | (\d+)e(\+|-)?(\d+))'


# String literal
def t_STRING(t):
    r'\"([^\\\n]|(\\.))*?\"'
    t.lexer.lineno += t.value.count('\n')
    return t


# Whitespace
def t_WHITESPACE(t):
    r'\s+'
    t.lexer.lineno += t.value.count('\n')


# Comment (C-Style)
def t_COMMENT(t):
    r'/\*(.|\n)*?\*/'
    t.lexer.lineno += t.value.count('\n')


# Comment (C++-Style)
def t_CPPCOMMENT(t):
    r'//.*\n'
    t.lexer.lineno += 1


# Error handling rule
num_errors = 0


def t_error(t):
    """Handle an error in lexing."""
    global num_errors
    print("Illegal character '{0}'".format(t.value[0]))
    num_errors += 1
    t.lexer.skip(1)


# Build lexer
lex = importlib.import_module('lex')
lexer = lex.lex()


# ----------------------------------------------------------------------
# Syntax
# ----------------------------------------------------------------------

precedence = (
    ('left', 'PUSH', 'POP'),
    ('right', 'EQUALS'),
    ('left', 'LOR'),
    ('left', 'LAND'),
    ('nonassoc', 'EQ', 'NE'),
    ('nonassoc', 'LT', 'LE', 'GT', 'GE'),
    ('left', 'PLUS', 'MINUS'),
    ('left', 'TIMES', 'DIVIDE', 'MODULO'),
    ('right', 'PREFIX', 'LNOT', 'INCREMENT', 'DECREMENT', 'ID'),
    ('left', 'PERIOD', 'LBRACKET')
)


def p_program(p):
    """Program : Declarations"""
    p[0] = ProgramNode(p.lineno(1), p[1])


def p_declarations(p):
    """Declarations : Declarations Declaration
                    | empty
    """
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[1].append(p[2])
        p[0] = p[1]


def p_declaration(p):
    """Declaration : FunctionDecl
                   | StructDecl
    """
    p[0] = p[1]


def p_structdecl(p):
    """StructDecl : STRUCT Name LPAREN VarDeclsOpt RPAREN SEMI"""
    p[0] = StructDeclNode(p.lineno(1), p[2], p[4])


def p_vardeclsopt(p):
    """VarDeclsOpt : VarDecls
                   | empty
    """
    p[0] = p[1]


def p_vardecls(p):
    """VarDecls : VarDecl
                | VarDecls COMMA VarDecl
    """
    if len(p) == 2:
        p[0] = [p[1]]
    else:
        p[1].append(p[3])
        p[0] = p[1]


def p_vardecl(p):
    """VarDecl : Type Name"""
    p[0] = VarDeclNode(p.lineno(1), p[1], p[2])


def p_type(p):
    """Type : Name
            | Type LBRACKET RBRACKET
    """
    if len(p) == 2:
        p[0] = TypeNameNode(p.lineno(1), p[1])
    else:
        p[0] = ArrayTypeNameNode(p.lineno(1), p[1])


def p_name(p):
    """Name : IDENT"""
    p[0] = NameNode(p.lineno(1), p[1])


def p_parametersopt(p):
    """ParametersOpt : Parameters
                      | empty
    """
    p[0] = p[1]


def p_parameters(p):
    """Parameters : Parameter
                   | Parameters COMMA Parameter
    """
    if len(p) == 2:
        p[0] = [p[1]]
    else:
        p[1].append(p[3])
        p[0] = p[1]


def p_parameter(p):
    """Parameter : Type Name"""
    p[0] = ParameterNode(p.lineno(1), p[1], p[2])


def p_functiondecl(p):
    """FunctionDecl : Type Name LPAREN ParametersOpt RPAREN \
                          LPAREN VarDeclsOpt RPAREN Block"""
    p[0] = FunctionDeclNode(p.lineno(3), p[1], p[2], p[4], p[7], p[9])


def p_block(p):
    """Block : LBRACE StatementsOpt RBRACE"""
    p[0] = BlockNode(p.lineno(1), p[2])


def p_statementsopt(p):
    """StatementsOpt : Statements
                     | empty
    """
    p[0] = p[1]


def p_statements(p):
    """Statements : Statement
                  | Statements Statement
    """
    if len(p) == 2:
        p[0] = [p[1]]
    else:
        p[1].append(p[2])
        p[0] = p[1]


def p_statement(p):
    """Statement : IfStatement
                 | WhileStatement
                 | ForStatement
                 | BreakStatement
                 | ContinueStatement
                 | ReturnStatement
                 | ExpressionStatement
    """
    p[0] = p[1]


def p_ifstatement(p):
    """IfStatement : IF LPAREN Expression RPAREN Block ElseOpt"""
    p[0] = IfNode(p.lineno(1), p[3], p[5], p[6])


def p_elseopt(p):
    """ElseOpt : ELSE Block
               | ELSE IfStatement
               | empty
    """
    if len(p) == 3:
        p[0] = (p[2] if isinstance(p[2], BlockNode)
                else BlockNode(p.lineno(1), [p[2]]))
    else:
        p[0] = BlockNode(p.lineno(1), p[1])


def p_whilestatement(p):
    """WhileStatement : WHILE LPAREN Expression RPAREN Block"""
    p[0] = WhileNode(p.lineno(1), p[3], p[5])


def p_forstatement(p):
    """ForStatement : FOR LPAREN ExpressionOpt SEMI ExpressionOpt \
                          SEMI ExpressionOpt RPAREN Block"""
    p[0] = ForNode(p.lineno(1), p[3], p[5], p[7], p[9])


def p_breakstatement(p):
    """BreakStatement : BREAK SEMI"""
    p[0] = BreakNode(p.lineno(1))


def p_continuestatement(p):
    """ContinueStatement : CONTINUE SEMI"""
    p[0] = ContinueNode(p.lineno(1))


def p_returnstatement(p):
    """ReturnStatement : RETURN Expression SEMI
                       | RETURN SEMI
    """
    if len(p) == 4:
        p[0] = ReturnNode(p.lineno(1), p[2])
    else:
        p[0] = ReturnNode(p.lineno(1), None)


def p_expressionstatement(p):
    """ExpressionStatement : Expression SEMI"""
    p[0] = ExpressionStatementNode(p.lineno(2), p[1])


def p_expression(p):
    """Expression : Literal
                  | NameExpression
                  | ParenthesizedExpression
                  | CallExpression
                  | NewExpression
                  | FieldAccessExpression
                  | ArrayIndexExpression
                  | UnaryPrefixOperation
                  | BinaryOperation
    """
    p[0] = p[1]


def p_expressionopt(p):
    """ExpressionOpt : Expression
                     | empty
    """
    if not p[1]:
        p[0] = None  # replace empty list with None
    else:
        p[0] = p[1]


# separate out literals
def p_literal(p):
    """Literal : IntegerLiteral
               | FloatLiteral
               | StringLiteral
               | BooleanLiteral
               | NullLiteral
    """
    p[0] = p[1]


def p_integerliteral(p):
    """IntegerLiteral : INTEGER"""
    p[0] = IntegerNode(p.lineno(1), p[1])
    check_integer_literal(p[0])


def p_floatliteral(p):
    """FloatLiteral : FLOAT"""
    p[0] = FloatNode(p.lineno(1), p[1])


def p_stringliteral(p):
    """StringLiteral : STRING"""
    p[0] = StringNode(p.lineno(1), p[1])


def p_booleanliteral(p):
    """BooleanLiteral : TRUE
                      | FALSE
    """
    p[0] = BooleanNode(p.lineno(1), p[1])


def p_nullliteral(p):
    """NullLiteral : NULL"""
    p[0] = NullNode(p.lineno(1))


def p_nameexpression(p):
    """NameExpression : Name"""
    p[0] = NameExpressionNode(p.lineno(1), p[1])


def p_parenthesizedexpression(p):
    """ParenthesizedExpression : LPAREN Expression RPAREN"""
    p[0] = p[2]


def p_callexpression(p):
    """CallExpression : Name LPAREN ArgumentsOpt RPAREN"""
    p[0] = CallNode(p.lineno(2), p[1], p[3])


def p_argumentsopt(p):
    """ArgumentsOpt : Arguments
                    | empty
    """
    p[0] = p[1]


def p_arguments(p):
    """Arguments : Expression
                 | Arguments COMMA Expression
    """
    if len(p) == 2:
        p[0] = [p[1]]
    else:
        p[1].append(p[3])
        p[0] = p[1]


def p_newexpression(p):
    """NewExpression : NEW Type LPAREN ArgumentsOpt RPAREN
                     | NEW Type LBRACE ArgumentsOpt RBRACE
    """
    p[0] = NewNode(p.lineno(1), p[2], p[4])


def p_fieldaccessexpression(p):
    """FieldAccessExpression : Expression PERIOD Name"""
    p[0] = FieldAccessNode(p.lineno(2), p[1], p[3])


def p_arrayindexexpression(p):
    """ArrayIndexExpression : Expression LBRACKET Expression RBRACKET"""
    p[0] = ArrayIndexNode(p.lineno(2), p[1], p[3])


unary_ops = {
    '+': PrefixPlusNode,
    '-': PrefixMinusNode,
    '!': NotNode,
    '++': PrefixIncrNode,
    '--': PrefixDecrNode,
    '#': IDNode
}


def p_unaryprefixoperation(p):
    """UnaryPrefixOperation : PLUS Expression %prec PREFIX
                            | MINUS Expression %prec PREFIX
                            | LNOT Expression
                            | INCREMENT Expression
                            | DECREMENT Expression
                            | ID Expression
    """
    p[0] = unary_ops[p[1]](p.lineno(1), p[2])


binary_ops = {
    '+': PlusNode,
    '-': MinusNode,
    '*': TimesNode,
    '/': DivideNode,
    '%': ModuloNode,
    '||': LogicalOrNode,
    '&&': LogicalAndNode,
    '<': LessNode,
    '<=': LessEqualNode,
    '>': GreaterNode,
    '>=': GreaterEqualNode,
    '==': EqualNode,
    '!=': NotEqualNode,
    '=': AssignNode,
    '<<': PushNode,
    '>>': PopNode
}


def p_binaryoperation(p):
    """BinaryOperation : Expression PLUS Expression
                       | Expression MINUS Expression
                       | Expression TIMES Expression
                       | Expression DIVIDE Expression
                       | Expression MODULO Expression
                       | Expression LOR Expression
                       | Expression LAND Expression
                       | Expression LT Expression
                       | Expression LE Expression
                       | Expression GT Expression
                       | Expression GE Expression
                       | Expression EQ Expression
                       | Expression NE Expression
                       | Expression EQUALS Expression
                       | Expression PUSH Expression
                       | Expression POP Expression
    """
    p[0] = binary_ops[p[2]](p.lineno(2), p[1], p[3])


def p_empty(p):
    """empty :"""
    p[0] = []


def p_error(t):
    """Handle an error in parsing."""
    global num_errors
    print("Syntax error at line {0}: '{1}'".format(t.lexer.lineno,
                                                   t.value))
    num_errors += 1


INT_MIN = -2**31
LONG_MIN = -2**63


def check_integer_literal(inode):
    """Check validity of an integer literal."""
    if inode.text[-1] in 'lL':
        text = inode.text[:-1]
        lower = LONG_MIN
    else:
        text = inode.text
        lower = INT_MIN
    value = int(text)
    if value not in range(0, -lower):
        global num_errors
        msg = ('Syntax error at line {0}: integer literal {1} '
               'outside of valid range [0, {2}]')
        print(msg.format(inode.position, inode.text, -lower-1))
        num_errors += 1


yacc = importlib.import_module('yacc')
parser = yacc.yacc()


def error_count():
    """Return the number of errors during lexing and parsing."""
    return num_errors


def parse(filename):
    """Read a uC source file, parse it, and return an AST."""
    with open(filename) as f:
        return parser.parse(f.read(), tracking=True)


if __name__ == '__main__':
    import sys
    if len(sys.argv) != 2:
        print('Usage: python3 {0} <filename>'.format(sys.argv[0]))
    else:
        outname = (sys.argv[1] if '.uc' not in sys.argv[1]
                   else sys.argv[1][:-3]) + '.dot'
        with open(outname, 'w') as out:
            graph_gen(parse(sys.argv[1]), out=out)
        print('Wrote graph to {0}.'.format(outname))
