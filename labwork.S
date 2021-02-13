  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #



.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

.data
.align 2
.text 

.global 

hexasc:
	addi	$sp, $sp, -4	# increment stack
	sw	$t0, 0($sp)	# save $t0 to the stack
	
	andi	$v0, $0, 0	# clear return value
	andi	$t0, $a0, 0xf	# we will only check the 4 lsb
	ori	$v0, $t0, 0x30	# Start counting from 0x30 (0x30 = 0)
	
	sub	$t0, $t0, 0xa	# check if value is 0-9 (result < 0)	
	
	bltz	$t0, return	# our value is less than 10, return			
	addi	$v0, $v0, 0x7	# if our value is more than zero, add 0x7 (A = 0x41)
return:	
	lw	$t0, 0($sp)	# restore $t0 from the stack
	addi	$sp, $sp, 4	# decrement stack
	
	jr	$ra
	
.global time2string
time2string:

	PUSH	$ra

	addi	$t1, $0, 0		# set $t1 to 0
	addi	$t2, $a0, 5		# set $t2 to target address & move to end of target address array
	addi	$t3, $0, 0x3A		# save a colon to $t3
	
	sb	$0, 0($t2)		# store null byte
	sub	$t2, $t2, 1		# decrement array pointer	

time2stringloop:

# first check if we stay in loop
	beq	$t1, 4, time2stringdone	# counter < 4, else done
	
# then if we should add a colon
	bne	$t1, 2, time2stringskip	# counter == 2, else skip
	sb	$t3, 0($t2)		# save colon character ":", from $t3 (0x3A)
	sub	$t2, $t2, 1		# decrement array pointer	
	
time2stringskip:

# then execute loop conditions	
	andi	$a0, $0, 0		# clear $a0
	andi	$a0, $a1, 0xf		# save last nibble of $a1 -> $a0
	jal	hexasc			# convert to ASCI character
	sb	$v0, 0($t2)		# store the ascii character
		
	srl	$a1, $a1, 4		# look at next digit
	sub	$t2, $t2, 1		# decrement array pointer	
	addi	$t1, $t1, 1		# increment counter
	j	time2stringloop
	
time2stringdone:

	POP	$ra
	
	jr	$ra
	nop

.global enable_interrupt
enable_interrupt:
	ei
	jr $ra
	nop