void main(string[] args)(foo f, bar b, baz z) {
  f = new foo();
  b = new bar();
  z = new baz();
  println(int_to_string(f.x));
  println(boolean_to_string(b.f == null));
  println(boolean_to_string(b.a == null));
  test();
}

void test()(int start, int num, int[] arr) {
  start = 0;
  num = 0;
  arr = new int[]{};

  while(start < 10){
    arr << start;
    ++start; 
  }

  println(int_to_string(arr[5]));
  println(int_to_string(arr[num]));
  println("arr.length 23");
  println(int_to_string(arr.length));
  start = 0;
  while(start < 10){
    arr >> num;
    ++start; 
  }

  println(int_to_string(arr.length));

  start = 0;
  num = 0;
  while(start < 10){
    arr << 1;
    ++start; 
  }

  println(int_to_string(arr[5]));
  println(int_to_string(arr[num]));

  start = 0;
  while(start < 10){
    arr >> num;
    ++start; 
  }
  println("arr.length");
  println(int_to_string(arr.length));

}


struct foo(int x);

struct bar(foo f, int x, string[] a);

struct baz();