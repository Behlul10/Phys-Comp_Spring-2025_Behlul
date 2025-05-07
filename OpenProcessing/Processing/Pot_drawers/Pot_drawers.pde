/*
Drawing Cirlces with pots. 
*/

import processing.serial.*; 
Serial myPort;
byte[] val ;

void setup() 
{
  size(400, 400);
  textAlign(CENTER);
  rectMode(CENTER);
  textSize(24);

  printArray(Serial.list()); 
  String portName = Serial.list()[2]; 
  myPort = new Serial(this, portName, 115200);  
}

void draw() 
{

  if (myPort.available() > 0 ) 
  {
    val = myPort.readBytesUntil('e'); 
  }
  
  if (val.length == 5)
  {
    println(val); 
    int pot_1 = int(map(val[2], -128, 127, 0, 255));
    int pot_2 = int(map(val[3], -128, 127, 0, 255));
    
    //casting Byte button values to boolean
    boolean b_1 = boolean(val[0]);
    boolean b_2 = boolean(val[1]);

    if (b_1)
    {
      fill(255 - pot_2);
      rect(width/8, height/2, 90, 90);
      background(100,20,200);
      triangle(pot_2,pot_2, pot_1, pot_1,pot_2,pot_1);
    }    
    if (b_2)
    {
      fill(255 - pot_2);
      rect(width - width/8, height/2, 90, 90);
      background(50,200,50);
      rect(pot_2*1.5, pot_1*1.5, 50, 50);
    } 
    else
    {
      ellipse (pot_2*1.5, pot_1*1.5, 50, 50);
    }
    
    fill (pot_1, pot_2, 0);
  }
}
