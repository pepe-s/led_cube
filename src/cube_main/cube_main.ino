/*************************************************************************
* LED Cube 
* 2017/02/26
* Teppei
*************************************************************************/


/*------------------------------------------------------------------------
*         definition
------------------------------------------------------------------------*/
#define DATAPIN 9     // 74HC595のDSへ
#define LATCHPIN 12   // 74HC595のST_CPへ
#define CLOCKPIN 11   // 74HC595のSH_CPへ
#define LAYER1PIN 2   //1層目(最下層)
#define LAYER2PIN 3   //2層目
#define LAYER3PIN 4   //3層目
#define LAYER4PIN 5   //4層目(最上層)

/*------------------------------------------------------------------------
*         variable
------------------------------------------------------------------------*/
int LAYERS[4] = {LAYER1PIN,LAYER2PIN,LAYER3PIN,LAYER4PIN};


/*------------------------------------------------------------------------
*         function
------------------------------------------------------------------------*/

/*----------------------------------------
* シフトレジスタに出力する
----------------------------------------*/
void MyShiftOut( int dataPin, int clockPin, int bit, unsigned long val )
{
  for( int i = 0; i < bit; i++ )
  {
    digitalWrite(dataPin, !!(val & (1L << i)));
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  }
}

/*----------------------------------------
* レイヤーを変更する
----------------------------------------*/
void LayerSwitch(int layer)
{
  digitalWrite(LAYER1PIN,HIGH); 
  digitalWrite(LAYER2PIN,HIGH); 
  digitalWrite(LAYER3PIN,HIGH); 
  digitalWrite(LAYER4PIN,HIGH); 
  digitalWrite(LAYERS[layer],LOW); 
}

/*----------------------------------------
* LEDナンバーからレイヤーを割り出す
----------------------------------------*/
int ConvLayer(int num){
  if(num < 16)
    return 0;
  else if(num < 16 * 2)
    return 1;
  else if(num < 16 * 3)
    return 2;
  else
    return 3;
}

/*----------------------------------------
* 指定した番号のLEDを点灯させる
----------------------------------------*/
void Led_ON(int num){
  unsigned long pin = 0;

  //レイヤーを選択
  LayerSwitch(ConvLayer(num));

  //アノードのピンを算出
  pin = (num % 16) + 1;

  // シフト演算を使って点灯するLEDを選択
  digitalWrite(LATCHPIN, LOW);    // 送信中はLATCHPINをLOW
  MyShiftOut( DATAPIN, CLOCKPIN, 16, 1L << pin );
  digitalWrite(LATCHPIN, HIGH);   // 送信後はLATCHPINをHIGHに戻す
}

/*------------------------------------------------------------------------
*         main
------------------------------------------------------------------------*/

/*----------------------------------------
* setup
----------------------------------------*/
void setup()
{
  pinMode(DATAPIN, OUTPUT);
  pinMode(LATCHPIN, OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);
  pinMode(LAYER1PIN, OUTPUT);
  pinMode(LAYER2PIN, OUTPUT);
  pinMode(LAYER3PIN, OUTPUT);
  pinMode(LAYER4PIN, OUTPUT);
  for(int i = 0; i > 3; i++){
    digitalWrite(LAYERS[i],HIGH);
  }
}

/*----------------------------------------
* loop
----------------------------------------*/
void loop()
{
  for(int i = 0; i < 10; i++)
    eight();
  for(int i = 0; i < 50; i++)
    onece();
  for(int i = 0; i < 200; i++)
    slide();
  for(int i = 0; i < 200; i++)
    updown();
    
}


