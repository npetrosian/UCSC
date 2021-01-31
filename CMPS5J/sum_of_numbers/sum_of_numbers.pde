void setup(){
  int answer;
  answer = sum(3);
  println(answer);
}


int sum(int n){
  int answer = 0;
  for (int i = 1; i <= n; i++){
    answer = answer + i; 
  }
  return answer;
}