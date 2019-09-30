/*
 * 
 * Created by Noah Williams on 9/29/2019.
 * 
 * Purpose: An example of saving a file using a button. The button uses the button documentation hookup example.
 */

#include <save.h>
#include <button.h>
save save;
button button;
unsigned int time = millis();
void setup() {
  // put your setup code here, to run once:

  save.setup();
  button.setup(2);
  save.writeFile("noah.txt");
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10);
  save.saveToFile("hi"); //Needs to be a string. Get location of time variable, and cast it to a pointer for a string.
  if(button.checkButton()){
    Serial.println("LED ON");
    save.closeFile();
    delay(100);
  }
}
