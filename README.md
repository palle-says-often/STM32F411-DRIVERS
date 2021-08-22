# STM32F411-DRIVERS
Few drivers for stm32f411ve microcontroller. Also compatible with most stm32f4 microcontrollers!

-- IMPORTANT INFORMATION
	1)
	I have created these drivers on Keil MDK-ARM (uVision 5) using only CMSIS Core and Device Startup from Package installer
	2)
	Most of the drivers are still under progress. Few drivers you can use:
		GPIO driver (fully finished and functional!!!)
		16x2 LCD driver
		4x4 keypad driver
	3) The MAX-CLOCK-CONFIGURATION helps your STM32F411VE microcontroller to run at highest clock configuration allowed.
		(System clock @ 100MHz, AHB1 and APB2 @ 100MHz, APB1 @ 50MHz etc)
		More information in the folder's README