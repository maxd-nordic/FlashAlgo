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

/** @file FlashPrg.c */

#include "FlashOS.h"
#include "FlashPrg.h"

#if NRF5340_APP
#define UICR_BASE_ADDR            (0x00FF8000)
#define FLASH_REG_BASE_ADDR       (0x50039000)
#elif NRF5340_NET
#define UICR_BASE_ADDR            (0x01FF8000)
#define FLASH_REG_BASE_ADDR       (0x41080000)
#endif

#define FLASH_REG_CONFIG          *((volatile uint32_t*)(FLASH_REG_BASE_ADDR + 0x504))
#define FLASH_REG_READY           *((volatile uint32_t*)(FLASH_REG_BASE_ADDR + 0x400))
#define FLASH_REG_ERASEALL        *((volatile uint32_t*)(FLASH_REG_BASE_ADDR + 0x50C))

static void wait_ready(void)
{
    while (1) {
        uint32_t ready = FLASH_REG_READY;
        if (ready == 1) {
            break;
        }
    }
}

uint32_t Init(uint32_t adr, uint32_t clk, uint32_t fnc)
{
    return 0;
}

uint32_t UnInit(uint32_t fnc)
{
    return 0;
}

uint32_t EraseChip(void)
{
    FLASH_REG_CONFIG = 2; // erase enable
    wait_ready();
    FLASH_REG_ERASEALL = 1;
    wait_ready();
    FLASH_REG_CONFIG = 0;

    return 0;
}

uint32_t EraseSector(uint32_t adr)
{
    volatile uint32_t* pDest = (volatile uint32_t*)adr;
    FLASH_REG_CONFIG = 2; // erase enable
    wait_ready();
    *pDest = 0xFFFFFFFF;
    wait_ready();
    FLASH_REG_CONFIG = 0;
    return 0;
}

uint32_t ProgramPage(uint32_t adr, uint32_t sz, uint32_t *buf)
{
    volatile uint32_t* pDest = (volatile uint32_t*)adr;
    volatile uint32_t* pSrc = (volatile uint32_t*)buf;
    uint32_t NumWords = sz >> 2;

    FLASH_REG_CONFIG = 1; // write enable

    wait_ready();

    for (uint32_t i = 0; i < NumWords; i++)
    {
        *pDest++ = *pSrc++;
    }

    wait_ready();

    FLASH_REG_CONFIG = 0;

    return 0;
}
