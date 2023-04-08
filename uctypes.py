"""
uctypes.py.

This file contains definitions of classes that represent uC types, as
well as utility functions that operate on types.

Project UID c49e54971d13f14fbc634d7a0fe4b38d421279e7
"""

from ucerror import error


class Type:
    """Parent class for all uC types."""

    __creator_token = None  # controls access to type creation

    def __init__(self, token, name):
        """Initialize this type to have the given name."""
        Type._check_token(token)
        self.name = name
        self._array_type = None  # cache for the array type

    @staticmethod
    def _check_token(token):
        """Check whether the given token has permission to create types."""
        if Type.__creator_token is None:
            Type.__creator_token = token
        elif Type.__creator_token is not token:
            raise AssertionError(
                "types can only be created by add_type() on the "
                "global environment or by accessing the array_type "
                "property on an existing type"
            )

    def __str__(self):
        """Return the name of this type."""
        return self.name

    @property
    def array_type(self):
        """Return the array type corresponding to this type."""
        if not self._array_type:
            self._array_type = ArrayType(self.__creator_token, self)
        return self._array_type

    def lookup_field(self, phase, position, name, global_env):
        """Lookup up a field in this type.

        phase is the current compiler phase, position is the source
        position from where this lookup occurs, name is the name of
        the field, and global_env is the global environment. Reports
        an error if the field is not found. Returns the type of the
        field if it is found, int otherwise.
        """
        error(phase, position, f"type {self.name} has no field {name}")
        return global_env.lookup_type(phase, position, "int")


class ArrayType(Type):
    """A class representing an array type.

    The instance attribute elem_type refers to the element type of the
    array.
    """

    def __init__(self, token, elem_type):
        """Initialize this type to have the given element type."""
        super().__init__(token, elem_type.name + "[]")
        self.elem_type = elem_type

    def mangle(self):
        """Return the mangled name of this type.

        The mangled name is the name that should be used in code
        generation.
        """
        return f"UC_ARRAY({self.elem_type.mangle()})"

    def check_args(self, phase, position, args):
        """Check if the arguments are compatible with this array type.

        Compares the arguments against the element type of this array.
        The arguments must have already have their types computed.
        phase is the current compiler phase, position is the source
        position where this check occurs. Reports an error if an
        argument is incompatible.
        """
        for arg in args:
            if not is_compatible(arg.type, self.elem_type):
                error(
                    phase,
                    position,
                    "arguments are not compatible with the elem_type.",
                )
                return False
        return True

    def lookup_field(self, phase, position, name, global_env):
        """Lookup up a field in this type.

        phase is the current compiler phase, position is the source
        position from where this lookup occurs, name is the name of
        the field, and global_env is the global environment. Reports
        an error if the field is not found. Returns the type of the
        field if it is found, int otherwise.
        """
        # fill in your solution here
        if name != "length":
            error(
                phase,
                position,
                f"Field {name} is not present in the array type fields.",
            )
        return global_env.lookup_type(phase, position, "int")


class PrimitiveType(Type):
    """A class representing a primitive type."""

    def mangle(self):
        """Return the mangled name of this type.

        The mangled name is the name that should be used in code
        generation.
        """
        return f"UC_PRIMITIVE({self.name})"


class UserType(Type):
    """A class representing a user-defined type."""

    def __init__(self, token, name, decl):
        """Initialize this type.

        name is a string representing the name of the type and decl is
        the AST node for the declaration of this type.
        """
        super().__init__(token, name)
        self.decl = decl
        self.fields = decl.vardecls

    def check_args(self, phase, position, args):
        """Check if the arguments are compatible with the field types.

        Compares the arguments against the types of the fields this
        type. The arguments must have already have their types
        computed. phase is the current compiler phase, position is the
        source position where this check occurs. Reports an error if
        an argument is incompatible.
        """
        # The arguments may be empty, in which case the fields of the newly
        # created object undergo Default Initialization.
        # Otherwise, the number of arguments must match
        # the number of fields in the given type,
        # and the argument types must match or be implicitly convertible
        # to the corresponding field types.
        if len(args) != 0 and len(args) != len(self.fields):
            error(
                phase,
                position,
                "number of args does not match the num of fields.",
            )
            return False
        for arg, field in zip(args, self.fields):
            if not is_compatible(arg.type, field.vartype.type):
                error(
                    phase,
                    position,
                    "arguments of type do not work w/ fields",
                )
                return False
        return True

    def lookup_field(self, phase, position, name, global_env):
        """Lookup up a field in this type.

        phase is the current compiler phase, position is the source
        position from where this lookup occurs, name is the name of
        the field, and global_env is the global environment. Reports
        an error if the field is not found. Returns the type of the
        field if it is found, int otherwise.
        """
        # fill in your solution here
        # gotta get self.fields.name
        if any(field.name.raw == name for field in self.fields):
            return self.decl.local_env.get_type(phase, position, name)
        error(phase, position, f"Field: {name} is not present in the fields.")
        return global_env.lookup_type(phase, position, "int")

    def mangle(self):
        """Return the mangled name of this type.

        The mangled name is the name that should be used in code
        generation.
        """
        return f"UC_REFERENCE({self.name})"


def is_compatible(source, target):
    """Return whether the source type is assignable to the target type."""
    return (
        (source is target)
        or (source.name == "int" and target.name in ("long", "float"))
        or (source.name == "long" and target.name == "float")
        or (source.name == "null" and not isinstance(target, PrimitiveType))
    )


def is_numeric_type(type_):
    """Return whether the given type is a primitive numeric type."""
    return type_.name in ("int", "long", "float")


def is_integral_type(type_):
    """Return whether the given type is a primitive integral type."""
    return type_.name in ("int", "long")


def join_types(phase, position, type1, type2, global_env):
    """Compute the type of a binary operation from the operand types."""
    if type1 is type2:
        return type1
    if type1.name == "string" or type2.name == "string":
        return global_env.lookup_type(phase, position, "string")
    if type1.name == "float" or type2.name == "float":
        return global_env.lookup_type(phase, position, "float")
    if type1.name == "long" or type2.name == "long":
        return global_env.lookup_type(phase, position, "long")
    # default to int
    return global_env.lookup_type(phase, position, "int")


def add_builtin_types(types, token):
    """Add primitive types to the given dictionary."""
    for name in ("int", "long", "float", "boolean", "string", "void", "null"):
        types[name] = PrimitiveType(token, name)
