# Piezoelectric Energy Harvester 🔋⚡

A footstep energy harvesting system that converts mechanical vibrations from footsteps into electrical energy using piezoelectric sensors. The system detects steps in real-time, counts them, and displays estimated energy generation on an LCD display.

## Project Overview

This project demonstrates how piezoelectric sensors can be used to harvest energy from everyday activities like walking. It's an eco-friendly way to generate small amounts of electrical energy that can be stored or used to power low-energy devices.

**Key Application**: Converting human movement into usable electrical energy for sustainable power generation.

## Features

✨ **Core Functionality:**
- Real-time footstep detection and counting
- Automatic debouncing to avoid false counts (300ms threshold)
- Energy estimation in millijoules (mJ)
- Live LCD display showing step count and total energy
- Serial monitor output with detailed step information
- Adjustable sensitivity for different environments

## Hardware Components

### Components Used:
- **Arduino Microcontroller** (Uno/Nano/Mega)
- **4x Piezoelectric Sensors** (arranged in a 2x2 matrix pattern on wooden base)
- **16x2 I2C LCD Display** (real-time feedback)
- **Breadboard & Jumper Wires** (circuit prototyping)
- **Connecting wires** (red, green, blue, yellow, purple)
- **Wooden/Cork Base** (mounting surface for sensors)

### Piezoelectric Sensor Configuration:
The four piezoelectric sensors are connected in parallel on a wooden stepping platform:
```
    [Sensor 1]  [Sensor 2]
         |            |
         └─────┬──────┘
               |
          [Sensor 3]  [Sensor 4]
               |            |
               └─────┬──────┘
                     |
              Analog Input A0
```

### Wiring Diagram:
```
Piezoelectric Sensors (4x in parallel) → Arduino Pin A0 (Analog Input)

I2C LCD Display:
  - SDA → Arduino A4 (SDA)
  - SCL → Arduino A5 (SCL)
  - VCC → 5V
  - GND → GND

Power: Arduino powered via USB or external 5V supply
```

## Software Configuration

### Key Parameters:
```cpp
const int PIEZO_PIN = A0;              // Analog sensor input pin
const int THRESHOLD = 100;             // Step detection threshold (adjustable)
const unsigned long DEBOUNCE_MS = 300; // Debounce delay in milliseconds
```

### Energy Calculation:
```
Energy per step = 0.1 mJ (configurable based on actual piezo output)
Total Energy = Number of Steps × 0.1 mJ
```

## How It Works

1. **Sensor Reading**: Continuously reads analog values from the piezoelectric sensor array
2. **Peak Detection**: Identifies peaks above the threshold value when foot pressure is applied
3. **Debouncing**: Ignores multiple signals within 300ms to count each step only once
4. **Energy Calculation**: Estimates energy harvested (0.1 mJ per step)
5. **Display Update**: Shows real-time step count and total energy on LCD
6. **Serial Output**: Prints detailed information to Serial Monitor for debugging/analysis

## Display Output

### LCD Display (16x2):
```
Line 1: Steps: [count]
Line 2: Energy: [value] mJ
```

### Serial Monitor (9600 baud):
```
Step #1 | Intensity: 250 | Estimated Energy: 0.10 mJ
Step #2 | Intensity: 245 | Estimated Energy: 0.20 mJ
Step #3 | Intensity: 268 | Estimated Energy: 0.30 mJ
```

## Installation & Setup

### Step 1: Hardware Assembly
1. Mount 4 piezoelectric sensors on the wooden/cork base in a 2x2 pattern
2. Connect sensors in parallel to Arduino Pin A0
3. Connect I2C LCD Display to Arduino (SDA: A4, SCL: A5)
4. Connect power supply to Arduino (USB or 5V external)

### Step 2: Software Installation
1. Open `sketch_jun12a.ino` in Arduino IDE
2. Ensure Wire library is installed (comes default with Arduino IDE)
3. Select correct board type and COM port
4. Upload sketch to Arduino

### Step 3: Testing
1. Open Serial Monitor (Tools → Serial Monitor) at 9600 baud
2. Step on the piezoelectric platform
3. Watch the LCD display and Serial Monitor for step counts and energy readings

## Calibration & Tuning

### Adjusting Sensitivity:
- **Increase THRESHOLD** (e.g., 150): Fewer false positives, requires harder steps
- **Decrease THRESHOLD** (e.g., 50): More sensitive, may detect vibrations/taps

### Adjusting Debounce Time:
- **Increase DEBOUNCE_MS** (e.g., 500): Better for slower step rates
- **Decrease DEBOUNCE_MS** (e.g., 200): Better for faster step rates

### Energy Calculation:
Modify the energy value based on actual measurements:
```cpp
float energyMj = footfallCount * 0.1; // Change 0.1 to your calibrated value
```

## Performance Characteristics

- **Step Detection Range**: ~50-300 intensity units (adjustable)
- **Response Time**: <10ms per reading
- **Debounce Delay**: 300ms (configurable)
- **Display Refresh**: Updates with each detected step
- **Serial Output**: Real-time data at 9600 baud

## Code Structure

### Main Functions:
- `lcdInit()` - Initialize I2C LCD display
- `lcdCommand()` - Send command to LCD
- `lcdWrite()` - Write character to LCD
- `lcdPrint()` - Print string to LCD
- `lcdPrintLong()` - Print step count
- `lcdPrintFloat()` - Print energy value
- `updateDisplay()` - Update LCD with current data
- `printStepInfo()` - Output step details to Serial
- `loop()` - Main sensing and processing loop

## Future Enhancements

- 📊 **Data Logging**: Save step data to SD card for analysis
- 🔋 **Battery Monitoring**: Track stored energy in a capacitor/battery
- 📡 **Wireless Transmission**: Send data via Bluetooth/WiFi
- 🌡️ **Temperature Compensation**: Adjust for environmental factors
- 📈 **Multi-Sensor Array**: Increase sensor count for better accuracy
- 🎯 **Machine Learning**: Differentiate between walking patterns

## Troubleshooting

### LCD Display Not Showing:
- Check I2C address (default: 0x27) using I2C Scanner
- Verify SDA/SCL connections
- Check power supply to LCD

### No Step Detection:
- Verify piezo sensor connection to A0
- Check THRESHOLD value (may be too high)
- Test sensor with Serial Monitor to see analog readings
- Ensure sensors are properly mounted for contact pressure

### Multiple Counts per Step:
- Increase DEBOUNCE_MS value
- Raise THRESHOLD to filter noise

### Inconsistent Energy Readings:
- Calibrate energy factor (0.1 mJ value)
- Ensure even pressure distribution across sensors
- Check sensor wiring for loose connections

## Project Photos

The system consists of:
- **Wooden Platform**: Cork/wood base mounting the 4 piezoelectric sensors
- **Sensor Array**: 2x2 arrangement with color-coded wiring
- **Arduino & Breadboard**: Central electronics for signal processing
- **LCD Display**: Real-time data output module

## Technical Specifications

| Parameter | Value |
|-----------|-------|
| Sensors | 4x Piezoelectric (Parallel) |
| Input Voltage | 5V |
| Analog Resolution | 10-bit (0-1023) |
| Detection Threshold | 100 (configurable) |
| Debounce Time | 300ms (configurable) |
| LCD Type | 16x2 I2C |
| LCD Address | 0x27 |
| Serial Baud Rate | 9600 |
| Update Rate | 100ms (10Hz) |

## License

This project is open source and available for educational and research purposes.

## Author

**poorvikair**

---

**Last Updated**: August 2026

**Status**: ✅ Active & Functional

Feel free to fork, modify, and contribute to this project!
