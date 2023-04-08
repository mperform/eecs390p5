void main(string[] args)(foo f, bar b, baz z) {
  f = new foo();
  b = new bar();
  z = new baz();
  println(int_to_string(f.x));
  println(boolean_to_string(b.f == null));
  println(boolean_to_string(b.a == null));
}

struct foo(int x);

struct bar(foo f, int x, string[] a);

struct baz();
