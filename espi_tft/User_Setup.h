#define USER_SETUP_INFO "User_Setup"

// =========================================================================
// KART SEÇİMİ (Aşağıdaki iki satırdan SADECE BİRİNİ aktif bırak)
// =========================================================================
//#define BOARD_ESP32_OLD     // Eski ESP32 (CYD / ILI9341 240x320)
#define BOARD_ESP32_S3_35   // Yeni ESP32-S3 2.8" TE066 (ST7789 / 240x320)
// =========================================================================


#ifdef BOARD_ESP32_OLD
  // -----------------------------------------------------------------------
  // 1. AYAR: Standart ESP32 (Eski Kartın)
  // -----------------------------------------------------------------------
  #define ILI9341_DRIVER

  #define TFT_WIDTH  240
  #define TFT_HEIGHT 320

  #define TFT_INVERSION_OFF

  #define TFT_BL   27
  #define TFT_BACKLIGHT_ON HIGH

  #define ESP32_DMA
  #define TFT_MISO 12
  #define TFT_MOSI 13
  #define TFT_SCLK 14
  #define TFT_CS   15
  #define TFT_DC    2
  #define TFT_RST  -1

  #define TOUCH_CS 33
  #define TOUCH_OFFSET_ROTATION 1

  #define TFT_RGB_ORDER TFT_BGR
  #define USE_HSPI_PORT 
#elif defined(BOARD_ESP32_S3_35)
// -----------------------------------------------------------------------
// 2. AYAR: LCDWIKI 2.8" ESP32-S3 ES3C28P / ES3N28P
// LCD: ILI9341V - 240x320 IPS
// TOUCH: FT6336G - I2C
// -----------------------------------------------------------------------

#define ILI9341_DRIVER
#define USE_HSPI_PORT
#define TFT_WIDTH  240
#define TFT_HEIGHT 320

// LCDWIKI resmi pinout
#define TFT_MISO 13
#define TFT_MOSI 11
#define TFT_SCLK 12
#define TFT_CS   10
#define TFT_DC   46

// LCD reset, ESP32-S3 reset hattı ile ortak
#define TFT_RST -1

// Backlight
#define TFT_BL 45
#define TFT_BACKLIGHT_ON HIGH

// IPS ILI9341 için
#define TFT_RGB_ORDER TFT_BGR
#define TFT_INVERSION_ON

// Display SPI
#define SPI_FREQUENCY 55000000
#define SPI_READ_FREQUENCY 20000000

#endif


// =========================================================================
// ORTAK AYARLAR (Her iki kart için de geçerli olan font ve hızlar)
// =========================================================================
#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font
#define LOAD_FONT2  // Font 2. Small 16 pixel high font
#define LOAD_FONT4  // Font 4. Medium 26 pixel font
#define LOAD_FONT6  // Font 6. Large 48 pixel font
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font
#define LOAD_FONT8  // Font 8. Large 75 pixel font
#define LOAD_GFXFF  // FreeFonts

#define SMOOTH_FONT
#define SPI_FREQUENCY       20000000
#define SPI_READ_FREQUENCY  10000000
#define SPI_TOUCH_FREQUENCY   2500000

