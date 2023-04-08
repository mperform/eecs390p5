"""
ucfrontend.py.

This file implements entry points into the frontend phases of the
compiler.

Project UID c49e54971d13f14fbc634d7a0fe4b38d421279e7
"""

import ucbase
import ucerror
import uccontext


#############
# Utilities #
#############

def make_global_env():
    """Return an empty global environment."""
    return ucbase.GlobalEnv()


###################
# Frontend Phases #
###################

def find_decls(tree, global_env):
    """Search the given AST node for type and function declarations.

    Adds the types and functions that are found to global_env. Reports
    an error if a type or function is multiply defined.
    """
    ctx = uccontext.PhaseContext(1, global_env)
    tree.find_decls(ctx)


def resolve_types(tree, global_env):
    """Resolve type names to their actual types in the given AST.

    Uses global_env to look up a type name. Reports an error if an
    unknown type is named.
    """
    ctx = uccontext.PhaseContext(2, global_env)
    # whether or not the current node is the node specifying the
    # return type of a function
    ctx['is_return'] = False
    tree.resolve_types(ctx)


def resolve_calls(tree, global_env):
    """Match function calls to the actual functions they name.

    Uses global_env to look up a function name. Reports an error if an
    unknown function is named.
    """
    ctx = uccontext.PhaseContext(3, global_env)
    tree.resolve_calls(ctx)


def check_names(tree, global_env):
    """Check names in types and functions for uniqueness.

    Checks the names introduced within a type or function to ensure
    they are unique in the scope of the type or function.
    """
    ctx = uccontext.PhaseContext(4, global_env)
    tree.check_names(ctx)


def basic_control(tree, global_env):
    """Check basic control flow within the given AST node."""
    ctx = uccontext.PhaseContext(5, global_env)
    # whether or not the current node is within a loop
    ctx['in_loop'] = False
    tree.basic_control(ctx)


def type_check(tree, global_env):
    """Compute the type of each expression in the given AST.

    Checks that the type of an expression is compatible with the
    context in which it is used. Checks that a valid main function
    exists.
    """
    ctx = uccontext.PhaseContext(6, global_env)
    # used to look up local names
    ctx['local_env'] = None
    # used to check types of return expressions
    ctx['rettype'] = None
    tree.type_check(ctx)
    # check for main
    func = global_env.lookup_function(ctx.phase, tree.position,
                                      'main', False)
    if func is None:
        ucerror.error(ctx.phase, tree.position,
                      'no definition for function main')
    elif (len(func.param_types) != 1 or
          func.param_types[0] is not
          global_env.lookup_type(ctx.phase, tree.position,
                                 'string').array_type or
          func.rettype is not
          global_env.lookup_type(ctx.phase, tree.position, 'void')):
        params = ', '.join(str(param) for param in func.param_types)
        ucerror.error(ctx.phase, func.decl.position,
                      'signature for main must be '
                      'void main(string[]), got: '
                      f'{func.rettype} main({params})')


def advanced_control(tree, global_env):
    """Check advanced control flow within the given AST node."""
    ctx = uccontext.PhaseContext(7, global_env)
    tree.advanced_control(ctx)


def write_types(tree, global_env, out):
    """Write out a representation of the given AST node to out.

    Includes type annotations for each node that has a type.
    """
    ctx = uccontext.PhaseContext(0, global_env, out)
    tree.write_types(ctx)
