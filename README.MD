# ⏰ ESP32 Hourly LED Timer – Eiffel Tower Decoration

This project uses an **XIAO ESP32C3** to control a relay (or MOSFET) that powers an **LED Eiffel Tower decoration** for exactly **5 seconds at the top of every hour**.

It's optimized for **low power** operation using **deep sleep**, and automatically syncs time using **NTP** with correct handling for **Eastern Time and Daylight Saving**.

## ✨ Features

- Turns on an output (relay, LED, etc.) for 5 seconds at the top of every hour
- Syncs time via NTP (Internet time servers)
- Automatically adjusts for Daylight Saving Time (US Eastern)
- Enters deep sleep between activations for maximum battery life
- Wi-Fi connection only used briefly when syncing

## 🛠️ PlatformIO Setup

This project is configured for **PlatformIO** with the **XIAO ESP32-C3** board.

### Prerequisites

1. **Install PlatformIO IDE Extension** (recommended for VS Code):

   - Open VS Code
   - Go to Extensions (Ctrl+Shift+X)
   - Search for "PlatformIO IDE"
   - Install the extension

2. **Install PlatformIO Core** (if not using VS Code):

   ```bash
   pip install platformio
   ```

### Board Setup

The **XIAO ESP32-C3** is a compact development board with:

- **ESP32-C3** RISC-V processor
- **4MB Flash** memory
- **400KB SRAM**
- **USB-C** connector for programming
- **11 GPIO pins** (including 10-bit ADC)
- **Built-in LED** on GPIO10

### Project Structure

```
eiffle-tower-esp32/
├── platformio.ini          # PlatformIO configuration
├── src/
│   ├── main.cpp            # Main application code
│   ├── secrets.h           # Wi-Fi credentials (create from template)
│   └── secrets_template.h  # Template for Wi-Fi credentials
├── .gitignore              # Git ignore rules
└── README.MD               # This file
```

## ⚙️ Configuration

### 🔐 Wi-Fi Credentials

This project uses a `secrets.h` file to store Wi-Fi credentials.  
To run it, copy `src/secrets_template.h` to `src/secrets.h` and fill in your own values:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

### 🔧 Hardware Connections

- **Output Pin**: GPIO10 (built-in LED on XIAO ESP32-C3)
- **Power**: USB-C or external 3.3V supply
- **Optional**: Connect external relay/MOSFET to GPIO10 for higher current loads

## 🚀 Building and Uploading

### Using PlatformIO IDE (VS Code)

1. **Open the project** in VS Code
2. **Connect your XIAO ESP32-C3** via USB-C
3. **Click the PlatformIO icon** in the sidebar
4. **Select your environment**: `seeed_xiao_esp32c3`
5. **Use the toolbar buttons**:
   - 🔨 **Build** - Compile the project
   - ➡️ **Upload** - Upload to board
   - 🔌 **Monitor** - View serial output
   - 🧹 **Clean** - Clean build files

### Board Selection

If PlatformIO doesn't automatically detect your board:

1. **Check USB connection** and drivers
2. **Select correct port** in PlatformIO IDE
3. **Verify board selection** in `platformio.ini`:
   ```ini
   board = seeed_xiao_esp32c3
   ```

### Using PlatformIO CLI

1. **Build the project**:

   ```bash
   pio run
   ```

2. **Upload to board**:

   ```bash
   pio run --target upload
   ```

3. **Monitor serial output**:

   ```bash
   pio device monitor
   ```

4. **Build and upload in one command**:
   ```bash
   pio run --target upload --target monitor
   ```

## 📊 Serial Monitor

The project outputs detailed information via Serial Monitor at **115200 baud**:

- Wi-Fi connection status
- Time synchronization details
- Current time and countdown to next activation
- Sleep duration calculations
- Activation confirmations

## 🔋 Power Management

The XIAO ESP32-C3 is optimized for low-power operation:

- **Deep Sleep Mode**: ~10µA current draw
- **Active Mode**: ~150mA during Wi-Fi and activation
- **Battery Life**: Months of operation on a single charge (1000mAh+ battery)
- **Wake-up**: Timer-based wake-up every hour

## 🐛 Troubleshooting

### Common Issues

1. **Upload fails**:

   - Check USB cable and drivers
   - Hold BOOT button during upload
   - Verify board selection in `platformio.ini`

2. **Wi-Fi connection fails**:

   - Verify credentials in `src/secrets.h`
   - Check Wi-Fi signal strength
   - Ensure 2.4GHz network (ESP32-C3 doesn't support 5GHz)

3. **Time sync issues**:
   - Check internet connection
   - Verify NTP server accessibility
   - Check timezone configuration

### Debug Information

Enable debug output by modifying `platformio.ini`:

```ini
build_flags =
    -DCORE_DEBUG_LEVEL=5  # Maximum debug output
```

## 📝 License

This project is open source. Feel free to modify and distribute.

## 🤝 Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.
