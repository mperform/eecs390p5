void main(string[] args)(foo f, bar b, baz z) {
  f = new foo();
  b = new bar();
  z = new baz();
  println(int_to_string(f.x));
  println(boolean_to_string(b.f == null));
  println(boolean_to_string(b.a == null));
  if_test();
  while_test();
  for_test();
}

void if_test()(int num, int zero) {
  
  num = 1;
  zero = 0;
  
  if(num > zero){
    println("Hello");
  }
  if(num < zero){
    println(int_to_string(num));
  }else{
    println(int_to_string(zero));
  }
}

void while_test()(int num, int zero) {
  num = 1;
  zero = 0;
  while(num > zero){
    println(int_to_string(zero));
    --num; 
  }
  --num;
  while((num < zero) || (num < zero)){
    println(int_to_string(zero));
    ++num;
  }
}

void for_test()(int num, int zero, int i) {
  num = 1;
  zero = 0;
  for(i = 0; i < num; ++i){
    println(int_to_string(zero));
  }
  
  for (; num < zero; ){
    println(int_to_string(zero));
  }

  for (; num < zero; ++num){
    println(int_to_string(zero));
  }

}

struct foo(int x);

struct bar(foo f, int x, string[] a);

struct baz();