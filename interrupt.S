  # interrupt.S
  # Written 2021 by Erik Malm & Kalle Elmdahl


.global enable_interrupt
enable_interrupt:
	ei
	jr $ra
	nop