####################################################################
# Created by:  Petrosian, Natalie
#              CruzID: npetrosi
#              8 November 2018
#
# Assignment:  Lab3: Looping in MIPS
#              CMPE 012, Computer Science and Assembly Language
#              UC Santa Cruz, Fall 2018
#
# Description: This program prompts the user for a positive integer
#              and then loops from 0 to the number that the user
#              entered. However, at any point in the loop if the
#              current value is divisabe by 5 it prints Flux and
#              if it's divisable by 7 it prints Bunny and if it's
#              divisable by both it prints Flux Bunny. Otherwise it
#              just prints the number.
#
# Notes:       This program is intended to be run from MARS IDE.
####################################################################

.text
      
main:
        # Prompt for the integer to enter
        li $v0, 4
        la $a0, prompt
        syscall
   
        # Read the integer and save it in $t0
        li $v0, 5
        syscall
        move $t0, $v0
     
        # set $t1 to 0. This is basically our counter 
        # from 0 up to the number the user entered
        li $t1, 0
   
loop:
        # if $t1 is greater than the number the user
        # has provided in $t0 exit the program
        bgt $t1, $t0, exit
     
        # get the remainder of dividing $t1 by 5 
        # and save it in $t2
        addi $t7, $zero, 5      # Store 5 in $t7
        div $t8, $t1, $t7       # Divide $t1 by 5 
        mfhi $t2                # Save remainder in $t2
         
        # get the remainder of dividing $t1 by 7
        # and save it $t3
        addi $t7, $zero, 7      # Store 7 in $t7
        div $t8, $t1, $t7       # Divide $t1 by 5
        mfhi $t3                # Save remainder in $t3
   
        # Add the two remainders and put the result
        # in $t4 if they are both 0 then $t4 will also
        # be zero so we can jump to where Flux Bunny is
        # being printed and then jump back to where we
        # just print a carriage return
        add $t4, $t2, $t3
        beqz $t4, fluxbunny
   
        # if we are still here that means $t1 is not divisable
        # by both 5 and 7 so let's check for 5
        # if the remainder of dividing $t1 by 5 was zero, then
        # jump to where Flux is being printed and then from
        # there back to where we just print a carriage return
        beqz $t2, justflux
   
        # if we are still here that means $t1 is not divisable
        # by 5 so let's check for 7
        # if the remainder of dividing $t1 by 7 was zero, then
        # jump to where Bunny is being printed and then from 
        # there back to where where we just print a carriage return
        beqz $t3, justbunny
    
        # if we are still here $t1 is neither divisable by 5
        # nor by 7 so let's just print the number out
        # Output the number in $t1
        li $v0, 1
        move $a0, $t1
        syscall
   
carriage:
        # Output a carriage return
        li $v0, 4
        la $a0, return
        syscall
     
        #increment register 1
        addi $t1, $t1, 1
   
        # jump to loop
        j loop
          
exit:          
        # Exit the program
        li $v0, 10
        syscall
   
fluxbunny:
        # print Flux Bunny and jump to
        # the carriage label
        li $v0, 4
        la $a0, fandb
        syscall
        j carriage
   
justbunny:
        # print Bunny and jump to
        # the carriage label
        li $v0, 4
        la $a0, justb
        syscall
        j carriage
   
justflux:
        # print Flux and jump to
        # the carriage label
        li $v0, 4
        la $a0, justf
        syscall
        j carriage
   
.data
prompt: .asciiz "Please input a positive integer: "
return: .asciiz "\n"
fandb: .asciiz "Flux Bunny"
justb: .asciiz "Bunny"
justf: .asciiz "Flux"
