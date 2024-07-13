        .data
values: .word 1,2,3,4,5,6,7,8,9,10 ; values to be ordered
nelem:  .word 10 ; array size
        .text
        .global main

main:   addi r1,r0,nelem ; r1 = add(nelem)
	nop
	nop
        lw r1,0(r1) ; r1 = val(nelem)
        addi r2,r0,values ; r2 = addr(values[0])
        add r3,r0,r0 ; r3 = i = 0 (counting variable)
        addi r8,r1,-1 ; r8 = nelem - 1
	nop
	nop

loop1: slt r9,r3,r8 ; r9 = (i < nelem - 1)
	nop
	nop
        beqz r9,end ; is the end of operations been reached? 
	nop
	nop
	nop
        addi r6,r2,4 ; r6 = addr(values[j])
        lw r4,0(r2) ; r4 = val(values[i])
        addi r5,r3,1 ; r5 = j = i+1 (counting variable)

loop2: lw r7,0(r6) ; r7 = val(values[j])
	nop
	nop
        slt r9,r4,r7 ; r9 =;(val(values[i]) < val(values[j]))
	nop
	nop
        beqz r9,goon ; no element swap is required?
	nop
	nop
	nop
        add r9,r4,r0 ; r9 = tmp = val(values[i])
        add r4,r7,r0 ; val(values[i]) = val(values[j])
        add r7,r9,r0 ; val(values[j]) = tmp
	nop
        sw 0(r2),r4 ; val(values[i]) = r4
	nop
        sw 0(r6),r7 ; val(values[j]) = r7

goon:   addi r5,r5,1 ; j = j + 1
	nop
        addi r6,r6,4 ; r6 = add(values[j])
        slt r9,r5,r1 ; r9 = (j < nelem)
	nop
	nop
        bnez r9,loop2 ; are still elements to be compared?
	nop
	nop
	nop
        addi r3,r3,1 ; i = i + 1
        addi r2,r2,4 ; r2 = add(values[i])
        j loop1 ; check for end of operations
	nop
	nop
	nop

end: trap 0 ; end of program
