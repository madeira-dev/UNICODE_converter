#include <stdio.h>
#include <stdlib.h>
#include "converteutf.h"

int main(void)
{

    FILE *entry_file;
    FILE *output_file;

    entry_file = fopen("test_1", "rb");
    output_file = fopen("utf8_testFileOut", "wb");
    converteUtf8Para32(entry_file, output_file);
    fclose(entry_file);
    fclose(output_file);

    return 0;
}