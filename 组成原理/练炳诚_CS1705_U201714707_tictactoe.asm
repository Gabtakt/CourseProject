# this is a  tic-tac-toe chess game mips program
# there are nine interrupt sources in the program,each interrupt source represents a grid
# author: lbc, 2020-8-12

addi $sp,$zero,0x200 #data buffer address
addi $s1,$zero,127 # each line has 127 points
addi $s2,$zero,42 # line offset
addi $s3,$zero,126 # end value
addi $s4,$zero,0 #loop control

initial_map_1:
addi $s5,$zero,0
add $s4,$s4,$s2
bne $s4,$s3,vertical
addi $s4,$zero,0

initial_map_2:
addi $s5,$zero,0
add $s4,$s4,$s2
bne $s4,$s3,horizontal
j loop_forever

horizontal:
addi $a0,$zero,0
add $a0,$a0,$s4

horizontal_loop:
sll $s6,$s5,7
or $a0,$a0,$s6
addi $v0,$zero,2
syscall
and $a0,$a0,127
add $s5,$s5,1
bne $s5,$s1,horizontal_loop
j initial_map_2

vertical:
addi $a0,$zero,0
add $a0,$a0,$s4
sll $a0,$a0,7

vertical_loop:
or $a0,$a0,$s5
addi $v0,$zero,2
syscall
and $a0,$a0,0x3f80
add $s5,$s5,1
bne $s5,$s1,vertical_loop
j initial_map_1

loop_forever:
j loop_forever

# interrept program : show map, and check status
# use register: $s0,$s1,$s2,$s3,$s4，$a0,$vo
interrept:
sw $s0,0x0($sp)
sw $s1,0x4($sp)
sw $s2,0x8($sp)
sw $s3,0xc($sp)
sw $s4,0x10($sp)
sw $a0,0x14($sp)
sw $v0,0x18($sp)

addi $s0,$zero,0x00 # grid number address, begin at 0x0,  end at 0x20
addi $s1,$zero,0x40 # user number address, begin at 0x40, end at 0x60
addi $s2,$zero,4 # base offset
j show_piece

# next lable show_1~show_9 change $s1 to center X and change $s2 to center Y,then call show_o or show_x to draw graph
show_1:
lw $s3,0($s0)
sw $s3,0($s1)
addi $s1,$zero,8
addi $s2,$zero,8
beq $s3,1,show_o
j show_x

show_2:
lw $s3,0($s0)
sw $s3,0($s1)
addi $s1,$zero,50
addi $s2,$zero,8
beq $s3,1,show_o
j show_x

show_3:
lw $s3,0($s0)
sw $s3,0($s1)
addi $s1,$zero,92
addi $s2,$zero,8
beq $s3,1,show_o
j show_x

show_4:
lw $s3,0($s0)
sw $s3,0($s1)
addi $s1,$zero,8
addi $s2,$zero,50
beq $s3,1,show_o
j show_x

show_5:
lw $s3,0($s0)
sw $s3,0($s1)
addi $s1,$zero,50
addi $s2,$zero,50
beq $s3,1,show_o
j show_x

show_6:
lw $s3,0($s0)
sw $s3,0($s1)
addi $s1,$zero,92
addi $s2,$zero,50
beq $s3,1,show_o
j show_x

show_7:
lw $s3,0($s0)
sw $s3,0($s1)
addi $s1,$zero,8
addi $s2,$zero,92
beq $s3,1,show_o
j show_x

show_8:
lw $s3,0($s0)
sw $s3,0($s1)
addi $s1,$zero,50
addi $s2,$zero,92
beq $s3,1,show_o
j show_x

show_9:
lw $s3,0($s0)
sw $s3,0($s1)
addi $s1,$zero,92
addi $s2,$zero,92
beq $s3,1,show_o
j show_x

# drow a cycle, X and Y in $s1 and $s2, each graph size is 26*26
show_o:
addi $s3,$zero,13 # loop_counter
addi $s2,$s2,13
show_o_v1:
add $a0,$zero,$s1
sll $a0,$a0,7
or $a0,$a0,$s2
addi $v0,$zero,2
syscall
addi $s1,$s1,1
addi $s2,$s2,-1
addi $s3,$s3,-1
bne $s3,$zero,show_o_v1

addi $s3,$zero,13 # loop_counter
show_o_v2:
add $a0,$zero,$s1
sll $a0,$a0,7
or $a0,$a0,$s2
addi $v0,$zero,2
syscall
addi $s1,$s1,1
addi $s2,$s2,1
addi $s3,$s3,-1
bne $s3,$zero,show_o_v2

addi $s3,$zero,13 # loop_counter
show_o_h1:
add $a0,$zero,$s1
sll $a0,$a0,7
or $a0,$a0,$s2
addi $v0,$zero,2
syscall
addi $s1,$s1,-1
addi $s2,$s2,1
addi $s3,$s3,-1
bne $s3,$zero,show_o_h1

addi $s3,$zero,13 # loop_counter
show_o_h2:
add $a0,$zero,$s1
sll $a0,$a0,7
or $a0,$a0,$s2
addi $v0,$zero,2
syscall
addi $s1,$s1,-1
addi $s2,$s2,-1
addi $s3,$s3,-1
bne $s3,$zero,show_o_h2
j victory_judgment

# dorw a X, X and Y in $s1 and $s2, each graph size is 26*26
show_x:
addi $s3,$zero,26 # loop counter
show_x_1:
add $a0,$s2,$zero
sll $s4,$s1,7
or $a0,$a0,$s4
addi $v0,$zero,2
syscall
addi $a0,$zero,0
addi $s1,$s1,1
addi $s2,$s2,1
addi $s3,$s3,-1
bne $s3,$zero,show_x_1

addi $s1,$s1,-26
addi $s3,$zero,26 # loop counter
show_x_2:
add $a0,$s2,$zero
sll $s4,$s1,7
or $a0,$a0,$s4
addi $v0,$zero,2
syscall
addi $a0,$zero,0
addi $s1,$s1,1
addi $s2,$s2,-1
addi $s3,$s3,-1
bne $s3,$zero,show_x_2
j victory_judgment

show_piece: # each interrept just show one piece, it is guaranteed by game driver, user1 show o, user2 show x
lw $s3,0($s0)
lw $s4,0($s1)
bne $s3,$s4,show_1
add $s0,$s0,$s2
add $s1,$s1,$s2
lw $s3,0($s0)
lw $s4,0($s1)
bne $s3,$s4,show_2
add $s0,$s0,$s2
add $s1,$s1,$s2
lw $s3,0($s0)
lw $s4,0($s1)
bne $s3,$s4,show_3
add $s0,$s0,$s2
add $s1,$s1,$s2
lw $s3,0($s0)
lw $s4,0($s1)
bne $s3,$s4,show_4
add $s0,$s0,$s2
add $s1,$s1,$s2
lw $s3,0($s0)
lw $s4,0($s1)
bne $s3,$s4,show_5
add $s0,$s0,$s2
add $s1,$s1,$s2
lw $s3,0($s0)
lw $s4,0($s1)
bne $s3,$s4,show_6
add $s0,$s0,$s2
add $s1,$s1,$s2
lw $s3,0($s0)
lw $s4,0($s1)
bne $s3,$s4,show_7
add $s0,$s0,$s2
add $s1,$s1,$s2
lw $s3,0($s0)
lw $s4,0($s1)
bne $s3,$s4,show_8
add $s0,$s0,$s2
add $s1,$s1,$s2
lw $s3,0($s0)
lw $s4,0($s1)
bne $s3,$s4,show_9

victory_judgment:
lw $v0,0x18($sp)
lw $a0,0x14($sp)
lw $s4,0x10($sp)
lw $s3,0xc($sp)
lw $s2,0x8($sp)
lw $s1,0x4($sp)
lw $s0,0x0($sp)

eret







