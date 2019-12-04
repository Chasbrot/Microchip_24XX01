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

#include "MC24XX01.h";

MC24XX01 chip;


void setup() {
  Serial.begin(9600);
  chip.init();
  Serial.println("Init finished");
  Serial.println("Start R/W Test");

  // Writing single byte
  Serial.println("Writing single byte: 0x7");
  chip.writeByte(0x0, 0x7);

  // Reading single byte
  byte data = chip.readByte(0x0);
  Serial.print("Reading single byte: ");
  Serial.println(data, HEX);

  // Writing page
  uint8_t page[8] = {2, 3, 4, 5, 6, 7, 8, 9};
  Serial.print("Wrinting array at 0x8 (page write): ");
  uint8_t written = chip.writePage(0x8, page, sizeof(page));
  Serial.print(written);
  Serial.println(" Bytes written");
  // Wait until finished
  while (!chip.checkAvailable())
    delay(5);

  // Writing partial page
  Serial.print("Wrinting array at 0x2C (partial page write): ");
  written = chip.writePage(0x2C, page, sizeof(page));
  if (!chip.checkAvailable()) {
    Serial.print("Writing  ");
  }
  Serial.print(written);
  Serial.println(" Bytes written");

  // Chucking in some test data
  chip.writeByte(0x64, 0xAA);
  
  // Reading the chip sequentially
  Serial.print("Read chip sequentially: ");
  uint8_t img[32];
  Serial.print("\n0-31 ");
  Serial.println(chip.readSeqBytes(0x0, img, 32));
  for (int i = 0; i < 32; i++) {
    Serial.print(img[i], HEX);
    Serial.print(" ");
    if (i % 16 == 0 && i != 0)
      Serial.println();
  }
  Serial.print("\n32-63 ");
  Serial.println(chip.readSeqBytes(0x20, img, 32));
  for (int i = 0; i < 32; i++) {
    Serial.print(img[i], HEX);
    Serial.print(" ");
    if (i % 16 == 0 && i != 0)
      Serial.println();
  }
  Serial.print("\n64-95 ");
  Serial.println(chip.readSeqBytes(0x40, img, 32));
  for (int i = 0; i < 32; i++) {
    Serial.print(img[i], HEX);
    Serial.print(" ");
    if (i % 16 == 0 && i != 0)
      Serial.println();
  }
  Serial.print("\n96-127 ");
  Serial.println(chip.readSeqBytes(0x60, img, 32));
  for (int i = 0; i < 32; i++) {
    Serial.print(img[i], HEX);
    Serial.print(" ");
    if (i % 16 == 0 && i != 0)
      Serial.println();
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
