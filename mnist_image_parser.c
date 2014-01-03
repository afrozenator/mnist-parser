/*
 ============================================================================
 Name        : mnist_image_parser.c
 Author      : Afroz Mohiuddin
 Version     : 1
 Description : Parser for mnist image db file.
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
  // If MSB is first then magic_number_bytes will be 0x00000803
  if (magic_number_bytes[2] == 0x08 && magic_number_bytes[3] == 0x03) {
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
  int32_t number_of_images = hex_array_to_int(number_of_images_bytes, 4);
  LOG_INFO("number of images: %d", number_of_images);

  int32_t num_rows = 0, num_cols = 0;
  char num_row_cols[4];
  CHECK(fread(num_row_cols, sizeof(char), 4, input_file_pointer));
  num_rows = hex_array_to_int(num_row_cols, 4);
  CHECK(fread(num_row_cols, sizeof(char), 4, input_file_pointer));
  num_cols = hex_array_to_int(num_row_cols, 4);
  LOG_INFO("pixel rows: %d and pixel columns: %d", num_rows, num_cols);

  FILE* output_file_pointer = fopen(argv[2], "w");
  CHECK_NOTNULL(output_file_pointer);

  int32_t num_pixles_in_image = num_cols * num_rows;
  char images_pixels_bytes[num_pixles_in_image];
  int images_done = 0;
  while (images_done++ < number_of_images) {
    CHECK(fread(images_pixels_bytes, sizeof(char), num_pixles_in_image,
                input_file_pointer));
    int32_t idx = 0;
    for (idx = 0; idx < num_pixles_in_image; ++idx) {
      int32_t image_pixel_value = hex_char_to_int(images_pixels_bytes[idx]);
      int char_written =
          fprintf(output_file_pointer, "%"PRId32" ", image_pixel_value);
      CHECK(char_written);

      // A graphic of the number this represents.
      if (idx % num_cols == 0) printf("\n");
      if (image_pixel_value < 10) {
        printf(".");
      } else {
        printf("*");
      }
    }
    printf("\n----------------------------------------------------------\n");
    fprintf(output_file_pointer, "\n");
  }

  fclose(input_file_pointer);
  fclose(output_file_pointer);
}
