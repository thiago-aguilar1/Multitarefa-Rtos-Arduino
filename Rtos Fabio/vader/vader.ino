byte ledPin = 13;
int speakerPin = 3;
 
//speaker connected to one of the PWM ports




 
#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880
//frequencies for the tones we're going to use
//used http://home.mit.bme.hu/~bako/tonecalc/tonecalc.htm to get these




// --- Funções Auxiliares ---
void march(char oitava);
void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds);




 
void setup()
{
  pinMode(ledPin, OUTPUT);
  // sets the ledPin to be an output
  pinMode(speakerPin, OUTPUT);
  //sets the speakerPin to be an output

  march(1);
  march(2);
  march(4);
}
 
void loop()     // run over and over again
{
  
  
  
} //end loop





 
void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{
    digitalWrite(ledPin, HIGH);
    //use led to visualize the notes being played
 
    int x;
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++)    {
        digitalWrite(speakerPin,HIGH);
        delayMicroseconds(delayAmount);
        digitalWrite(speakerPin,LOW);
        delayMicroseconds(delayAmount);
    }
 
    digitalWrite(ledPin, LOW);
    //set led back to low
 
    delay(20);
    //a little delay to make all notes sound separate
}
 
void march(char oitava)
{
    //for the sheet music see:
    //http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0016254
    //this is just a translation of said sheet music to frequencies / time in ms
    //used 500 ms for a quart note
 
    beep(speakerPin, oitava*a, 500);
    beep(speakerPin, oitava*a, 500);
    beep(speakerPin, oitava*a, 500);
    beep(speakerPin, oitava*f, 350);
    beep(speakerPin, oitava*cH, 150);
 
    beep(speakerPin, oitava*a, 500);
    beep(speakerPin, oitava*f, 350);
    beep(speakerPin, oitava*cH, 150);
    beep(speakerPin, oitava*a, 1000);
    //first bit
 
    beep(speakerPin, oitava*eH, 500);
    beep(speakerPin, oitava*eH, 500);
    beep(speakerPin, oitava*eH, 500);
    beep(speakerPin, oitava*fH, 350);
    beep(speakerPin, oitava*cH, 150);
 
    beep(speakerPin, oitava*gS, 500);
    beep(speakerPin, oitava*f, 350);
    beep(speakerPin, oitava*cH, 150);
    beep(speakerPin, oitava*a, 1000);
    //second bit...
 
    beep(speakerPin, oitava*aH, 500);
    beep(speakerPin, oitava*a, 350);
    beep(speakerPin, oitava*a, 150);
    beep(speakerPin, oitava*aH, 500);
    beep(speakerPin, oitava*gSH, 250);
    beep(speakerPin, oitava*gH, 250);
 
    beep(speakerPin, oitava*fSH, 125);
    beep(speakerPin, oitava*fH, 125);
    beep(speakerPin, oitava*fSH, 250);
    delay(250);
    beep(speakerPin, oitava*aS, 250);
    beep(speakerPin, oitava*dSH, 500);
    beep(speakerPin, oitava*dH, 250);
    beep(speakerPin, oitava*cSH, 250);
    //start of the interesting bit
 
    beep(speakerPin, oitava*cH, 125);
    beep(speakerPin, oitava*b, 125);
    beep(speakerPin, oitava*cH, 250);
    delay(250);
    beep(speakerPin, oitava*f, 125);
    beep(speakerPin, oitava*gS, 500);
    beep(speakerPin, oitava*f, 375);
    beep(speakerPin, oitava*a, 125);
 
    beep(speakerPin, oitava*cH, 500);
    beep(speakerPin, oitava*a, 375);
    beep(speakerPin, oitava*cH, 125);
    beep(speakerPin, oitava*eH, 1000);
    //more interesting stuff (this doesn't quite get it right somehow)
 
    beep(speakerPin, oitava*aH, 500);
    beep(speakerPin, oitava*a, 350);
    beep(speakerPin, oitava*a, 150);
    beep(speakerPin, oitava*aH, 500);
    beep(speakerPin, oitava*gSH, 250);
    beep(speakerPin, oitava*gH, 250);
 
    beep(speakerPin, oitava*fSH, 125);
    beep(speakerPin, oitava*fH, 125);
    beep(speakerPin, oitava*fSH, 250);
    delay(250);
    beep(speakerPin, oitava*aS, 250);
    beep(speakerPin, oitava*dSH, 500);
    beep(speakerPin, oitava*dH, 250);
    beep(speakerPin, oitava*cSH, 250);
    //repeat... repeat
 
    beep(speakerPin, oitava*cH, 125);
    beep(speakerPin, oitava*b, 125);
    beep(speakerPin, oitava*cH, 250);
    delay(250);
    beep(speakerPin, oitava*f, 250);
    beep(speakerPin, oitava*gS, 500);
    beep(speakerPin, oitava*f, 375);
    beep(speakerPin, oitava*cH, 125);
 
    beep(speakerPin, oitava*a, 500);
    beep(speakerPin, oitava*f, 375);
    beep(speakerPin, oitava*c, 125);
    beep(speakerPin, oitava*a, 1000);
    //and we're done \ó/
}
