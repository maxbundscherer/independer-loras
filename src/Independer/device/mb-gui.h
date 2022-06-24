// Keyboard Config
#define CARDKB_ADDR 0x5F

#include <math.h>

/*
 * ####################################
 *  Config GUI Section
 * ####################################
 */

#define C_GUI_DELAY_STATIC 3000
#define C_GUI_DELAY_STATIC_SHORT 1000
#define C_GUI_DELAY_LONG_STATIC 10000

#define C_GUI_DELAY_MSG_SHORT_I 20
#define C_GUI_DELAY_MSG_MIDDLE_I 40
#define C_GUI_DELAY_MSG_LONG_I 60

/*
 * ####################################
 *  Test Section
 * ####################################
 */

void i_gui_test_drawLines()
{
  for (int16_t i = 0; i < DISPLAY_WIDTH; i += 4)
  {
    Heltec.display->drawLine(0, 0, i, DISPLAY_HEIGHT - 1);
    Heltec.display->display();
    delay(10);
  }
  for (int16_t i = 0; i < DISPLAY_HEIGHT; i += 4)
  {
    Heltec.display->drawLine(0, 0, DISPLAY_WIDTH - 1, i);
    Heltec.display->display();
    delay(10);
  }
  delay(250);

  Heltec.display->clear();
  for (int16_t i = 0; i < DISPLAY_WIDTH; i += 4)
  {
    Heltec.display->drawLine(0, DISPLAY_HEIGHT - 1, i, 0);
    Heltec.display->display();
    delay(10);
  }
  for (int16_t i = DISPLAY_HEIGHT - 1; i >= 0; i -= 4)
  {
    Heltec.display->drawLine(0, DISPLAY_HEIGHT - 1, DISPLAY_WIDTH - 1, i);
    Heltec.display->display();
    delay(10);
  }
  delay(250);

  Heltec.display->clear();
  for (int16_t i = DISPLAY_WIDTH - 1; i >= 0; i -= 4)
  {
    Heltec.display->drawLine(DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1, i, 0);
    Heltec.display->display();
    delay(10);
  }
  for (int16_t i = DISPLAY_HEIGHT - 1; i >= 0; i -= 4)
  {
    Heltec.display->drawLine(DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1, 0, i);
    Heltec.display->display();
    delay(10);
  }
  delay(250);
  Heltec.display->clear();
  for (int16_t i = 0; i < DISPLAY_HEIGHT; i += 4)
  {
    Heltec.display->drawLine(DISPLAY_WIDTH - 1, 0, 0, i);
    Heltec.display->display();
    delay(10);
  }
  for (int16_t i = 0; i < DISPLAY_WIDTH; i += 4)
  {
    Heltec.display->drawLine(DISPLAY_WIDTH - 1, 0, i, DISPLAY_HEIGHT - 1);
    Heltec.display->display();
    delay(10);
  }
  delay(250);
}

// Adapted from Adafruit_SSD1306
void i_gui_test_drawRect(void)
{
  for (int16_t i = 0; i < DISPLAY_HEIGHT / 2; i += 2)
  {
    Heltec.display->drawRect(i, i, DISPLAY_WIDTH - 2 * i, DISPLAY_HEIGHT - 2 * i);
    Heltec.display->display();
    delay(10);
  }
}

// Adapted from Adafruit_SSD1306
void i_gui_test_fillRect(void)
{
  uint8_t color = 1;
  for (int16_t i = 0; i < DISPLAY_HEIGHT / 2; i += 3)
  {
    Heltec.display->setColor((color % 2 == 0) ? BLACK : WHITE); // alternate colors
    Heltec.display->fillRect(i, i, DISPLAY_WIDTH - i * 2, DISPLAY_HEIGHT - i * 2);
    Heltec.display->display();
    delay(10);
    color++;
  }
  // Reset back to WHITE
  Heltec.display->setColor(WHITE);
}

// Adapted from Adafruit_SSD1306
void i_gui_test_drawCircle(void)
{
  for (int16_t i = 0; i < DISPLAY_HEIGHT; i += 2)
  {
    Heltec.display->drawCircle(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, i);
    Heltec.display->display();
    delay(10);
  }
  delay(1000);
  Heltec.display->clear();

  // This will draw the part of the circel in quadrant 1
  // Quadrants are numberd like this:
  //   0010 | 0001
  //  ------|-----
  //   0100 | 1000
  //
  Heltec.display->drawCircleQuads(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, DISPLAY_HEIGHT / 4, 0b00000001);
  Heltec.display->display();
  delay(200);
  Heltec.display->drawCircleQuads(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, DISPLAY_HEIGHT / 4, 0b00000011);
  Heltec.display->display();
  delay(200);
  Heltec.display->drawCircleQuads(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, DISPLAY_HEIGHT / 4, 0b00000111);
  Heltec.display->display();
  delay(200);
  Heltec.display->drawCircleQuads(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, DISPLAY_HEIGHT / 4, 0b00001111);
  Heltec.display->display();
}

void i_gui_test_buffer()
{

  // Initialize the log buffer
  // allocate memory to store 8 lines of text and 30 chars per line.
  Heltec.display->setLogBuffer(5, 30);

  // Some test data
  const char *test[] = {
      "Hello",
      "World",
      "----",
      "Show off",
      "how",
      "the log buffer",
      "is",
      "working.",
      "Even",
      "scrolling is",
      "working"};

  for (uint8_t i = 0; i < 11; i++)
  {
    Heltec.display->clear();
    // Print to the screen
    Heltec.display->println(test[i]);
    // Draw it to the internal screen buffer
    Heltec.display->drawLogBuffer(0, 0);
    // Display it on the screen
    Heltec.display->display();
    delay(500);
  }
}

void gui_test()
{

  Heltec.display->clear();

  i_gui_test_drawLines();
  delay(1000);
  Heltec.display->clear();

  i_gui_test_drawRect();
  delay(1000);
  Heltec.display->clear();

  i_gui_test_fillRect();
  delay(1000);
  Heltec.display->clear();

  i_gui_test_drawCircle();
  delay(1000);
  Heltec.display->clear();

  i_gui_test_buffer();
  delay(1000);
  Heltec.display->clear();
}

/*
 * ####################################
 *  Logo Section
 * ####################################
 */

const unsigned char LOGO_bits[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00,
    0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
    0x80, 0x07, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0e, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00,
    0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
    0x80, 0xc7, 0x3c, 0xe0, 0x1d, 0x3c, 0x38, 0x0f, 0x78, 0x60, 0x1e, 0xf0,
    0x0e, 0x1e, 0xdc, 0x03, 0x80, 0xc7, 0x7f, 0xf8, 0x1f, 0xff, 0xf8, 0x1f,
    0xfe, 0xe1, 0x3f, 0xfc, 0x8f, 0x7f, 0xfc, 0x01, 0x80, 0xc7, 0xf3, 0x38,
    0x1e, 0xe7, 0xf8, 0x3c, 0xce, 0xe1, 0x79, 0x1c, 0x8f, 0x73, 0x3c, 0x00,
    0x80, 0xc7, 0xe1, 0x1c, 0x9c, 0xc3, 0x79, 0x38, 0x87, 0xe3, 0x70, 0x0e,
    0xce, 0xe1, 0x3c, 0x00, 0x80, 0xc7, 0xe1, 0x1c, 0x9c, 0xc3, 0x79, 0x38,
    0x87, 0xe3, 0x70, 0x0e, 0xce, 0xe1, 0x3c, 0x00, 0x80, 0xc7, 0xe1, 0x1c,
    0x9c, 0xff, 0x79, 0x70, 0xff, 0xe3, 0x70, 0x0e, 0xce, 0xff, 0x3c, 0x00,
    0x80, 0xc7, 0xe1, 0x1c, 0x9c, 0xff, 0x79, 0x70, 0xff, 0xe3, 0x70, 0x0e,
    0xce, 0xff, 0x1c, 0x00, 0x80, 0xc7, 0xe1, 0x1c, 0x9c, 0x03, 0x78, 0x38,
    0x07, 0xe0, 0x70, 0x0e, 0xce, 0x01, 0x1c, 0x00, 0x80, 0xc7, 0xe1, 0x1c,
    0x9c, 0xc3, 0x79, 0x38, 0x87, 0xe3, 0x70, 0x0e, 0xce, 0xe1, 0x1c, 0x00,
    0x80, 0xc7, 0xe1, 0x38, 0x1e, 0xe7, 0xf9, 0x3c, 0xce, 0xe3, 0x70, 0x1c,
    0x8f, 0xf3, 0x1c, 0x00, 0x80, 0xc7, 0xe1, 0xf8, 0x1f, 0xff, 0xf8, 0x1f,
    0xfe, 0xe1, 0x70, 0xfc, 0x8f, 0x7f, 0x1c, 0x00, 0x80, 0xc7, 0xe1, 0xe0,
    0x1d, 0x7c, 0x78, 0x0f, 0xf8, 0xe0, 0x70, 0xf0, 0x0e, 0x3e, 0x1c, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x1e, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1c, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0c, 0xff, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x03, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xe0, 0x81, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00};

void gui_logo_static(String version_string, String my_id, String gateway_id, boolean isActor)
{
  Heltec.display->clear();
  Heltec.display->drawXbm(0, 0, 128, 64, LOGO_bits);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  if (isActor)
    Heltec.display->drawString(8, 35, version_string + " Actor\n" + my_id + " -> " + gateway_id);
  else
    Heltec.display->drawString(8, 35, version_string + " Gateway\n" + gateway_id);
  Heltec.display->display();
}

/*
 * ####################################
 *  Msg Section
 * ####################################
 */

void gui_msg_animated(String msg_title, String msg, int i_delay)
{
  Heltec.display->clear();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(5, 5, msg_title);

  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  Heltec.display->drawString(64, 10 * 2 + 2 + 4, msg);
  Heltec.display->display();

  for (int i = 1; i <= 120; i += 1)
  {
    Heltec.display->drawLine(5, 17, 5 + i, 17);
    Heltec.display->display();
    delay(i_delay);
  }
}

void gui_msg_static(String msg_title, String msg)
{
  Heltec.display->clear();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(5, 5, msg_title);
  Heltec.display->drawLine(5, 17, 5 + 120, 17);

  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  Heltec.display->drawString(64, 10 * 2 + 2 + 4, msg);
  Heltec.display->display();
}

void gui_msg_static_gateway(String msg_title, String msg, int global_tx_time)
{
  Heltec.display->clear();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(5, 5, msg_title);
  Heltec.display->drawLine(5, 17, 5 + 120, 17);

  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  Heltec.display->drawString(64, 10 * 2 + 2 + 4, msg);

  int progress = (((float)global_tx_time - 0) / ((float)36000 - 0)) * (float)100;
  if (progress > 100)
    progress = 100;
  if (progress < 0)
    progress = 0;

  Heltec.display->drawProgressBar(0, 0 + 53, 120, 10, progress);

  Heltec.display->display();
}

/*
 * ####################################
 *  Prg Section
 * ####################################
 */

void gui_display_prg_animated(String menu_title, int value, int min, int max, int i_delay)
{
  int progress = (((float)value - min) / ((float)max - min)) * (float)100;
  if (progress > 100)
    progress = 100;
  if (progress < 0)
    progress = 0;
  Heltec.display->clear();

  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(5, 5, menu_title);

  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  Heltec.display->drawString(64, 0 + 23, String(progress) + "%\n" + String(value) + " [" + String(min) + "; " + String(max) + "]");
  Heltec.display->drawProgressBar(0, 0 + 53, 120, 10, progress);
  Heltec.display->display();

  for (int i = 1; i <= 120; i += 1)
  {
    Heltec.display->drawLine(5, 17, 5 + i, 17);
    Heltec.display->display();
    delay(i_delay);
  }
}

void gui_display_prg_static(String menu_title, int value, int min, int max)
{
  int progress = (((float)value - min) / ((float)max - min)) * (float)100;
  if (progress > 100)
    progress = 100;
  if (progress < 0)
    progress = 0;
  Heltec.display->clear();

  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(5, 5, menu_title);
  Heltec.display->drawLine(5, 17, 5 + 120, 17);

  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  Heltec.display->drawString(64, 0 + 23, String(progress) + "%\n" + String(value) + " [" + String(min) + "; " + String(max) + "]");
  Heltec.display->drawProgressBar(0, 0 + 53, 120, 10, progress);
  Heltec.display->display();
}

/*
 * ####################################
 *  Menu Section
 * ####################################
 */

void i_gui_flush_input()
{
  // Serial.println("FLUSH START");
  Wire.requestFrom(CARDKB_ADDR, 1);
  Wire.read();
  // Serial.println("FLUSH END");
}

void i_gui_menu(String menu_title, String page, String menu0, String menu1, String menu2, String menu3, int pos)
{
  Heltec.display->clear();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(5, 5, menu_title);

  Heltec.display->drawLine(5, 17, 5 + 120, 17);

  Heltec.display->setTextAlignment(TEXT_ALIGN_RIGHT);
  Heltec.display->drawString(120, 5, page);

  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(15, 10 * 2 + 2, menu0);
  Heltec.display->drawString(15, 10 * 3 + 2, menu1);
  Heltec.display->drawString(15, 10 * 4 + 2, menu2);
  Heltec.display->drawString(15, 10 * 5 + 2, menu3);

  Heltec.display->display();

  pos += 2;

  for (int i = 1; i <= 4; i += 1)
  {
    Heltec.display->drawCircle(7, 10 * pos + 8, i);
    Heltec.display->display();
    delay(40);
  }

  //  for (int i = 1; i <= 6; i += 1) {
  //    Heltec.display -> drawLine(5, 10 * pos + 8, 5 + i, 10 * pos + 8);
  //    Heltec.display -> display();
  //    delay(20);
  //  }
}

int gui_selection(String menu_title, String menu_items[], int count_items, boolean disableShortcuts = false)
{

  // Serial.println("Got " + String(count_items) + " in menu onl");
  // Serial.println("Got " + String(count_items) + " in menu first '" + String(menu_items[0]) + "'");
  // Serial.println("Got " + String(count_items) + " in menu last '" + String(menu_items[count_items]) + "'");

  // for (int i = 0; i < count_items; i++) {
  //     String r = menu_items[i];
  //     Serial.println("Menu Item '" + r + "'");
  //   }

  // Serial.println("After Menu Item");

  i_gui_flush_input();

  //
  //  for(int i=0; i<count_items; i++) {
  //    Serial.println("Got " + String(i) + "\t: " + menu_items[i]);
  //  }

  int numPages = ceil((float)(count_items + 1) / 4);
  //  Serial.println("Num Items " + String(count_items));
  //  Serial.println("Num Pages " + String(numPages));

  boolean hasSelected = false;
  boolean hasChanged = true;
  int curSelected = 0;
  int curPage = 0;
  while (!hasSelected)
  {

    if (hasChanged)
    {
      curPage = floor((float)(curSelected) / 4);
      int curPageMaxItems = count_items - curPage * 4 + 1;
      int curOffset = curSelected - 4 * curPage;
      //  Serial.println();
      //  Serial.println("CurSel " + String(curSelected) + " '" + menu_items[curSelected] + "'");
      //  Serial.println("CurPage " + String(curPage));
      //  Serial.println("CurOffset " + String(curOffset`));
      //  Serial.println("CurPageItems " + String(curPageMaxItems));

      int outputNumber;
      String outputNumberStr;

      String menu0;
      outputNumber = curPage * 4 + 1;
      if (outputNumber > 9)
        outputNumberStr = "+";
      // else if (disableShortcuts) outputNumberStr = "";
      else
        outputNumberStr = String(curPage * 4 + 1);
      if (disableShortcuts)
        menu0 = menu_items[curPage * 4 + 0];
      else if (curPageMaxItems >= 1)
        menu0 = outputNumberStr + ": " + menu_items[curPage * 4 + 0];
      else
        menu0 = "";

      String menu1;
      outputNumber = curPage * 4 + 2;
      if (outputNumber > 9)
        outputNumberStr = "+";
      // else if (disableShortcuts) outputNumberStr = "";
      else
        outputNumberStr = String(curPage * 4 + 2);
      if (disableShortcuts)
        menu1 = menu_items[curPage * 4 + 1];
      else if (curPageMaxItems >= 2)
        menu1 = outputNumberStr + ": " + menu_items[curPage * 4 + 1];
      else
        menu1 = "";

      String menu2;
      outputNumber = curPage * 4 + 3;
      if (outputNumber > 9)
        outputNumberStr = "+";
      // else if (disableShortcuts) outputNumberStr = "";
      else
        outputNumberStr = String(curPage * 4 + 3);
      if (disableShortcuts)
        menu2 = menu_items[curPage * 4 + 2];
      else if (curPageMaxItems >= 3)
        menu2 = outputNumberStr + ": " + menu_items[curPage * 4 + 2];
      else
        menu2 = "";

      String menu3;
      outputNumber = curPage * 4 + 4;
      if (outputNumber > 9)
        outputNumberStr = "+";
      // else if (disableShortcuts) outputNumberStr = "";
      else
        outputNumberStr = String(curPage * 4 + 4);
      if (disableShortcuts)
        menu3 = menu_items[curPage * 4 + 3];
      else if (curPageMaxItems >= 4)
        menu3 = outputNumberStr + ": " + menu_items[curPage * 4 + 3];
      else
        menu3 = "";

      i_gui_menu(menu_title, "(" + String(curPage + 1) + "/" + String(numPages) + ")", menu0, menu1, menu2, menu3, curOffset);
      hasChanged = false;
    }

    Wire.requestFrom(CARDKB_ADDR, 1);
    while (Wire.available())
    {
      char c = Wire.read();
      if (c != 0)
      {
        if (c == 0xB6)
        { // Press Up
          curSelected += 1;
          hasChanged = true;
        }
        if (c == 0xB5)
        { // Press Down
          curSelected -= 1;
          hasChanged = true;
        }
        if (curSelected < 0)
          curSelected = count_items;
        if (curSelected > count_items)
          curSelected = 0;

        if (c == 0xD)
          hasSelected = true; // Press Enter

        if (c == '1' and count_items + 1 >= 1)
        {
          curSelected = 0;
          hasSelected = true;
        }
        if (c == '2' and count_items + 1 >= 2)
        {
          curSelected = 1;
          hasSelected = true;
        }
        if (c == '3' and count_items + 1 >= 3)
        {
          curSelected = 2;
          hasSelected = true;
        }
        if (c == '4' and count_items + 1 >= 4)
        {
          curSelected = 3;
          hasSelected = true;
        }
        if (c == '5' and count_items + 1 >= 5)
        {
          curSelected = 4;
          hasSelected = true;
        }
        if (c == '6' and count_items + 1 >= 6)
        {
          curSelected = 5;
          hasSelected = true;
        }
        if (c == '7' and count_items + 1 >= 7)
        {
          curSelected = 6;
          hasSelected = true;
        }
        if (c == '8' and count_items + 1 >= 8)
        {
          curSelected = 7;
          hasSelected = true;
        }
        if (c == '9' and count_items + 9 >= 9)
        {
          curSelected = 8;
          hasSelected = true;
        }
      }
    }
  }

  return curSelected;
}

/*
 * ####################################
 *  Input Section
 * ####################################
 */

void i_gui_input_single_line(String menu_title, String val, int current_cursor)
{

  int c_chars_per_line = 3;

  int val_length = val.length() + 1; // Add 1 for cursor

  int num_lines = ceil((float)val_length / c_chars_per_line);

  String pre = val.substring(0, current_cursor);
  String post = val.substring(current_cursor, val.length());

  val = pre + "_" + post;

  String outStringLines[num_lines] = "";
  int newLineBreakCounter = 0;
  int currentNumLine = 0;

  for (int i = 0; i < val_length; i++)
  {

    outStringLines[currentNumLine] = outStringLines[currentNumLine] + val[i];
    newLineBreakCounter++;

    if (newLineBreakCounter == c_chars_per_line)
    {
      currentNumLine++;
      newLineBreakCounter = 0;
    }
  }

  int current_line_cursor = ceil((float)current_cursor / c_chars_per_line);

  // Serial.println("\n'" + pre + "' '" + post + "' '" + val + "'");
  // Serial.println("Num Of Lines " + String(num_lines));
  // Serial.println("Current Num Line Cursor " + String(current_line_cursor));

  // for(int i = 0; i<num_lines; i++) {
  //   Serial.println("Line " + String(i) + ": '" + outStringLines[i] + "'");
  // }

  int firstLine = current_line_cursor - 1;
  int secondLine = current_line_cursor;

  String out = "";

  if (num_lines == 1)
    out = outStringLines[0];
  else
  {
    if (firstLine < 0)
    {
      firstLine = 0;
      secondLine = 1;
    }
    if (secondLine > num_lines - 1)
    {
      firstLine = num_lines - 2;
      secondLine = num_lines - 1;
    }
    out = outStringLines[firstLine] + "\n" + outStringLines[secondLine];
  }

  Heltec.display->clear();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(5, 5, menu_title);

  Heltec.display->drawLine(5, 17, 5 + 120, 17);

  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(5, 10 * 2 + 2, "'" + out + "'");

  Heltec.display->setTextAlignment(TEXT_ALIGN_RIGHT);
  Heltec.display->drawString(128 - 5, 64 - 15, "[Enter] Ok");

  Heltec.display->display();
}

String gui_input_text(String menu_title, String default_value)
{

  i_gui_flush_input();

  String current = default_value;
  int current_length = current.length();
  int current_cursor = current_length;

  boolean hasSelected = false;
  while (!hasSelected)
  {

    i_gui_input_single_line(menu_title, current, current_cursor);

    Wire.requestFrom(CARDKB_ADDR, 1);
    while (Wire.available())
    {
      char c = Wire.read();
      if (c != 0)
      {
        // Serial.println();
        // Serial.println(c, HEX);
        // Serial.println("Current Length: " + String(current_length));
        // Serial.println("Current Cursor: " + String(current_cursor));
        if (c == 0x8) // Press Rm
        {
          if (current_length != 0)
          {
            // current.remove(current_length - 1, 1);
            current = current.substring(0, current_cursor - 1) + current.substring(current_cursor, current_length);
            current_length--;
            current_cursor--;
          }
        }
        else if (c == 0xB4 or c == 0xB7) // Press Left or right
        {
          if (c == 0xB4) // Press Left
            current_cursor -= 1;
          else // Press Right
            current_cursor += 1;

          if (current_cursor < 0)
            current_cursor = 0;
          else if (current_cursor > current_length)
            current_cursor = current_length;
        }
        else if (c == 0xD) // Press Enter
          hasSelected = true;
        else if (c != 0xB5 and c != 0xB6) // Ignore Down and Up
        {
          // current += c;
          current = current.substring(0, current_cursor) + c + current.substring(current_cursor, current_length);
          current_length++;
          current_cursor++;
        }
      }
    }
  }

  return current;
}