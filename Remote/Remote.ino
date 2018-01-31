// one pin to ground and one to 3
#include <IRremote.h>
IRsend irsend;
//#define POWER         0xE0E040BF      // from IRrecvDemo, Ken Shirriff
//#define SPEAKER_POWER 0x4FBE817       // old speakers, recorded value, NEC
//#define TV_POWER      0x2FD48B7       // toshiba TV, recorded value, NEC
#define VOLUME_UP     0x4BB640BF      // onkyo amp, recorded value, NEC
#define VOLUME_DOWN   0x4BB6C03F      // onkyo amp, recorded value, NEC
int incoming = -1;

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming number, 0 if no number
    incoming = Serial.parseInt();
    Serial.println(incoming);
    int i = 0;
    long signalCode;
    
    if (incoming >= 0 && incoming <= 2) {
      i = 5 * (incoming + 1);
      signalCode = VOLUME_DOWN;
    } else if (incoming >= 3 && incoming <= 5) {
      i = 5 * (incoming - 2);
      signalCode = VOLUME_UP;
    }
    int j = 0;
    while (j < i) {
      irsend.sendNEC(signalCode, 32);
      j++;
      if (j != i) {
        delay(300);
      }
    }
  }
}
