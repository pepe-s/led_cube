/*
* LED Cube pattern
* 2017/02/26
*/


/*------------------------------------------------------------------------
*         defined
------------------------------------------------------------------------*/
#define LED_INTERVAL 100    //点滅インターバル

/*------------------------------------------------------------------------
*         variable
------------------------------------------------------------------------*/
unsigned long signal = 0;
unsigned long time1 = millis();
unsigned long time2 = time1;
int col = 4;
int shift = 0;


/*------------------------------------------------------------------------
*         function
------------------------------------------------------------------------*/

void onece(){
  int led = 0;

  //光らすLEDの選定
  led = random(0,64);

  //LEDの点滅  
  for(int i = 0; i < LED_INTERVAL; i++){
    Led_ON(led);
    delay(1);
  }

}

 void eight(){
  int led[8] = {0,0,0,0,0,0,0,0};

  //光らすLEDの選定
  for(int i = 0; i < 8; i++){
    led[i] = random(0,64);  
  }
  
  //LEDの点滅  
  for(int i = 0; i < LED_INTERVAL; i++){
    for(int j = 0; j < 8; j++)
      Led_ON(led[j]);
    delay(1);
  }

}

void slide()
{
  static bool reverse = false;
  
  for(int layer = 0; layer < 4; layer++)
  {
    LayerSwitch(layer);
    for( int i = shift; i <  col; i++ )
    {
      digitalWrite(LATCHPIN, LOW);    // 送信中はLATCHPINをLOWに
  
      // シフト演算を使って点灯するLEDを選択
      MyShiftOut( DATAPIN, CLOCKPIN, 16, 1L << i );

      digitalWrite(LATCHPIN, HIGH);   // 送信後はLATCHPINをHIGHに戻す

      delay(1);
    }
  }
  time2 = millis();
  if((time2 - time1) > 50)
  {
    time1 = millis();     //タイム更新
    if (!reverse)
    {
      col += 4;
      shift += 4;
      if(col >= 16)
        reverse = true;
    }
    else
    {
      col -= 4;
      shift -= 4;
      if(col <= 4)
        reverse = false;
    }
  } 
}


void updown(){
  static bool reverse = false;
  static int layer = 0;
    
  for( int i = 0; i <  16; i++ )
  {
    digitalWrite(LATCHPIN, LOW);                    // 送信中はLATCHPINをLOWに
    MyShiftOut( DATAPIN, CLOCKPIN, 16, 1L << i );   // シフト演算を使って点灯するLEDを選択
    digitalWrite(LATCHPIN, HIGH);                   // 送信後はLATCHPINをHIGHに戻す

    delay(1);
  }
  
  time2 = millis();
  if((time2 - time1) > 50)
  {
    time1 = millis();     //タイム更新
    if (!reverse)
    {
      layer ++;
      if(layer >= 3)
        reverse = true;
    }
    else
    {
      layer --;
      if(layer <= 0)
        reverse = false;
    }
    LayerSwitch(layer);
  } 
}

