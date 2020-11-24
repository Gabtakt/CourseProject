.globl main0
.text
main0:
    addi $fp, $0, 0x10010000
    move $t0,$sp
    addi $sp, $sp, -24
    sw $ra,0($sp)
    jal main
    lw $ra,0($sp)
    addi $sp,$sp,24
    li $v0,10
    syscall

fibo:
    li $t3, 1
    sw $t3, 16($sp)
    lw $t1, 12($sp)
    lw $t2, 16($sp)
    beq $t1,$t2,label3
    j label4

label4:
    li $t3, 2
    sw $t3, 16($sp)
    lw $t1, 12($sp)
    lw $t2, 16($sp)
    beq $t1,$t2,label3
    j label2

label3:
    li $t3, 1
    sw $t3, 16($sp)
    lw $v0,16($sp)
    jr $ra

label2:
    li $t3, 3
    sw $t3, 16($sp)
    lw $t1, 12($sp)
    lw $t2, 16($sp)
    bge $t1,$t2,label6
    j label5

label6:
    li $t3, 2
    sw $t3, 16($sp)
    li $t3, 1
    sw $t3, 20($sp)
    li $t3, 10
    sw $t3, 24($sp)
    lw $t1, 20($sp)
    lw $t2, 24($sp)
    mul $t3,$t1,$t2
    sw $t3, 28($sp)
    lw $t1, 16($sp)
    lw $t2, 28($sp)
    add $t3,$t1,$t2
    sw $t3, 16($sp)
    lw $t1,  16($sp)
    addi $t2, $fp, 20
    add $t1, $t1, $t2
    lw $t2, 0($t1)
    sw $t2, 8($fp)
    li $t3, 1
    sw $t3, 16($sp)
    lw $t1, 12($sp)
    lw $t2, 16($sp)
    sub $t3,$t1,$t2
    sw $t3, 20($sp)
    move $t0,$sp
    addi $sp, $sp, -44
    sw $ra,0($sp)
    lw $t1, 20($t0)
    move $t3,$t1
    sw $t3,12($sp)
    jal fibo
    lw $ra,0($sp)
    addi $sp,$sp,44
    sw $v0,24($sp)
    li $t3, 2
    sw $t3, 28($sp)
    lw $t1, 12($sp)
    lw $t2, 28($sp)
    sub $t3,$t1,$t2
    sw $t3, 32($sp)
    move $t0,$sp
    addi $sp, $sp, -44
    sw $ra,0($sp)
    lw $t1, 32($t0)
    move $t3,$t1
    sw $t3,12($sp)
    jal fibo
    lw $ra,0($sp)
    addi $sp,$sp,44
    sw $v0,36($sp)
    lw $t1, 24($sp)
    lw $t2, 36($sp)
    add $t3,$t1,$t2
    sw $t3, 40($sp)
    lw $v0,40($sp)
    jr $ra

label5:
    li $t3, 0
    sw $t3, 16($sp)
    lw $v0,16($sp)
    jr $ra

label1:

main:
    li $t3, 1
    sw $t3, 0($sp)
    lw $t1, 0($sp)
    move $t3, $t1
    sw $t3, 16($sp)

label12:
    li $t3, 10
    sw $t3, 0($sp)
    lw $t1, 16($sp)
    lw $t2, 0($sp)
    blt $t1,$t2,label10
    j label9

label10:
    li $t3, 9
    sw $t3, 20($sp)
    lw $t1, 16($sp)
    lw $t2, 20($sp)
    bgt $t1,$t2,label15
    j label16

label15:
    move $t0,$sp
    addi $sp, $sp, -44
    sw $ra,0($sp)
    lw $t1, 16($t0)
    move $t3,$t1
    sw $t3,12($sp)
    jal fibo
    lw $ra,0($sp)
    addi $sp,$sp,44
    sw $v0,20($sp)
    j label9
    j label14

label16:
    move $t0,$sp
    addi $sp, $sp, -44
    sw $ra,0($sp)
    lw $t1, 16($t0)
    move $t3,$t1
    sw $t3,12($sp)
    jal fibo
    lw $ra,0($sp)
    addi $sp,$sp,44
    sw $v0,20($sp)
    j label13

label14:
    lw $t1, 16($sp)
    move $t3, $t1
    sw $t3, 20($sp)
    addi $t1, $t1, +1
    sw $t1, 16($sp)

label13:
    lw $t1, 16($sp)
    move $t3, $t1
    sw $t3, 0($sp)
    addi $t1, $t1, +1
    sw $t1, 16($sp)
    j label12

label9:
    li $t3, 1
    sw $t3, 20($sp)
    lw $v0,20($sp)
    jr $ra

label8:
