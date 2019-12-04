;; mathlib.s
;; Yunlu Li, yl4df, 2019-11-01, mathlib.s
	global product
	global power

	section .text

;; product
;; Take two parameter (positive integer) and return their product
product:
	;; prologue
	xor	rax,rax 	;zero out the return integer
	xor	r10,r10		;zero out the counter
start:
	cmp 	r10,rsi         ;check if counter reaches the second parameter
	je	done		;loop ends if it meets the condition above
	add	rax,rdi         ;add the first parameter to return register
	inc     r10		;increment counter by 1
	jmp	start		;iterate again
done:
	;;  epologue:
	ret

;; power
;; Take two parameter (x and n) and return x^n
power:
	xor 	r11,r11		;zero out the counter
base:
	cmp 	rsi,r11		;check if n = 0
	je	done2
recursion:
	push 	rsi		;push second parameter to the stack
	dec 	rsi		;decrement by one (used for recursion)
	call 	power		;call power(x, n-1)
	mov	rsi,rax		;assign the return value to second parameter
	call	product		;call product(x, power(x,n-1))
	pop 	rsi		;save rsi;
	ret
done2:
	mov rax,1		;the result for base case
	ret
	
	
	

	
