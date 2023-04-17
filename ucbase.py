"""
ucbase.py.

This file contains definitions of the base AST node, declaration
nodes, global and local environments, and utility functions.

Project UID c49e54971d13f14fbc634d7a0fe4b38d421279e7
"""

import dataclasses
from dataclasses import dataclass
import itertools
import sys
from typing import List, Optional, ClassVar, Iterator
from ucerror import error
import uctypes
import ucfunctions

# import pdb


#################
# AST Functions #
#################


def attribute():
    """Specify that a field is an attribute.

    An attribute is initially defaulted to None but will be filled in
    with its proper value in an analysis phase.
    """
    return dataclasses.field(default=None, init=False)


def ast_map(func, item, terminal_func=None):
    """Map the given function on an AST item.

    If the item is a list, then the function is mapped across its
    elements. If the item is a terminal rather than an AST node, then
    terminal_func is applied if given.
    """
    if isinstance(item, list):
        for i in item:
            ast_map(func, i, terminal_func)
    elif isinstance(item, ASTNode):
        func(item)
    elif terminal_func:
        terminal_func(item)


################################
# Environments in the Compiler #
################################


class GlobalEnv:
    """A class that represents the global environment of a uC program.

    Maps names to types and to functions.
    """

    def __init__(self):
        """Initialize the environment with built-in names."""
        self.__types = {}
        self.__functions = {}
        self.__token = object()
        uctypes.add_builtin_types(self.__types, self.__token)
        ucfunctions.add_builtin_functions(self.__functions,
                                          self.__types, self.__token)

    def add_type(self, phase, position, name, declnode):
        """Add the given type to this environment.

        phase is the current compiler phase, position is the source
        position of the type declaration, name is a string containing
        the name of the type, and declnode is the AST node
        corresponding to the declaration. Reports an error if a type
        of the given name is already defined.
        """
        if name in self.__types:
            error(phase, position, "redefinition of type " + name)
        else:
            self.__types[name] = uctypes.UserType(self.__token, name, declnode)
        return self.__types[name]

    def add_function(self, phase, position, name, declnode):
        """Add the given function to this environment.

        phase is the current compiler phase, position is the source
        position of the function declaration, name is a string
        containing the name of the function, and declnode is the AST
        node corresponding to the declaration. Reports an error if a
        function of the given name is already defined.
        """
        if name in self.__functions:
            error(phase, position, "redefinition of function " + name)
        else:
            self.__functions[name] = ucfunctions.UserFunction(
                self.__token, name, declnode
            )
        return self.__functions[name]

    def lookup_type(self, phase, position, name, strict=True):
        """Return the type represented by the given name.

        phase is the current compiler phase, position is the source
        position that resulted in this lookup, name is a string
        containing the name of the type to look up. If strict is True,
        then an error is reported if the name is not found, and the
        int type is returned. Otherwise, if the name is not found,
        None is returned.
        """
        if name not in self.__types:
            if strict:
                error(phase, position, "undefined type " + name)
                return self.__types["int"]  # treat it as int by default
            return None
        return self.__types[name]

    def lookup_function(self, phase, position, name, strict=True):
        """Return the function represented by the given name.

        phase is the current compiler phase, position is the source
        position that resulted in this lookup, name is a string
        containing the name of the function to look up. If strict is
        True, then an error is reported if the name is not found, and
        string_to_int function is returned. Otherwise, if the name is
        not found, None is returned.
        """
        if name not in self.__functions:
            if strict:
                error(phase, position, "undefined function " + name)
                return self.__functions["string_to_int"]  # default
            return None
        return self.__functions[name]

    def get_type_names(self):
        """Return a sequence of the type names in the environment."""
        return self.__types.keys()

    def get_function_names(self):
        """Return a sequence of the function names in the environment."""
        return self.__functions.keys()


class VarEnv:
    """A class that represents a local environment in a uC program.

    Maps names to types of fields, parameters, and variables.
    """

    def __init__(self, global_env):
        """Initialize this to an empty local environment.

        The given global environment is used to lookup a default type
        when a name is not defined.
        """
        self.__global_env = global_env
        self.__var_types = {}

    def add_variable(self, phase, position, name, var_type, kind_str):
        """Insert a variable into this environment.

        phase is the current compiler phase, position is the source
        position of the field, parameter, or variable declaration,
        name is a string containing the name of the field, variable,
        or parameter, var_type is its type, and kind_str is one of
        'field, 'variable', or 'parameter'. Reports an error if a
        field, variable, or parameter of the given name already exists
        in this environment.
        """
        if name in self.__var_types:
            error(phase, position, f"redeclaration of {kind_str} {name}")
        else:
            self.__var_types[name] = var_type

    def contains(self, name):
        """Return whether or not name is defined in the environment."""
        return name in self.__var_types

    def get_type(self, phase, position, name):
        """Look up a name and return the type of the entity it names.

        phase is the current compiler phase, position is the source
        position where the name appears, and name is a string
        containing the name. Reports an error if the given name is not
        defined and returns the int type.
        """
        if name not in self.__var_types:
            error(phase, position, "undefined variable " + name)
            # default to int
            return self.__global_env.lookup_type(phase, position, "int")
        return self.__var_types[name]


#################
# Base AST Node #
#################


@dataclass
class ASTNode:
    """The base class for all AST nodes.

    Implements default functionality for an AST node.
    """

    # used for giving each node a unique id
    next_id: ClassVar[Iterator[int]] = itertools.count()

    node_id: int = dataclasses.field(
        init=False, default_factory=lambda: next(ASTNode.next_id)
    )
    position: int

    @property
    def children(self):
        """Return the children of this AST node."""
        return [getattr(self, field) for field in self.child_names]

    @property
    def child_names(self):
        """Return the names of the children of this AST node."""
        return [
            field.name
            for field in dataclasses.fields(self)[2:]
            if field.default == dataclasses.MISSING
        ]

    def __str__(self):
        """Return a string representation of this and its children."""
        result = "{" + type(self).__name__ + ":"
        for name in self.child_names:
            result += " " + child_str(self.__dict__[name])
        return result + "}"

    def find_decls(self, ctx):
        """Process the type and function declarations in this subtree.

        Adds the types and functions that are found to ctx.global_env.
        Reports an error if a type or function is multiply defined.
        """
        ast_map(lambda n: n.find_decls(ctx), self.children)

    def resolve_types(self, ctx):
        """Resolve type names to the actual types they name.

        Uses ctx.global_env to look up a type name. Reports
        an error if an unknown type is named.
        """
        ast_map(lambda n: n.resolve_types(ctx), self.children)

    def resolve_calls(self, ctx):
        """Match function calls to the actual functions they name.

        Uses ctx.global_env to look up a function name. Reports an
        error if an unknown function is named.
        """
        ast_map(lambda n: n.resolve_calls(ctx), self.children)

    def check_names(self, ctx):
        """Check names in types and functions for uniqueness.

        Checks the names introduced within a type or function to
        ensure they are unique in the scope of the type or
        function.
        """
        ast_map(lambda n: n.check_names(ctx), self.children)

    def basic_control(self, ctx):
        """Check basic control flow within this AST node."""
        ast_map(lambda n: n.basic_control(ctx), self.children)

    def type_check(self, ctx):
        """Compute the type of each expression.

        Uses ctx['local_env'] to compute the type of a local name.
        Checks that the type of an expression is compatible with the
        context in which it is used.
        """
        ast_map(lambda n: n.type_check(ctx), self.children)

    def advanced_control(self, ctx):
        """Check advanced control flow within this AST node."""
        ast_map(lambda n: n.advanced_control(ctx), self.children)

    def write_types(self, ctx):
        """Write out a representation of this AST to ctx.out.

        Includes type annotations for each node that has a type.
        """
        ctx.print(type(self).__name__, indent=True, end="")
        if "type" in dir(self):
            node_type = getattr(self, "type")
            ctx.print(f": {node_type.name if node_type else node_type}",
                      end="")
        ctx.print(" {")
        new_ctx = ctx.clone()
        new_ctx.indent += "  "
        ast_map(
            lambda n: n.write_types(new_ctx),
            self.children,
            lambda s: new_ctx.print(s, indent=True),
        )
        ctx.print("}", indent=True)

    def gen_type_decls(self, ctx):
        """Generate forward type declarations, writing them to out."""
        ast_map(lambda n: n.gen_type_decls(ctx), self.children)

    def gen_function_decls(self, ctx):
        """Generate forward function declarations, writing them to out."""
        ast_map(lambda n: n.gen_function_decls(ctx), self.children)

    def gen_type_defs(self, ctx):
        """Generate full type definitions, writing them to out."""
        ast_map(lambda n: n.gen_type_defs(ctx), self.children)

    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        ast_map(lambda n: n.gen_function_defs(ctx), self.children)


##############
# Start Node #
##############


@dataclass
class DeclNode(ASTNode):
    """The base node for type and function declarations."""


@dataclass
class ProgramNode(ASTNode):
    """Represents a uC program."""

    decls: List[DeclNode]


##########################
# Names and Declarations #
##########################


@dataclass
class NameNode(ASTNode):
    """An AST node representing a name.

    raw is the actual string containing the name.
    """

    raw: str

    # add your code below if necessary


@dataclass
class BaseTypeNameNode(ASTNode):
    """The base node for type names and array type names.

    type is the instance of uctypes.Type associated with the type
    named by this node.
    """

    type: Optional[uctypes.Type] = attribute()


@dataclass
class TypeNameNode(BaseTypeNameNode):
    """An AST node representing the name of a type.

    name is a node representing the name of the type.
    """

    name: NameNode

    # add your code below if necessary
    # use 'is return'
    # tested
    def resolve_types(self, ctx):
        """Resolve type name to their actual type in TypeNameNode.

        Overrides method in ucfrontend.py
        """
        if not ctx["is_return"] and self.name == "void":
            error(ctx.phase, self.position,
                  "A non return type can't be of type void")

        new_ctx = ctx.clone()
        new_ctx["is_return"] = False

        self.type = ctx.global_env.lookup_type(ctx.phase,
                                               self.position, self.name.raw)


@dataclass
class ArrayTypeNameNode(BaseTypeNameNode):
    """An AST node representing an array type.

    elem_type is a node representing the element type.
    """

    elem_type: BaseTypeNameNode

    # add your code below if necessary
    # Phase 2
    # Tested
    def resolve_types(self, ctx):
        """Resolve type name to their actual type in ArrayTypeNameNode.

        Overrides method in ucfrontend.py
        """
        # In particular, its elem_type child must have its type computed first
        super().resolve_types(ctx)
        self.type = self.elem_type.type.array_type


# UC_PRIMITIVE(void)
#   UC_FUNCTION(main)(UC_ARRAY(UC_PRIMITIVE(string)) UC_VAR(args));
@dataclass
class VarDeclNode(ASTNode):
    """An AST node representing a variable or field declaration.

    vartype is a node representing the type and name is a node
    representing the name.
    """

    vartype: BaseTypeNameNode
    name: NameNode


@dataclass
class ParameterNode(ASTNode):
    """An AST node representing a parameter declaration.

    vartype is a node representing the type and name is a node
    representing the name.
    """

    vartype: BaseTypeNameNode
    name: NameNode

    # add your code below if necessary
    # def gen_function_decls(self, ctx):
    #     self.vartype.gen_function_decls(ctx)
    #     ctx.print(self.mangle())


# UC_PRIMITIVE(void)
#   UC_FUNCTION(main)(UC_ARRAY(UC_PRIMITIVE(string)) UC_VAR(args));
@dataclass
class StructDeclNode(DeclNode):
    """An AST node representing a type declaration.

    name is the name of the type and vardecls is a list of field
    declarations. type is the instance of uctypes.Type that is
    associated with this declaration.
    """

    name: NameNode
    vardecls: List[VarDeclNode]
    type: Optional[uctypes.Type] = attribute()

    # add your code below
    local_env: Optional[VarEnv] = attribute()

    def find_decls(self, ctx):
        """Search the given AST node for type and function declarations.

        Adds the types and functions that are found to global_env. Reports
        an error if a type or function is multiply defined.
        """
        self.type = ctx.global_env.add_type(
            ctx.phase, self.position, self.name.raw, self
        )

    def check_names(self, ctx):
        """Check names in types and functions for uniqueness.

        Checks the names introduced within struct to
        ensure they are unique in the scope of the struct.
        """
        self.local_env = VarEnv(ctx.global_env)
        for var in self.vardecls:
            self.local_env.add_variable(
                ctx.phase,
                self.position, var.name.raw, var.vartype.type, "field"
            )

    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        new_ctx = ctx.clone()
        new_ctx["local_env"] = self.local_env
        super().type_check(new_ctx)

    def gen_type_decls(self, ctx):
        """Generate forward type declarations, writing them to out."""
        ctx.print(f"struct UC_TYPEDEF({self.name.raw});", indent=True)
        # print("gen type decls")

    def gen_type_defs(self, ctx):
        """Generate full type definitions, writing them to out."""
        # struct UC_TYPEDEF(bar) {
        print("gen_type defs in struct")
        ctx.print(f"struct UC_TYPEDEF({self.name.raw}) \u007b", indent=False)

        # Declare variables in struct def
        ctx.print("// member variable declaratons", indent=True)
        for var in self.vardecls:
            ctx.print(
                f"{var.vartype.type.mangle()} "
                + f"UC_VAR({var.name.raw});",
                indent=True
            )

        self.gen_equality_helper(ctx)

        self.gen_inequality_helper(ctx)

        self.gen_constructor_helper(ctx)

    def gen_equality_helper(self, ctx):
        """Print equality."""
        ctx.print("// equality operator", indent=True)
        name = self.name.raw
        ctx.print(
            "UC_PRIMITIVE(boolean) "
            + f"operator==(const UC_TYPEDEF({name}) &rhs) const \u007b",
            indent=True,
        )
        # // Check if the fields of the two structs are equal
        # return a == rhs.a && b == rhs.b;

        out = "return "
        if len(self.vardecls) != 0:
            for var in self.vardecls:
                out = out + f"UC_VAR({var.name.raw}) == "
                out = out + f"rhs.UC_VAR({var.name.raw}) && "
            out = out.rstrip("&& ")
        else:
            out = out + "true"
        out = out + ";"
        ctx.print(out, indent=True)
        #   }
        ctx.print("}", indent=True)

    def gen_inequality_helper(self, ctx):
        """Print inequality."""
        # Inequality Operator
        ctx.print("// inequality operator", indent=True)
        # UC_PRIMITIVE(boolean) operator!=(const UC_TYPEDEF(bar) &rhs) const {
        name = self.name.raw
        ctx.print(
            "UC_PRIMITIVE(boolean) operator!="
            + f"(const UC_TYPEDEF({name}) &rhs) const \u007b",
            indent=True,
        )
        # // Check if the fields of the two structs are equal
        # return a != rhs.a || b != rhs.b;
        out = "return "
        if len(self.vardecls) != 0:
            for var in self.vardecls:
                out = out + f"UC_VAR({var.name.raw}) "
                out = out + f"!= rhs.UC_VAR({var.name.raw}) || "
            out = out.rstrip("|| ")
        else:
            out = out + "false"
        out = out + ";"
        ctx.print(out, indent=True)
        #   }
        ctx.print("}", indent=False)

    def gen_constructor_helper(self, ctx):
        """Print default and custom constructor."""
        if len(self.vardecls) != 0:
            ctx.print("//default constructor", indent=False)
            out = f"UC_TYPEDEF({self.name.raw})() : \n"
            ctx.print(out, indent=False)
            out = ""
            for var in self.vardecls:
                out = out + f"UC_VAR({var.name.raw})(), "
            out = out.rstrip(", ")
            ctx.print(out, indent=True)
            out = "{"
            out = out + "}"
            ctx.print(out, indent=False)
            # Non default
            ctx.print("//non default constructor", indent=False)
            out = f"UC_TYPEDEF({self.name.raw})("
            for var in self.vardecls:
                out = out + f"{var.vartype.type.mangle()} "
                out = out + f"UC_VAR({var.name.raw}), "
            out = out.rstrip(", ")
            out = out + ") : "
            for var in self.vardecls:
                out = (
                    out + f"UC_VAR({var.name.raw})\u007b"
                    + f"UC_VAR({var.name.raw})\u007D, "
                )
            out = out.rstrip(", ")
            out = out + "\u007b\u007D"
            ctx.print(out, indent=False)
        out = "};"
        ctx.print(out, indent=False)


@dataclass
class FunctionDeclNode(DeclNode):
    """An AST node representing a function declaration.

    rettype is a node representing the return type, name is the name
    of the function, parameters is a list of parameter declarations,
    vardecls is a list of local variable declarations, and body is the
    body of the function.
    """

    rettype: BaseTypeNameNode
    name: NameNode
    parameters: List[ParameterNode]
    vardecls: List[VarDeclNode]
    body: "BlockNode"  # 'BlockNode' is quoted since it's a forward
    # reference to BlockNode, which is defined in ucstmt.py. We can't
    # import ucstmt since it would result in a circular import --
    # ucstmt.py imports ucbase. See
    # https://www.python.org/dev/peps/pep-0484/#forward-references for
    # more details about forward references.
    func: Optional[ucfunctions.Function] = attribute()

    # add your code below
    local_env: Optional[VarEnv] = attribute()

    def find_decls(self, ctx):
        """Search the given AST node for type and function declarations.

        Adds the types and functions that are found to global_env. Reports
        an error if a type or function is multiply defined.
        """
        self.func = ctx.global_env.add_function(
            ctx.phase, self.position, self.name.raw, self
        )

    def resolve_types(self, ctx):
        """Resolve type name to their actual type in FunctionDeclNode.

        Overrides method in ucfrontend.py
        """
        new_ctx = ctx.clone()
        new_ctx["is_return"] = True

        self.rettype.resolve_types(new_ctx)

        for node in self.parameters + self.vardecls + [self.body]:
            node.resolve_types(ctx)
        param_types = []
        for param in self.parameters:
            param_types.append(param.vartype.type)

        self.func.add_param_types(param_types)

        self.func.rettype = self.rettype.type

    def check_names(self, ctx):
        """Check names in types and functions for uniqueness.

        Checks the names introduced within function to
        ensure they are unique in the scope of the function.
        """
        self.local_env = VarEnv(ctx.global_env)

        for var in self.vardecls:
            self.local_env.add_variable(
                ctx.phase,
                self.position,
                var.name.raw,
                var.vartype.type,
                "variable"
            )

        for param in self.parameters:
            self.local_env.add_variable(
                ctx.phase,
                self.position,
                param.name.raw,
                param.vartype.type,
                "parameter",
            )

    def type_check(self, ctx):
        """Compute the type of each expression in the given AST.

        Checks that the type of an expression is compatible with the
        context in which it is used. Checks that a valid main function
        exists.
        """
        new_ctx = ctx.clone()
        new_ctx["rettype"] = self.func.rettype
        new_ctx["local_env"] = self.local_env
        super().type_check(new_ctx)

    def print_helper(self, ctx):
        """Print parameters."""
        for parameter in self.parameters:
            parameter.gen_function_decls(ctx)

    def gen_function_decls(self, ctx):
        """Generate forward function declarations, writing them to out."""
        ctx.print(f"{self.rettype.type.mangle()}", indent=False)  # Primitive
        out = self.func.mangle()
        out = out + "("
        for param in self.parameters:
            out = out + param.vartype.type.mangle() + ", "
        out = out.rstrip(", ")
        ctx.print(f"{out});", indent=True)

    def gen_function_defs(self, ctx):
        """Generate full function definitions, writing them to out."""
        # UC_TYPE(type) UC_FUNCTION(func_name) (parameters)
        out = f"{self.rettype.type.mangle()} UC_FUNCTION({self.name.raw}) ("
        for param in self.parameters:
            # parameters are of format UC_TYPE(type) UC_VAR(var_name)
            out = out + f"{param.vartype.type.mangle()} "
            out = out + f"UC_VAR({param.name.raw}), "
        out = out.rstrip(", ")
        out = out + ")"
        out = out + "{"
        ctx.print(out, indent=False)

        # at the top of the body of a generated function
        ctx.print("// decl local uC vars", indent=True)
        for var in self.vardecls:
            ctx.print(
                f"{var.vartype.type.mangle()}"
                + f" UC_VAR({var.name.raw});", indent=True
            )

        self.body.gen_function_defs(ctx)
        ctx.print("}", indent=False)


######################
# Printing Functions #
######################


def child_str(child):
    """Convert an AST item into a string.

    Converts list elements to strings using str() rather than repr().
    """
    if isinstance(child, list):
        result = "["
        if child:
            result += child_str(child[0])
        for i in range(1, len(child)):
            result += ", " + child_str(child[i])
        return result + "]"
    return str(child)


def graph_gen(item, parent_id=None,
              child_num=None,
              child_name=None,
              out=sys.stdout):
    """Print a graph representation of the given AST node to out.

    The output is in a format compatible with Graphviz.
    """
    if isinstance(item, ASTNode):
        if parent_id:
            edge = '  {0} -> {{N{1} [label="{2}{4}"]}} [label="{3}"]'
            print(
                edge.format(
                    parent_id,
                    item.node_id,
                    type(item).__name__,
                    child_name,
                    f" ({item.type.name})"
                    if "type" in item.__dict__ and item.type
                    else "",
                ),
                file=out,
            )
            new_parent_id = f"N{item.node_id}"
        else:
            print("digraph {", file=out)
            new_parent_id = type(item).__name__
        for i, child in enumerate(item.children):
            graph_gen(child, new_parent_id, i, item.child_names[i], out)
        if not parent_id:
            print("}", file=out)
    elif isinstance(item, list):
        edge = '  {0} -> {{{0}L{1} [label="[list]"]}} [label="{2}"]'
        print(edge.format(parent_id, child_num, child_name), file=out)
        for i, child in enumerate(item):
            graph_gen(child, f"{parent_id}L{child_num}", i, i, out)
    else:
        edge = '  {0} -> {{{0}T{1} [label="{2}"]}} [label="{3}"]'
        print(
            edge.format(
                parent_id,
                child_num,
                str(item).replace("\\", "\\\\").replace('"', '\\"'),
                child_name,
            ),
            file=out,
        )
