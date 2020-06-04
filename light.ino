

int photosensor = A0; // This is where your photoresistor or phototransistor is plugged in. The other side goes to the "power" pin (below).

int analogvalue; // Here we are declaring the integer variable analogvalue, which we will use later to store the value of the photoresistor or phototransistor.

bool shouldNotify = true;

// Next we go into the setup function.

void setup() {
    // This is here to allow for debugging using the USB serial port
    Serial.begin();

    // First, declare all of our pins. This lets our device know which ones will be used for outputting voltage, and which ones will read incoming voltage.
    

    // We are going to declare a Particle.variable() here so that we can access the value of the photosensor from the cloud.
    Particle.variable("analogvalue", &analogvalue, INT);
    // This is saying that when we ask the cloud for "analogvalue", this will reference the variable analogvalue in this app, which is an integer variable.
    
    

}


// Next is the loop function...

void loop() {

    // check to see what the value of the photoresistor or phototransistor is and store it in the int variable analogvalue
    analogvalue = analogRead(photosensor);

    // This prints the value to the USB debugging serial port (for optional debugging purposes)
    Serial.printlnf("%d", analogvalue);
    
    String Light = String(analogvalue);
    
    int max = 200;
    
    
    
    
    
    if (analogvalue > max )
    {
        
        
        
        if (shouldNotify) 
        {
            shouldNotify = false;
            Particle.publish("lightlevel", Light, PRIVATE);
            Particle.publish("lightlevel", "Sunlight", PRIVATE);
        }        
    }
    else if (analogvalue <= max)
    {
    
        
        if (!shouldNotify)
        {
            shouldNotify = true;
            Particle.publish("lightlevel", Light, PRIVATE);
            Particle.publish("lightlevel", "NoSunlight", PRIVATE);
        }
    }


    // This delay is just to prevent overflowing the serial buffer, plus we really don't need to read the sensor more than
    // 10 times per second (100 millisecond delay)
    delay(5000);
}

    
    
    
    
    