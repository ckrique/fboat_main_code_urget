void set_speed_suave(int vel_motor){
  // velocidade atual
  // calcula o erro
  // calcula o PID
  // joga na saída
  int erro = _motor_vela_ant - vel_motor;

  int output = P_m(erro) + I_m(erro);
  Serial.println(output);
  //md.setM2Speed(output);código ponte h antiga
  setM2Speed(output);
}

void set_speed_incremental(int velocidade_motor){
  int erro = velocidade_motor - vel_acc;
  if(erro > 0){
    vel_acc += vel_incremento;
  }
  if (erro < 0){
    vel_acc -= vel_incremento;
  }
  vel_acc = constrain(vel_acc, -400, 400);
  //md.setM2Speed(vel_acc); código ponte h antiga
  setM2Speed(vel_acc);
  //Serial.println(vel_acc);
}


// Set speed for motor 2, speed is a number betwenn -400 and 400
void setM2Speed(int speed)
{

	static const unsigned char _PWM1_TIMER1_PIN = 9;
	static const unsigned char _PWM2_TIMER1_PIN = 10;

	 unsigned char reverse = 0;

	  if (speed < 0)
	  {
		speed = -speed;  // make speed a positive quantity
		reverse = 1;  // preserve the direction
	  }
	  if (speed > 400)  // Max
		speed = 400;


	OCR1B = speed;

//#ifdef DUALVNH5019MOTORSHIELD_TIMER1_AVAILABLE
	if (_PWM1 == _PWM1_TIMER1_PIN && _PWM2 == _PWM2_TIMER1_PIN)
	{
		OCR1B = speed;
	}
	else
	{
		analogWrite(_PWM2, speed * 51 / 80); // map 400 to 255
	}
//#else
//	    analogWrite(_PWM2, speed * 51 / 80); // map 400 to 255
//#endif
	

  if (speed == 0)
  {
    digitalWrite(_INA2,LOW);   // Make the motor coast no
    digitalWrite(_INB2,LOW);   // matter which direction it is spinning.
  }
  else if (reverse)
  {
    digitalWrite(_INA2,LOW);
    digitalWrite(_INB2,HIGH);
  }
  else
  {
    digitalWrite(_INA2,HIGH);
    digitalWrite(_INB2,LOW);
  }
}