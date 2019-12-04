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
 
#include<Wire.h>;
#include "MC24XX01.h";

/*
 * "Initialises" the Library
 */
void MC24XX01::init() {
  Wire.begin();
}

/*
 * Reads a single Byte from a given address
 */
uint8_t MC24XX01::readByte(uint8_t address) {
  Wire.beginTransmission((CONTROL_CODE << 3));
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom((CONTROL_CODE << 3),1);
  return Wire.read();
}
/*
 * Read data from the chip sequentially starting from a start address.
 * The data is stored in a provided array. Reads up to 32 Bytes at once
 */
uint8_t MC24XX01::readSeqBytes(uint8_t start_address, uint8_t *data, uint8_t num_bytes){
  if((start_address + num_bytes-1) > 127)
    return 0;
  // Set start address by making a random read
  Wire.beginTransmission((CONTROL_CODE << 3));
  Wire.write(start_address);
  Wire.endTransmission();
  Wire.requestFrom((CONTROL_CODE << 3),(int) num_bytes);
  for(uint8_t i=0; i< num_bytes; i++)
    data[i] = Wire.read();
  return 1;
}

/*
 * Writes a single Byte to a given memory address
 */
uint8_t MC24XX01::writeByte(uint8_t address, uint8_t data) {
  Wire.beginTransmission((CONTROL_CODE << 3));
  Wire.write(address);
  Wire.write(data);
  return Wire.endTransmission();
}

/*
 * Writes an array sequential to the memory starting at the given address during one transaction
 * Can only write up to 8 Bytes if start_address starts a new page
 * Returns number of actually writen bytes
 */
uint8_t MC24XX01::writePage(uint8_t start_address, uint8_t *data, uint8_t num_bytes){
  if((start_address + num_bytes) > 127)
    return 0;
  Wire.beginTransmission((CONTROL_CODE << 3));
  Wire.write(start_address);
  // Write only until the current page is full
  for(uint8_t i = 0; i< (num_bytes - (start_address % PAGE_SIZE));i++)
    Wire.write(data[i]);
  Wire.endTransmission();
  return (num_bytes - (start_address % PAGE_SIZE));
}

/*
 * Checks if the device is available or writing data.
 * Returns 0 if busy or 1 if available
 */
uint8_t MC24XX01::checkAvailable(){
  Wire.beginTransmission((CONTROL_CODE << 3));
  if(Wire.endTransmission()==2)
    return 0;
  return 1;
}
