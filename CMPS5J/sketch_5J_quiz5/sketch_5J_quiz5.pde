void draw(){
  println(pow(2,3));
}
int pow (int x, int n) {
  int answer = 1;
  while (n > 0){
    n--;
    answer = answer * x;
  }
  return answer;
}
  