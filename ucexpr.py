"""
ucexpr.py.

This file contains definitions of AST nodes that represent uC
expressions.

Project UID c49e54971d13f14fbc634d7a0fe4b38d421279e7
"""

from dataclasses import dataclass
from typing import List, Optional
from ucbase import attribute
import ucbase
from ucerror import error
import ucfunctions
import uctypes

# import pdb


#############################
# Base Node for Expressions #
#############################


@dataclass
class ExpressionNode(ucbase.ASTNode):
    """The base class for all nodes representing expressions.

    type is a reference to the computed uctypes.Type of this
    expression.
    """

    type: Optional[uctypes.Type] = attribute()

    # Tested
    def is_lvalue(self):
        """Return whether or not this node produces an l-value."""
        return False

    # add your code below if necessary


############
# Literals #
############


@dataclass
class LiteralNode(ExpressionNode):
    """The base class for all nodes representing literals.

    text is the textual representation of the literal for code
    generation.
    """

    text: str

    # add your code below if neccessary
    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        ctx.print(self.text, end='')
@dataclass
class IntegerNode(LiteralNode):
    """An AST node representing an integer (int or long) literal."""

    # add your code below
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in ch it is used. Checks that a valid main function
        exists.
        """
        if self.text[-1] == "l" or self.text[-1] == "L":
            self.type = ctx.global_env.lookup_type(ctx.phase,
                                                   self.position,
                                                   "long")
        else:
            self.type = ctx.global_env.lookup_type(ctx.phase,
                                                   self.position,
                                                   "int")
    # int x = 3;

@dataclass
class FloatNode(LiteralNode):
    """An AST node representing a float literal."""

    # add your code below
    # Phase 6 Start by computing the type of literals.
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.type = ctx.global_env.lookup_type(ctx.phase,
                                               self.position,
                                               "float")


@dataclass
class StringNode(LiteralNode):
    """An AST node representing a string literal."""

    # add your code below
    # Phase 6 Start by computing the type of literals.
    def type_check(self, ctx):
        # Tested
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.type = ctx.global_env.lookup_type(ctx.phase,
                                               self.position,
                                               "string")
    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        ctx.print(f'{self.text}s', end='')

@dataclass
class BooleanNode(LiteralNode):
    """An AST node representing a boolean literal."""

    # add your code below
    # Tested

    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.type = ctx.global_env.lookup_type(ctx.phase,
                                               self.position,
                                               "boolean")


@dataclass
class NullNode(LiteralNode):
    """An AST node representing the null literal."""

    text: str = "nullptr"

    # add your code below
    # Phase 6 Start by computing the type of literals.
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.type = ctx.global_env.lookup_type(ctx.phase,
                                               self.position,
                                               "null")


###################
# Name Expression #
###################


@dataclass
class NameExpressionNode(ExpressionNode):
    """An AST node representing a name expression.

    name is an AST node denoting the actual name.
    """

    name: ucbase.NameNode

    # add your code below
    def is_lvalue(self):
        """Return whether or not this node produces an l-value."""
        return True

    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        super().type_check(ctx)
        self.type = ctx["local_env"].get_type(ctx.phase,
                                              self.position,
                                              self.name.raw)
    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        #TODO: is UC_VAR here correct? 
        ctx.print(f"UC_VAR({self.name.raw})", end='')

#######################
# Calls and Accessors #
#######################


@dataclass
class CallNode(ExpressionNode):
    """An AST node representing a function-call expression.

    name is an AST node representing the name of the function and args
    is a list of argument expressions to the function. func is a
    reference to the ucfunctions.Function named by this call.
    """

    name: ucbase.NameNode
    args: List[ExpressionNode]
    func: Optional[ucfunctions.Function] = attribute()

    # add your code below
    def resolve_calls(self, ctx):
        """Match function calls to the actual functions they name.

        Uses global_env to look up a function name. Reports an error if an
        unknown function is named.
        """
        new_ctx = ctx.clone()
        new_ctx["is_return"] = False
        self.func = ctx.global_env.lookup_function(
            ctx.phase, self.position, self.name.raw
        )
        super().resolve_calls(ctx)

    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.type = self.func.rettype
        super().type_check(ctx)
        self.func.check_args(ctx.phase, self.position, self.args)

    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        ctx.print(f'UC_FUNCTION({self.name.raw})(', end='')
        if self.args:
            self.args[0].gen_function_defs(ctx)
            for arg in self.args[1:]:
                ctx.print(', ', end='')
                arg.gen_function_defs(ctx)
        ctx.print(')', end='')

@dataclass
class NewNode(ExpressionNode):
    """An AST node representing a new expression.

    typename is an AST node representing the type of the object and
    args is a list of argument expressions to the constructor.
    """

    typename: ucbase.BaseTypeNameNode
    args: List[ExpressionNode]

    # add your code below
    def resolve_types(self, ctx):
        """Resolve type name to their actual type in NewNode.

        Overrides method in ucfrontend.py. Resolves type of child
        typename first and then resolves NewNode's type
        """
        new_ctx = ctx.clone()
        new_ctx["is_return"] = False

        self.typename.resolve_types(new_ctx)
        self.type = self.typename.type

        super().resolve_types(ctx)

    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        if is_primitive(self.type):
            error(
                ctx.phase,
                self.position,
                f"NewNode cannot be primitive type {self.type}",
            )
        super().type_check(ctx)
        self.type.check_args(ctx.phase, self.position, self.args)
    
    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        #           // Generic construction of a uC array or user-defined object.
        #   // Dispatches to uc_construct_dispatch for the actual
        #   // implementation.
        #   template<class T, class... Args>
        #   T uc_construct(Args&&... args) {
        #     return uc_construct_dispatch<T>::construct(
        #       std::forward<Args>(args)...
        #     );
        #   }
        # uc_construct<UC_REFERENCE(bar)>();
        ctx.print(f"uc_construct<{self.typename.type.mangle()}>(", end='')
        if self.args:
            self.args[0].gen_function_defs(ctx)
            for arg in self.args[1:]:
                ctx.print(", ", end='')
                arg.gen_function_defs(ctx)
        ctx.print(")")

@dataclass
class FieldAccessNode(ExpressionNode):
    """An AST node representing access to a field of an object.

    receiver is an expression representing the object whose field is
    being accessed and field is is an AST node representing the name
    of the field.
    """

    receiver: ExpressionNode
    field: ucbase.NameNode

    # add your code below
    def is_lvalue(self):
        """Return whether or not this node produces an l-value."""
        return True

    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.receiver.type_check(ctx)
        if isinstance(self.receiver.type, uctypes.ArrayType):
            self.type = self.receiver.type.lookup_field(
                ctx.phase, self.position, self.field.raw, ctx.global_env
            )
            if self.field.raw == "length":
                self.type = ctx.global_env.lookup_type(ctx.phase,
                                                       self.position,
                                                       "int")
            else:
                error(
                    ctx.phase,
                    self.position,
                    "field must be length when receiver is of arraytype",
                )
        elif isinstance(self.receiver.type, uctypes.UserType):
            self.type = self.receiver.type.lookup_field(
                ctx.phase, self.position, self.field.raw, ctx.global_env
            )
        else:
            error(
                ctx.phase,
                self.position,
                "must be of arraytype or userdefined type",
            )
    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        # self.receiver.gen_function_defs(ctx)
        #TODO: Is this always UC_REFERENCE? and is there a case where .name doesn't exist?
        self.receiver.gen_function_defs(ctx)
        ctx.print(f"->UC_VAR({self.field.raw})", end='')
        # UC_REFERENCE(Person)->age
        #TODO: maybe need UC in front of field 
        

@dataclass
class ArrayIndexNode(ExpressionNode):
    """An AST node representing indexing into an array.

    receiver is an expression representing the array and index the
    index expression.
    """

    receiver: ExpressionNode
    index: ExpressionNode

    # add your code below
    def is_lvalue(self):
        """Return whether or not this node produces an l-value."""
        return True

    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.receiver.type_check(ctx)
        self.index.type_check(ctx)
        self.type = ctx.global_env.lookup_type(ctx.phase, self.position, "int")
        if isinstance(self.receiver.type, uctypes.ArrayType):
            if self.index.type.name == "int":
                self.type = self.receiver.type.elem_type
            else:
                error(
                    ctx.phase,
                    self.position,
                    "index must be of type int",
                )
        else:
            error(
                ctx.phase,
                self.position,
                "receiver must be array",
            )
    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        # self.receiver.gen_function_defs(ctx)
        # uc_array_index()
        ctx.print("uc_array_index(", end='')
        self.receiver.gen_function_defs(ctx)
        ctx.print(', ', end='')
        self.index.gen_function_defs(ctx)
        ctx.print(")", end='')
        
#####################
# Unary Expressions #
#####################


@dataclass
class UnaryPrefixNode(ExpressionNode):
    """A base AST node that represents a unary prefix operation.

    expr is the expression to which the operation is being applied and
    op_name is the string representation of the operator.
    """

    expr: ExpressionNode
    op_name: str

    # add your code below if necessary
    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        ctx.print(self.op_name, end='')
        self.expr.gen_function_defs(ctx)
       

@dataclass
class PrefixSignNode(UnaryPrefixNode):
    """A base AST node representing a prefix sign operation."""

    # add your code below if necessary Tested
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.expr.type_check(ctx)
        if uctypes.is_numeric_type(self.expr.type):
            self.type = ctx.global_env.lookup_type(
                ctx.phase, self.position, self.expr.type.name
            )
        else:
            error(
                ctx.phase, self.position,
                "Not an applicable type for unary sign node."
            )
    

@dataclass
class PrefixPlusNode(PrefixSignNode):
    """An AST node representing a prefix plus operation."""

    op_name: str = "+"

    # add your code below if necessary
    # implemented in prefixSignNode


@dataclass
class PrefixMinusNode(PrefixSignNode):
    """An AST node representing a prefix minus operation."""

    op_name: str = "-"

    # add your code below if necessary
    # implemented in prefixSignNode


@dataclass
class NotNode(UnaryPrefixNode):
    """An AST node representing a not operation."""

    op_name: str = "!"

    # add your code below if necessary Tested
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.expr.type_check(ctx)
        if self.expr.type.name == "boolean":
            self.type = ctx.global_env.lookup_type(
                ctx.phase, self.position, self.expr.type.name
            )
        else:
            error(
                ctx.phase,
                self.position,
                "Not an applicable type for unary Not node."
            )


@dataclass
class PrefixIncrDecrNode(UnaryPrefixNode):
    """A base AST node representing a prefix {in,de}crement operation."""

    # add your code below if necessary Tested
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.expr.type_check(ctx)
        if uctypes.is_numeric_type(self.expr.type) and self.expr.is_lvalue():
            self.type = self.expr.type
        else:
            error(
                ctx.phase, self.position,
                "Not an applicable type for unary Not node."
            )


@dataclass
class PrefixIncrNode(PrefixIncrDecrNode):
    """An AST node representing a prefix increment operation."""

    op_name: str = "++"

    # add your code below if necessary
    # implemented in PrefixIncDecrNode


@dataclass
class PrefixDecrNode(PrefixIncrDecrNode):
    """An AST node representing a prefix decrement operation.

    expr is the operand expression.
    """

    op_name: str = "--"

    # add your code below if necessary
    # implemented in PrefixIncrDecrNode


@dataclass
class IDNode(UnaryPrefixNode):
    """An AST node representing an id operation."""

    op_name: str = "#"

    # add your code below if necessary
    # Reference types could be user-defined methods, arrays, or null reference.
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        if is_primitive(
            self.expr
        ):  # if it's not a Primitive type, it must be a reference type
            error(ctx.phase,
                  self.position,
                  "Not an applicable type for IDnode.")
        else:
            self.type = ctx.global_env.lookup_type(
                ctx.phase, self.position, self.expr.type.name
            )
    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        ctx.print("uc_id(", end='', indent=True)
        self.expr.gen_function_defs(ctx)
        ctx.print(')')

######################
# Binary Expressions #
######################

# Base classes


@dataclass
class BinaryOpNode(ExpressionNode):
    """A base AST node that represents a binary infix operation.

    lhs is the left-hand side expression, rhs is the right-hand side
    expression, and op_name is the name of the operator.
    """

    lhs: ExpressionNode
    rhs: ExpressionNode
    op_name: str

    # add your code below if necessary
    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        ctx.print(f"(", end='')
        self.lhs.gen_function_defs(ctx)
        ctx.print(f" {self.op_name} ", end='')
        self.rhs.gen_function_defs(ctx)
        ctx.print(f")", end='')

@dataclass
class BinaryArithNode(BinaryOpNode):
    """A base AST node representing a binary arithmetic operation."""

    # add your code below if necessary
    # phase 6, copied from PlusNode
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.lhs.type_check(ctx)
        self.rhs.type_check(ctx)
        if uctypes.is_numeric_type(self.lhs.type) and uctypes.is_numeric_type(
            self.rhs.type
        ):
            self.type = uctypes.join_types(
                ctx.phase, self.position,
                self.lhs.type,
                self.rhs.type, ctx.global_env
            )
        else:
            error(
                ctx.phase,
                self.position,
                "Not an applicable type for arithmetics.",
            )


@dataclass
class BinaryLogicNode(BinaryOpNode):
    """A base AST node representing a binary logic operation."""

    # add your code below if necessary
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.lhs.type_check(ctx)
        self.rhs.type_check(ctx)
        if self.lhs.type.name != "boolean" or self.rhs.type.name != "boolean":
            error(
                ctx.phase,
                self.position,
                "Not an applicable type for logical operation.",
            )
        self.type = ctx.global_env.lookup_type(ctx.phase,
                                               self.position, "boolean")


@dataclass
class BinaryCompNode(BinaryOpNode):
    """A base AST node representing binary comparison operation."""

    # add your code below if necessary
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.lhs.type_check(ctx)
        self.rhs.type_check(ctx)
        if (
            uctypes.is_numeric_type(self.lhs.type)
            and uctypes.is_numeric_type(self.rhs.type)
        ) or (self.lhs.type.name == "string"
              and self.rhs.type.name == "string"):
            self.type = ctx.global_env.lookup_type(ctx.phase,
                                                   self.position, "boolean")
        else:
            error(
                ctx.phase,
                self.position,
                "Not an applicable type for Binary Comp operation.",
            )


@dataclass
class EqualityTestNode(BinaryOpNode):
    """A base AST node representing an equality comparison."""

    # add your code below if necessary
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.lhs.type_check(ctx)
        self.rhs.type_check(ctx)
        if (
            (self.lhs.type is self.rhs.type)
            or is_convertible(self.lhs, self.rhs)
            or is_convertible
        ):
            self.type = ctx.global_env.lookup_type(ctx.phase,
                                                   self.position, "boolean")
        else:
            error(ctx.phase, self.position,
                  "Not a valid pair of types for equality.")


def is_convertible(lhs, rhs):
    """Check if convertible.

    Takes in lhs and rhs and checks .type.name.
    """
    if lhs.type.name == "int" and (rhs.type.name in ("float", "long")):
        return True
    if lhs.type.name == "long" and rhs.type.name == "float":
        return True
    if lhs.type.name == "nullptr":
        return True
    return False


def is_primitive(operand):
    """Check if operand is a primitive.

    A Helper function for plusNode that
    checks if a given operand is a primitive
    but also not null or void.
    """
    if isinstance(operand, uctypes.PrimitiveType):  # jsut null
        return True
    return False


def is_comp_bool_string(lhs, rhs):
    """Check if lhs and rhs are compatible in the pairing of bool and string.

    Helper function for plusNode that checks if a given operand is a primitive
    but also not null or void
    """
    if lhs.type.name != "boolean" and rhs.type.name != "boolean":
        return True
    if lhs.type.name == "boolean" and rhs.type.name == "string":
        return True
    if lhs.type.name == "string" and rhs.type.name == "boolean":
        return True
    return False


@dataclass
class PlusNode(BinaryArithNode):
    """An AST node representing a binary plus operation."""

    op_name: str = "+"

    # add your code below
    # Phase 6
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        # both operands must be primitives (excluding void and null)
        # if one operand is a bool the other must be a string
        self.lhs.type_check(ctx)
        self.rhs.type_check(ctx)
        if (
            is_primitive(self.lhs.type)
            and is_primitive(self.rhs.type)
            and (self.lhs.type.name not in ("null", "void"))
            and (self.rhs.type.name not in ("null", "void"))
        ):
            if is_comp_bool_string(self.lhs, self.rhs) or is_comp_bool_string(
                self.rhs, self.lhs
            ):
                self.type = uctypes.join_types(
                    ctx.phase,
                    self.position,
                    self.lhs.type,
                    self.rhs.type,
                    ctx.global_env,
                )
            else:
                error(
                    ctx.phase,
                    self.position,
                    "Bool operand must be accompanied with String operand.",
                )
        else:
            error(
                ctx.phase,
                self.position,
                "Invalid primitive type for Plus Operation.",
            )


@dataclass
class MinusNode(BinaryArithNode):
    """An AST node representing a binary minus operation."""

    op_name: str = "-"

    # add your code below if necessary


@dataclass
class TimesNode(BinaryArithNode):
    """An AST node representing a binary times operation."""

    op_name: str = "*"

    # add your code below if necessary


@dataclass
class DivideNode(BinaryArithNode):
    """An AST node representing a binary divide operation."""

    op_name: str = "/"

    # add your code below if necessary


@dataclass
class ModuloNode(BinaryArithNode):
    """An AST node representing a binary modulo operation."""

    op_name: str = "%"

    # add your code below if necessary


# Logical operations


@dataclass
class LogicalOrNode(BinaryLogicNode):
    """An AST node representing a logical or operation."""

    op_name: str = "||"

    # add your code below if necessary


@dataclass
class LogicalAndNode(BinaryLogicNode):
    """An AST node representing a logical and operation."""

    op_name: str = "&&"

    # add your code below if necessary


# Arithmetic comparisons


@dataclass
class LessNode(BinaryCompNode):
    """An AST node representing a less than operation."""

    op_name: str = "<"

    # add your code below if necessary


@dataclass
class LessEqualNode(BinaryCompNode):
    """An AST node representing a less than or equal operation.

    lhs is the left-hand operand and rhs is the right-hand operand.
    """

    op_name: str = "<="

    # add your code below if necessary


@dataclass
class GreaterNode(BinaryCompNode):
    """An AST node representing a greater than operation."""

    op_name: str = ">"

    # add your code below if necessary


@dataclass
class GreaterEqualNode(BinaryCompNode):
    """An AST node representing a greater than or equal operation."""

    op_name: str = ">="

    # add your code below if necessary


# Equality comparisons


@dataclass
class EqualNode(EqualityTestNode):
    """An AST node representing an equality comparison."""

    op_name: str = "=="

    # add your code below if necessary


@dataclass
class NotEqualNode(EqualityTestNode):
    """An AST node representing an inequality comparison."""

    op_name: str = "!="

    # add your code below if necessary


# Other binary operations


@dataclass
class AssignNode(BinaryOpNode):
    """An AST node representing an assignment operation."""

    op_name: str = "="

    # add your code below
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.rhs.type_check(ctx)
        self.lhs.type_check(ctx)
        if uctypes.is_compatible(self.rhs.type, self.lhs.type):
            if self.lhs.is_lvalue():
                self.type = self.lhs.type
            else:
                error(ctx.phase, self.position, f"{self.lhs} is not an lvalue")
        else:
            error(
                ctx.phase,
                self.position,
                f"{self.rhs.type} is not assignable to {self.lhs.type}",
            )


@dataclass
class PushNode(BinaryOpNode):
    """An AST node representing an array insertion operation."""

    op_name: str = "<<"

    # add your code below
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.lhs.type_check(ctx)
        self.rhs.type_check(ctx)

        # Is lhs an array?
        if isinstance(self.lhs.type, uctypes.ArrayType):
            # target = source
            # lhs = rhs
            if uctypes.is_compatible(self.rhs.type.array_type,
                                     self.lhs.type):
                self.type = self.lhs.type
            else:
                error(
                    ctx.phase,
                    self.position,
                    "Not an applicable type for Pop Array operation.",
                )
        else:
            error(
                ctx.phase,
                self.position,
                "Not an applicable type for Push Array.",
            )
    
    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        ctx.print("uc_array_push(", end='')
        self.lhs.gen_function_defs(ctx)
        ctx.print(', ', end='')
        self.rhs.gen_function_defs(ctx)
        ctx.print(")", end='')
    


@dataclass
class PopNode(BinaryOpNode):
    """An AST node representing an array extraction operation."""

    op_name: str = ">>"

    # add your code below
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used.
        Checks that a valid main function exists.
        """
        self.lhs.type_check(ctx)
        self.rhs.type_check(ctx)

        if isinstance(self.lhs.type, uctypes.ArrayType):
            if self.rhs.type.name == "nullptr" or (
                self.rhs.is_lvalue()
                and uctypes.is_compatible(self.rhs.type.array_type,
                                          self.lhs.type)
            ):
                # The result of the push operation
                # has the same type as the left-hand operand
                self.type = self.lhs.type
            else:
                error(
                    ctx.phase,
                    self.position,
                    f"wrong type for pop. LHS:{self.lhs}, RHS:{self.rhs}",
                )
        else:
            error(
                ctx.phase,
                self.position,
                "Not an applicable type for pop.",
            )
    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        ctx.print("uc_array_pop(", end='')
        self.lhs.gen_function_defs(ctx)
        ctx.print(', ', end='')
        self.rhs.gen_function_defs(ctx)
        ctx.print(")", end='')
