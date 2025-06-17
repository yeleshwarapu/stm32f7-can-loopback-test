# STM32F7 CAN Loopback Test

## Overview
This project performs a loopback test on the CAN1 peripheral of an STM32F7 microcontroller (e.g., STM32F746G-DISCO board). It validates the send and receive paths using a single node and toggles an LED when transmission and reception succeed.

## Features
- STM32 HAL-based CAN implementation
- Standard ID (0x123), 8-byte payload
- Filter config to accept all messages
- Loopback verification with LED feedback

## Hardware Setup
- LED connected to GPIOB Pin 0
- STM32F7 board running at default clock config
- CAN1 in **loopback mode** (set via CubeMX or manually)

## How to Use
1. Import this into STM32CubeIDE
2. Ensure CAN1 is in loopback mode
3. Flash to your board
4. LED will toggle when message is received and validated

## License
MIT
