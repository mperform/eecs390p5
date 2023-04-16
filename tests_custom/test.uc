void main(string[] args)(foo f, bar b, baz z) {
  f = new foo();
  b = new bar();
  z = new baz();
  println(int_to_string(f.x));
  println(boolean_to_string(b.f == null));
  println(boolean_to_string(b.a == null));
}

void if_test()(int num, int zero) {
  
  num = 1;
  zero = 0;
  
  if(num > zero){
    println("Hello");
  }
  if(num < zero){
    println(num);
  }else{
    println(zero);
  }
}

void while_test()(int num, int zero) {
  num = 1;
  zero = 0;
  while(num > zero){
    println(zero);
  }
  while((num > zero) || (num < zero)){
    println(zero);
  }
}

struct foo(int x);

struct bar(foo f, int x, string[] a);

struct baz();