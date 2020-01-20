#include <Arduino.h>
#include "qrcode.h"
#include "qrencode.h"

int offsetsX = 42;
int offsetsY = 10;
int screenwidth = 128;
int screenheight = 64;
bool QRDEBUG = false;
int multiply = 1;

QRcode::QRcode(OLEDDisplay *display){
	this->display = display;
  this->model = OLED_MODEL;
}

QRcode::QRcode(Adafruit_ST7735 *tft, uint8_t model){
	this->tft = tft;
  this->model = model;
  offsetsX = 20;
  offsetsY = 20;
}

QRcode::QRcode(Adafruit_ST7789 *tft, uint8_t model){
	this->tft = tft;
  this->model = model;
  offsetsX = 20;
  offsetsY = 20;
}

void QRcode::init(){
	if (this->model==OLED_MODEL){
    display->init();
    display->flipScreenVertically();
    display->setColor(WHITE);
    multiply = 1;
  } else {
    ((Adafruit_ST7735 *)tft)->initR(model);
    screenwidth = tft->width();
    screenheight = tft->height(); 
    //tft->setRotation(1);
    tft->fillScreen(ST77XX_WHITE);
    int min = screenwidth;
    if (screenheight<screenwidth)
      min = screenheight;
    multiply = min/WD;
    offsetsX = (screenwidth-(WD*multiply))/2;
    offsetsY = (screenheight-(WD*multiply))/2;
  }
}

void QRcode::init(uint16_t width, uint16_t height){
	if (this->model==OLED_MODEL){
    display->init();
    display->flipScreenVertically();
    display->setColor(WHITE);
  } else {
    ((Adafruit_ST7789 *)tft)->init(width,height);
    screenwidth = tft->width();
    screenheight = tft->height(); 
    //tft->setRotation(1);
    tft->fillScreen(ST77XX_WHITE);
    int min = screenwidth;
    if (screenheight<screenwidth)
      min = screenheight;
    multiply = WD/min;
    offsetsX = (screenwidth-(WD*multiply))/2;
    offsetsY = (screenheight-(WD*multiply))/2;
  }
}

void QRcode::debug(){
	QRDEBUG = true;
}

void QRcode::render(int x, int y, int color){
  
  if (model != OLED_MODEL)
    multiply = 2;
  x=(x*multiply)+offsetsX;
  y=(y*multiply)+offsetsY;
  if(color==1) {
    if (model==OLED_MODEL) {
	    display->setColor(BLACK);
      display->setPixel(x, y);
    } else {
      tft->drawPixel(x,y,ST77XX_BLACK);
      if (multiply>1) {
        tft->drawPixel(x+1,y,ST77XX_BLACK);
        tft->drawPixel(x+1,y+1,ST77XX_BLACK);
        tft->drawPixel(x,y+1,ST77XX_BLACK);
      }
    }
  }
  else {
    if (model==OLED_MODEL) {
	    display->setColor(WHITE);
      display->setPixel(x, y);
    } else {
      tft->drawPixel(x,y,ST77XX_WHITE);
      if (multiply>1) {
        tft->drawPixel(x+1,y,ST77XX_WHITE);
        tft->drawPixel(x+1,y+1,ST77XX_WHITE);
        tft->drawPixel(x,y+1,ST77XX_WHITE);
      }
    }
  }
}

void QRcode::screenwhite(){
   if (model==OLED_MODEL) {
      display->clear();
      display->setColor(WHITE);
      display->fillRect(0, 0, screenwidth, screenheight);
      display->display();
   } else {
      tft->fillScreen(ST77XX_WHITE);
   }
}

void QRcode::create(String message) {

  // create QR code
  message.toCharArray((char *)strinbuf,260);
  qrencode();
  screenwhite();

  
  // print QR Code
  for (byte x = 0; x < WD; x+=2) {
    for (byte y = 0; y < WD; y++) {
      if ( QRBIT(x,y) &&  QRBIT((x+1),y)) {
        // black square on top of black square
        render(x, y, 1);
        render((x+1), y, 1);
      }
      if (!QRBIT(x,y) &&  QRBIT((x+1),y)) {
        // white square on top of black square
        render(x, y, 0);
        render((x+1), y, 1);
      }
      if ( QRBIT(x,y) && !QRBIT((x+1),y)) {
        // black square on top of white square
        render(x, y, 1);
        render((x+1), y, 0);
      }
      if (!QRBIT(x,y) && !QRBIT((x+1),y)) {
        // white square on top of white square
        render(x, y, 0);
        render((x+1), y, 0);
      }
    }
  }
  if (model==OLED_MODEL)
    display->display();
}
