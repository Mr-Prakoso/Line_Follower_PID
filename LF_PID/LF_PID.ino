//konfigurasi pin sensor
#define s1 analogRead(A1)
#define s2 analogRead(A2)
#define s3 analogRead(A3)
#define s4 analogRead(A4)

bool S1,S2,S3,S4;

//konfigurasi konstanta PID
double kp = 40.0; //40
double ki = 0.5;  //0.5
double kd = 45.0; //60

//variabel PID
double P, I, D;
double error = 0, last_error = 0, sumerror = 0;
double PID;

int speed_kiri, speed_kanan, speed = 100;

void setup() {
  // Serial.begin(9600);
  //konfigurasi pin motor
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  //konfigurasi pin sensor
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
}

void loop() {
  //baca nilai sensor
  if(s1>500){S1=1;}
  else{S1=0;}
  if(s2>500){S2=1;}
  else{S2=0;}
  if(s3>500){S3=1;}
  else{S3=0;}
  if(s4>500){S4=1;}
  else{S4=0;}

  // Serial.print(sensor[0]);
  // Serial.print("\t");
  // Serial.print(sensor[1]);
  // Serial.print("\t");
  // Serial.print(sensor[2]);
  // Serial.print("\t");
  // Serial.println(sensor[3]);

  //hitung error
  // error = (S1 * -4) + (S2 * -2) + (S3 * 2) + (S4 * 4);
  if(S2 && S3){error = 0;}
  else if(!S1 && !S2 && !S3 && S4){error = 3;}
  else if(!S1 && !S2 && S3 && S4){error = 2;}
  else if(!S1 && !S2 && S3 && !S4){error = 1;}
  else if(!S1 && S2 && S3 && !S4){error = 0;}
  else if(!S1 && S2 && !S3 && !S4){error = -1;}
  else if(S1 && S2 && !S3 && !S4){error = -2;}
  else if(S1 && !S2 && !S3 && !S4){error = -3;}

  //hitung P, I, D
  sumerror += last_error;
  P = kp * error;
  I = ki * (I + error);
  D = kd * (error - last_error);
  PID = P + I + D;
  // P = kp * error;
  // I = I + (ki * error);
  // D = kd * (error - last_error);
  // PID = P + I + D;

  //simpan error terakhir
  last_error = error;

  //batasi nilai PID
  if (PID > speed) PID = speed;
  if (PID < -speed) PID = -speed;

  //koreksi kecepatan motor
  // if (PID > 0) {
    speed_kanan = speed - PID;
  // } else if (PID < 0) {
    speed_kiri = speed + PID;
  // }

  if(speed_kanan > speed){speed_kanan = speed;}
  if(speed_kiri > speed){speed_kiri = speed;}

  // Serial.print(error);
  // Serial.print("\t");
  // Serial.print(PID);
  // Serial.print("\t");
  // Serial.print(speed_kiri);
  // Serial.print("\t");
  // Serial.println(speed_kanan);
  

  // if(S1){   //putar kiri
  //   analogWrite(5, speed_kanan);
  //   analogWrite(6, 0);
  //   analogWrite(10, 0);
  //   analogWrite(9, speed_kanan);
  // }
  // else if(S4){   //putar kanan
  //   analogWrite(5, 0);
  //   analogWrite(6, speed_kiri);
  //   analogWrite(10, speed_kiri);
  //   analogWrite(9, 0);
  // }
  // else{   //lurus
    analogWrite(5, speed_kanan);
    analogWrite(6, 0);
    analogWrite(10, speed_kiri);
    analogWrite(9, 0);
  // }
}