// -----------------------------------
// Controlling LEDs over the Internet
// -----------------------------------

// name the pins
int led1 = D0;
int led2 = D1;

// Create a variable that will store the temperature value
int temperature = 0;

// This routine runs only once upon reset
void setup()
{
   //Register our Spark function here
   Spark.function("led", ledControl);

   // Configure the pins to be outputs
   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);

   // Initialize both the LEDs to be OFF
   digitalWrite(led1, LOW);
   digitalWrite(led2, LOW);
   
   // Register a Spark variable here
  Spark.variable("temperature", &temperature, INT);

  // Connect the temperature sensor to A7 and configure it
  // to be an input
  pinMode(A7, INPUT);
}


// This routine loops forever
void loop()
{
   // Nothing to do here
   temperature = analogRead(A7);
}


// This function gets called whenever there is a matching API request
// the command string format is l<led number>,<state>
// for example: l1,HIGH or l1,LOW
//              l2,HIGH or l2,LOW

int ledControl(String command)
{
   int state = 0;
   //find out the pin number and convert the ascii to integer
   int pinNumber = (command.charAt(1) - '0') - 1;
   //Sanity check to see if the pin numbers are within limits
   if (pinNumber < 0 || pinNumber > 1) return -1;

   // find out the state of the led
   if(command.substring(3,7) == "HIGH") state = 1;
   else if(command.substring(3,6) == "LOW") state = 0;
   else return -1;

   // write to the appropriate pin
   digitalWrite(pinNumber, state);
   return 1;
}