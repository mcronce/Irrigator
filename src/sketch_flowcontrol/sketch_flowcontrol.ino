// Constants
const byte pin_flow_sensor = 2;
const byte pin_led = 13;
// Serial commands - using chars for now for debug reasons, _might_ change in the future
const byte COMMAND_READ_REVS = '1';
const byte COMMAND_READ_MOISTURE1 = '2';
const byte COMMAND_READ_MOISTURE2 = '3';
const byte COMMAND_VERBOSE = 'v';

// Globals
//volatile unsigned long revs;
unsigned long revs;
boolean last_state;
boolean verbose_mode;

// TODO: Figure out why this doesn't work with interrupts
/*
void handle_flow_sensor_rising() {
  revs++;
  digitalWrite(pin_led, HIGH);
}

void handle_flow_sensor_falling() {
  digitalWrite(pin_led, LOW);
}
*/

void setup() {
  // Initialize our globals
  revs = 0;
  last_state = false;
  verbose_mode = false;
  
  // Fire up our pins and our serial interface
  pinMode(pin_flow_sensor, INPUT);
  pinMode(pin_led, OUTPUT);
  Serial.begin(115200);

  // Initialize LED pin to off
  digitalWrite(pin_led, LOW);
}

void loop() {
  // Read the pin
  boolean current_state = digitalRead(pin_flow_sensor);
  digitalWrite(pin_led, current_state);
  
  // If the reading has changed and is currently high, increment our counter
  if(current_state && current_state != last_state) {
    revs++;
    if(verbose_mode) Serial.println(revs);
  }
  
  if(Serial.available()) {
    byte buf[1];
    Serial.readBytes(buf, 1);

    switch(buf[0]) {
      case COMMAND_READ_REVS:
        Serial.println(revs);
        break;
      case COMMAND_READ_MOISTURE1:
      case COMMAND_READ_MOISTURE2:
        Serial.print("Not implemented \"");
        Serial.print(char(buf[0]));
        Serial.println('"');
        break;
      case COMMAND_VERBOSE:
        verbose_mode = !verbose_mode;
        if(verbose_mode) {
          Serial.println("Verbose mode enabled");
        } else {
          Serial.println("Verbose mode disabled");
        }
        break;
      default:
        Serial.print("Invalid command \"");
        Serial.print(char(buf[0]));
        Serial.println('"');
        break;
    }
  }
  
  last_state = current_state;
}

