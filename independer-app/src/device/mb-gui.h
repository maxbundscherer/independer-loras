#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define DISPLAY_WIDTH 128 // OLED display width, in pixels

#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define DISPLAY_HEIGHT 64 // OLED display height, in pixels

long c_patience_s = 5 * 60; // MAX TIME NO INPUT BEFORE SLEEP

// LED Power Pin
#define LED 25

#if USE_HELTEC
#define OLED_RESET 16
#define OLED_SDA 4
#define OLED_SCL 15
SSD1306Wire display(0x3c, OLED_SDA, OLED_SCL);
void gui_init_display()
{
  pinMode(OLED_RESET, OUTPUT);
  digitalWrite(OLED_RESET, HIGH);

  pinMode(LED, OUTPUT);

  display.init();
  display.setBrightness(state_oled_brightness);
  display.flipScreenVertically();
}
#else

#define OLED_RESET 4
#define OLED_SDA 21
#define OLED_SCL 22
SSD1306Wire display(0x3c, OLED_SDA, OLED_SCL);
void gui_init_display()
{

  pinMode(LED, OUTPUT);

  display.init();
  display.setBrightness(state_oled_brightness);
  display.flipScreenVertically();
}
#endif

void gui_set_screen_brightness(int br)
{
  display.setBrightness(br);
}

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

#define C_GUI_DELAY_MSG_VERY_SHORT_I 5
#define C_GUI_DELAY_MSG_SHORT_I 20
#define C_GUI_DELAY_MSG_MIDDLE_I 40
#define C_GUI_DELAY_MSG_LONG_I 60

#define C_GUI_CHARS_PER_LINE 25

/*
 * ####################################
 *  Test Section
 * ####################################
 */

void i_gui_test_drawLines()
{
  for (int16_t i = 0; i < DISPLAY_WIDTH; i += 4)
  {
    display.drawLine(0, 0, i, DISPLAY_HEIGHT - 1);
    display.display();
    delay(10);
  }
  for (int16_t i = 0; i < DISPLAY_HEIGHT; i += 4)
  {
    display.drawLine(0, 0, DISPLAY_WIDTH - 1, i);
    display.display();
    delay(10);
  }
  delay(250);

  display.clear();
  for (int16_t i = 0; i < DISPLAY_WIDTH; i += 4)
  {
    display.drawLine(0, DISPLAY_HEIGHT - 1, i, 0);
    display.display();
    delay(10);
  }
  for (int16_t i = DISPLAY_HEIGHT - 1; i >= 0; i -= 4)
  {
    display.drawLine(0, DISPLAY_HEIGHT - 1, DISPLAY_WIDTH - 1, i);
    display.display();
    delay(10);
  }
  delay(250);

  display.clear();
  for (int16_t i = DISPLAY_WIDTH - 1; i >= 0; i -= 4)
  {
    display.drawLine(DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1, i, 0);
    display.display();
    delay(10);
  }
  for (int16_t i = DISPLAY_HEIGHT - 1; i >= 0; i -= 4)
  {
    display.drawLine(DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1, 0, i);
    display.display();
    delay(10);
  }
  delay(250);
  display.clear();
  for (int16_t i = 0; i < DISPLAY_HEIGHT; i += 4)
  {
    display.drawLine(DISPLAY_WIDTH - 1, 0, 0, i);
    display.display();
    delay(10);
  }
  for (int16_t i = 0; i < DISPLAY_WIDTH; i += 4)
  {
    display.drawLine(DISPLAY_WIDTH - 1, 0, i, DISPLAY_HEIGHT - 1);
    display.display();
    delay(10);
  }
  delay(250);
}

// Adapted from Adafruit_SSD1306
void i_gui_test_drawRect(void)
{
  for (int16_t i = 0; i < DISPLAY_HEIGHT / 2; i += 2)
  {
    display.drawRect(i, i, DISPLAY_WIDTH - 2 * i, DISPLAY_HEIGHT - 2 * i);
    display.display();
    delay(10);
  }
}

// Adapted from Adafruit_SSD1306
void i_gui_test_fillRect(void)
{
  uint8_t color = 1;
  for (int16_t i = 0; i < DISPLAY_HEIGHT / 2; i += 3)
  {
    display.setColor((color % 2 == 0) ? BLACK : WHITE); // alternate colors
    display.fillRect(i, i, DISPLAY_WIDTH - i * 2, DISPLAY_HEIGHT - i * 2);
    display.display();
    delay(10);
    color++;
  }
  // Reset back to WHITE
  display.setColor(WHITE);
}

// Adapted from Adafruit_SSD1306
void i_gui_test_drawCircle(void)
{
  for (int16_t i = 0; i < DISPLAY_HEIGHT; i += 2)
  {
    display.drawCircle(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, i);
    display.display();
    delay(10);
  }
  delay(1000);
  display.clear();

  // This will draw the part of the circel in quadrant 1
  // Quadrants are numberd like this:
  //   0010 | 0001
  //  ------|-----
  //   0100 | 1000
  //
  display.drawCircleQuads(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, DISPLAY_HEIGHT / 4, 0b00000001);
  display.display();
  delay(200);
  display.drawCircleQuads(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, DISPLAY_HEIGHT / 4, 0b00000011);
  display.display();
  delay(200);
  display.drawCircleQuads(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, DISPLAY_HEIGHT / 4, 0b00000111);
  display.display();
  delay(200);
  display.drawCircleQuads(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, DISPLAY_HEIGHT / 4, 0b00001111);
  display.display();
}

void i_gui_test_buffer()
{

  // Initialize the log buffer
  // allocate memory to store 8 lines of text and 30 chars per line.
  display.setLogBuffer(5, 30);

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
    display.clear();
    // Print to the screen
    display.println(test[i]);
    // Draw it to the internal screen buffer
    display.drawLogBuffer(0, 0);
    // Display it on the screen
    display.display();
    delay(500);
  }
}

void gui_test()
{

  display.clear();

  i_gui_test_drawLines();
  delay(1000);
  display.clear();

  i_gui_test_drawRect();
  delay(1000);
  display.clear();

  i_gui_test_fillRect();
  delay(1000);
  display.clear();

  i_gui_test_drawCircle();
  delay(1000);
  display.clear();

  i_gui_test_buffer();
  delay(1000);
  display.clear();
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

void gui_logo_static(String version_string, String my_id, String gateway_id, boolean isActor, String gateway_owner)
{
  display.clear();
  display.drawXbm(0, 0, 128, 64, LOGO_bits);
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  if (isActor)
    display.drawString(8, 35, version_string + I18N_DEVICE_GUI_ACTOR + my_id + " -> " + gateway_id);
  else
    display.drawString(8, 35, version_string + I18N_DEVICE_GUI_GATEWAY + gateway_id + I18N_DEVICE_GUI_BY + gateway_owner);
  display.display();
}

/*
 * ####################################
 *  Msg Section
 * ####################################
 */

void gui_msg_animated(String msg_title, String msg, int i_delay)
{
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(5, 5, msg_title);

  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 10 * 2 + 2 + 4, msg);
  display.display();

  for (int i = 1; i <= 120; i += 1)
  {
    display.drawLine(5, 17, 5 + i, 17);
    display.display();
    delay(i_delay);
  }
}

void gui_msg_static(String msg_title, String msg)
{
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(5, 5, msg_title);
  display.drawLine(5, 17, 5 + 120, 17);

  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 10 * 2 + 2 + 4, msg);
  display.display();
}

void gui_msg_static_gateway(String msg_title, String msg, int tx_time)
{
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(5, 5, msg_title);
  display.drawLine(5, 17, 5 + 120, 17);

  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 10 * 2 + 2 + 4, msg);

  int progress = (((float)tx_time - 0) / ((float)(C_LORA_QUOTA_CONTINGENT_SECONDS * 1000) - 0)) * (float)100;
  if (progress > 100)
    progress = 100;
  if (progress < 0)
    progress = 0;

  display.drawProgressBar(0, 0 + 53, 120, 10, progress);

  display.display();
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
  display.clear();

  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(5, 5, menu_title);

  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 0 + 23, String(progress) + "%\n" + String(value) + " [" + String(min) + "; " + String(max) + "]");
  display.drawProgressBar(0, 0 + 53, 120, 10, progress);
  display.display();

  for (int i = 1; i <= 120; i += 1)
  {
    display.drawLine(5, 17, 5 + i, 17);
    display.display();
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
  display.clear();

  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(5, 5, menu_title);
  display.drawLine(5, 17, 5 + 120, 17);

  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 0 + 23, String(progress) + "%\n" + String(value) + " [" + String(min) + "; " + String(max) + "]");
  display.drawProgressBar(0, 0 + 53, 120, 10, progress);
  display.display();
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
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(5, 5, menu_title);

  display.drawLine(5, 17, 5 + 120, 17);

  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(120, 5, page);

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(15, 10 * 2 + 2, menu0);
  display.drawString(15, 10 * 3 + 2, menu1);
  display.drawString(15, 10 * 4 + 2, menu2);
  display.drawString(15, 10 * 5 + 2, menu3);

  display.display();

  pos += 2;

  for (int i = 1; i <= 4; i += 1)
  {
    display.drawCircle(7, 10 * pos + 8, i);
    display.display();
    delay(40);
  }
}

struct S_GUI_SELECTION_ITEM
{
  boolean success;
  int value;
};

S_GUI_SELECTION_ITEM gui_selection(String menu_title, String menu_items[], int count_items, boolean disableShortcuts = false)
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

  long patience_duration = 20; // millis
  long patience_counter = 0;

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
        // Input
        patience_counter = 0;
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
        if (c == 0x1B) // Press Escape
          return S_GUI_SELECTION_ITEM{false, -1};
      }
    }

    // No input
    if (state_auto_sleep_enabled)
    {
      delay(patience_duration);
      patience_counter = patience_counter + 1;
      if ((patience_counter * patience_duration) > (c_patience_s * 1000))
      {
        utils_go_to_sleep(true && state_is_registered_independer);
      }
    }
  }

  return S_GUI_SELECTION_ITEM{true, curSelected};
}

/*
 * ####################################
 *  Input Section
 * ####################################
 */

void i_gui_input_single_line(String menu_title, String val, int current_cursor)
{

  int c_chars_per_line = C_GUI_CHARS_PER_LINE;

  int val_length = val.length() + 1 + 2; // Add 1 for cursor and Add 2 for Start and Stop Mark

  int num_lines = ceil((float)val_length / c_chars_per_line);

  String pre = val.substring(0, current_cursor);
  String post = val.substring(current_cursor, val.length());

  val = "'" + pre + "_" + post + "'";

  String outStringLines[num_lines];
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

  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(5, 5, menu_title);

  display.drawLine(5, 17, 5 + 120, 17);

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(5, 10 * 2 + 2, out);

  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128 - 5, 64 - 15, I18N_DEVICE_GUI_ENTER_OK);

  display.display();
}

struct S_GUI_INPUT_TEXT
{
  boolean success;
  String value;
};

S_GUI_INPUT_TEXT gui_input_text(String menu_title, String default_value)
{

  i_gui_flush_input();

  String current = default_value;
  int current_length = current.length();
  int current_cursor = current_length;

  long patience_duration = 20; // millis
  long patience_counter = 0;

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
        // Input
        patience_counter = 0;
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
        else if (c == 0x1B) // Press Escape
          return S_GUI_INPUT_TEXT{false, ""};
        else if (c != 0xB5 and c != 0xB6) // Ignore Down and Up
        {
          // current += c;
          current = current.substring(0, current_cursor) + c + current.substring(current_cursor, current_length);
          current_length++;
          current_cursor++;
        }
      }
    }

    // No input
    if (state_auto_sleep_enabled)
    {
      delay(patience_duration);
      patience_counter = patience_counter + 1;
      if ((patience_counter * patience_duration) > (c_patience_s * 1000))
      {
        utils_go_to_sleep(true && state_is_registered_independer);
      }
    }
  }

  return S_GUI_INPUT_TEXT{true, current};
}

char gui_input_char_no_output(boolean displayOffFlag)
{

  if (displayOffFlag)
    display.displayOff();

  i_gui_flush_input();

  char ret_char;

  boolean hasSelected = false;
  while (!hasSelected)
  {

    Wire.requestFrom(CARDKB_ADDR, 1);
    while (Wire.available())
    {
      char c = Wire.read();
      if (c != 0)
      {
        ret_char = c;
        hasSelected = true;
      }
    }
  }

  if (displayOffFlag)
    display.displayOn();
  return ret_char;
}

/*
 * ####################################
 *  Long Text Section
 * ####################################
 */

void i_gui_msg_long_text(String msg_title, String msg, String page)
{

  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  display.drawString(5, 5, msg_title);
  display.drawLine(5, 17, 5 + 120, 17);

  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(120, 5, page);

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(5, 10 * 2 + 2, msg);

  display.display();
}

void gui_msg_long_text(String msg_title, String msg)
{

  i_gui_flush_input();

  int c_chars_per_line = C_GUI_CHARS_PER_LINE;
  int c_lines_per_page = 3;

  int val_length = msg.length() + 2; // Add 2 for Start and Stop Mark

  msg = "'" + msg + "'";

  int num_lines = ceil((float)val_length / c_chars_per_line);

  String outStringLines[num_lines];
  int newLineBreakCounter = 0;
  int currentNumLine = 0;

  for (int i = 0; i < val_length; i++)
  {

    outStringLines[currentNumLine] = outStringLines[currentNumLine] + msg[i];
    newLineBreakCounter++;

    if (newLineBreakCounter == c_chars_per_line)
    {
      currentNumLine++;
      newLineBreakCounter = 0;
    }
  }

  int num_pages = ceil((float)num_lines / c_lines_per_page);

  // Serial.println("\nNum of lines " + String(num_lines));
  // Serial.println("Num of pages " + String(num_pages));

  // for (int i = 0; i < num_lines; i++)
  // {
  //   Serial.println("Line " + String(i) + ": '" + outStringLines[i] + "'");
  // }

  long patience_duration = 20; // millis
  long patience_counter = 0;

  int currentPage = 0;
  boolean hasSelected = false;
  while (!hasSelected)
  {

    String t_msg = "";
    for (int i = currentPage * c_lines_per_page; i < num_lines; i++)
    {
      t_msg += outStringLines[i] + "\n";
    }

    i_gui_msg_long_text(msg_title, t_msg, "(" + String(currentPage + 1) + "/" + String(num_pages) + ")");

    Wire.requestFrom(CARDKB_ADDR, 1);
    while (Wire.available())
    {
      char c = Wire.read();
      if (c != 0)
      {
        // Input
        patience_counter = 0;
        if (c == 0xB5 or c == 0xB6) // Press Down or Up
        {
          if (c == 0xB5) // Press Down
            currentPage -= 1;
          else // Press Up
            currentPage += 1;

          if (currentPage < 0)
            currentPage = 0;
          else if (currentPage > num_pages - 1)
            currentPage = num_pages - 1;
        }
        else if (c == 0xD or c == 0x1B) // Press Enter or Escape
          hasSelected = true;
      }
    }

    // No input
    if (state_auto_sleep_enabled)
    {
      delay(patience_duration);
      patience_counter = patience_counter + 1;
      if ((patience_counter * patience_duration) > (c_patience_s * 1000))
      {
        utils_go_to_sleep(true && state_is_registered_independer);
      }
    }
  }
}

bool gui_dialog(String menu_title, String menu_desc)
{

  bool fin = false;
  S_GUI_SELECTION_ITEM i;

  while (!fin)
  {
    gui_msg_long_text(menu_title, menu_desc);

    String menu_items[] = {
        I18N_DIALOG_NO,
        I18N_DIALOG_YES,
        I18N_DIALOG_AGAIN};

    i = gui_selection(menu_title, menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (i.success and i.value != 2)
      fin = true;
  }

  return (i.value == 1);
}