	;; Yunlu Li, yl4df, 2019-11-16, threexplusone.s
	;; Optimization:
	;; I used idiv to do the division, but later I changed it to shift.
	;; I tried to limit the use of push and pop by deleting unnecessary
	;;        instruction.
	global threexplusone
	section .text

threexplusone:
	xor rax, rax
	cmp rdi, 1
	je end
	jmp test
test:
	mov rbx, rdi
	shr rbx, 1
	jnc even
	jmp odd
odd:
	imul rdi, 3
	add rdi, 1
	call threexplusone
	add rax, 1
	jmp end
even:
	shr rdi, 1
	call threexplusone
	add rax, 1
	jmp end
end:
	ret
