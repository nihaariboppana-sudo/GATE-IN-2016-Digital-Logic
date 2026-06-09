void setup() {
  asm volatile (
    "cbi 0x0A, 2 \n\t"  // Configure Pin 2 (Port D2) as Input
    "cbi 0x0A, 3 \n\t"  // Configure Pin 3 (Port D3) as Input
    "cbi 0x0A, 4 \n\t"  // Configure Pin 4 (Port D4) as Input
    "sbi 0x04, 5 \n\t"  // Configure Pin 13 (Port B5) as Output
  );
}

void loop() {
  asm volatile (
    "in r16, 0x09 \n\t"    // Read input statuses from PIND
    
    "mov r17, r16 \n\t"
    "andi r17, 0x04 \n\t"  // Isolate bit 2 position (Input X)
    "mov r18, r16 \n\t"
    "andi r18, 0x08 \n\t"  // Isolate bit 3 position (Input Y)
    "mov r19, r16 \n\t"
    "andi r19, 0x10 \n\t"  // Isolate bit 4 position (Input Z)
    
    "mov r20, r17 \n\t"
    "lsl r20 \n\t"         // Align X to match bit position 3
    "and r20, r18 \n\t"    // Term 1 Operation: (X AND Y)
    
    "mov r21, r18 \n\t"
    "com r21 \n\t"         // Inverting Y to yield NOT Y behavior
    "andi r21, 0x08 \n\t" 
    "mov r22, r19 \n\t"
    "lsr r22 \n\t"         // Align Z to match bit position 3
    "and r21, r22 \n\t"    // Term 2 Operation: (NOT Y AND Z)
    
    "or r20, r21 \n\t"     // Merge terms via logical OR
    "bst r20, 3 \n\t"      // Store result inside hardware T flag bit
    "in r23, 0x05 \n\t"    
    "bld r23, 5 \n\t"      // Transfer T flag value to output bit 5
    "out 0x05, r23 \n\t"   // Drive output hardware PORTB (LED updates)
  );
}
