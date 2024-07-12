    .equ	inkey, 1
	.equ getChar, 2
.equ putChar, 3
	.equ	RESET_CORE_TIMER, 12
	.equ	READ_CORE_TIMER, 11
	.equ	FREQUENCY_Hz, 1000
	.equ	TARGET_CORE_VAL, 20000000/FREQUENCY_Hz

	.equ	SFR_BASE_HI, 0xBF88
	.equ	TRISE, 0x6100	
	.equ	PORTE, 0x6110
	.equ	LATE, 0x6120

	.data
	.text
	.globl	main
main:						# void main(){
	addi	$sp, $sp, -20
	sw	$ra, 0($sp)
	sw	$s0, 4($sp)
    sw	$s1, 8($sp)
    sw	$s2, 12($sp)
    sw	$s3, 16($sp)
	
	lui	$s0, SFR_BASE_HI

	lw	$s1, TRISE($s0) 		# $s0 =  0xBF880000+0x00006110
	andi	$s1, $s1, 0xFFE0	# bit[0-4] = 0 (output)	
	sw	$s1, TRISE($s0)			# Configured TRISE register

	# vamos por tudo a zero no princípio
	lw	$s1, LATE($s0)			# Read LATE register
	andi $s1, $s1, 0xFFE0   	# bit1=0
	sw	$s1, LATE($s0)			# Writer LATE register



loop:	
	li	$v0, inkey		# inkey não fica à espera de caracter
	syscall					   
   move $s2, $v0              # c = inkey(); |  c = getChar();

	move $a0, $s2 	
	li	$v0, putChar		
	syscall					   
    	          

	#LED0
if:	bne	$s2, '0', led1 #endif
	lw	$s1, LATE($s0)			# Read LATE register
	ori	$s1, $s1, 1					#or	$s1, $s1, $s3	    	# bit0=1
	sw	$s1, LATE($s0)			# Writer LATE register
	j loop
	#LED1
led1:	bne	$s2, '1', led2
	lw	$s1, LATE($s0)			# Read LATE register
	ori	$s1, $s1, 2   		# bit1=1
	sw	$s1, LATE($s0)			# Writer LATE register
	j loop
	#LED2
led2:	bne	$s2, '2', led3
	lw	$s1, LATE($s0)			# Read LATE register
	ori	$s1, $s1, 4    		# bit2=1
	sw	$s1, LATE($s0)			# Writer LATE register	 
	j loop
	#LED3
led3:	bne	$s2, '3', led4
	lw	$s1, LATE($s0)			# Read LATE register
	ori	$s1, $s1, 8     		# bit3=1
	sw	$s1, LATE($s0)			# Writer LATE register
	j loop
	#LED4
led4:	bne	$s2, '4', loop
	lw	$s1, LATE($s0)			# Read LATE register
	andi	$s1, $s1, 0xFFF0		# apaga b3 ... b0
	ori	$s1, $s1, 0x0010   		# bit4=1
	sw	$s1, LATE($s0)			# Writer LATE register
						# li	$s0, 2000 destrói SFR_BASE
	li	$a0, 2000
	jal	delay				    # delay(2000ms) -> 2secods
 	
	
	lw	$s1, LATE($s0)			# Read LATE register
	andi	$s1, $s1, 0xFFEF   		# bit4=0
	sw	$s1, LATE($s0)			# Writer LATE register
    
    j   loop

	lw	$ra, 0($sp)
	lw	$s0, 4($sp)
    lw	$s1, 8($sp)
    lw	$s2, 12($sp)
    lw	$s3, 16($sp)
	addi	$sp, $sp, 20
     
     
	
	li	$v0, 0              # return 0;
endif:	jr	$ra				# end }

delay:
while:	blt	$a0, 0, endw			# while(ms > 0){
	li	$v0, RESET_CORE_TIMER
	syscall					# resetCoreTimer();
 wait:	li	$v0, READ_CORE_TIMER
	syscall
	blt	$v0,20000, wait	# 20000 da 1msg TARGET_CORE_VAL é a frequência do clockwhile(readCoreTimer() < k);
	
	addi	$a0, $a0, -1			# ms--;	
	j	while 

endw:	jr	$ra				#end }
	



