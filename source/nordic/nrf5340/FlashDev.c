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

/** @file FlashDev.c */

#include "FlashOS.h"

#define FLASH_DRV_VERS (0x0100+VERS)   // Driver Version, do not modify!

#if NRF5340_APP
#define DEVICE_NAME    "nRF5340_APP"

struct FlashDevice const FlashDevice = {
    FLASH_DRV_VERS,             // Driver Version, do not modify!
    DEVICE_NAME,                // Device Name (128 chars max)
    ONCHIP,                     // Device Type
    0x00000000,                 // Device Start Address
    0x00100000,                 // Device Size
    4096,                       // Programming Page Size
    0x00000000,                 // Reserved, must be 0
    0xFF,                       // Initial Content of Erased Memory
    100,                        // Program Page Timeout 100 mSec
    3000,                       // Erase Sector Timeout 3000 mSec
    {
        {0x00100000, 0x00000000}, // 1524 KBs of flash
        {0x00001000, 0x00FF8000}, // 1KB UICR
        {SECTOR_END}            // Marks end of sector table
    }
};
#elif NRF5340_NET
#define DEVICE_NAME    "nRF5340_NET"

struct FlashDevice const FlashDevice = {
    FLASH_DRV_VERS,             // Driver Version, do not modify!
    DEVICE_NAME,                // Device Name (128 chars max)
    ONCHIP,                     // Device Type
    0x00000000,                 // Device Start Address
    0x00040000,                 // Device Size
    2048,                       // Programming Page Size
    0x00000000,                 // Reserved, must be 0
    0xFF,                       // Initial Content of Erased Memory
    100,                        // Program Page Timeout 100 mSec
    3000,                       // Erase Sector Timeout 3000 mSec
    {
        {0x00040000, 0x01000000}, // 1524 KBs of flash
        {0x00001000, 0x01FF8000}, // 1KB UICR
        {SECTOR_END}            // Marks end of sector table
    }
};
#endif