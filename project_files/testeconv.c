#include <stdio.h>
#include <stdlib.h>
#include "converteutf.h"

int main(void)
{

    FILE *entry_file;
    FILE *output_file;

    converteUtf8Para32(entry_file, output_file);

    return 0;
}