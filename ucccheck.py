"""
ucccheck.py.

Simple check for correct output on a test for the frontend.

Project UID c49e54971d13f14fbc634d7a0fe4b38d421279e7
"""

import sys
import re


ERROR_PATTERN = re.compile(r'^Error \((\d*)\) at line (\d*): *')


def extract_info(line):
    """Extract phase and line information from an error message."""
    match = ERROR_PATTERN.match(line)
    return match.group(1, 2) if match else None


def main(filename):
    """Compare result of compiler frontend with expected output.

    filename is the name of the uC file for which to check output.
    """
    output = filename.replace('.uc', '.out')
    with open(output, encoding="utf8") as result_file,\
            open(output + '.correct', encoding="utf8") as correct_file:
        results = {extract_info(line)
                   for line in result_file.readlines()
                   if extract_info(line)}
        correct = {extract_info(line)
                   for line in correct_file.readlines()
                   if extract_info(line)}
        missing = correct - results
        extra = results - correct
        failed = len(missing) + len(extra)
        if missing:
            print('Missing errors:')
            for item in missing:
                print(f'  Phase {item[0]}, line {item[1]}')
        if extra:
            print('Extraneous errors:')
            for item in extra:
                print(f'  Phase {item[0]}, line {item[1]}')
        if failed:
            print(f'Test {filename} failed.')
            sys.exit(1)
        elif correct:
            print(f'Test {filename} passed.')
            sys.exit(0)

    types = filename.replace('.uc', '.types')
    with open(types, encoding="utf8") as result_file, \
            open(types + '.correct', encoding="utf8") as correct_file:
        if result_file.read() != correct_file.read():
            print('Error: mismatch detected in types output for ' +
                  filename)
            print(f'Run "diff {types} {types}.correct" to see '
                  'difference')
            print(f'Test {filename} failed.')
            sys.exit(1)
        else:
            print(f'Test {filename} passed.')
            sys.exit(0)


if __name__ == '__main__':
    main(sys.argv[1])
