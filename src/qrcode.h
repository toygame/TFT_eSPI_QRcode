#include "OLEDDisplay.h"
#include <Adafruit_GFX.h>   
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>

#define OLED_MODEL 255

class QRcode
{
	private:
		OLEDDisplay *display;
		Adafruit_ST77xx *tft;
		uint8_t model;
		void render(int x, int y, int color);

	public:
		QRcode(OLEDDisplay *display);
		QRcode(Adafruit_ST7735 *display, uint8_t model);
		QRcode(Adafruit_ST7789 *display, uint8_t model);

		void init(uint16_t width, uint16_t height);
		void init();
		void debug();
		void screenwhite();
		void create(String message);
		
};
