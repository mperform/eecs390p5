struct MyStruct {
  int param1;
  double param2;
  bool param3;

  MyStruct() :
    param1(), param2(), param3()
  {}
};


int main (){
    MyStruct m;
    m.param1 = 1;
    m.param2 = 1.2; 
    m.param3 = false;
    
}