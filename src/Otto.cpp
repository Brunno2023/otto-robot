#include <Otto.h>

Otto myOtto;

void setup() {
  myOtto.init(2, 3, 4, 5, true, 6);
}

void loop() {
  myOtto.home();
  myOtto.walk(2, 1000, FORWARD);
  myOtto.home();
  delay(1000);
}


myOtto.playGesture(OttoHappy);
myOtto.sing(S_happy);


int A[4] = {30, 30, 20, 20};
int O[4] = {0, 0, 4, -4};
double phase_diff[4] = {0, 0, DEG2RAD(-90), DEG2RAD(-90)};
myOtto._execute(A, O, 1000, phase_diff);
