void main(string[] args)(foo f) {
  f = new foo(new baz(args[0]));
  bar(f);
}

void bar(foo f)() {
  println(f.b.s);
}

struct foo(baz b);

struct baz(string s);
