#####################################################################
# Created by: 	Petrosian, Natalie
#	      	npetrosi
#	      	27 November 2018
#
# Assignment: 	Lab 4: ASCII Decimal to 2SC
#	      	CMPE 012, Computer Systems and Assembly Language
# 	      	UC Santa Cruz, Fall 2018
#
# Description: 	This program will read two program arguments, print
#               them out, print their sum, prints the sum's binary
#               representation in 2SC, and the sum in Morse code. 
#
# Notes: 	This program is intended to be run from the MARS IDE
####################################################################


# Step 1: Read 2 program arguments: signed decimal numbers 
# Before inputting the program arguments, ensure the appropriate settings are in place. 
# "Program arguments provided to MIPS program" is enabled, and "Delayed branching" is off. 
# The user will assemble, and is prompted to enter program arguments in the labeled text box. 
# Data is entered space separated (i.e -45 54)


# Step 2: Print the user inputs to the console
# To print the string "You entered the decimal numbers: " we need the following line in the .data segment: 
#
# .data
#       prompt: .asciiz "\nYou entered the decimal numbers:\n"
#
# We can print it to the console as follows: 
#
# li $v0, 4
# la $a0, prompt
# syscall
#
# The address of an array of null-terminated strings containing the arguments (argv) will be 
# placed in register $a1.
# To print the first parameter, do this:
#
# lw $a0, 0($a1)
# li $v0, 4
# syscall
#
# To print the second parameter, do this:
#
# lw $a0, 4($a1)
# li $v0, 4
# syscall
# 
# Obviously, the values of the first and second parameters should be separated by a space and the 
# second parameter should be followed by a carriage return when printing to the console. 
# These could be achieved by separate data segments like these:
# 
# space: .asciiz " "
# return: .asciiz "\n"


# Step 3: Convert 1st ASCII string into signed integer
# Converting ASCII to decimal: ASCII -48 = Decimal (this works for numbers 0-9)
# subi $t0 $t1 48
# For the first parameter, we need to parse every digit. Each digit will be in the range of 0-9 but the first
# character may also be a negative sign (decimal 45 in ASCII). We need a loop to traverse every byte. 
# If we encounter a (-) character, we need to set a flag that means the parameter is a negative number. 
# Our range of [-64, 63] includes two-digit and single-digit characters, so we must account for that. 
# The ASCII code for each character will be subtracted by 48, and the result will be added to a total sum of 
# most significant digit * 10 + least significant digit, saved in $t0 depending on whether it's a single-digit 
# integer or two-digit integer. If the negative flag is set, the calculated value will be subtracted from zero to 
# get the negated integer. 


# Step 4: Store the 1st signed integer, explained in step 3 above, into $s1
#
# move $s1, $t0


# Step 5: Convert 2nd ASCII string into signed integer
# This step is exactly like step 3, except that it is for the second parameter and $t1 will be used to save the signed
# integer for the second parameter. 


# Step 6: Store the 2nd signed integer, explained in step 5 (and 3), into $s2
# 
# move $s2, $t1


# Step 7: Add the two signed integers and store the sum in $s0
# The two signed integers are stored in $s1 and $s2
# add $s0 $s2 $s1


# Step 8: Print the sum to the console as a decimal
# Under the .data segment, we need the following for proper messaging: 
# 
# .data
#       sum: .asciiz "The sum in decimal is: "
#
# We can print it to the console as follows: 
#
# li $v0, 4
# la $a0, sum_prompt
# syscall
# To print the sum as a character, we need to convert $s0 back to ASCII so we can print it back to the console without using the forbidden syscalls


# Step 9: Print the sum as a 2SC binary number to the console
# The sum of the values of the program arguments are stored in $s0.
# To convert the value in $s0 to binary, we need to set up a loop as follows: 
# Start with a mask that has a 32nd-bit set to 1, and everything else to 0
# With each iteration of the loop, AND the mask with the value in $s0, and if the result of the logical AND is 0, print 0. Otherwise, print 1
# Then shift the mask by 1 and repeat this process
# Loop terminates when the mask turns to 0 

# EXTRA CREDIT SEGMENT
# 
# Step 10: Print the sum in Morse code to the console
# The morse code has a pattern to it, as follows here:
# A number N between 1 and 5 is represented by N dots and 5-N dashes.
# A number N between 6 and 9 is represented by N-5 dashes and 5-(N-5) dots.
# A zero will be treated as the exception, represented by 5 dashes.
# Once the sum is at hand in $s0, it's absolute value will be loaded into $s3
# The Most Significan digit (if there) and the least significant digit will be retrieved.
# Labels for the numbers between 1 and 5, 6 and 9, and the exception zero will be created.
# These labels will be jumped to in order to output the proper morse code for MSD of 1 to 9
# and LSD of 0 through 9.
# For negative numbers a field in .data will be created to handle a morse code for dash -....-
# For zero sum a field in .data will be created to handle a morse code for dash -----

.text 

lw $t0, ($a1)      # point to the first argument

lb $t1, ($t0)      # grab the first two bytes from the first argument
lb $t2, 1($t0)     # place them in $t1 and $t2

jal process_negative # first check to see if the first argument is negative, then proceed to pertinent labels from there

move $s1, $t7 # save the first parameter in $t7, which is populated below, into $s1

lw $t0, 4($a1) # point to the second argument

lb $t1, ($t0) # grab the first two bytes of the second argument
lb $t2, 1($t0) # place them in $t1 and $t2

jal process_negative # check to see if the second argument is negative, then proceed to pertinent labels from there

move $s2, $t7 # save the second parameter in $t7, which is populated below, into $s2

jal user_input # jump to the routine that informs the user of the program arguments

jal print_sum # print the sum per the rubric

jal print_sum_bin # print the 2SC sum in binary

jal morse # print the sum in morse code

j exit # exit the program


process_positive: nop
                  beq $t2, $0, pos_single_digit # if $t2 is null, the argument is a positive, single digit
                  j pos_double_digit # otherwise it is a positive, double digit
                  
pos_single_digit: nop
                  subi $t7, $t1, 48 # subtract 48 from the ASCII value, populate $t7
                  jr $ra # return to the line after jal

pos_double_digit: nop 
                  subi $t6, $t1, 48 # subtract 48 from the ASCII value and store in $t6 (LSD)
                  addi $t5, $zero, 10 # load 10 into $t5 (prepare to multiply by 10)
                  mult $t6, $t5 # multiply 10 to calculate MSD
                  mflo $t6
                  subi $t5, $t2, 48 # subtract 48 from the MSD and load into $t5
                  add $t7, $t6, $t5 # add $t5 and $t6 to get the integer value of the argument in $t7
                  jr $ra # return to the line after jal

process_negative: nop 
                  bne $t1, 45, process_positive # if no negative sign is found, go to process_positive
                  lb $t3, 2($t0) # load one more byte
                  beq $t3, $0, neg_single_digit # otherwise, determine if negative single digit or positive single digit
                  j neg_double_digit

neg_single_digit: nop
                  lb $t3, 2($t0) # load one more byte
                  subi $t6, $t2, 48 # subtract 48 from the ASCII to get the integer value, and store into $t6
                  sub $t7, $0, $t6 # negate the integer value in $t6 and store into $t7
                  jr $ra # return to the line after jal
                  
neg_double_digit: nop
                  lb $t3, 2($t0) # load one more byte
                  subi $t6, $t2, 48 # subtract 48 from ASCII value and store in $t6
                  addi $t5, $zero, 10 # prepare to multiply by 10
                  mult $t6, $t5 # multiply MSD by 10
                  mflo $t6
                  subi $t5, $t3, 48 # subtract 48 from ASCII LSD and store in $t5
                  add $t6, $t6, $t5 # add MSD*10 and LSD
                  sub $t7, $0, $t6 # negate the value and load into $t7
                  jr $ra # return to the line after jal

user_input: 
                  li $v0, 4 # print the prompt
                  la $a0, user_entered
                  syscall
                  
                  lw $t0, ($a1) # load first argument
                  
                  li $v0, 4 # print first argument
                  la $a0, ($t0)
                  syscall
                  
                  li $v0, 4 # print a space
                  la $a0, space
                  syscall
                  
                  lw $t0, 4($a1) # load second argument
                  
                  li $v0, 4 # print the second argument
                  la $a0, ($t0)
                  syscall
                  
                  li $v0, 4 # print a carriage return
                  la $a0, return
                  syscall
                  
                  jr $ra # return to the line after jal

print_sum: 
                  
                  li $v0, 4 # print the sum message
                  la $a0, sum_prompt
                  syscall
                  
                  add $s0, $s2, $s1 # add $s1 and $s2 and save into $s0
                  
                  abs $s3, $s0 # save the absolute value of $s0 into $s3
                  
                  j print_sum_sign # jump to where the sign may be printed
                  
                  print_sum_l1: 
                  
                  j print_sum_val # jump to the routine that prints the sum value
                  
                  print_sum_l2: 
                  
                  li $v0, 4 # print a return
                  la $a0, return
                  syscall
                  
                  jr $ra # return to the line after jal
                  
print_sum_sign: 
                  bgez $s0, print_sum_l1 # jump to print_sum_l1 if the sum is greater than or equal to 0
                  
                  li $v0, 4 # otherwise, print a dash to denote negation
                  la $a0, dash
                  syscall
                  
                  j print_sum_l1 # jump to the routine that prints the value
                 
                  
                  
print_sum_val: 
                  div $s4, $s3, 10 # divide the absolute value by 10 and load into $s4
                  bgt $s4, 0, print_sum_MSD # if greater than 0, branch to print_sum_MSD
                  
                  print_sum_val_l1: 
                  
                  rem $s5, $s3, 10 # get the remainder of $s3 % 10 and load into $s5
                  bgez $s5, print_sum_LSD # if greater than or equal to 0, print the LSD
                  
                  
                  
                  
print_sum_MSD: 
                  addi $s5, $s4, 48 # add 48 to MSD and load into $s5
                  li $v0, 11 # print as character
                  la $a0, ($s5)
                  syscall
                  
                  j print_sum_val_l1 # jump back to continue with print_sum_val
                  
print_sum_LSD: 
                  addi $s6, $s5, 48 # add 48 to MSD and load into $s6
                  li $v0, 11 # print as character
                  la $a0, ($s6)
                  syscall
                  
                  j print_sum_l2 # jump back to continue in print_sum




print_sum_bin:
               li $v0, 4
               la $a0, sum_2SC         # prints the 2SC message prompt
               syscall
               
               addi $t3, $zero, 1      # load 1 as a mask
               sll $t3, $t3, 31        # shift left to place a 1 at the msb

loop_sum_bin:  and $t1, $s0, $t3       # AND the mask with the sum in $s0 to see if set
               srl $t3, $t3, 1         # shift right the mask for next iteration

               beqz $t1 print_zero     # if result of AND is 0 print a 0 character
               j print_one             # otherwise print a 1 character

print_zero:    li $v0, 4               # print a 0 and jump to the loop
               la $a0, zero            
               syscall
               beqz $t3 exit_sum_bin   # but exit if the mask is 0
               j loop_sum_bin

print_one:    li $v0, 4                # print a 1 and jump to loop
              la $a0, one
              syscall
              beqz $t3 exit_sum_bin    # but exit if the mask is 0
              j loop_sum_bin  

exit_sum_bin: nop
              li $v0, 4               # print a carriage return before returning
              la $a0, return
              syscall
              jr $ra   




# EXTRA CREDIT Morse code

morse:                   
                  li $v0, 4
                  la $a0, morse_prompt   # print the morse prompt per the rubric
                  syscall
                  
                  
                  beqz $s3, morse_zero   # morse code for 0 screws up the pattern let's take care of it early
                  
                  j morse_sign           # print the sign if negative
                  
                  morse_l1:
                  
                  div $s4, $s3, 10  # most sig digit goes in $s4
                  rem $s5, $s3, 10  # least sig digit goes in $s5
                  
                  bgt $s4, 0, morse_MSD #if there is a most significant digit process it
                  
                  morse_l2: 
                  
                  j morse_LSD # process least significant
                  
                  li $v0, 4 # print a carriage return
                  la $a0, return
                  syscall

morse_done:
                  jr $ra # return to caller
                  
morse_sign: 
                  bgez $s0, morse_l1
                  
                  li $v0, 4
                  la $a0, morse_dash
                  syscall
                  
                  j morse_l1
                  
morse_zero: 
                  
                  li $v0, 4
                  la $a0, morse_zero_code
                  syscall
                  
                  j morse_done
                  
                                 
morse_MSD:        
                  ble  $s4, 5, MSD_LE_5
                  bge  $s4, 6, MSD_GE_6
                  
                  morse_MSD_l1:
                  
                            li $v0, 11 # print whatever is contained in $t0 which is dot or dash
                            la $a0, ($t0)
                            syscall
                            
                            subi $t2, $t2, 1
                            
                            bgtz $t2, morse_MSD_l1 # loop the number of times in $t2
                            beq $t3, 0, morse_MSD_done
                             
                  morse_MSD_l2:
                  
                            li $v0, 11 # print whatever is contained in $t1 which is dot or dash
                            la $a0, ($t1)
                            syscall
                            
                            subi $t3, $t3, 1
                            
                            bgtz $t3, morse_MSD_l2 # loop the number of times in $t3
                            
                           
                            
                  morse_MSD_done:
                  li $v0, 4               # print a space before returning
                  la $a0, space
                  syscall
                            
                  j morse_l2
                  
                  
morse_LSD:        beq  $s5, 0, LSD_EQ_0
                  ble  $s5, 5, LSD_LE_5
                  bge  $s5, 6, LSD_GE_6
                  
                  morse_LSD_l1:
                  
                            li $v0, 11 # print whatever is contained in $t0 which is dot or dash
                            la $a0, ($t0)
                            syscall
                            
                            subi $t2, $t2, 1 # loop the number of times in $t2
                            
                            bgtz $t2, morse_LSD_l1
                            
                            beq $t3, 0, morse_LSD_done
                            
                  morse_LSD_l2:
                  
                            li $v0, 11 # print whatever is contained in $t1 which is dot or dash
                            la $a0, ($t1)
                            syscall
                            
                            subi $t3, $t3, 1 # loop the number of times in $t3
                            
                            bgtz $t3, morse_LSD_l2
                            
                  morse_LSD_done:
                            
                  j morse_done
                  
                  
                           
                  
MSD_LE_5:
                  li $t0, 0x2E     # load the code for a dot in $t0
                  li $t1, 0x2D     # load the code for a dash in $t1
                  move $t2, $s4    # number of times $t0 (0x2E) will be printed
                  li  $t3, 5
                  sub $t3, $t3,$t2 # number of times $t1 (0x2D) will be printed
                  j morse_MSD_l1   # return to caller
                  
MSD_GE_6:
                  li $t0, 0x2D     # load the code for a dash in $t0
                  li $t1, 0x2E     # load the code for a dot in $t1
                  subi $t2, $s4, 5 # number of times $t0 (0x2D) will be printed
                  li $t3, 5        # load 5 into $t3
                  sub $t3,$t3,$t2  # number of times $t1 (0x2E) will be printed
                  j morse_MSD_l1   # return to caller
                  
LSD_LE_5:
                  li $t0, 0x2E     # load the code for a dot in $t0
                  li $t1, 0x2D     # load the code for a dash in $t1
                  move $t2, $s5    # number of times $t0 (0x2E) will be printed
                  li $t3, 5        #load 5 into $t3
                  sub $t3,$t3,$t2  # number of times $t1 (0x2D) will be printed
                  j morse_LSD_l1   # return to caller
                  
LSD_GE_6:
                  li $t0, 0x2D     # load the code for a dash in $t0
                  li $t1, 0x2E     # load the code for a dot in $t1
                  move $t2, $s5   
                  subi $t2,$t2,5   # number of times $t1 (0x2D) will be printed
                  li $t3, 5
                  sub $t3, $t3,$t2 # number of times $t1 (0x2E) will be printed
                  j morse_LSD_l1   # return to caller
                  
LSD_EQ_0:
                  li $t0, 0x2D     # load the code for a dash in $t0
                  li $t1, 0x2E     # load the code for a dot in $t1
                  li  $t2, 5       # number of times $t0 (0x2D) will be printed
                  li $t3,  0       # number of times $t1 (0x2E) will be printed
                  j morse_LSD_l1   # return to caller



exit:             nop
                  li $v0, 4 # print a carriage return
                  la $a0, return
                  syscall
                  
                  
.data
user_entered:     .asciiz "You entered the decimal numbers:\n"
space:            .asciiz " "
return:           .asciiz "\n"
dash:             .asciiz "-"
sum_prompt:       .asciiz "\nThe sum in decimal is:\n"
sum_2SC:          .asciiz "\nThe sum in two's complement binary is:\n"
zero:             .asciiz "0"
one:              .asciiz "1"
morse_prompt:     .asciiz "\nThe sum in Morse code is:\n"
morse_dash:       .asciiz "-....- "
morse_zero_code:  .asciiz "-----"
                  
