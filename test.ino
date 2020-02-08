void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned long R1, dump;
  do {
     R1 = SNVS_HPRTCLR;
     dump = SNVS_HPRTCLR;
  } while (R1 != dump);
  // to prevent glitch
  Serial.println((((R1 << 17) >> 17) * 1000) >> 15);
  /* first, remove all the bits above the milliseconds.
   from the "rtc.c" in the core, from the function rtc_get(),
   we could infer that 17 upper bits are for the seconds, minutes, etc, ...
   and the rest are for the milliseconds. It is because that the RTC frequency
   is 32.768kHz.
   So, ((R1 << 17) >> 17) results in the present count, which maximum is 32767.
   The result is apparently not bigger than the limitation of the unsigned long.
   So, multiply 1000 and then divide by 32768 (which is equal to the 15 bit right shift).
   As a result, you could get the millisecond RTC from the Teensy.
   If there's no problem for the board, then the Arduino will display the
   millisecond RTC value. You should be known that the SNVS_HPRTCLR is 32-bit register. */
  
  delay(200);
}
