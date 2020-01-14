#include "OLEDDisplay.h"
#include <Adafruit_GFX.h>      // include Adafruit graphics library
#include <Adafruit_ST7735.h>   // include Adafruit ST7735 TFT library

class QRcode
{
	private:
		OLEDDisplay *display;
		Adafruit_ST7735 *tft;
		uint8_t model;
		void render(int x, int y, int color);

	public:
		QRcode(OLEDDisplay *display);
		QRcode(Adafruit_ST7735 *display, uint8_t model);

		void init();
		void debug();
		void screenwhite();
		void create(String message);
		
};
