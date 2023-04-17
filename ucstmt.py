"""
ucstmt.py.

This file contains definitions of AST nodes that represent uC
statements.

Project UID c49e54971d13f14fbc634d7a0fe4b38d421279e7
"""

from dataclasses import dataclass
from typing import List, Optional
from ucbase import ASTNode
from ucerror import error
from ucexpr import ExpressionNode
import uctypes


@dataclass
class StatementNode(ASTNode):
    """The base class for all statement nodes."""

    # add your code below if necessary


@dataclass
class BlockNode(ASTNode):
    """An AST node representing a block of statements.

    statements is a list of statement nodes.
    """

    statements: List[StatementNode]

    # add your code below if necessary
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        for statement in self.statements:
            statement.type_check(ctx)

    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        ctx.print("// Block Body", indent=True)
        for statement in self.statements:
            statement.gen_function_defs(ctx)
            ctx.print("; //Statement", indent=False)


@dataclass
class IfNode(StatementNode):
    """An AST node representing an if statement.

    test is the condition, then_block is a block representing the then
    case, and else_block is a block representing the else case.
    """

    test: ExpressionNode
    then_block: BlockNode
    else_block: BlockNode

    # add your code below
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.test.type_check(ctx)
        if self.test.type.name != "boolean":
            error(ctx.phase,
                  self.position,
                  "Not an applicable type for IFnode.")
        self.then_block.type_check(ctx)
        self.else_block.type_check(ctx)

    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        ctx.print("", indent=True)
        ctx.print("// Start of If Block", indent=True)
        out = "if ("
        ctx.print(out, indent=True, end="")
        self.test.gen_function_defs(ctx)
        ctx.print("){", indent=False)
        self.then_block.gen_function_defs(ctx)
        if len(self.else_block.statements) != 0:
            ctx.print("} else {", indent=True)
            self.else_block.gen_function_defs(ctx)
            ctx.print("}", indent=True)
        else:
            ctx.print("}", indent=True)

    # if (
    # x == 3
    # && foo() == True
    # || y == 3
    # )
    # {

    # }


@dataclass
class WhileNode(StatementNode):
    """An AST node representing a while statement.

    test is the condition and body is a block representing the body.
    """

    test: ExpressionNode
    body: BlockNode

    # add your code below
    def basic_control(self, ctx):
        """Check basic control flow within the given WhileNode."""
        new_ctx = ctx.clone()
        new_ctx["in_loop"] = True
        super().basic_control(new_ctx)

    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.test.type_check(ctx)
        if self.test.type.name != "boolean":
            error(ctx.phase, self.position,
                  "Not an applicable type for Whilenode.")
        self.body.type_check(ctx)

    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        ctx.print("// Start of While Block", indent=True)
        ctx.print("while (", indent=False, end="")
        self.test.gen_function_defs(ctx)
        ctx.print(") {", indent=False)
        self.body.gen_function_defs(ctx)
        ctx.print("}", indent=True)


@dataclass
class ForNode(StatementNode):
    """An AST node representing a for statement.

    init is the initialization, test is the condition, update is the
    update expression, and body is a block representing the body.
    init, test, and update may be None if the corresponding expression
    is omitted.
    """

    init: Optional[ExpressionNode]
    test: Optional[ExpressionNode]
    update: Optional[ExpressionNode]
    body: BlockNode

    # add your code below
    def basic_control(self, ctx):
        """Check basic control flow within the given ForNode."""
        new_ctx = ctx.clone()
        new_ctx["in_loop"] = True
        super().basic_control(new_ctx)

    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.test.type_check(ctx)
        if self.test.type.name != "boolean":
            error(ctx.phase, self.position,
                  "Not an applicable type for FORnode.")
        # typecheck on expressions, IF present
        if self.init is not None:
            self.init.type_check(ctx)
        if self.update is not None:
            self.update.type_check(ctx)
        # type check on blocks
        self.body.type_check(ctx)

    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        ctx.print("// Start of For Block", indent=True)
        ctx.print("for (", indent=True, end="")
        if self.init:
            self.init.gen_function_defs(ctx)
        ctx.print("; ", indent=False, end="")
        if self.test:
            self.test.gen_function_defs(ctx)
        ctx.print("; ", indent=False, end="")
        if self.update:
            self.update.gen_function_defs(ctx)
        ctx.print(") {", indent=False)
        self.body.gen_function_defs(ctx)
        ctx.print("}", indent=True)


@dataclass
class BreakNode(StatementNode):
    """An AST node representing a break statement."""

    # add your code below
    def basic_control(self, ctx):
        """Check basic control flow within the given BreakNode."""
        if not ctx["in_loop"]:
            error(ctx.phase, self.position, "break not found in loop.")

    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        ctx.print("break", end="")


@dataclass
class ContinueNode(StatementNode):
    """An AST node representing a continue statement."""

    # add your code below
    def basic_control(self, ctx):
        """Check basic control flow within the given ContinueNode."""
        if not ctx["in_loop"]:
            error(ctx.phase, self.position, "continue not found in loop.")

    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        ctx.print("continue", end="")


@dataclass
class ReturnNode(StatementNode):
    """An AST node representing a return statement.

    expr is the return expression if there is one, None otherwise.
    """

    expr: Optional[ExpressionNode]

    # add your code below
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        if ctx["rettype"].name != "void":  # this function is not void
            if self.expr is None:
                error(
                    ctx.phase,
                    self.position,
                    f"return expression is not for {ctx['rettype']} function.",
                )
            else:
                # return statement must be given an expression whose type
                # matches or is implicitly convertible to the return type
                self.expr.type_check(ctx)
                if not uctypes.is_compatible(self.expr.type, ctx["rettype"]):
                    error(
                        ctx.phase,
                        self.position,
                        "return expression is not compatible with rettype.",
                    )
        else:  # this function is void
            if self.expr is not None:
                error(
                    ctx.phase,
                    self.position,
                    "a return expression is provided within a void function.",
                )

    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        ctx.print("return", end="")
        if self.expr:
            ctx.print(" ", end="")
            self.expr.gen_function_defs(ctx)
        ctx.print(";", end="")
        ctx.print("//return node", end="")


@dataclass
class ExpressionStatementNode(StatementNode):
    """An AST node representing a statement of just an expression.

    expr is the expression.
    """

    expr: ExpressionNode

    # add your code below if necessary
    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        self.expr.type_check(ctx)

    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        self.expr.gen_function_defs(ctx)
