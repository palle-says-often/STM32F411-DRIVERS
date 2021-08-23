## USING THIS DRIVER

#### IMPORTANT INFORMATION




#### STEPS TO USE THIS KEYPAD

1. After making your hardware connections, replace the GPIO Ports and GPIO pins with the appropriate values
2. Initialize the keypad in the main.c file
3. to read a key, use the function keypad_readKeyInASCII() and assign it to a uint8_t type variable.
4. if you do not desire the output in ASCII format, use any of the given functions to convert them.
- NOTE: * is converted to 0x0E and # is converted to 0x0F

