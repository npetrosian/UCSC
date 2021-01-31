.text 
       # read string from the user
       la $a0, userInput    # set the address for userInput
       li $a1, 256          # set maximum number of characters
       li $v0, 8            # syscall 8 to read strings
       syscall              # make the call

       la $t0, userInput
       loop: 
            lb $t1, ($t0)

            li $v0, 11
            move $a0, $t1
            syscall 

            addi $t0, $t0, 1

            bne $t1, 0, loop



.data
userInput: .space 256