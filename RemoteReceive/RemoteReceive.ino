// this doesn't seem to work
#include <IRremote.h>
IRrecv irrecv(11); // Receive on pin 11
decode_results results;
IRsend irsend;
#define SPEAKERPOWER    0x4FBE817             // recorded value for speaker
#define TVPOWER         0x2FD48B7             // recorded value for TV
int incoming = -1;

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    incoming = Serial.read() - 48;

    if (incoming == 1) {
      irsend.sendNEC(SPEAKERPOWER, 32);
      irrecv.enableIRIn();
    } else if (incoming == 2) {
      irsend.sendNEC(TVPOWER, 32);
      irrecv.enableIRIn();
    }
  }
  if (irrecv.decode(&results)) {
    irrecv.resume();
    Serial.print(results.decode_type);
    Serial.print(", ");
    Serial.print(results.value, HEX);
    Serial.print(", ");
    Serial.println(results.bits, DEC);
    irrecv.resume(); // Continue receiving
  }
}
