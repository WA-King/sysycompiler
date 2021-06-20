.text
jal FUN1
li $v0 ,10
syscall
FUN1: 
sw $ra,-4($sp)
sw $fp,-8($sp)
sw $sp,-12($sp)
move $fp, $sp
subi $sp,$sp,32
lw $t6,-16($fp)
addi $t0, $zero,10
move $t6,$t0
L1:
addi $t0, $zero,0
lw $t1,-20($fp)
sgt $t1,$t6,$t0
sw $t1,-20($fp)
lw $t0,-20($fp)
beq $t0, $zero,L3
addi $t0, $zero,5
lw $t1,-24($fp)
sgt $t1,$t6,$t0
sw $t1,-24($fp)
lw $t0,-24($fp)
beq $t0, $zero,L2
addi $t0, $zero,1
lw $t1,-28($fp)
sub $t1,$t6,$t0
sw $t1,-28($fp)
lw $t0,-28($fp)
move $t6,$t0
j L1
L2:
move $a0, $t6
li $v0, 1
syscall
li $a0, 10
li $v0, 11
syscall
j L1
L3:
addi $t0, $zero,0
move $v0, $t0
j L4
L4:
lw $ra,-4($fp)
lw $sp,-12($fp)
lw $fp,-8($fp)
jr $ra
.data
