/* 
 * @description main script for UFC controller board assumed to be an Arduino Leonardo
 * @author Jeff Underdown <jeff.underdown@gmail.com>
 * 
 * notes from DCS BIOS author:
 *      default: '#define DCSBIOS_IRQ_SERIAL'
 *      use '#define DCSBIOS_DEFAULT_SERIAL' instead if your Arduino board
 *      does not feature an ATMega328 or ATMega2650 controller.
 * 
 * my notes:
 *      my Arduino Leo has an ATmega32u4
 * 
 */
#define DCSBIOS_DEFAULT_SERIAL
#include "display-segment/constants.h"
#include "display-segment/functions.h"
#include "display-lcd/constants.h"
#include <DcsBios.h>
#include <LiquidCrystal_I2C.h>
#include <TimerEvent.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_CHARS_PER_LINE, LCD_LINE_COUNT);

/**
 * @description main program loop
 */
void loop() {
    DcsBios::loop();
}

/********************************* begin init functions *************************************/

/**
 * @description initializes output pins, serial connections and peripherals
 */
void setup() {
    delay(100);
    setupSegmentDisplays();
    delay(100);
    setupLCDDisplays();
    delay(100);
    DcsBios::setup();
}

/**
 * @description initializes backlit lcd display(s)
 */
void setupLCDDisplays() {
    // init backlit lcd 2 line screen
    lcd.init();
    lcd.backlight(); // enable backlight
    lcd.setCursor(0, 0); // set the cursor to column 0, line 0
    lcd.print("initializing..."); // Print a message to the LCD
    delay(500);
    lcd.clear();
}

/**
 * @description initializes 4 character 7 segment led displays
 */
void setupSegmentDisplays() {
    // set the pin mode to output for segment driver pins
    for (int i = 0; i < SEGMENT_DATA_LINES; i++) {
        pinMode(SEGMENT_DATA_PINS[i], OUTPUT);
    }
    // set the pin mode to output for segment driver pins
    for (int i = 0; i < SEGMENT_DIGIT_COUNT; i++) {
        pinMode(SEGMENT_DIGIT_PINS[i], OUTPUT);
    }
    // set pin mode to output for display address pins
    for (int i = 0; i < SEGMENT_ADDRESS_LINES; i++) {
        pinMode(SEGMENT_ADDRESS_PINS[i], OUTPUT);
    }

    
    printStringTo7SegmentDisplay("0000", 1); // print 0000 to display 1 (the 2nd display)
    delay(300);
    // printStringTo7SegmentDisplay("    ", 0);
}
/********************************** end init functions **************************************/

/**************************** begin DCS BIOS event handlers *********************************/

/**
 * @description handles output event to UFC options 1 - 4 digit 7 segment display
 */
void onUfcOptionDisplay1Change(char* newValue) {
    printStringTo7SegmentDisplay(newValue, 0);
}
DcsBios::StringBuffer<4> ufcOptionDisplay1Buffer(0x7432, onUfcOptionDisplay1Change);

/**
 * @description handles output event to UFC scratchpad big digit 1 display - 2 line lcd display
 */
void onUfcScratchpadString1DisplayChange(char* newValue) {
    lcd.setCursor(0, 0); // set the cursor to col 0, line 0
    lcd.print(newValue);  // Print a message to the LCD
}
DcsBios::StringBuffer<2> ufcScratchpadString1DisplayBuffer(0x744e, onUfcScratchpadString1DisplayChange);

/**
 * @description handles output event to UFC scratchpad big digit 2 display - 2 line lcd display
 */
void onUfcScratchpadString2DisplayChange(char* newValue) {
    lcd.setCursor(1, 0); // set the cursor to col 2, line 0
    lcd.print(newValue);  // Print a message to the LCD
}
DcsBios::StringBuffer<2> ufcScratchpadString2DisplayBuffer(0x7450, onUfcScratchpadString2DisplayChange);

/**
 * @description handles output event to UFC scratchpad number display - 2 line lcd display
 */
void onUfcScratchpadNumberDisplayChange(char* newValue) {
    int col = LCD_CHARS_PER_LINE - strlen(newValue);
    lcd.setCursor(col, 0); // set the cursor to col, line 0
    lcd.print(newValue);  // Print a message to the LCD
}
DcsBios::StringBuffer<8> ufcScratchpadNumberDisplayBuffer(0x7446, onUfcScratchpadNumberDisplayChange);

/***************************** end DCS BIOS event handlers **********************************/
