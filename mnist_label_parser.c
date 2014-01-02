/*
 ============================================================================
 Name        : mnist_label_parser.c
 Author      : Afroz Mohiuddin
 Version     : 1
 Description : Parser for mnist label file.
 ============================================================================
 */

#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "hex_lib.h"
#include "macros.h"

// Usage
const char* kUsage = "./a.out input_file output_file";

int main(int argc, char** argv) {
  if (argc != 3) {
    printf("Usage: %s\n", kUsage);
    return 1;
  }
  FILE* input_file_pointer = fopen(argv[1], "r");
  CHECK_NOTNULL(input_file_pointer);
  
  char magic_number_bytes[4];
  CHECK(fread(magic_number_bytes, sizeof(char), 4, input_file_pointer));
  // If MSB is first then magic_number_bytes will be 0x00000801
  if (magic_number_bytes[2] == 0x08 && magic_number_bytes[3] == 0x01) {
    LOG_INFO("Little Endian : MSB first");
  } else if (magic_number_bytes[0] == 0x01 && magic_number_bytes[1] == 0x08) {
    // I haven't taken into account big indian-ness, yet.
    LOG_FATAL("Big Endian : MSB last");
  } else {
    LOG_FATAL("This doesn't correspond to a MNIST Label file.");
  }

  LOG_INFO("magic number: %d", hex_array_to_int(magic_number_bytes, 4));

  char number_of_images_bytes[4];
  CHECK(fread(number_of_images_bytes, sizeof(char), 4, input_file_pointer));
  LOG_INFO("number of labels: %d", hex_array_to_int(number_of_images_bytes, 4));

  // Open a file for dumping the labels.
  FILE* output_file_pointer = fopen(argv[2], "w");
  CHECK_NOTNULL(output_file_pointer);

  char label_byte;
  while (fread(&label_byte, sizeof(char), 1, input_file_pointer)) {
    int char_written = fprintf(output_file_pointer,
                               "%"PRId32"\n",
                               hex_char_to_int(label_byte));
    CHECK(char_written);
  }

  fclose(input_file_pointer);
  fclose(output_file_pointer);

  return 0;
}
