/*
 ============================================================================
 Name        : hex_lib.h
 Author      : Afroz Mohiuddin
 Version     : 1
 Description : Hexadecimal libraries. These assumes little endian.
 ============================================================================
 */

#ifndef __HEX_LIB_H__
#define __HEX_LIB_H__

#include <stdlib.h>

// 0xAB -> 0x0B
char lower_half(char input_byte);
// 0xAB -> 0x0A
char higher_half(char input_byte);

// Hex characters to int, i.e. 0x0 -> 0 .. OxF -> 15
int32_t hex_alphabet_to_int(char hex_char);

// Hex character to int.
// OxFF -> 255
int32_t hex_char_to_int(char hex_char);

// Byte array to integer.
// 0x 00 00 EA 60 --> 60,000
int32_t hex_array_to_int(char* byte_array, int32_t length);

#endif  /* __HEX_LIB_H__ */
