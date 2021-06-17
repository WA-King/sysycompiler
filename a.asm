.text
jal FUN2
li $v0 ,10
syscall
FUN1: 
sw $ra,-4($sp)
sw $fp,-8($sp)
sw $sp,-12($sp)
move $fp, $sp
subi $sp,$sp,44
li $t0,5
sw $t0,-16($fp)
li $t0,7
sw $t0,-20($fp)
L1:
lw $t1,-16($fp)
li $t2,100
slt $t0,$t1,$t2
beq $t0, $zero,L4
li $t2,30
add $t0,$t1,$t2
sw $t0,-16($fp)
L2:
lw $t1,-20($fp)
li $t2,100
slt $t0,$t1,$t2
beq $t0, $zero,L3
li $t2,6
add $t0,$t1,$t2
sw $t0,-20($fp)
j L2
L3:
lw $t1,-20($fp)
li $t2,100
sub $t0,$t1,$t2
sw $t0,-20($fp)
j L1
L4:
lw $t0,-20($fp)
move $v0, $t0
j L5
L5:
lw $ra,-4($fp)
lw $sp,-12($fp)
lw $fp,-8($fp)
jr $ra
FUN2: 
sw $ra,-4($sp)
sw $fp,-8($sp)
sw $sp,-12($sp)
move $fp, $sp
subi $sp,$sp,24
jal FUN1
move $t0,$v0
sw $t0,-16($fp)
lw $t0,-16($fp)
move $a0, $t0
li $v0, 1
syscall
li $t0,0
move $v0, $t0
j L6
L6:
lw $ra,-4($fp)
lw $sp,-12($fp)
lw $fp,-8($fp)
jr $ra
