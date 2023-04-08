"""
uccontext.py.

This file defines the PhaseContext type that is used by both the
frontend and backend.

Project UID c49e54971d13f14fbc634d7a0fe4b38d421279e7
"""

import sys
import copy


class PhaseContext:
    """Contains contextual information required in a compiler phase.

    Contextual information can be added to this context using the
    dictionary interface (e.g. ctx['is_return'] = False).
    """

    # Hardcoded field set. Do NOT modify or add to this.
    __slots__ = ('phase', 'global_env', 'out', 'indent', '_info')

    def __init__(self, phase=0, global_env=None, out=sys.stdout,
                 indent='', info=None):
        """Initialize this context.

        out is the output stream for writing an AST representation or
        for code generation. The internal dictionary is set to be a
        copy of info, if it is not None.
        """
        self.phase = phase
        self.global_env = global_env
        self.out = out
        self.indent = indent
        self._info = dict(info) if info else {}

    def clone(self):
        """Return a shallow copy of this context."""
        return PhaseContext(self.phase, self.global_env, self.out,
                            self.indent, self._info)

    def __copy__(self):
        """Return a shallow copy of this context."""
        return self.clone()

    def deep_clone(self):
        """Return a deep copy of this context."""
        new_ctx = self.clone()
        # make (shallow) copies of each item in info
        for key, value in self._info.items():
            new_ctx[key] = copy.copy(value)
        return new_ctx

    def __deepcopy__(self, memo):
        """Return a deep copy of this context."""
        return self.deep_clone()

    def __getitem__(self, key):
        """Return the value associated with the key in this context."""
        return self._info[key]

    def __setitem__(self, key, value):
        """Set the value associated with the key in this context."""
        self._info[key] = value

    def __contains__(self, key):
        """Return whether the given key exists in this context."""
        return key in self._info

    def print(self, *args, **kwargs):
        """Print to the context's output.

        Indents with this context's indent string if indent=True is
        provided. The trailing newline can be suppressed by end='',
        as with the standard print() function.
        """
        if 'indent' in kwargs:
            if kwargs['indent']:
                print(self.indent, file=self.out, end='')
            del kwargs['indent']
        print(*args, file=self.out, **kwargs)
