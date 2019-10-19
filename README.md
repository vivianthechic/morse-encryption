# morse-encryption
Encrypts or decrypts messages from files depending on arguments given when running the program in a terminal window.
Practice using malloc() and free(), as well as pointers.

## main function
Arguments are parsed to determine encryption or decryption, input files, and output files.
Checks for valid arguments, uses arguments to call functions from hw2.c

## hw2 file
### Encryption
Reads input file and converts the message to morse code.
Creates key given the default keyphrase or given the keyphrase from the arguments.
Uses the key to encode the morse code message into the encrypted message.
### Decryption
Uses the key to decode the encrypted message into morse code, to then convert back into the original message.
Helper functions used from helpers2.c in both encryption and decryption functions.
