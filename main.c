/*-------------------------------------------------------------------------------------------------------------
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT License. See https://go.microsoft.com/fwlink/?linkid=2090316 for license information.
 *-------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include "hello.h"

int main() 
{   
    printf("Version %d.%d.%d\n",
        HelloWorld_VERSION_MAJOR,
        HelloWorld_VERSION_MINOR,
        HelloWorld_VERSION_PATCH
    );
    
    return 0;
}