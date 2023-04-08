void main(string[] args)(int i, float f) {
  i = 3;
  f = 4.0;
  println(boolean_to_string(i == i));
  println(boolean_to_string(f != f));
  println(boolean_to_string(i == f));
  println(boolean_to_string(i != f));
  println(boolean_to_string(new foo{3} == new foo(3)));
  println(boolean_to_string(new foo{3} != new foo(3)));
  println(boolean_to_string(new foo{3} == new foo(4)));
  println(boolean_to_string(new foo{3} != new foo(4)));
  println(boolean_to_string(new foo{3} == null));
  println(boolean_to_string(new foo(3) != null));
  println(boolean_to_string(new foo[] ( new foo(3) ) == new foo[] { new foo(3) }));
  println(boolean_to_string(new foo[] ( new foo(3) ) != new foo[] { new foo(4) }));
  println(boolean_to_string(new foo[] ( new foo(3) ) != new foo[] { new foo(3),
                                                    new foo(4) }));
  println(boolean_to_string(new foo[] { new foo(3) } == null));
  println(boolean_to_string(new foo[] ( new foo(3) ) != null));
  println(boolean_to_string(new bar{} == new bar()));
  println(boolean_to_string(new bar{} != new bar()));
  println(boolean_to_string(new bar{} == null));
  println(boolean_to_string(new bar() != null));
}

struct foo(int x);

struct bar();
