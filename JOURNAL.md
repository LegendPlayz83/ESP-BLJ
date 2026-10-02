---
title: "ESP-BLJ"
author: "adr"
description: "This is a bluetooth jammer using an ESP32 and two NRF24L01 modules, which can generate a 2.4 GHz spectrum signal, which could be used to interrupt bluetooth communications temporarily"
created_at: "2026-05-09"
---

# 2026-05-31: Code v2

**Total time spent: 1 hour**

(https://lapse.hackclub.com/timelapse/YrB5tWes4MFK)

# 2026-05-15: Code v1

**Total time spent: 0.67 hours**

The first version of firmware focuses on building a simple proof-of-concept RF scanner of two nRF24L01 connected over separate SPI buses. This version aimed to initialise both radios successfully and scan across the 2.4GHz spectrum to detect general wireless activities. :)

![Screenshot 2026-05-15 at 7.24.19 PM.png](https://cdn.hackclub.com/019e2bea-f124-70d9-a7c9-716f46f10fc1/Screenshot%202026-05-15%20at%207.24.19%E2%80%AFPM.png)

# 2026-05-10: Designed the circuit online!

**Total time spent: 1.5 hours**

I designed the circuit online on the Wokwi simulator. Since the website doesn't have the symbols for the nrf24l01-transceiver chip myself.
![nrf24l01.png](https://cdn.hackclub.com/019e102e-30de-7ea2-b834-b66bdfcee71f/nrf24l01.png)
code for the nrf24l01:
![nrf24l01-wokwi.png](https://cdn.hackclub.com/019e102f-1cae-74ae-9ef0-33b35e9c1ff9/nrf24l01-wokwi.png)

Final circuit:
![circuit.png](https://cdn.hackclub.com/019e102f-628b-7aa9-963b-5ac6ad36f6d8/circuit.png)

