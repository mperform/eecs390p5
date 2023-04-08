void main(string[] args)(foo f) {
  println("" + args.length);
  f = new foo(3, "hello");
  println(f.length);
  f.length = "world";
  println(f.length);
}

void bar(foo f)() {
}

struct foo(int x, string length);
