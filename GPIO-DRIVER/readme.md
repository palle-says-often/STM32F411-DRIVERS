##STM32F411_GPIO_DRIVERS

### IMPORTANT INFORMATION

1. I have created this driver using MDK-ARM with only CMSIS Core and Device Startup
2. This driver is complete only for stm32f411 microcontroller, other MCUs might have more GPIO ports and thus no code is present for them.
3. I havent made the driver for GPIOE and GPIOH.


### USING THIS DRIVER

1. The driver exposed APIs are mentioned and explained in the header file and examples of some functions are present in the main.c file.
2. This driver is compatible with other stm32f4 MCUs as well but only GPIOA to GPIOD peripherals are accessible.

### NOTE: ABOUT THE PERIPHERAL CLOCK

1. There is a seperate function in the driver for enabling the clock of the peripheral used.
2. There is no requirement of calling this seperately, it is already present in the init_pin function.
##### CORRECT WAY TO ENABLE THE PERIPHERAL CLOCK:
- While defining your GPIO_InitTypedef variable in the main.c file, give the value of the portName variable in the structure as either PORTA, PORTB, PORTC or PORTD, which ever you are using.
- Example: We are using gpio port D ,
- GPIO_InitTypedef gpioInit;
- gpioInit.PortName = PORTD;

3. If you dont want to use this way of enabling the GPIO peripheral clocks, feel free to comment it out in line 62 of the stm32f411xe_gpio_driver.c file

