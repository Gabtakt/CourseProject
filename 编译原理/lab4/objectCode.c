#include "def.h"

void objectCode(struct codenode *head, struct codenode *tail){
    char opnstr1[32],opnstr2[32],resultstr[32];
    struct codenode *h=head,*hh,*hhh;
    int i,global_flag1,global_flag2,global_flag3;
    printf(".globl main0\n");
    printf(".text\n");
    printf("main0:\n");
    printf("    addi $fp, $0, 0x10010000\n");//mars仿真器下data段的起始地址
    for ( i = 0; i < symbolTable.index; i++)
    {
        if (!strcmp("main",symbolTable.symbols[i].name))
        {
            break;
        }
        
    }
    printf("    move $t0,$sp\n"); 
    printf("    addi $sp, $sp, -%d\n", symbolTable.symbols[i].offset);
    printf("    sw $ra,0($sp)\n");
    printf("    jal main\n");
    printf("    lw $ra,0($sp)\n");
    printf("    addi $sp,$sp,%d\n",symbolTable.symbols[i].offset);
    printf("    li $v0,10\n");
    printf("    syscall\n");
    do
    {       
        switch (h->op)
        {

          case ASSIGNOP:  
                        if (h->opn1.kind==INT)//只考虑整形运算
                            printf("    li $t3, %d\n", h->opn1.const_int);
                        else
                        {
                            if(h->opn1.level == 0)
                            {
                                printf("    addi $t2, $fp, %d\n", h->opn1.offset);
                                printf("    lw $t1, 0($t2)\n");
                            }
                            else
                                printf("    lw $t1, %d($sp)\n", h->opn1.offset);
                            printf("    move $t3, $t1\n");
                        }
                        if(h->result.level == 0)
                        {
                            printf("    addi $t2, $fp, %d\n", h->result.offset);
                            printf("    lw $t1, 0($t2)\n");
                        }
                        else
                            printf("    sw $t3, %d($sp)\n", h->result.offset);
                        break;
          case ASSIGNOP_ARRAY:
                        printf("    lw $t1,  %d($sp)\n",h->opn2.offset);
                        if(h->opn1.level == 0)
                        {
                            printf("    addi $t2, $fp, %d\n",h->opn1.offset);
                            printf("    add $t1, $t1, $t2\n");
                        }
                        else
                            printf("    add $t1, $t1, %d($sp)\n",h->opn1.offset);
                        printf("    lw $t2, 0($t1)\n",h->opn1.offset);
                        if (h->result.level == 0)
                        {
                            printf("    sw $t2, %d($fp)\n",h->result.offset);
                        }
                        else
                            printf("    sw $t2, %d($sp)\n", h->result.offset);
                        break;
          case ARRAY_ASSIGNOP:
                        printf("    lw $t2,  %d($sp)\n",h->opn1.offset);
                        printf("    lw $t1,  %d($sp)\n",h->opn2.offset);
                        if(h->result.level == 0)
                            printf("    add $t1, $t1, -%d($fp)\n",h->result.offset);
                        else
                            printf("    add $t1, $t1, %d($sp)\n",h->result.offset);
                        printf("    sw $t2, %d($t1)\n",h->opn1.offset);
                        break;
          case PLUS:
          case MINUS:
          case STAR:
          case DIV:
                        printf("    lw $t1, %d($sp)\n", h->opn1.offset);
                        printf("    lw $t2, %d($sp)\n", h->opn2.offset);
                        if (h->op == PLUS)
                            printf("    add $t3,$t1,$t2\n");
                        else if (h->op == MINUS)
                            printf("    sub $t3,$t1,$t2\n");
                        else if (h->op == STAR)
                            printf("    mul $t3,$t1,$t2\n");
                        else
                        {
                            printf("    div $t1, $t2\n");
                            printf("    mflo $t3\n");
                        }
                        printf("    sw $t3, %d($sp)\n", h->result.offset);
                        break;
          case PRE_PLUS_SELF:
          case PRE_MINUS_SELF:
                        printf("    lw $t1, %d($sp)\n",h->opn1.offset);
                        printf("    addi $t1, $t1, %c1\n",h->op == PRE_PLUS_SELF?'+':'-');
                        printf("    sw $t1, %d($sp)\n",h->opn1.offset);
                        printf("    move $t3, $t1\n");
                        printf("    sw $t3, %d($sp)\n", h->result.offset);
                        break;
          case NEXT_PLUS_SELF:
          case NEXT_MINUS_SELF:
                        printf("    lw $t1, %d($sp)\n",h->opn1.offset);
                        printf("    move $t3, $t1\n");
                        printf("    sw $t3, %d($sp)\n", h->result.offset);
                        printf("    addi $t1, $t1, %c1\n",h->op == NEXT_PLUS_SELF?'+':'-');
                        printf("    sw $t1, %d($sp)\n",h->opn1.offset);
                        break;
          case ASSIGNOP_PLUS:
          case ASSIGNOP_MINUS:
          case ASSIGNOP_STAR:
          case ASSIGNOP_DIV:
                        printf("    lw $t1, %d($sp)\n",h->opn2.offset);
                        printf("    lw $t2, %d($sp)\n",h->opn1.offset);
                        if (h->op != ASSIGNOP_DIV)
                            printf("    %s $t3, $t2, $t1\n",h->op==ASSIGNOP_PLUS?"add":h->op==ASSIGNOP_MINUS?"sub":"mul");
                        else
                        {
                            printf("    div $1, $2\n");
                            printf("    mflo $3\n");
                        }
                        printf("    sw $t3, %d($sp)\n",h->opn1.offset);
                        break;
          case GOTO:    
                        printf("    j %s\n",h->result.id);
                        break;
          case RETURN:  
                        printf("    lw $v0,%d($sp)\n",h->result.offset);
                        printf("    jr $ra\n");
                        break;
          case JLE:
          case JLT:
          case JGE:
          case JGT:
          case EQ:
          case NEQ:
                        printf("    lw $t1, %d($sp)\n", h->opn1.offset);
                        printf("    lw $t2, %d($sp)\n", h->opn2.offset);
                        if (h->op == JLE)
                            printf("    ble $t1,$t2,%s\n", h->result.id);
                        else if (h->op == JLT)
                            printf("    blt $t1,$t2,%s\n", h->result.id);
                        else if (h->op == JGE)
                            printf("    bge $t1,$t2,%s\n", h->result.id);
                        else if (h->op == JGT)
                            printf("    bgt $t1,$t2,%s\n", h->result.id);
                        else if (h->op == EQ)
                            printf("    beq $t1,$t2,%s\n", h->result.id);
                        else
                            printf("    bne $t1,$t2,%s\n", h->result.id);
                        break; 
          case FUNCTION: 
                        printf("\n%s:\n", h->result.id);
                        // if (!strcmp(h->result.id,"main"))
                        //     printf("    addi $sp, $sp, -%d\n",symbolTable.symbols[h->result.offset].offset);
                        break;
          case PARAM:    
                        break;
          case LABEL:   
                        printf("\n%s:\n",h->result.id);
                        break;
          case ARG:      
                        break;
          case CALL:     
                        for(hh=h,i=0;i<symbolTable.symbols[h->opn1.offset].paramnum;i++)
                            hh=hh->prior;
                        printf("    move $t0,$sp\n"); 
                        printf("    addi $sp, $sp, -%d\n", symbolTable.symbols[h->opn1.offset].offset);
                        printf("    sw $ra,0($sp)\n"); 
                        i=h->opn1.offset+1;  
                        while (symbolTable.symbols[i].flag=='P')
                        {
                            printf("    lw $t1, %d($t0)\n", hh->result.offset);
                            printf("    move $t3,$t1\n");
                            printf("    sw $t3,%d($sp)\n",  symbolTable.symbols[i].offset);
                            hh=hh->next;
                            i++;
                        }
                        printf("    jal %s\n",h->opn1.id);
                        printf("    lw $ra,0($sp)\n");
                        printf("    addi $sp,$sp,%d\n",symbolTable.symbols[h->opn1.offset].offset);
                        printf("    sw $v0,%d($sp)\n", h->result.offset);
                        break;
        }
    h=h->next;
    } while (h != tail);
}