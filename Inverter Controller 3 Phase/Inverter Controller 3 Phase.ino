#define sin_freq 50    //Hz
#define tri_freq 1200  //Hz
#define pi 3.1416

double tri = 0, sine1 = 0, sine2 = 0, sine3 = 0, time;
const float period_tri = 1000000 / tri_freq;
const float omega_sin = 2 * pi * sin_freq / 1000000;
const float theta_sin = 2 * pi / 3;
byte out = 0;
float ratio;

void setup() {
  DDRD = B11111100;
  // Serial.begin(115200);
}

void loop() {
  time = micros();
  sine1 = sin(omega_sin * time);
  sine2 = sin((omega_sin * time) + theta_sin);
  sine3 = sin((omega_sin * time) - theta_sin);
  ratio = time / period_tri; 
  tri = 4 * abs(ratio - floor(ratio + 0.5)) - 1;

  // Serial.println(String(sine1) + " " + String(sine2) + " " + String(sine3) + " " + String(tri));
  // Serial.println(tri);

  (sine1 > tri) ? out |= B00000100 : out |= B00001000;
  (sine1 > tri) ? out &= B11110111 : out &= B11111011;

  (sine2 > tri) ? out |= B00010000 : out |= B00100000;
  (sine2 > tri) ? out &= B11011111 : out &= B11101111;

  (sine3 > tri) ? out |= B01000000 : out |= B10000000;
  (sine3 > tri) ? out &= B01111111 : out &= B10111111;

  PORTD = out;
}