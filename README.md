# Embedded Peripheral Drivers

This repository provides basic driver functions for common microcontroller peripherals. It is designed to be lightweight and easy to integrate into embedded projects. Each peripheral module includes initialization routines and essential I/O operations.

## Features

### ✅ GPIO (General-Purpose Input/Output)
- Configure pins as input or output.
- Set pin mode: pull-up, pull-down, floating.
- Read digital input state.
- Write high/low to output pins.

### ✅ USART (Universal Synchronous/Asynchronous Receiver Transmitter)
- Serial communication with configurable baud rate.
- Support for 8N1 frame format (8 data bits, no parity, 1 stop bit).
- Polling-based transmit and receive functions.
- Optional: line-based receive parsing.

### ✅ I2C (Inter-Integrated Circuit)
- Master mode communication.
- Send/receive bytes to/from common slave devices (sensors, EEPROMs).
- Supports START, STOP, RESTART conditions.
- Acknowledge control after each byte.

### ✅ TIMER
- Basic timer setup for time base generation.
- Generate millisecond or microsecond delays.
- Schedule periodic tasks using timer overflow or compare events.

### ✅ PWM (Pulse Width Modulation)
- Timer-based PWM generation.
- Adjustable duty cycle (0–100%).
- Used for motor control, dimming LEDs, and more.
- Support for multiple PWM channels.

### ✅ ADC (Analog-to-Digital Converter)
- Single and multi-channel analog signal acquisition.
- Basic software-based filtering.

