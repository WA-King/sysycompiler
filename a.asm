.text
jal FUN1
li $v0 ,10
syscall
FUN1: 
sw $ra,-4($sp)
sw $fp,-8($sp)
sw $sp,-12($sp)
move $fp, $sp
subi $sp,$sp,36
lw $t6,-16($fp)
addi $t0, $zero,10
move $t6,$t0
lw $t7,-20($fp)
addi $t0, $zero,0
move $t7,$t0
L1:
lw $t0,-24($fp)
slt $t0,$t7,$t6
sw $t0,-24($fp)
lw $t0,-24($fp)
beq $t0, $zero,L3
addi $t0, $zero,1
lw $t1,-28($fp)
add $t1,$t7,$t0
sw $t1,-28($fp)
lw $t0,-28($fp)
move $t7,$t0
addi $t0, $zero,7
lw $t1,-32($fp)
seq $t1,$t7,$t0
sw $t1,-32($fp)
lw $t0,-32($fp)
beq $t0, $zero,L2
j L3
L2:
move $a0, $t7
li $v0, 1
syscall
li $a0, 10
li $v0, 11
syscall
j L1
L3:
L4:
lw $ra,-4($fp)
lw $sp,-12($fp)
lw $fp,-8($fp)
jr $ra
.data
