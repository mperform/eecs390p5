void main(string[] args)(foo f, bar b, baz z, baz x) {
  f = new foo();
  b = new bar();
  z = new baz();
  
  println(long_to_string(#f));
  println(long_to_string(#b));
  println(long_to_string(#z));

  x = z;
  println(long_to_string(#x));
  
}


struct foo(int x);

struct bar(foo f, int x, string[] a);

struct baz();