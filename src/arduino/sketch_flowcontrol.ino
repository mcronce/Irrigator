// Constants
const byte pin_flow_sensor = 2;
const byte pin_led = 13;

// Globals
unsigned long revs;
boolean last_state;

void setup() {
  // Initialize our globals
  revs = 0;
  last_state = false;
  
  // Fire up our pins and our serial interface
  pinMode(pin_flow_sensor, INPUT);
  pinMode(pin_led, OUTPUT);
  digitalWrite(pin_led, LOW);
  Serial.begin(9600);
}

void loop() {
  // Read the pin
  boolean current_state = digitalRead(pin_flow_sensor);
  
  // If it hasn't changed since our last iteration, ignore the reading
  if(current_state == last_state) {
    return;
  }
  
  // Act on the 
  if(current_state) {
    revs++;
    digitalWrite(pin_led, HIGH);
    Serial.println(revs);
  } else {
    digitalWrite(pin_led, LOW);
  }
  
  last_state = current_state;
}

