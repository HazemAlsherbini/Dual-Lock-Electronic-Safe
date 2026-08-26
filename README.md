# Dual-Verification Security Lock System

## 📌 Project Overview
This project is a robust embedded security system that combines digital keypad entry with analog dial verification for access control. Access is granted only when both conditions pass at the same moment — neither alone is sufficient.

## 🎥 Project Media & Demo
* **Simulation & Source Code:** [Google Drive Folder](https://drive.google.com/drive/folders/1kBnYrckhnnTPxcow9zH2G4hqQN9piQcm?usp=drive_link)

## 🏗️ System Architecture
The project is built using a professional Layered Embedded Architecture:
* **APP Layer:** Handles password verification, dial check, and change password logic.
* **HAL Layer:** Contains LCD and keypad driver abstractions, decoupling hardware from application code.
* **MCAL Layer:** Includes DIO and ADC microcontroller drivers operating at the register level.
* **LIB Layer:** Foundational utilities including `STD_TYPES` and `BIT_MATH` shared across all layers.

## ⚙️ Hardware Drivers & Features
* **LCD Driver:** Configured in 8-bit mode for reliable and high-speed alphanumeric data transmission to the display.
* **ADC Driver (Analog Dial):** Utilizes 10-bit resolution mapped and scaled from raw values into a Dial Value (0–99).
* **Keypad Driver:** Implements Matrix Scanning with software debounce to eliminate contact noise and false triggers.
* **DIO Driver:** Provides configurable pin direction and direct register access for all ports.

## 🚀 Security Logic Flow
* **Sequential Verification:** The system enforces strict sequential verification — password first, then dial position — before granting any access.
* **Attempt Limits & Lockout:** The system caps failed authentication attempts. After 3 consecutive failed attempts, the system completely locks down.
* **Buzzer / Alarm:** An audible alert and a red LED are triggered upon lockout for physical deterrence.
* **Master Password Override:** Once locked, the system can only be restored by entering a pre-configured Master Password.
