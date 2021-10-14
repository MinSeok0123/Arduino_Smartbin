#include <Servo.h>
#define trigPin1 8  // 초음파 발신핀 define은 쉽게말하면, 숫자의 이름을 정의해주는것. 
#define echoPin1 9  // 초음파 수신핀
#define trigPin2 2  // 초음파 발신핀 define은 쉽게말하면, 숫자의 이름을 정의해주는것. 
#define echoPin2 3  // 초음파 수신핀
#define SERVO_PIN 7             // 서보모터 7번 사용
#define buz 10
int led = 11;
long duration1, distance1;
long duration2, distance2;
Servo myservo;
boolean isNear = false;
void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);  // trig를 출력 모드로 설정
  pinMode(echoPin2, INPUT);   // echo를 입력모드로 설정
  pinMode(buz, OUTPUT);  // 피에조 부저 출력 설정
  pinMode(led, OUTPUT);
  myservo. write(0);
  Serial.begin(9600);
}
void loop() {
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;
  if (distance1 <10) {
    if (!isNear) {
      isNear = true;
      myservo. write(0);
      delay(1000);
    }
  } else {
    if (isNear) {
      isNear = false;
      myservo. write(180);
      delay(1000);
    }

    digitalWrite(trigPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    duration2 = pulseIn(echoPin2, HIGH);
    distance2 = duration2 * 0.034 / 2;

    if (distance2 >10)
    {
      tone(buz, 2093, 1000);
      digitalWrite(led, HIGH);
      delay(150);
      digitalWrite(led, LOW);
    }
  }
  Serial.print("거리1: ");
  Serial.print(distance1); // 거리를 시리얼 모니터에 출력
  Serial.println("cm");
  Serial.print("거리2: ");
  Serial.print(distance2); // 거리를 시리얼 모니터에 출력
  Serial.println("cm");
  myservo.attach(SERVO_PIN);  // 서보모터 초기화
  delay (100);
}
