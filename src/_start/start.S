// Application entry and exit points
.global _start
.global _exit

_start:
	bl		main

_exit:
	// System call -> TaskExit()
	mov		r7, #0x20
	svc		#0