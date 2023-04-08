"""
ucerror.py.

This file defines the error-handling function used by the uC compiler.

Project UID c49e54971d13f14fbc634d7a0fe4b38d421279e7
"""


def error(phase, position, message):
    """Print an error message if error checking is enabled.

    If error checking is enabled, prints an error message for the
    given phase at the given source position, with the given message
    content. Increments the number of errors encountered. If error
    checking is disabled, does nothing.
    """
    if not error.disabled:
        print(f'Error ({phase}) at line {position}: {message}')
        error.num_errors += 1


error.disabled = False
error.num_errors = 0


def error_count():
    """Return the number of errors detected in static analysis."""
    return error.num_errors


def disable_errors():
    """Disable error checking."""
    error.disabled = True
