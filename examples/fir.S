fir:
        .frame  r1,0,r15                # vars= 0, regs= 0, args= 0
        .mask   0x00000000
        addik   r3,r0,delay_line.1450
        lwi     r4,r3,8           # Unrolled loop to shift the delay line
        swi     r4,r3,12
        lwi     r4,r3,4
        swi     r4,r3,8
        lwi     r4,r3,0
        swi     r4,r3,4
        swi     r5,r3,0           # Store the new input sample into the delay line
        addik   r5,r0,4 	  # Initialize the loop counter
        addk    r8,r0,r0          # Initialize accumulator to zero
        addk    r4,r8,r0          # Initialize index expression to zero
$L2:
        muli    r3,r4,4           # Compute a byte offset into the delay_line array
        addik   r9,r3,delay_line.1450
        lw      r3,r3,r7          # Load filter tap
        lwi     r9,r9,0           # Load value from delay line
        mul     r3,r3,r9	  # Filter Multiply
        addk    r8,r8,r3	  # Filter Accumulate
        addik   r5,r5,-1          # update the loop counter
        bneid   r5,$L2
        addik   r4,r4,1           # branch delay slot, update index expression

        rtsd    r15, 8		  
        swi     r8,r6,0		  # branch delay slot, store the output
        .end    fir
