# ⏰ ESP32 Hourly LED Timer – Eiffel Tower Decoration

This project uses an **XIAO ESP32C3** to control a relay (or MOSFET) that powers an **LED Eiffel Tower decoration** for exactly **5 seconds at the top of every hour**.

It’s optimized for **low power** operation using **deep sleep**, and automatically syncs time using **NTP** with correct handling for **Eastern Time and Daylight Saving**.

## ✨ Features

- Turns on an output (relay, LED, etc.) for 5 seconds at the top of every hour
- Syncs time via NTP (Internet time servers)
- Automatically adjusts for Daylight Saving Time (US Eastern)
- Enters deep sleep between activations for maximum battery life
- Wi-Fi connection only used briefly when syncing

## ⚙️ Setup

### 🔐 Wi-Fi Credentials

This project uses a `secrets.h` file to store Wi-Fi credentials.  
To run it, copy `secrets_template.h` to `secrets.h` and fill in your own values.
