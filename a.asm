.text
jal FUN3
li $v0 ,10
syscall
FUN1: 
sw $ra,-12($sp)
sw $fp,-16($sp)
sw $sp,-20($sp)
move $fp, $sp
subi $sp,$sp,24
lw $t6,-4($fp)
lw $t7,-8($fp)
move $a0, $t6
li $v0, 1
syscall
li $a0, 10
li $v0, 11
syscall
move $a0, $t7
li $v0, 1
syscall
li $a0, 10
li $v0, 11
syscall
L1:
lw $ra,-12($fp)
lw $sp,-20($fp)
lw $fp,-16($fp)
jr $ra
FUN2: 
sw $ra,-8($sp)
sw $fp,-12($sp)
sw $sp,-16($sp)
move $fp, $sp
subi $sp,$sp,28
la $t6,cnt
lw $t6,0($t6)
addi $t0, $zero,1
lw $t1,-20($fp)
add $t1,$t6,$t0
sw $t1,-20($fp)
lw $t0,-20($fp)
move $t6,$t0
move $v0, $t6
j L2
L2:
la $t0,cnt
sw $t6,0($t0)
lw $ra,-8($fp)
lw $sp,-16($fp)
lw $fp,-12($fp)
jr $ra
FUN3: 
sw $ra,-4($sp)
sw $fp,-8($sp)
sw $sp,-12($sp)
move $fp, $sp
subi $sp,$sp,28
addi $t0, $zero,1
sw $t0,-4($sp)
jal FUN2
lw $t0,-16($fp)
move $t0,$v0
sw $t0,-16($fp)
addi $t0, $zero,1
sw $t0,-4($sp)
jal FUN2
lw $t0,-20($fp)
move $t0,$v0
sw $t0,-20($fp)
lw $t0,-16($fp)
sw $t0,-4($sp)
lw $t0,-20($fp)
sw $t0,-8($sp)
jal FUN1
lw $t0,-24($fp)
move $t0,$v0
sw $t0,-24($fp)
addi $t0, $zero,0
move $v0, $t0
j L3
L3:
lw $ra,-4($fp)
lw $sp,-12($fp)
lw $fp,-8($fp)
jr $ra
.data
cnt:
.word 0
