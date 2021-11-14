int segment[7]={4,5,6,7,8,9,10};
int digit[3]={11,12,13};
// 0: ON, 1: OFF
int num[10][7] = {
  {0,0,0,0,0,0,1},  
  {1,0,0,1,1,1,1}, 
  {0,0,1,0,0,1,0}, 
  {0,0,0,0,1,1,0}, 
  {1,0,0,1,1,0,0}, 
  {0,1,0,0,1,0,0}, 
  {0,1,0,0,0,0,0}, 
  {0,0,0,1,1,0,1}, 
  {0,0,0,0,0,0,0},
  {0,0,0,0,1,0,0}
};

int dispDelay=8;

void setSegment(int N) {
  int D3 = N/100; // 100의 자리수
  int D2 = N/10 - 10*D3; // 10의 자리수
  int D1 = N%10; // 1의 자리수

/*  Serial.print(D3);
  Serial.print(" ");
  Serial.print(D2);
  Serial.print(" ");
  Serial.println(D1);
*/

// 1의 자리
  digitalWrite(digit[0], LOW);
  digitalWrite(digit[1], LOW);
  digitalWrite(digit[2], HIGH);
  for (int s=0;s<7;s++) {
    digitalWrite(segment[s], num[D1][s]);
  }
  delay(dispDelay);
// 10의 자리
  if ( N >= 10) {
    digitalWrite(digit[0], LOW);
    digitalWrite(digit[1], HIGH);
    digitalWrite(digit[2], LOW);
    for (int s=0;s<7;s++) {
      digitalWrite(segment[s], num[D2][s]);
    }
    delay(dispDelay);
  }

// 100의 자리
  if ( N >= 100) {
    digitalWrite(digit[0], HIGH);
    digitalWrite(digit[1], LOW);
    digitalWrite(digit[2], LOW);
    for (int s=0;s<7;s++) {
      digitalWrite(segment[s], num[D3][s]);
    }
    delay(dispDelay);
  }
}

void setup() {
  Serial.begin(9600);
  for ( int i = 0; i<7; i++ ) {
    pinMode(segment[i], OUTPUT);
    if ( i < 3 ) {
      pinMode(digit[i], OUTPUT);  
    }
  }
  pinMode(A0, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
//  Serial.println(analogRead(A0));
  unsigned long A=analogRead(A0);
  unsigned long DUTY = A * 100 /1023;
  setSegment(DUTY);
  unsigned long PWM = A/4;
  analogWrite(3, PWM);
  Serial.print(A);
  Serial.print(" ");
  Serial.print(DUTY);
  Serial.print(" ");
  Serial.print(PWM);
  Serial.println(" ");
}
