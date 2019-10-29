
#include <stdio.h>

#define MAIN_PORT_SPEED 115200
#define GSM_PORT_SPEED  2400

int  tryGetFromPort(char *buf, int bufsize);
void trySendToPort(char *buf, int outlen);
int  tryGetFromGSM(char *buf, int bufsize);
void trySendToGSM(char *buf, int outlen);

void setup() 
{
	Serial.begin(MAIN_PORT_SPEED);
  delay(100);
	Serial1.begin(GSM_PORT_SPEED);
  delay(100);
  Serial.println("Start..."); 
}

void loop() 
{ 
  char buf[16];
  int  buflen = 0;
   
  while(1){
    buflen = tryGetFromPort(buf, sizeof(buf));
    if(buflen > 0)
      trySendToGSM(buf, buflen);
    buflen = tryGetFromGSM(buf, sizeof(buf));
    if(buflen > 0)
      trySendToPort(buf, buflen);
  }
}

int tryGetFromPort(char *buf, int bufsize)
{
  int inlen = Serial.available();

  if(inlen > 0){
    if(bufsize < inlen){
     inlen = bufsize;
    }
    for(int i = 0; i < inlen; i++){
      buf[i] = Serial.read();
    } 
  }

  return inlen;
}

void trySendToPort(char *buf, int outlen)
{
  for(int i = 0; i < outlen; i++){
    Serial.print(buf[i]);
  }
}

int tryGetFromGSM(char *buf, int bufsize)
{
  int inlen = Serial1.available();

  if(inlen > 0){
    if(bufsize < inlen){
     inlen = bufsize;
    }
    for(int i = 0; i < inlen; i++){
      buf[i] = Serial1.read();
    } 
  }

  return inlen;
}

void trySendToGSM(char *buf, int outlen)
{
  for(int i = 0; i < outlen; i++){
    Serial1.print(buf[i]);
  }
}
