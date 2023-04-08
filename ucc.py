"""
ucc.py.

This file is the driver for the uC compiler.

Project UID c49e54971d13f14fbc634d7a0fe4b38d421279e7
"""

import sys
import argparse
import ucbase
import ucerror
import ucparser
import ucfrontend
import ucbackend


def uc_compile(filename, analyze_only, write_types, write_graph,
               frontend_phase, backend_phase):
    """Run the uC compiler on the given source file.

    If analyze_only is false and no errors are detected, writes
    generated code to an output file (backend project only). If
    write_types is true, writes a representation of the AST produced
    from parsing the source file, with annotated type information, to
    an output file. If write_graph is true, writes a representation of
    the AST that can be processed by GraphViz's dot tool to an output
    file.
    """
    tree, global_env = uc_frontend(filename, write_types, write_graph,
                                   frontend_phase)
    if analyze_only:
        print('No errors reported.')
    else:
        uc_backend(filename, tree, global_env, backend_phase)


def uc_frontend(filename, write_types, write_graph, frontend_phase):
    """Run the uC compiler frontend on the given source file.

    If write_types is true, writes a representation of the AST
    produced from parsing the source file, with annotated type
    information, to an output file. If write_graph is true, writes a
    representation of the AST that can be processed by GraphViz's dot
    tool to an output file. Returns the resulting AST and global
    environment.
    """
    tree = ucparser.parse(filename)
    check_errors(ucparser.error_count(), 0)
    global_env = ucfrontend.make_global_env()
    phases = (
        (ucfrontend.find_decls, 'Finding declarations...'),
        (ucfrontend.resolve_types, 'Resolving types...'),
        (ucfrontend.resolve_calls, 'Resolving function calls...'),
        (ucfrontend.check_names, 'Checking field and variable names...'),
        (ucfrontend.basic_control, 'Checking basic control flow...'),
        (ucfrontend.type_check, 'Type checking...'),
        (ucfrontend.advanced_control, 'Checking advanced control flow...'),
    )
    if not frontend_phase:
        frontend_phase = len(phases)
    for i, phase in enumerate(phases[:frontend_phase]):
        print(phase[1])
        phase[0](tree, global_env)
        check_errors(ucerror.error_count(), i + 1)
    if write_types:
        print('Writing types...')
        outname = (filename[:-3] if filename.endswith('.uc')
                   else filename) + '.types'
        with open(outname, 'w', encoding="utf8") as out:
            ucfrontend.write_types(tree, global_env, out)
        print(f'Wrote types to {outname}.')
    if write_graph:
        print('Writing graph...')
        outname = (filename[:-3] if filename.endswith('.uc')
                   else filename) + '.dot'
        with open(outname, 'w', encoding="utf8") as out:
            ucbase.graph_gen(tree, out=out)
        print(f'Wrote graph to {outname}.')
    return tree, global_env


def check_errors(num_errors, phase):
    """Report number of errors and Exit if num_errors is non-zero."""
    if num_errors:
        msg = '{0} error{1} generated in phase {2}.'
        print(msg.format(num_errors, 's' if num_errors != 1 else '',
                         phase))
        sys.exit(1)


def uc_backend(filename, tree, _global_env, backend_phase):
    """Run the uC compiler backend on the given AST and environment.

    Writes generated code to an output file (backed project only).
    """
    outname = (filename[:-3] if filename.endswith('.uc')
               else filename) + '.cpp'
    phases = (
        ucbackend.gen_type_decls,
        ucbackend.gen_function_decls,
        ucbackend.gen_type_defs,
        ucbackend.gen_function_defs
    )
    print('Generating code...')
    with open(outname, 'w', encoding="utf8") as out:
        if not backend_phase:
            ucbackend.gen_header(tree, out)
        for phase in (phases[:backend_phase]
                      if backend_phase else phases):
            phase(tree, out)
        if not backend_phase:
            ucbackend.gen_footer(tree, out)
    print(f'Wrote code to {outname}.')


def main():
    """Command-line interface."""
    aparser = argparse.ArgumentParser(description='Compile a uC '
                                      'source file.')
    group = aparser.add_mutually_exclusive_group(required=True)
    aparser.add_argument('filename', help='name of uC source file')
    group.add_argument('-S', '--analyze-only', action='store_true',
                       help='perform static analysis only')
    group.add_argument('-C', '--code-gen', action='store_true',
                       help='generate code for the input uC file')
    aparser.add_argument('-T', '--write-types', action='store_true',
                         help='write types for each expression and '
                         'declaration')
    aparser.add_argument('-G', '--write-graph', action='store_true',
                         help='generate a graph of the AST in dot '
                         'format')
    aparser.add_argument('-NE', '--no-errors', action='store_true',
                         help='disable error checking')
    aparser.add_argument('--frontend-phase', nargs='?', type=int,
                         default=0,
                         help='stop semantic analysis after the '
                         'given frontend phase')
    aparser.add_argument('--backend-phase', nargs='?', type=int,
                         default=0,
                         help='restrict code generation to the given '
                         'backend phase')
    args = aparser.parse_args()
    if args.code_gen and not args.frontend_phase:
        # restrict frontend to first two phases, with no error
        # checking
        args.frontend_phase = 2
        args.no_errors = True
    if args.analyze_only and not args.frontend_phase:
        # restrict frontend to first six phases
        args.frontend_phase = 6
    if args.no_errors:
        ucerror.disable_errors()
    uc_compile(args.filename, args.analyze_only, args.write_types,
               args.write_graph, args.frontend_phase,
               args.backend_phase)


if __name__ == '__main__':
    main()
