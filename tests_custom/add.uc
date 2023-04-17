void main(string[] args)(foo f, bar b, baz z) {
  println(int_to_string(1 + 1));
  println(int_to_string(1 + 1.5));
  println(1 + "hello");
  println("hello" + 1);
  println(true + "hello");
  println(false + "hello");
  println("Hello" + true);
  println("Hello" + false);
  //complicated add
  println("Hello" + (1 + "str"));
  println(int_to_string((5 + 3) + 9));
  println(int_to_string(5 + 3 + 9));
  println(5 + (3 + "4") + false);
  println(int_to_string(5 + 3 * 9));
  println(int_to_string(5 - 3 * 9));
  println(1.0 + "false" + (false + "true" + 1));
}