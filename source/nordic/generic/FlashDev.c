/* Flash OS Routines
 * Copyright (c) 2009-2015 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "FlashOS.h"
#include "nrfx.h"

#define FLASH_DRV_VERS (0x0100+VERS)   // Driver Version, do not modify!
#define DEVICE_NAME    "nRF53xx_app" //-> define in records
#define DEVICE_FLASH_START  0x00000000
#define DEVICE_FLASH_SIZE   0x00200000
#define UICR_BASE_ADDRESS ((uint32_t)NRF_UICR)
#define DEVICE_FLASH_PAGE_SIZE 4096

struct FlashDevice const FlashDevice  =  {
    FLASH_DRV_VERS,             // Driver Version, do not modify!
    DEVICE_NAME,                // Device Name
    ONCHIP,                     // Device Type
    DEVICE_FLASH_START,         // Flash start address
    DEVICE_FLASH_SIZE,          // Flash total size (512 KB)
    DEVICE_FLASH_PAGE_SIZE,     // Programming Page Size (4 bytes minimum write)
    0,                          // Reserved, must be 0
    0xFF,                       // Initial Content of Erased Memory
    100,                        // Program Page Timeout 100 mSec
    3000,                       // Erase Sector Timeout 3000 mSec
    {
        {DEVICE_FLASH_SIZE, DEVICE_FLASH_START}, // 512 KBs of flash
        {0x001000, UICR_BASE_ADDRESS}, // UICR
        {SECTOR_END}            // Marks end of sector table
    }
};
