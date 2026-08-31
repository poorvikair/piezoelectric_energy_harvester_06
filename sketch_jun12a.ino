#include <Wire.h>

#define LCD_ADDR 0x27
#define LCD_BACKLIGHT 0x08
#define ENABLE_BIT    0x04
#define RS_BIT        0x01

const int PIEZO_PIN = A0;
const int THRESHOLD = 100;
const unsigned long DEBOUNCE_MS = 300;

unsigned long footfallCount = 0;
unsigned long lastStepTime = 0;
int peakValue = 0;

void lcdSendNibble(uint8_t nibble, uint8_t mode) {
    uint8_t data = (nibble & 0xF0) | LCD_BACKLIGHT | mode;
    Wire.beginTransmission(LCD_ADDR);
    Wire.write(data | ENABLE_BIT);
    Wire.endTransmission();
    delayMicroseconds(1);
    Wire.beginTransmission(LCD_ADDR);
    Wire.write(data & ~ENABLE_BIT);
    Wire.endTransmission();
    delayMicroseconds(50);
}

void lcdSendByte(uint8_t value, uint8_t mode) {
    lcdSendNibble(value & 0xF0, mode);
    lcdSendNibble((value << 4) & 0xF0, mode);
}

void lcdCommand(uint8_t cmd) {
    lcdSendByte(cmd, 0x00);
}

void lcdWrite(uint8_t ch) {
    lcdSendByte(ch, RS_BIT);
}

void lcdInit() {
    Wire.begin();
    delay(50);
    lcdSendNibble(0x30, 0); delay(5);
    lcdSendNibble(0x30, 0); delay(1);
    lcdSendNibble(0x30, 0); delay(1);
    lcdSendNibble(0x20, 0); delay(1);
    lcdCommand(0x28);
    lcdCommand(0x0C);
    lcdCommand(0x06);
    lcdCommand(0x01);
    delay(2);
}

void lcdSetCursor(uint8_t col, uint8_t row) {
    uint8_t offsets[] = {0x00, 0x40};
    lcdCommand(0x80 | (col + offsets[row]));
}

void lcdClear() {
    lcdCommand(0x01);
    delay(2);
}

void lcdPrint(const char* str) {
    while (*str) lcdWrite(*str++);
}

void lcdPrintFloat(float val, int decimals) {
    char buf[10];
    dtostrf(val, 4, decimals, buf);
    lcdPrint(buf);
}

void lcdPrintLong(unsigned long val) {
    char buf[12];
    ltoa(val, buf, 10);
    lcdPrint(buf);
}

void updateDisplay() {
    lcdSetCursor(0, 0);
    lcdPrint("Steps: ");
    lcdPrintLong(footfallCount);
    lcdPrint("      ");

    lcdSetCursor(0, 1);
    lcdPrint("Energy: ");
    float energyMj = footfallCount * 0.1;
    lcdPrintFloat(energyMj, 1);
    lcdPrint(" mJ   ");
}

void printStepInfo(int intensity) {
    Serial.print("Step #");
    Serial.print(footfallCount);
    Serial.print(" | Intensity: ");
    Serial.print(intensity);
    Serial.print(" | Estimated Energy: ");
    Serial.print(footfallCount * 0.1, 2);
    Serial.println(" mJ");
}

void setup() {
    Serial.begin(9600);
    lcdInit();

    lcdSetCursor(0, 0);
    lcdPrint("Footstep Energy");
    lcdSetCursor(0, 1);
    lcdPrint("Harvester Ready");
    delay(2000);
    lcdClear();
    updateDisplay();

    Serial.println("Footstep Energy Harvester Initialized");
    Serial.println("Step on the piezo sensor to begin...");
}

void loop() {
    int sensorValue = analogRead(PIEZO_PIN);
    unsigned long currentTime = millis();

    if (sensorValue > peakValue) {
        peakValue = sensorValue;
    }

    if (sensorValue > THRESHOLD) {
        if (currentTime - lastStepTime > DEBOUNCE_MS) {
            footfallCount++;
            lastStepTime = currentTime;
            updateDisplay();
            printStepInfo(sensorValue);
            peakValue = 0;
        }
    }

    delay(10);
}