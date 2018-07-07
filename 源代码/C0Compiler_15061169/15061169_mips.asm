.data
	STR1: .asciiz "  p: "
	STR2: .asciiz "  q: "
	STR3: .asciiz "  f: "
	STR4: .asciiz ","
	STR5: .asciiz "  a="
	STR6: .asciiz "  f="
	STR7: .asciiz "; "
	STR8: .asciiz "  c="
	STR9: .asciiz "  f0: "
	STR10: .asciiz "  x: "
	STR11: .asciiz "  f1: "
	STR12: .asciiz "  y: "
	STR13: .asciiz "  farr[1]: "
	STR14: .asciiz "  farr[2]: "
	STR15: .asciiz "  farr[3]: "
	STR16: .asciiz "  arr: "
	STR17: .asciiz " "
	STR18: .asciiz "  test = "
	STR19: .asciiz "  x = "
	STR20: .asciiz "  y = "
	STR21: .asciiz "  h = "
	STR22: .asciiz "  please input x:  "
	STR23: .asciiz "Fibonacci(x) = "
	STR24: .asciiz "Fibonacci(5) = "
	STR25: .asciiz "  please input str[len==5]:  "
	STR26: .asciiz "  test function input(p,q,f1,f2,f3,f4,f5,f6):  "
	STR27: .asciiz "  test function test1, test2, fulltest:  "
	STR28: .asciiz "  last = "
.text
li $k0, 0x10020000
move $gp, $sp
move $fp, $sp
li $t0, 10
sw $t0, ($sp)
subi $sp, $sp, 4
li $t0, -1
sw $t0, ($sp)
subi $sp, $sp, 4
li $t0, 'a'
sw $t0, ($sp)
subi $sp, $sp, 4
li $t0, 5
sw $t0, ($sp)
subi $sp, $sp, 4
li $t0, -5
sw $t0, ($sp)
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 40
subi $sp, $sp, 20
subi $sp, $sp, 4
subi $sp, $sp, 4
jal main
nop

Fibonacci:
sw $fp, ($sp)
subi $sp, $sp, 4
sw $ra, ($sp)
subi $sp, $sp, 4
move $fp, $sp
sw $t0, 0($k0)
sw $t1, -4($k0)
sw $t2, -8($k0)
sw $t3, -12($k0)
sw $t4, -16($k0)
sw $t5, -20($k0)
sw $t6, -24($k0)
sw $t7, -28($k0)
sw $t8, -32($k0)
sw $t9, -36($k0)
subi $k0, $k0, 40
lw $t0, 44($k0)
sw $t0, ($sp)
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 4
lw $t0, 0($fp)
li $t1, 1
bne $t0, $t1, lab1
nop
li $t0, 1
move $v1, $t0
lw $t9, 4($k0)
lw $t8, 8($k0)
lw $t7, 12($k0)
lw $t6, 16($k0)
lw $t5, 20($k0)
lw $t4, 24($k0)
lw $t3, 28($k0)
lw $t2, 32($k0)
lw $t1, 36($k0)
lw $t0, 40($k0)
addi $k0, $k0, 40
addi $k0, $k0, 4
move $sp, $fp
lw $ra, 4($sp)
lw $fp, 8($sp)
addi $sp, $sp, 8
jr $ra
nop
j lab2
nop
lab1:
lw $t0, 0($fp)
li $t1, 0
bgt $t0, $t1, lab3
nop
li $t0, 0
move $v1, $t0
lw $t9, 4($k0)
lw $t8, 8($k0)
lw $t7, 12($k0)
lw $t6, 16($k0)
lw $t5, 20($k0)
lw $t4, 24($k0)
lw $t3, 28($k0)
lw $t2, 32($k0)
lw $t1, 36($k0)
lw $t0, 40($k0)
addi $k0, $k0, 40
addi $k0, $k0, 4
move $sp, $fp
lw $ra, 4($sp)
lw $fp, 8($sp)
addi $sp, $sp, 8
jr $ra
nop
j lab4
nop
lab3:
lw $t0, 0($fp)
li $t1, 1
sub $t0, $t0, $t1
sw $t0, ($k0)
subi $k0, $k0, 4
jal Fibonacci
nop
move $t0, $v1
sw $t0, -4($fp)
lw $t0, 0($fp)
li $t1, 2
sub $t0, $t0, $t1
sw $t0, ($k0)
subi $k0, $k0, 4
jal Fibonacci
nop
move $t0, $v1
sw $t0, -8($fp)
lw $t0, -4($fp)
lw $t1, -8($fp)
add $t0, $t0, $t1
move $v1, $t0
lw $t9, 4($k0)
lw $t8, 8($k0)
lw $t7, 12($k0)
lw $t6, 16($k0)
lw $t5, 20($k0)
lw $t4, 24($k0)
lw $t3, 28($k0)
lw $t2, 32($k0)
lw $t1, 36($k0)
lw $t0, 40($k0)
addi $k0, $k0, 40
addi $k0, $k0, 4
move $sp, $fp
lw $ra, 4($sp)
lw $fp, 8($sp)
addi $sp, $sp, 8
jr $ra
nop
lab4:
lab2:
lw $t9, 4($k0)
lw $t8, 8($k0)
lw $t7, 12($k0)
lw $t6, 16($k0)
lw $t5, 20($k0)
lw $t4, 24($k0)
lw $t3, 28($k0)
lw $t2, 32($k0)
lw $t1, 36($k0)
lw $t0, 40($k0)
addi $k0, $k0, 40
addi $k0, $k0, 4
move $sp, $fp
lw $ra, 4($sp)
lw $fp, 8($sp)
addi $sp, $sp, 8
jr $ra
nop

judgemax:
sw $fp, ($sp)
subi $sp, $sp, 4
sw $ra, ($sp)
subi $sp, $sp, 4
move $fp, $sp
sw $t0, 0($k0)
sw $t1, -4($k0)
sw $t2, -8($k0)
sw $t3, -12($k0)
sw $t4, -16($k0)
sw $t5, -20($k0)
sw $t6, -24($k0)
sw $t7, -28($k0)
sw $t8, -32($k0)
sw $t9, -36($k0)
subi $k0, $k0, 40
lw $t0, 48($k0)
sw $t0, ($sp)
subi $sp, $sp, 4
lw $t0, 44($k0)
sw $t0, ($sp)
subi $sp, $sp, 4
lw $t0, 0($fp)
lw $t1, -4($fp)
bge $t0, $t1, lab5
nop
li $t0, 0
move $v1, $t0
lw $t9, 4($k0)
lw $t8, 8($k0)
lw $t7, 12($k0)
lw $t6, 16($k0)
lw $t5, 20($k0)
lw $t4, 24($k0)
lw $t3, 28($k0)
lw $t2, 32($k0)
lw $t1, 36($k0)
lw $t0, 40($k0)
addi $k0, $k0, 40
addi $k0, $k0, 8
move $sp, $fp
lw $ra, 4($sp)
lw $fp, 8($sp)
addi $sp, $sp, 8
jr $ra
nop
j lab6
nop
lab5:
li $t0, 1
move $v1, $t0
lw $t9, 4($k0)
lw $t8, 8($k0)
lw $t7, 12($k0)
lw $t6, 16($k0)
lw $t5, 20($k0)
lw $t4, 24($k0)
lw $t3, 28($k0)
lw $t2, 32($k0)
lw $t1, 36($k0)
lw $t0, 40($k0)
addi $k0, $k0, 40
addi $k0, $k0, 8
move $sp, $fp
lw $ra, 4($sp)
lw $fp, 8($sp)
addi $sp, $sp, 8
jr $ra
nop
lab6:
lw $t9, 4($k0)
lw $t8, 8($k0)
lw $t7, 12($k0)
lw $t6, 16($k0)
lw $t5, 20($k0)
lw $t4, 24($k0)
lw $t3, 28($k0)
lw $t2, 32($k0)
lw $t1, 36($k0)
lw $t0, 40($k0)
addi $k0, $k0, 40
addi $k0, $k0, 8
move $sp, $fp
lw $ra, 4($sp)
lw $fp, 8($sp)
addi $sp, $sp, 8
jr $ra
nop

getnum:
sw $fp, ($sp)
subi $sp, $sp, 4
sw $ra, ($sp)
subi $sp, $sp, 4
move $fp, $sp
sw $t0, 0($k0)
sw $t1, -4($k0)
sw $t2, -8($k0)
sw $t3, -12($k0)
sw $t4, -16($k0)
sw $t5, -20($k0)
sw $t6, -24($k0)
sw $t7, -28($k0)
sw $t8, -32($k0)
sw $t9, -36($k0)
subi $k0, $k0, 40
lw $t0, -20($gp)
li $t1, 0
ble $t0, $t1, lab7
nop
li $t0, 1
lw $t1, -12($gp)
mul $t0, $t0, $t1
li $t1, 2
mul $t0, $t0, $t1
li $t1, 6
sub $t0, $t0, $t1
move $v1, $t0
lw $t9, 4($k0)
lw $t8, 8($k0)
lw $t7, 12($k0)
lw $t6, 16($k0)
lw $t5, 20($k0)
lw $t4, 24($k0)
lw $t3, 28($k0)
lw $t2, 32($k0)
lw $t1, 36($k0)
lw $t0, 40($k0)
addi $k0, $k0, 40
addi $k0, $k0, 0
move $sp, $fp
lw $ra, 4($sp)
lw $fp, 8($sp)
addi $sp, $sp, 8
jr $ra
nop
j lab8
nop
lab7:
lw $t0, -16($gp)
li $t1, 2
mul $t0, $t0, $t1
li $t1, 8
add $t0, $t0, $t1
move $v1, $t0
lw $t9, 4($k0)
lw $t8, 8($k0)
lw $t7, 12($k0)
lw $t6, 16($k0)
lw $t5, 20($k0)
lw $t4, 24($k0)
lw $t3, 28($k0)
lw $t2, 32($k0)
lw $t1, 36($k0)
lw $t0, 40($k0)
addi $k0, $k0, 40
addi $k0, $k0, 0
move $sp, $fp
lw $ra, 4($sp)
lw $fp, 8($sp)
addi $sp, $sp, 8
jr $ra
nop
lab8:
lw $t9, 4($k0)
lw $t8, 8($k0)
lw $t7, 12($k0)
lw $t6, 16($k0)
lw $t5, 20($k0)
lw $t4, 24($k0)
lw $t3, 28($k0)
lw $t2, 32($k0)
lw $t1, 36($k0)
lw $t0, 40($k0)
addi $k0, $k0, 40
addi $k0, $k0, 0
move $sp, $fp
lw $ra, 4($sp)
lw $fp, 8($sp)
addi $sp, $sp, 8
jr $ra
nop

input:
sw $fp, ($sp)
subi $sp, $sp, 4
sw $ra, ($sp)
subi $sp, $sp, 4
move $fp, $sp
sw $t0, 0($k0)
sw $t1, -4($k0)
sw $t2, -8($k0)
sw $t3, -12($k0)
sw $t4, -16($k0)
sw $t5, -20($k0)
sw $t6, -24($k0)
sw $t7, -28($k0)
sw $t8, -32($k0)
sw $t9, -36($k0)
subi $k0, $k0, 40
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 84
subi $sp, $sp, 84
li $v0, 5
syscall
sw $v0, 0($fp)
li $v0, 12
syscall
sw $v0, -4($fp)
li $v0, 5
syscall
sw $v0, -8($fp)
li $v0, 5
syscall
sw $v0, -12($fp)
li $v0, 5
syscall
sw $v0, -16($fp)
li $v0, 12
syscall
sw $v0, -20($fp)
li $v0, 12
syscall
sw $v0, -24($fp)
li $v0, 12
syscall
sw $v0, -28($fp)
la $a0, STR1
li $v0, 4
syscall
lw $t0, 0($fp)
move $a0, $t0
li $v0, 1
syscall
la $a0, STR2
li $v0, 4
syscall
lw $t0, -4($fp)
move $a0, $t0
li $v0, 11
syscall
la $a0, STR3
li $v0, 4
syscall
lw $t0, -8($fp)
move $a0, $t0
li $v0, 1
syscall
la $a0, STR4
li $v0, 4
syscall
lw $t0, -12($fp)
move $a0, $t0
li $v0, 1
syscall
la $a0, STR4
li $v0, 4
syscall
lw $t0, -16($fp)
move $a0, $t0
li $v0, 1
syscall
la $a0, STR4
li $v0, 4
syscall
lw $t0, -20($fp)
move $a0, $t0
li $v0, 11
syscall
la $a0, STR4
li $v0, 4
syscall
lw $t0, -24($fp)
move $a0, $t0
li $v0, 11
syscall
la $a0, STR4
li $v0, 4
syscall
lw $t0, -28($fp)
move $a0, $t0
li $v0, 11
syscall
lw $t9, 4($k0)
lw $t8, 8($k0)
lw $t7, 12($k0)
lw $t6, 16($k0)
lw $t5, 20($k0)
lw $t4, 24($k0)
lw $t3, 28($k0)
lw $t2, 32($k0)
lw $t1, 36($k0)
lw $t0, 40($k0)
addi $k0, $k0, 40
addi $k0, $k0, 0
move $sp, $fp
lw $ra, 4($sp)
lw $fp, 8($sp)
addi $sp, $sp, 8
jr $ra
nop

output:
sw $fp, ($sp)
subi $sp, $sp, 4
sw $ra, ($sp)
subi $sp, $sp, 4
move $fp, $sp
sw $t0, 0($k0)
sw $t1, -4($k0)
sw $t2, -8($k0)
sw $t3, -12($k0)
sw $t4, -16($k0)
sw $t5, -20($k0)
sw $t6, -24($k0)
sw $t7, -28($k0)
sw $t8, -32($k0)
sw $t9, -36($k0)
subi $k0, $k0, 40
lw $t0, 48($k0)
sw $t0, ($sp)
subi $sp, $sp, 4
lw $t0, 44($k0)
sw $t0, ($sp)
subi $sp, $sp, 4
li $t0, 1
sw $t0, ($sp)
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 4
jal getnum
nop
move $t0, $v1
sw $t0, -12($fp)
lw $t0, -12($fp)
sw $t0, ($k0)
subi $k0, $k0, 4
lw $t0, -8($fp)
sw $t0, ($k0)
subi $k0, $k0, 4
jal judgemax
nop
move $t0, $v1
sw $t0, -16($fp)
lw $t0, -16($fp)
beq $t0, $0, lab9
nop
la $a0, STR5
li $v0, 4
syscall
lw $t0, 0($fp)
move $a0, $t0
li $v0, 1
syscall
la $a0, STR4
li $v0, 4
syscall
la $a0, STR6
li $v0, 4
syscall
lw $t0, -12($fp)
move $a0, $t0
li $v0, 1
syscall
la $a0, STR7
li $v0, 4
syscall
j lab10
nop
lab9:
la $a0, STR8
li $v0, 4
syscall
lw $t0, -4($fp)
move $a0, $t0
li $v0, 11
syscall
la $a0, STR4
li $v0, 4
syscall
la $a0, STR6
li $v0, 4
syscall
lw $t0, -12($fp)
move $a0, $t0
li $v0, 1
syscall
la $a0, STR7
li $v0, 4
syscall
lab10:
lw $t9, 4($k0)
lw $t8, 8($k0)
lw $t7, 12($k0)
lw $t6, 16($k0)
lw $t5, 20($k0)
lw $t4, 24($k0)
lw $t3, 28($k0)
lw $t2, 32($k0)
lw $t1, 36($k0)
lw $t0, 40($k0)
addi $k0, $k0, 40
addi $k0, $k0, 8
move $sp, $fp
lw $ra, 4($sp)
lw $fp, 8($sp)
addi $sp, $sp, 8
jr $ra
nop

test1:
sw $fp, ($sp)
subi $sp, $sp, 4
sw $ra, ($sp)
subi $sp, $sp, 4
move $fp, $sp
sw $t0, 0($k0)
sw $t1, -4($k0)
sw $t2, -8($k0)
sw $t3, -12($k0)
sw $t4, -16($k0)
sw $t5, -20($k0)
sw $t6, -24($k0)
sw $t7, -28($k0)
sw $t8, -32($k0)
sw $t9, -36($k0)
subi $k0, $k0, 40
li $t0, 2
sw $t0, ($sp)
subi $sp, $sp, 4
li $t0, 'a'
sw $t0, ($sp)
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 84
lw $t0, 0($fp)
sw $t0, -8($fp)
la $a0, STR9
li $v0, 4
syscall
lw $t0, -8($fp)
move $a0, $t0
li $v0, 1
syscall
lw $t0, -8($fp)
sw $t0, -20($gp)
la $a0, STR10
li $v0, 4
syscall
lw $t0, -20($gp)
move $a0, $t0
li $v0, 1
syscall
lw $t0, -20($gp)
lw $t1, -8($fp)
li $t2, 2
mul $t1, $t1, $t2
add $t0, $t0, $t1
sw $t0, -12($fp)
la $a0, STR11
li $v0, 4
syscall
lw $t0, -12($fp)
move $a0, $t0
li $v0, 1
syscall
lw $t0, -12($fp)
lw $t1, -8($fp)
mul $t0, $t0, $t1
lw $t1, -20($gp)
li $t2, 3
add $t1, $t1, $t2
div $t0, $t1
mflo $t0
sw $t0, -24($gp)
la $a0, STR12
li $v0, 4
syscall
lw $t0, -24($gp)
move $a0, $t0
li $v0, 1
syscall
li $t0, 1
li $t1, 1
sll $t0, $t0, 2
sub $t0, $gp, $t0
sw $t1, -32($t0)
li $t0, 2
lw $t1, -24($gp)
sll $t0, $t0, 2
sub $t0, $gp, $t0
sw $t1, -32($t0)
li $t0, 3
lw $t1, -20($gp)
lw $t2, 0($fp)
li $t3, 3
sub $t2, $t2, $t3
mul $t1, $t1, $t2
sll $t0, $t0, 2
sub $t0, $gp, $t0
sw $t1, -32($t0)
li $t0, 4
lw $t1, -4($fp)
li $t2, 3
mul $t1, $t1, $t2
li $t2, 2
add $t1, $t1, $t2
sll $t0, $t0, 2
sub $t0, $gp, $t0
sw $t1, -32($t0)
li $t0, 5
li $t1, 'd'
li $t2, 3
sub $t1, $t1, $t2
sll $t0, $t0, 2
sub $t0, $gp, $t0
sw $t1, -32($t0)
li $t0, 1
li $t1, 'b'
sll $t0, $t0, 2
sub $t0, $fp, $t0
sw $t1, -16($t0)
la $a0, STR13
li $v0, 4
syscall
li $t0, 1
sll $t0, $t0, 2
sub $t0, $fp, $t0
lw $t0, -16($t0)
move $a0, $t0
li $v0, 1
syscall
li $t0, 2
li $t1, 'a'
li $t2, 'b'
add $t1, $t1, $t2
sll $t0, $t0, 2
sub $t0, $fp, $t0
sw $t1, -16($t0)
la $a0, STR14
li $v0, 4
syscall
li $t0, 2
sll $t0, $t0, 2
sub $t0, $fp, $t0
lw $t0, -16($t0)
move $a0, $t0
li $v0, 1
syscall
li $t0, 3
li $t1, 'a'
li $t2, 3
mul $t1, $t1, $t2
sll $t0, $t0, 2
sub $t0, $fp, $t0
sw $t1, -16($t0)
la $a0, STR15
li $v0, 4
syscall
li $t0, 3
sll $t0, $t0, 2
sub $t0, $fp, $t0
lw $t0, -16($t0)
move $a0, $t0
li $v0, 1
syscall
li $t0, 3
sll $t0, $t0, 2
sub $t0, $gp, $t0
lw $t0, -32($t0)
sw $t0, -8($fp)
la $a0, STR9
li $v0, 4
syscall
lw $t0, -8($fp)
move $a0, $t0
li $v0, 1
syscall
li $t0, 2
sll $t0, $t0, 2
sub $t0, $fp, $t0
lw $t0, -16($t0)
sw $t0, -12($fp)
la $a0, STR11
li $v0, 4
syscall
lw $t0, -12($fp)
move $a0, $t0
li $v0, 1
syscall
li $t0, 2
sll $t0, $t0, 2
sub $t0, $gp, $t0
lw $t0, -32($t0)
lw $t1, -8($fp)
add $t0, $t0, $t1
sw $t0, -8($fp)
la $a0, STR9
li $v0, 4
syscall
lw $t0, -8($fp)
move $a0, $t0
li $v0, 1
syscall
li $t0, 3
sll $t0, $t0, 2
sub $t0, $gp, $t0
lw $t0, -32($t0)
li $t1, 2
sll $t1, $t1, 2
sub $t1, $fp, $t1
lw $t1, -16($t1)
sub $t0, $t0, $t1
sw $t0, -12($fp)
la $a0, STR11
li $v0, 4
syscall
lw $t0, -12($fp)
move $a0, $t0
li $v0, 1
syscall
li $t0, 1
li $t1, 5
sll $t0, $t0, 2
sub $t0, $fp, $t0
sw $t1, -16($t0)
la $a0, STR16
li $v0, 4
syscall
lab11:
li $t0, 1
sll $t0, $t0, 2
sub $t0, $fp, $t0
lw $t0, -16($t0)
beq $t0, $0, lab13
nop
la $a0, STR17
li $v0, 4
syscall
li $t0, 1
sll $t0, $t0, 2
sub $t0, $fp, $t0
lw $t0, -16($t0)
sll $t0, $t0, 2
sub $t0, $gp, $t0
lw $t0, -32($t0)
move $a0, $t0
li $v0, 1
syscall
li $t0, 1
li $t1, 1
sll $t1, $t1, 2
sub $t1, $fp, $t1
lw $t1, -16($t1)
li $t2, 1
sub $t1, $t1, $t2
sll $t0, $t0, 2
sub $t0, $fp, $t0
sw $t1, -16($t0)
j lab11
nop
lab13:
lw $t9, 4($k0)
lw $t8, 8($k0)
lw $t7, 12($k0)
lw $t6, 16($k0)
lw $t5, 20($k0)
lw $t4, 24($k0)
lw $t3, 28($k0)
lw $t2, 32($k0)
lw $t1, 36($k0)
lw $t0, 40($k0)
addi $k0, $k0, 40
addi $k0, $k0, 0
move $sp, $fp
lw $ra, 4($sp)
lw $fp, 8($sp)
addi $sp, $sp, 8
jr $ra
nop

test2:
sw $fp, ($sp)
subi $sp, $sp, 4
sw $ra, ($sp)
subi $sp, $sp, 4
move $fp, $sp
sw $t0, 0($k0)
sw $t1, -4($k0)
sw $t2, -8($k0)
sw $t3, -12($k0)
sw $t4, -16($k0)
sw $t5, -20($k0)
sw $t6, -24($k0)
sw $t7, -28($k0)
sw $t8, -32($k0)
sw $t9, -36($k0)
subi $k0, $k0, 40
lw $t0, 44($k0)
sw $t0, ($sp)
subi $sp, $sp, 4
subi $sp, $sp, 4
lw $t0, 0($fp)
li $t1, 5
ble $t0, $t1, lab14
nop
li $t0, 5
sw $t0, 0($fp)
j lab15
nop
lab14:
lab15:
lab16:
lw $t0, 0($fp)
li $t1, 10
bge $t0, $t1, lab17
nop
lw $t0, 0($fp)
li $t1, 2
add $t0, $t0, $t1
sw $t0, 0($fp)
lw $t0, 0($fp)
sw $t0, -4($fp)
lab18:
lw $t0, -4($fp)
li $t1, 0
ble $t0, $t1, lab19
nop
lw $t0, -4($fp)
li $t1, 3
sub $t0, $t0, $t1
sw $t0, -4($fp)
j lab18
nop
lab19:
j lab16
nop
lab17:
lw $t0, -20($gp)
bne $t0, 1, lab21
nop
li $t0, 2
sw $t0, -20($gp)
j lab20
nop
lab21:
bne $t0, 2, lab22
nop
li $t1, 3
sw $t1, -20($gp)
j lab20
nop
lab22:
bne $t0, 3, lab23
nop
j lab20
nop
lab23:
bne $t0, 4, lab24
nop
lw $t1, -20($gp)
li $t2, 5
add $t1, $t1, $t2
sw $t1, -20($gp)
j lab20
nop
lab24:
lab20:
lw $t1, -4($fp)
bne $t1, 2, lab26
nop
li $t1, 2
sub $t1, $0, $t1
sw $t1, -4($fp)
li $t1, 2
sw $t1, -20($gp)
j lab25
nop
lab26:
lab25:
la $a0, STR18
li $v0, 4
syscall
lw $t1, -4($fp)
move $a0, $t1
li $v0, 1
syscall
la $a0, STR19
li $v0, 4
syscall
lw $t1, -20($gp)
move $a0, $t1
li $v0, 1
syscall
li $t1, 'x'
move $v1, $t1
lw $t9, 4($k0)
lw $t8, 8($k0)
lw $t7, 12($k0)
lw $t6, 16($k0)
lw $t5, 20($k0)
lw $t4, 24($k0)
lw $t3, 28($k0)
lw $t2, 32($k0)
lw $t1, 36($k0)
lw $t0, 40($k0)
addi $k0, $k0, 40
addi $k0, $k0, 4
move $sp, $fp
lw $ra, 4($sp)
lw $fp, 8($sp)
addi $sp, $sp, 8
jr $ra
nop
lw $t9, 4($k0)
lw $t8, 8($k0)
lw $t7, 12($k0)
lw $t6, 16($k0)
lw $t5, 20($k0)
lw $t4, 24($k0)
lw $t3, 28($k0)
lw $t2, 32($k0)
lw $t1, 36($k0)
lw $t0, 40($k0)
addi $k0, $k0, 40
addi $k0, $k0, 4
move $sp, $fp
lw $ra, 4($sp)
lw $fp, 8($sp)
addi $sp, $sp, 8
jr $ra
nop

fulltest:
sw $fp, ($sp)
subi $sp, $sp, 4
sw $ra, ($sp)
subi $sp, $sp, 4
move $fp, $sp
sw $t0, 0($k0)
sw $t1, -4($k0)
sw $t2, -8($k0)
sw $t3, -12($k0)
sw $t4, -16($k0)
sw $t5, -20($k0)
sw $t6, -24($k0)
sw $t7, -28($k0)
sw $t8, -32($k0)
sw $t9, -36($k0)
subi $k0, $k0, 40
li $t0, 1
sw $t0, ($sp)
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 4
la $a0, STR19
li $v0, 4
syscall
lw $t1, -20($gp)
move $a0, $t1
li $v0, 1
syscall
li $t1, 0
sw $t1, -4($fp)
lab27:
lw $t1, -4($fp)
lw $t2, 0($gp)
bge $t1, $t2, lab28
nop
lw $t1, -4($fp)
lw $t2, -4($fp)
sll $t1, $t1, 2
sub $t1, $gp, $t1
sw $t2, -32($t1)
lw $t1, -4($fp)
li $t2, 5
bge $t1, $t2, lab29
nop
lw $t1, -4($fp)
sll $t1, $t1, 2
sub $t1, $gp, $t1
lw $t1, -72($t1)
sw $t1, -12($fp)
j lab30
nop
lab29:
lab30:
lw $t1, -4($fp)
li $t2, 3
bge $t1, $t2, lab31
nop
lw $t1, -20($gp)
lw $t2, -4($fp)
li $t3, 1
add $t2, $t2, $t3
mul $t1, $t1, $t2
sw $t1, -20($gp)
j lab32
nop
lab31:
lw $t1, -20($gp)
lw $t2, -4($fp)
sub $t1, $t1, $t2
sw $t1, -20($gp)
lab32:
lw $t1, -4($fp)
sll $t1, $t1, 2
sub $t1, $gp, $t1
lw $t1, -32($t1)
sw $t1, ($k0)
subi $k0, $k0, 4
lw $t1, -12($fp)
sw $t1, ($k0)
subi $k0, $k0, 4
jal output
nop
lw $t1, -4($fp)
li $t2, 1
add $t1, $t1, $t2
sw $t1, -4($fp)
j lab27
nop
lab28:
li $t1, 3
sw $t1, -8($fp)
lw $t1, -20($gp)
li $t2, 0
ble $t1, $t2, lab33
nop
lw $t1, -20($gp)
li $t2, 1
add $t1, $t1, $t2
sw $t1, -24($gp)
j lab34
nop
lab33:
lw $t1, -20($gp)
sub $t1, $0, $t1
li $t2, 1
add $t1, $t1, $t2
sw $t1, -24($gp)
lab34:
li $t1, 'a'
sw $t1, -12($fp)
la $a0, STR19
li $v0, 4
syscall
lw $t1, -20($gp)
move $a0, $t1
li $v0, 1
syscall
lab35:
lw $t1, -8($fp)
lw $t2, -4($gp)
ble $t1, $t2, lab36
nop
lw $t1, -12($fp)
bne $t1, 97, lab38
nop
li $t1, 'b'
sw $t1, -12($fp)
lw $t1, -24($gp)
lw $t2, -8($fp)
div $t1, $t2
mflo $t1
sw $t1, -24($gp)
j lab37
nop
lab38:
bne $t1, 98, lab39
nop
li $t2, 'c'
sw $t2, -12($fp)
lw $t2, -24($gp)
lw $t3, -8($fp)
add $t2, $t2, $t3
sw $t2, -24($gp)
j lab37
nop
lab39:
lw $t2, -24($gp)
lw $t3, -8($fp)
sub $t2, $t2, $t3
sw $t2, -24($gp)
lab37:
la $a0, STR20
li $v0, 4
syscall
lw $t2, -24($gp)
move $a0, $t2
li $v0, 1
syscall
lw $t2, -8($fp)
li $t3, 1
sub $t2, $t2, $t3
sw $t2, -8($fp)
j lab35
nop
lab36:
la $a0, STR21
li $v0, 4
syscall
lw $t2, 0($fp)
move $a0, $t2
li $v0, 1
syscall
lw $t9, 4($k0)
lw $t8, 8($k0)
lw $t7, 12($k0)
lw $t6, 16($k0)
lw $t5, 20($k0)
lw $t4, 24($k0)
lw $t3, 28($k0)
lw $t2, 32($k0)
lw $t1, 36($k0)
lw $t0, 40($k0)
addi $k0, $k0, 40
addi $k0, $k0, 0
move $sp, $fp
lw $ra, 4($sp)
lw $fp, 8($sp)
addi $sp, $sp, 8
jr $ra
nop

main:
sw $fp, ($sp)
subi $sp, $sp, 4
sw $ra, ($sp)
subi $sp, $sp, 4
move $fp, $sp
sw $t0, 0($k0)
sw $t1, -4($k0)
sw $t2, -8($k0)
sw $t3, -12($k0)
sw $t4, -16($k0)
sw $t5, -20($k0)
sw $t6, -24($k0)
sw $t7, -28($k0)
sw $t8, -32($k0)
sw $t9, -36($k0)
subi $k0, $k0, 40
li $t0, -5
sw $t0, ($sp)
subi $sp, $sp, 4
subi $sp, $sp, 4
subi $sp, $sp, 4
la $a0, STR22
li $v0, 4
syscall
li $v0, 5
syscall
sw $v0, -20($gp)
lw $t2, -20($gp)
sw $t2, -28($gp)
lw $t2, -20($gp)
li $t3, 6
bge $t2, $t3, lab40
nop
la $a0, STR23
li $v0, 4
syscall
lw $t2, -20($gp)
sw $t2, ($k0)
subi $k0, $k0, 4
jal Fibonacci
nop
move $t2, $v1
move $a0, $t2
li $v0, 1
syscall
j lab41
nop
lab40:
la $a0, STR24
li $v0, 4
syscall
li $t2, 5
sw $t2, ($k0)
subi $k0, $k0, 4
jal Fibonacci
nop
move $t2, $v1
move $a0, $t2
li $v0, 1
syscall
lab41:
la $a0, STR25
li $v0, 4
syscall
li $t2, 0
sw $t2, -4($fp)
lab42:
lw $t2, -4($fp)
li $t3, 5
bge $t2, $t3, lab43
nop
li $v0, 12
syscall
sw $v0, -8($fp)
lw $t2, -4($fp)
lw $t3, -8($fp)
sll $t2, $t2, 2
sub $t2, $gp, $t2
sw $t3, -72($t2)
lw $t2, -4($fp)
li $t3, 1
add $t2, $t2, $t3
sw $t2, -4($fp)
j lab42
nop
lab43:
la $a0, STR26
li $v0, 4
syscall
jal input
nop
la $a0, STR27
li $v0, 4
syscall
jal test1
nop
li $t2, 3
sw $t2, -96($gp)
lw $t2, -96($gp)
sw $t2, ($k0)
subi $k0, $k0, 4
jal test2
nop
move $t2, $v1
sw $t2, -8($fp)
jal fulltest
nop
la $a0, STR28
li $v0, 4
syscall
jal getnum
nop
move $t2, $v1
lw $t3, 0($fp)
sub $t3, $0, $t3
lw $t4, -20($gp)
add $t3, $t3, $t4
sw $t3, ($k0)
subi $k0, $k0, 4
jal Fibonacci
nop
move $t3, $v1
add $t2, $t2, $t3
move $a0, $t2
li $v0, 1
syscall
li $v0, 10
syscall
