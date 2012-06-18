; Copyright 2012 Aaron Ogden

; this file contains macros for computing indices into a half-filled array,
; for instance, if you wished to represent an edge's value as the value in a two dimensional array where the indices are the possibly connected nodes
; if the edges are bidirectional, nearly one half of a two-dimensional array would be not used or filled with duplicat data
; this code computes the index into a one-dimensional array that corresponds to such a 2D array being linearized.
; 1D index
; [0]      [1]      [2]      [3]      [4]      [5]
; 2D indices
; [0][0]   [0][1]   [0][2]   [1][1]   [1][2]   [2][2]


; it also contains a macro to compute the summation of integers from 1-N

; summation 1-N macro, parameters should be register names, result supplied and returned in N, N1 is overwritten
macro summation1N N,N1
{
	mov N1, N
	add N, 1
	mul N, N1
	shr N,1 	; equivalent to dividing by 2, safe here because the result is always an even integer
}

; parameters are operand names
; t1, t2, and retval are overwritten
; postcondition: X <= Y
macro FindHalfIndex size,X,Y,t1,t2,retval
{
	cmp X,Y 		; compare X and Y
	jle .fhipostswap	; skip if X is less than or equal to Y
	xchg X,Y		; swap X & Y if X is greater than Y
	.fhipostswap:
	mov t1, size		; t1 now holds the size
	sub t1, X		; t1 now holds numtier
	mov t2, size		; t2 now holds the size
	summation1N t2,retval	; t2 now holds the summation of size
	summation1N t1,retval	; t1 now holds the summation of numtier
	sub t2,t1		; t2 now holds the number of elts preceding
	mov t1,Y		; t1 now holds the Y
	sub t1,X		; t1 now holds the offset
	mov retval,t1		; retval now holds the offset
	add retval,t2		; retval now holds the answer
}