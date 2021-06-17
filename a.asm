.text
jal FUN1
li $v0 ,10
syscall
FUN1: 
sw $ra,-4($sp)
sw $fp,-8($sp)
sw $sp,-12($sp)
move $fp, $sp
subi $sp,$sp,16
li $t0,0
move $v0, $t0
j L1
L1:
lw $ra,-4($fp)
lw $sp,-12($fp)
lw $fp,-8($fp)
jr $ra
