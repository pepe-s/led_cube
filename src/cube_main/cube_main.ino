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
void MyShiftOut( int dataPin, int clockPin, int bit, unsigned long val )
{
  for( int i = 0; i < bit; i++ )
  {
    digitalWrite(dataPin, !!(val & (1L << i)));
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  }
}

void LayerSwitch(int layer)
{
  digitalWrite(LAYER1PIN,HIGH); 
  digitalWrite(LAYER2PIN,HIGH); 
  digitalWrite(LAYER3PIN,HIGH); 
  digitalWrite(LAYER4PIN,HIGH); 
  digitalWrite(LAYERS[layer],LOW); 
}


/*------------------------------------------------------------------------
*         main
------------------------------------------------------------------------*/
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

void loop()
{
  onece();
  /*
  for(int i = 0; i < 100; i++)
    slide();
  for(int j = 0; j < 100; j++)
    updown();
    */
}


