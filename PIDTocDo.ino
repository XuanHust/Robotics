#define QuayDuong 8
#define QuayAm 7
#define PWM 3

long int tgtr =0, tocdo = 0, temp, tdmm = 140, loi;


void quay(int nangluong){
  if(nangluong >= 255)
  {
    nangluong = 255;
  }
  if(nangluong <= -255){
    nangluong = -255;
  }

  
  if(nangluong > 0){
    digitalWrite(QuayDuong,0);
    digitalWrite(QuayAm, 0);
    analogWrite(PWM, nangluong);
    digitalWrite(QuayDuong,0);
    digitalWrite(QuayAm, 1);
  }
  if(nangluong < 0){
    digitalWrite(QuayDuong,0);
    digitalWrite(QuayAm, 0);
    analogWrite(PWM, -nangluong);
    digitalWrite(QuayAm,0);
    digitalWrite(QuayDuong, 1);
  }
}

float pid(float loi, float kp, float ki, float kd){
  int dloi;
  static float iloi = 0;
  static float loitr = 0;
  float temp;
  dloi = loi - loitr;
  iloi += loi;
  if(iloi >= 200)
  {
    iloi = 200;
  }
  if(iloi <= -200){
    iloi = -200;
  }
  loitr = loi;
  temp = kp*loi + ki*iloi + kd*dloi;
  
  if(temp >= 255)
  {
    temp = 255;
  }
  if(temp <= -255){
    temp = -255;
  }
  return temp;
}

void setup(){
  TCCR1A = 0;
  TCCR1B = 0b111;
  //attachInterrupt(0, chay, RISING);
  pinMode(PWM, OUTPUT);
  pinMode(QuayDuong, OUTPUT);
  pinMode(QuayAm, OUTPUT);
  Serial.begin(9600);
}

void loop(){

  if(micros() - tgtr >= 1000){
    tgtr = micros();
    tocdo = TCNT1;
    TCNT1 = 0;
    //tocdo = (float)tocdo/6.0*14.0;
    loi = tdmm - tocdo;
    temp += pid(loi, 0.5, 0.005, 0.9);
    quay(temp);
    Serial.println(tocdo);
  }

}
