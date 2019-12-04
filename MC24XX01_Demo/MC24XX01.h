/* 
 * This file is part of the MC24XX01 Arduino Library.
 * Copyright (c) 2019 Michael Selinger.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * PINOUT
 * 
 *      -|*   |- VCC
 *      -|    |- WP
 *      -|    |- SCL (A5)
 *  VSS -|    |- SDA (A4)
 * 
 */

// Useful Stuff
#define CONTROL_CODE 0xA
#define PAGE_SIZE 8

class MC24XX01 {
  public:
    void init();
    uint8_t checkAvailable();
    uint8_t readByte(uint8_t address);
    uint8_t readSeqBytes(uint8_t start_address, uint8_t *data, uint8_t num_bytes);
    uint8_t writeByte(uint8_t address, uint8_t data);
    uint8_t writePage(uint8_t start_address, uint8_t *data, uint8_t num_bytes);
};
