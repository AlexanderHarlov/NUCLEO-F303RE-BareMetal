# NUCLEO-F303RE-BareMetal
This is a simple example of STM32F303RE Nucleo board development.
- LED and button control
- UART with IRQ for RXNE and DMA enabled for TX
- Systick and hardware timers (TIM2 is used as output compare to toggle the LED, and TIM3 has input capture
- ADC for temperature sensor (currently not working)
- I2C driver
- SPI driver
- ADXL365 accelerometer driver
