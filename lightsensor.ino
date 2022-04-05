// The library file is taken from the community libraries available on Particle
// The original author of this library is https://github.com/aliktab/Particle_BH1750
// Copyright (C) 2014 Alik <aliktab@gmail.com> All rights reserved.
// Adapted for IFTTT by Daniel Fantin

#include "BH1750.h"
BH1750 sensor(0x23, Wire);

const int SUNLIGHT = 2000;
double lux = 0;
double priorLux = 0;

void setup()
{
  sensor.begin();

  sensor.set_sensor_mode(BH1750::forced_mode_high_res2);

  Serial.begin();
}

void loop()
{
  sensor.make_forced_measurement();

  lux = sensor.get_light_level();
  
  if (lux > SUNLIGHT && priorLux < SUNLIGHT)
  {
    Particle.publish("Sunlight", String(lux), PRIVATE);      
  }
  else if (lux < SUNLIGHT && priorLux > SUNLIGHT)
  {
    Particle.publish("Dusk", String(lux), PRIVATE);      
  } 
  else
  {
      Particle.publish("No change in condition", String(lux), PRIVATE);
  }

  priorLux = lux;  
  delay(10000);
}