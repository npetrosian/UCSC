#####################################################################
# Created by: 	Petrosian, Natalie
#	      	npetrosi
#	      	7 December 2018
#
# Assignment: 	Lab 5: Subroutines
#	      	CMPE 012, Computer Systems and Assembly Language
# 	      	UC Santa Cruz, Fall 2018
#
# Description: 	This program will display a string and prompt the 
#               user to type the same string in a given time limit.
#               It will check if this string is identical to the 
#               given one and whether the user made the time limit.
#               If the user types in the prompt incorrectly or does
#               not finish the prompt in the given time limit, the
#               game is over. 
#
# Notes: 	This program is intended to be run from the MARS IDE
####################################################################

.text 

#--------------------------------------------------------------------
# give_type_prompt
#
# input:  $a0 - address of type prompt to be printed to user
#
# output: $v0 - lower 32 bit of time prompt was given in milliseconds
#--------------------------------------------------------------------

give_type_prompt: 
                  li $v0, 4 # printing the prompt to the console
                  # $a0 is already populated with prompt by caller
                  syscall
                  
                  li $v0, 30 # getting the current time into $a0
                  syscall
                  
                  move $v0, $a0 # moving $a0 into $v0 as instructed
                  
                  jr $ra 
                
#--------------------------------------------------------------------
# check_user_input_string
#
# input:  $a0 - address of type prompt printed to user
#         $a1 - time type prompt was given to user
#         $a2 - contains amount of time allowed for response
#
# output: $v0 - success or loss value (1 or 0)
#--------------------------------------------------------------------

check_user_input_string: 
                         # pushing $ra into the stack pointer to preserve it
                         subi $sp, $sp, 4
                         sw   $ra, ($sp)
                        
                         move $t0, $a0        # address of prompt 
                         move $t1, $a1        # start time (milliseconds) for current string
                         move $t2, $a2        # time (milliseconds) allotted for the user
                         
                         # read string from the user
                         la $a0, userInput    # set the address for userInput
                         li $a1, 256          # set maximum number of characters
                         li $v0, 8            # syscall 8 to read strings
                         syscall              # make the call
                         
                         li $v0, 30           # getting the current time into $a0
                         syscall
                         move $t3, $a0        # save current millisecond timestamp in $t3
                         
                         sub $t4, $t3, $t1    # milliseconds since user saw prompt
                         nop 
                         
                         # Check to see if $t4 is less than $t2, if so: save 1 into $v0
                         # If not, put 0 into $v0 before jr 
                         
                         ble $t4, $t2, finish_in_time
                         bgt $t4, $t2, finished_late
                         
                         finish_in_time: 
                                   li $v0, 1
                                   # restore $a0 and $a1 before calling compare_strings
                                   move $a0, $t0
                                   la   $a1, userInput
                                   
                                   #################################
                                   #                               #
                                   # This is done for extra credit #
                                   #                               #
                                   #################################
                                   jal setup_strings_extra_credit
                                   
                                   
                                   jal  compare_strings 
                                   j    exit_check_user_input
                         
                         finished_late: 
                                   li $v0, 0
                                   j exit_check_user_input 
                     
                         exit_check_user_input: 
                                   # popping $ra from the stack
                                   lw $ra, ($sp)
                                   addi $sp, $sp, 4
                                   # return to caller
                                   jr $ra

#--------------------------------------------------------------------
# compare_strings
#
# input:  $a0 - address of first string to compare
#         $a1 - address of second string to compare
#
# output: $v0 - comparison result (1 == strings the same, 0 == strings not the same)
#--------------------------------------------------------------------

compare_strings: 
                  # pushing $ra into the stack pointer to preserve it
                  subi $sp, $sp, 4
                  sw   $ra, ($sp)
                  
                  move $t0, $a0        # address of prompt 
                  move $t1, $a1        # address of what the user typed
                  
                  compare_strings_loop: 
                             move $a0, $zero
                             move $a1, $zero
                             lb   $a0, ($t0) # grab the byte at address $a0
                             lb   $a1, ($t1) # grab the byte at address $a1
                             
                             jal compare_chars
                             beqz $v0, compare_strings_failed
                              
                             # increment address of $t0 and $t1                              
                             addi $t0, $t0, 1 # increment $t0 for next iteration
                             addi $t1, $t1, 1 # increment $t1 for next iteration
     
                             bne $a0, 0, compare_strings_loop
                             
                  j compare_strings_success 
                  
                  compare_strings_success:
                             li $v0, 1
                             j exit_compare_strings
                                   
                             
                  compare_strings_failed:
                             li $v0, 0
                             j exit_compare_strings      
                  
                  
                  exit_compare_strings:
                            # popping $ra from the stack
                            lw $ra, ($sp)
                            addi $sp, $sp, 4
                            # return to caller
                            jr $ra

#--------------------------------------------------------------------
# compare_chars
#
# input:  $a0 - first char to compare (contained in the least significant byte)
#         $a1 - second char to compare (contained in the least significant byte)
#
# output: $v0 - comparison result (1 == chars the same, 0 == chars not the same)
#
#--------------------------------------------------------------------

compare_chars: 
                  # pushing $ra into the stack pointer to preserve it
                  subi $sp, $sp, 4
                  sw   $ra, ($sp)
                  
                  beq $a0, $a1, compare_chars_success # if characters are equal, jump to success
                  j compare_chars_failed              # else, jump to failure
 
                  compare_chars_success: 
                         li $v0, 1                    # set return value to 1 for success
                         j exit_compare_chars         # exit
                             
                  compare_chars_failed:  
                         li $v0, 0                    # set return value to 0 for failure
                         j exit_compare_chars         # exit   
                  
                  exit_compare_chars: 
                         # popping $ra from the stack
                         lw $ra, ($sp)
                         addi $sp, $sp, 4
                         # return to caller
                         jr $ra
                         
#--------------------------------------------------------------------
# setup_strings_extra_credit
#
# This subroutine copies the strings in $a0 and $a1 to buffer1 and
# buffer2 in .data but in the process it converts letters to uppercase
# and it skips punctuation found in the original strings. Hence we are
# left with two uppercase strings to compare, with no punctuations. This
# in effect achieves the result that the extra credit portion of the 
# rubric requests.
#
# input:  $a0 - address of primary string containing original string
#         $a1 - address of string containing the user typed string
#
# output: $a0 - address of buffer1 which has the primary string in 
#               UPPERCASE and no punctuation
#             
#         $a1 - address of buffer2 which contains the user typed
#               response in UPPERCASE excluding any punctuations
#
#--------------------------------------------------------------------
setup_strings_extra_credit:

                  # pushing $ra into the stack pointer to preserve it
                  subi $sp, $sp, 4
                  sw   $ra, ($sp)
                  
                  
                  # convert the letters in the primary string to be all uppercase, and
                  # drop punctuations from it. Put this string in address buffer1
                  move $t0, $a0      # save $a0 into $t0 - $t0 will be the pointer to primary string chars
                  la   $t2, buffer1  # $t2 is the pointer to buffer1
                  convert_primary_loop: 
                             
                             lb   $a3, ($t0) # grab the byte, pointed to by $t0
                                                   
                             addi $t0, $t0, 1 # increment $t0 for next iteration
                             
                             #ignore punctuations
                             beq $a3, 39, convert_primary_loop # skip apostrophe
                             beq $a3, 44, convert_primary_loop # skip comma
                             beq $a3, 46, convert_primary_loop # skip period
                             
                             # check character and convert to uppercase if need be
                             jal convert_to_uppercase
                             
                             # push $a3 into buffer1
                             sb $a3, ($t2)
                             addi $t2, $t2, 1 #increment pointer to buffer1 for next iteration
     
                             bne $a3, 0, convert_primary_loop
                             
                             
                  # convert the letters in the user input to be all uppercase, and
                  # drop punctuations from it. Put this string in address buffer2
                  move $t0, $a1      # save $a1 into $t0 - $t0 will be the pointer to user input string chars
                  la   $t2, buffer2  # $t2 is the pointer to buffer2
                  convert_userinput_loop: 
                             
                             lb   $a3, ($t0) # grab the byte, pointed to by $t0
                                                   
                             addi $t0, $t0, 1 # increment $t0 for next iteration
                             
                             #ignore punctuations
                             beq $a3, 39, convert_userinput_loop # skip apostrophe
                             beq $a3, 44, convert_userinput_loop # skip comma
                             beq $a3, 46, convert_userinput_loop # skip period
                             
                             # check character in $a3 and convert to uppercase if need be
                             jal convert_to_uppercase
                             
                             # push $a3 into buffer2
                             sb $a3, ($t2)
                             addi $t2, $t2, 1 #increment pointer to buffer2 for next iteration
     
                             bne $a3, 0, convert_userinput_loop
                             
                   setup_string_exit:
                   
                             # we need to load $a0 and $a1 with the addresses of buffer1 and buffer2
                             
                             # load $a0 with the address of buffer1
                             la $a0, buffer1
                             
                             # load $a1 with the address of buffer2
                             la $a1, buffer2
                   
                             # popping $ra from the stack
                             lw $ra, ($sp)
                             addi $sp, $sp, 4
                             # return to caller
                             jr $ra 
                             
                                                                 


#--------------------------------------------------------------------
# convert_to_uppercase
#
# input:  $a3 - character to be examined and converted to uppercase if need be
#      
# output: $a3 -  ensured to be uppercase
#    
#--------------------------------------------------------------------
convert_to_uppercase:

                 # pushing $ra into the stack pointer to preserve it
                  subi $sp, $sp, 4
                  sw   $ra, ($sp)
                  
                  bge $a3, 97, uppercase # if a lowecase character convert - lowercase a is 97
                  j convert_exit         # else, just exit
                  
                  uppercase:
                        subi $a3, $a3, 32 # subtract decimal 32 to convert to uppercase
                        j convert_exit
                  
                  convert_exit:
                         # popping $ra from the stack
                         lw $ra, ($sp)
                         addi $sp, $sp, 4
                         # return to caller
                         jr $ra
                  

                 
.data

userInput: .space 256
buffer1:   .space 256
buffer2:   .space 256






