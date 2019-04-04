#include "loop_gen.hpp"

std::string instr_str(std::string instr, int op1, int op2, int op3, std::string mode, std::string label){
    if (instr == "add"){
        //Signed addition
        //add rd, ra, rb
        return ("add\tr" + std::to_string(op1) + ", r" + std::to_string(op2) + ", r" + std::to_string(op3));

    } else if (instr == "addi"){
        //Signed Addition with Immediate
        //addi rd, imm
        return ("addi\tr" + std::to_string(op1) + ", " + std::to_string(op2));

    } else if (instr == "sub"){
        //Signed subtraction
        //sub rd, ra, rb
        return ("sub\tr" + std::to_string(op1) + ", r" + std::to_string(op2) + ", r" + std::to_string(op3));

    } else if (instr == "and"){
        //Bitwise AND
        //and rd, ra, rb
        return ("and\tr" + std::to_string(op1) + ", r" + std::to_string(op2) + ", r" + std::to_string(op3));

    } else if (instr == "or"){
        //Bitwise OR
        //or rd, ra, rb
        return ("or\tr" + std::to_string(op1) + ", r" + std::to_string(op2) + ", r" + std::to_string(op3));

    } else if (instr == "xor"){
        //Bitwise XOR
        //xor rd, ra, rb
        return ("xor\tr" + std::to_string(op1) + ", r" + std::to_string(op2) + ", r" + std::to_string(op3));

    } else if (instr == "lsh"){
        //Logic Shift Left
        //lsh rd, ra, imm
        return ("lsh\tr" + std::to_string(op1) + ", r" + std::to_string(op2) + ", " + std::to_string(op3));

    } else if (instr == "rsh"){
        //Logic Shift Right
        //rsh rd, ra, imm
        return ("rsh\tr" + std::to_string(op1) + ", r" + std::to_string(op2) + ", " + std::to_string(op3));

    } else if (instr == "cmp"){
        //Compare
        //cmp mode ra, rb
        return ("cmp\t" + mode + " r" + std::to_string(op1) + ", r" + std::to_string(op2));

    } else if (instr == "ldr"){
        //Load PC Relative
        //ldr rd, imm
        if (op2 == -1){
            return ("ldr\tr" + std::to_string(op1) + ", " + label);
        } else {
            return ("ldr\tr" + std::to_string(op1) + ", " + std::to_string(op2));
        }
    } else if (instr == "ld08"){
        //Load 8-bit Data from Pointer
        //ld08 rd, ra
        return ("ld08\tr" + std::to_string(op1) + ", r" + std::to_string(op2));

    } else if (instr == "ld16"){
        //Load 16-bit Data from Pointer
        //ld16 rd, ra
        return ("ld16\tr" + std::to_string(op1) + ", r" + std::to_string(op2));

    } else if (instr == "ld32"){
        //Load 32-bit Data from Pointer
        //ld32 rd, ra
        return ("ld32\tr" + std::to_string(op1) + ", r" + std::to_string(op2));

    } else if (instr == "st08"){
        //Store 8-bit Data to Pointer
        //st08 ra, rd
        return ("st08\tr" + std::to_string(op1) + ", r" + std::to_string(op2));

    } else if (instr == "st16"){
        //Store 16-bit Data to Pointer
        //st16 ra, rd
        return ("st16\tr" + std::to_string(op1) + ", r" + std::to_string(op2));

    } else if (instr == "st32"){
        //Store 32-bit Data to Pointer
        //st32 ra, rd
        return ("st32\tr" + std::to_string(op1) + ", r" + std::to_string(op2));

    } else if (instr == "bro"){
        //Branch to Offset: Warning: instruction modified from
        //original instruction set to differentiate from branch
        //to register!
        //br always/true imm
        if (op1 == -1){
            return ("br\t" + mode + " " + label);
        } else {
            return ("br\t" + mode + " " + std::to_string(op1));
        }

    } else if (instr == "brr"){
        //Branch to Register: Warning: instruction modified from
        //original instruction set to differentiate from branch
        //to offset!
        //br always/true ra
        return ("br\t" + mode + " r" + std::to_string(op1));

    } else if (instr == "brt"){
        //Branch to Table
        //brt always/true ra
        return ("brt\t" + mode + " r" + std::to_string(op1));

    } else if (instr == "callo"){
        //Call to Offset: Warning: instruction modified from
        //original instruction set to differentiate from call
        //register!
        //call always/true imm
        if (op1 == -1){
            return ("call\t" + mode + " " + label);
        } else {
            return ("call\t" + mode + " " + std::to_string(op1));
        }
    } else if (instr == "callr"){
        //Call to Register: Warning: instruction modified from
        //original instruction set to differentiate from call
        //offset!
        //call always/true ra
        return ("call\t" + mode + " r" + std::to_string(op1));

    } else if (instr == "trap"){
        //Trap
        //trap imm
        if (op1 == -1){
            return ("trap\t" + label);
        } else {
            return ("trap\t" + std::to_string(op1));
        }
    } else if (instr == "reti"){
        //return (from Interrupt
        //reti
        return ("reti");

    } else if (instr == "tst"){
        //Test and Set
        //tst rd, ra
        return ("tst\tr" + std::to_string(op1) + ", r" + std::to_string(op2));

    } else if (instr == "nop"){
        //No Operation
        //nop
        return ("nop");

    } else if (instr == "mov"){
        //Move Register
        //mov rd, ra
        return ("mov\tr" + std::to_string(op1) + ", r" + std::to_string(op2));

    } else if (instr == "ret"){
        //Return
        //ret
        return ("ret");

    } else if (instr == "clr") {
        //Clear Register
        //clr rd
        return ("clr\tr" + std::to_string(op1));
    } else {
        std::cout << ("Error: invalid instruction");
        return ("nop");
    }
}

std::string loop_independent(   int loop_id,
                                const std::string& loop_type,
                                int temp_reg0, int temp_reg1, int temp_reg2, int temp_reg3,
                                int n_loops, int n_loops_reg,
                                std::vector<std::string>& arrays_base, int n_arrays, int base_reg0, int base_reg1,
                                int *fir_taps, int n_taps, int fir_temp_reg0, int fir_temp_reg1){
    std::string loop_string;
    if (n_loops > max_imm){
        std::cout <<("Error: number of loops exceeds maximum limit of 127");
    } else if (n_loops < 1){
        std::cout <<("Error: number of loops must be at least 1");
    } else if (loop_type == "add_constant"){
        //##############################//#
        //case loop_type is add_constant: #
        //this kind of loop simply adds a #
        //random constant to the first    #
        //n_loops elements of every array #
        //it receives in arrays_base      #
        //##############################//#

        //load number of loops into n_loops_reg:
        loop_string.append(instr_str("clr", n_loops_reg,0,0,"","") + "\n");
        loop_string.append(instr_str("addi", n_loops_reg, n_loops,0,"","") + "\n");
        //load random constant into temp_reg0:
        loop_string.append(instr_str("clr", temp_reg0, 0, 0, "", "") + "\n");
        // Seed with a real random value, if available
        std::random_device r;
        // Choose a random between -128 and 127
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(min_imm , max_imm);
        int constant = uniform_dist(e1);
        loop_string.append(instr_str("addi", temp_reg0, constant, 0, "", "") + "\n");
        //use temp_reg1 as counter
        loop_string.append(instr_str("clr", temp_reg1, 0, 0, "", "") + "\n");
        //use temp_reg2 as offset
        loop_string.append(instr_str("clr", temp_reg2, 0, 0, "", "") + "\n");
        //insert dummy instruction with imm=0 to determine address of loop head:
        loop_string.append(instr_str("trap", 0, 0, 0, "", "") + "\n");
        //label the start of the loop with its id:
        loop_string.append("loop_" + std::to_string(loop_id) + ":\n");
        for (int i = 0; i < n_arrays; i ++){
            //load array base address into base_reg0:
            loop_string.append(instr_str("ldr", base_reg0, -1, 0, "", ">ptr_" + arrays_base[i]) + "\n");
            //add current offset to base address:
            loop_string.append(instr_str("add", base_reg0, base_reg0, temp_reg2, "", "") + "\n");
            //load array[base_reg0 + offset] into temp_reg3:
            loop_string.append(instr_str("ld32", temp_reg3, base_reg0, 0, "", "") + "\n");
            //add constant to array element into temp_reg1:
            loop_string.append(instr_str("add", temp_reg3, temp_reg3, temp_reg0, "", "") + "\n");
            //store array element from temp_reg1 to address [base_reg0 + current_iteration]:
            loop_string.append(instr_str("st32", base_reg0, temp_reg3, 0, "", "") + "\n");
        }
        //increase loop count:
        loop_string.append(instr_str("addi", temp_reg1, 1, 0, "", "") + "\n");
        loop_string.append(instr_str("addi", temp_reg2, 4, 0, "", "") + "\n");
        //check if we reached n_loops:
        loop_string.append(instr_str("cmp", temp_reg1, n_loops_reg, 0, "neq", "") + "\n");
        //if not yet zero, jump back to loop start:
        loop_string.append(instr_str("bro", -1, 0, 0, "true", ">loop_" + std::to_string(loop_id)) + "\n");
        //insert dummy instruction with imm=1 to determine address of loop tail:
        loop_string.append(instr_str("trap", 1, 0, 0, "", "") + "\n");
        loop_string.append("end_" + std::to_string(loop_id) + ":\n");
        //after end, loop 4ever:
        loop_string.append(instr_str("bro", -1, 0, 0, "always", ">end_" + std::to_string(loop_id)) + "\n");
        loop_string.append("nop\n");
        //create arrays:
        for(int j=0; j < n_arrays; j++){
        	//create pointer to array:
            loop_string.append(".align\n");
            loop_string.append("ptr_" + arrays_base[j] + " :.word =" + arrays_base[j] +"\n");
            //define start of array:
            loop_string.append(arrays_base[j] + ":\n");
            //save memory for the array:
            for(int i=0;i<n_loops;i++){
                loop_string.append(".word 0x" + std::to_string(i) + "\n");
            }
        }
    } else if (loop_type == "add_arrays"){
        //############################//#
        //case loop_type is add_arrays: #
        //this type of loop adds the    #
        //first n_loops elements of the #
        //arrays it receives in arrays_ #
        //base, and stores the result   #
        //in the first of those arrays  #
        //############################//#
        if (n_arrays < 2) {
            std::cout << "Error: this loop type requires at least two arrays";
        } else {
            //load number of loops into n_loops_reg:
            loop_string.append(instr_str("clr", n_loops_reg,0,0,"","") + "\n");
            loop_string.append(instr_str("addi", n_loops_reg, n_loops, 0, "","") + "\n");
            //use temp_reg2 as loop counter:
            loop_string.append(instr_str("clr", temp_reg2,0,0,"","") + "\n");
            //use temp_reg3 as array address offset:
            loop_string.append(instr_str("clr", temp_reg3,0,0,"","") + "\n");
            //use temp_reg0 as partial sum result:
            loop_string.append(instr_str("clr", temp_reg0, 0, 0, "", "") + "\n");
            //insert dummy instruction with imm=0 to determine address of loop head:
            loop_string.append(instr_str("trap", 0, 0, 0, "", "") + "\n");
            //label the start of the loop with its id:
            loop_string.append("loop_" + std::to_string(loop_id) + ":\n");
            for (int i = 0; i < n_arrays; i++) {
                //load array base address into base_reg0:
            	loop_string.append(instr_str("ldr", base_reg0, -1, 0, "", ">ptr_" + arrays_base[i]) + "\n");
                //add offset to base address:
                loop_string.append(instr_str("add", base_reg0, base_reg0, temp_reg3, "", "") + "\n");
                //load array[base_reg + offset] into temp_reg1:
                loop_string.append(instr_str("ld32", temp_reg1, base_reg0, 0, "", "") + "\n");
                //add array element into partial sum on temp_reg0:
                loop_string.append(instr_str("add", temp_reg0, temp_reg1, temp_reg0, "", "") + "\n");
            }
            //load array base 0 address into base_reg1:
            loop_string.append(instr_str("ldr", base_reg1, -1, 0, "", ">ptr_" + arrays_base[0]) + "\n");
            //add offset to base address:
            loop_string.append(instr_str("add", base_reg1, base_reg1, temp_reg3, "", "") + "\n");
            //store array element from temp_reg0 to address [base_reg1 + offset]:
            loop_string.append(instr_str("st32", base_reg1, temp_reg0, 0, "", "") + "\n");
            //prepare temp_reg0 for next iteration:
            loop_string.append(instr_str("clr", temp_reg0, 0, 0, "", "") + "\n");
            //increase loop count and offset:
            loop_string.append(instr_str("addi", temp_reg2, 1, 0, "", "") + "\n");
            loop_string.append(instr_str("addi", temp_reg3, 4, 0, "", "") + "\n");
            //check if we reached n_loops:
            loop_string.append(instr_str("cmp", temp_reg2, n_loops_reg, 0, "neq", "") + "\n");
            //if not yet zero, jump back to loop start:
            loop_string.append(instr_str("bro", -1, 0, 0, "true", ">loop_" + std::to_string(loop_id)) + "\n");
            //insert dummy instruction with imm=1 to determine address of loop tail:
            loop_string.append(instr_str("trap", 1, 0, 0, "", "") + "\n");
            loop_string.append("end_" + std::to_string(loop_id) + ":\n");
            //after end, loop 4ever:
            loop_string.append(instr_str("bro", -1, 0, 0, "always", ">end_" + std::to_string(loop_id)) + "\n");
            loop_string.append("nop\n");
            //create arrays:
            loop_string.append(".align\n");
            for(int j=0; j < n_arrays; j++){
            	//create pointer to array:
                loop_string.append("ptr_" + arrays_base[j] + " :.word =" + arrays_base[j] +"\n");
                //define start of array:
                loop_string.append(arrays_base[j] + ":\n");
                //save memory for the array:
                for(int i=0;i<n_loops;i++){
                    loop_string.append(".word 0x" + std::to_string(i+j*n_loops) + "\n");
                }
            }
        }
    } else if (loop_type == "swap_arrays"){
        //#############################//#
        //case loop_type is swap_arrays: #
        //this kind of loops swaps       #
        //the first n_loops elements of  #
        //array_i with array_(i+1), i.e. #
        //array_i[j] <= array_(i+1)[j] & #
        //array_(i+1)[j] <= array_i[j]   #
        //#############################//#
        if (n_arrays % 2 != 0) {
            std::cout << "Error: this type of loop requires an even amount of arrays";
        } else {
            //load number of loops into n_loops_reg:
            loop_string.append(instr_str("clr", n_loops_reg, 0, 0, "", "") + "\n");
            loop_string.append(instr_str("addi", n_loops_reg, n_loops, 0, "", "") + "\n");
            //use temp_reg2 as loop counter:
            loop_string.append(instr_str("clr", temp_reg2, 0, 0, "", "") + "\n");
            //use temp_reg3 as address offset:
            loop_string.append(instr_str("clr", temp_reg3, 0, 0, "", "") + "\n");
            //insert dummy instruction with imm=0 to determine address of loop head:
            loop_string.append(instr_str("trap", 0, 0, 0, "", "") + "\n");
            //label the start of the loop with its id:
            loop_string.append("loop_" + std::to_string(loop_id) + ":\n");

            for (int i = 0; i < n_arrays-1; i = i+2){
                //load array[i] base address into base_reg0:
                loop_string.append(instr_str("ldr", base_reg0, -1, 0, "", ">ptr_" + arrays_base[i]) + "\n");
                //add current offset to base address:
                loop_string.append(instr_str("add", base_reg0, base_reg0, temp_reg3, "", "") + "\n");
                //load array[base_reg + offset] into temp_reg0:
                loop_string.append(instr_str("ld32", temp_reg0, base_reg0, 0, "", "") + "\n");

                //load array[i+1] base address into base_reg1:
                loop_string.append(instr_str("ldr", base_reg1, -1, 0, "", ">ptr_" + arrays_base[i+1]) + "\n");
                //add current offset to base address:
                loop_string.append(instr_str("add", base_reg1, base_reg1, temp_reg3, "", "") + "\n");
                //load array[base_reg1 + offset] into temp_reg1:
                loop_string.append(instr_str("ld32", temp_reg1, base_reg1, 0, "", "") + "\n");

                //store array element from temp_reg0 to address [base_reg1 + current_iteration]:
                loop_string.append(instr_str("st32", base_reg1, temp_reg0, 0, "", "") + "\n");
                //store array element from temp_reg1 to address [base_reg0 + current_iteration]:
                loop_string.append(instr_str("st32", base_reg0, temp_reg1, 0, "", "") + "\n");
            }
            //increase loop count & offset:
            loop_string.append(instr_str("addi", temp_reg2, 1, 0, "", "") + "\n");
            loop_string.append(instr_str("addi", temp_reg3, 4, 0, "", "") + "\n");
            //check if we reached n_loops:
            loop_string.append(instr_str("cmp", temp_reg2, n_loops_reg, 0, "ll", "") + "\n");
            //if not yet zero, jump back to loop start:
            loop_string.append(instr_str("bro", -1, 0, 0, "true", ">loop_" + std::to_string(loop_id)) + "\n");
            //insert dummy instruction with imm=1 to determine address of loop tail:
            loop_string.append(instr_str("trap", 1, 0, 0, "", "") + "\n");
            loop_string.append("end_" + std::to_string(loop_id) +  ":\n");
            loop_string.append(instr_str("bro", -1, 0, 0, "always", ">end_" + std::to_string(loop_id)) + "\n");
            loop_string.append("nop\n");
            //create arrays:
            loop_string.append(".align\n");
            for(int j=0; j < n_arrays; j++){
            	//create pointer to array:
                loop_string.append("ptr_" + arrays_base[j] + " :.word =" + arrays_base[j] +"\n");
                //define start of array:
                loop_string.append(arrays_base[j] + ":\n");
                //save memory for the array:
                for(int i=0;i<n_loops;i++){
                    loop_string.append(".word 0x" + std::to_string(j) + "\n");
                }
            }
        }
    } else if (loop_type == "fir_filter") {
        //############################################################################//#
        //case loop_type is fir_filter:                                                 #
        //In "Design of cascade form FIR filters with discrete valued coefficients",    #
        //Y. C. Lim and B. Liu. demonstrate that an FIR filter with -60dB of frequency  #
        //response ripple magnitude can be realized using two power-of-two terms for    #
        //each coefficient value, given that the filter is in cascade form and the      #
        //coefficient values are derived using mixed integer linear programming.        #
        //Here we mimic this idea, so that each coefficient is given by two immediate   #
        //values hard-coded into the "Logic shift right" opcodes themselves. 			#
        //This gives us coefficients that range from +-9.2e-05 to +-4.92e+4.			#
        //In our version, we only implement negative powers, so the biggest positive    #
        //coefficient achievable is 2. The implementation is restricted to filtering    #
        //only one signal given by arrays_base and its length is determined by:         #
        //L(x) = n_loops + length(fir_taps)/2; result is L(f(x)) = n_loops.             #
        //############################################################################//#
        if ((n_taps % 2 != 0) | (n_taps > 20)){
            std::cout <<("Error: the number of taps must be even and no more than 20");
        } else if (n_arrays != 1) {
            std::cout <<("Error: the number of arrays must be one");
        } else {
        	//branch to start of program:
            loop_string.append(instr_str("bro", -1, 0, 0, "always", ">main_" + std::to_string(loop_id)) + "\n");
            loop_string.append("nop\n");
        	//define pointer to array:
			loop_string.append("ptr_" + arrays_base[0] + ":	.word 0x00000300\n");
            //main prog:
            loop_string.append("main_" + std::to_string(loop_id) + ":\n");
            //load number of loops into n_loops_reg:
            loop_string.append(instr_str("clr", n_loops_reg, 0, 0, "", "") + "\n");
            loop_string.append(instr_str("addi", n_loops_reg, n_loops, 0, "", "") + "\n");
            //use temp_reg3 to count loop iterations:
            loop_string.append(instr_str("clr", temp_reg3, 0, 0, "", "") + "\n");
            //use temp_reg0 as zero for possible negations:
            loop_string.append(instr_str("clr", temp_reg0, 0, 0, "", "") + "\n");
            //load array_i base address into base_reg0:
            loop_string.append(instr_str("ldr", base_reg0, -1, 0, "", ">ptr_" + arrays_base[0]) + "\n");
            //insert dummy instruction with imm=0 to determine address of loop head:
            loop_string.append(instr_str("trap", 0, 0, 0, "", "") + "\n");
            //label the start of the loop with its id (which is in address 20):
            loop_string.append("loop_" + std::to_string(loop_id) + ":\n");
            //clear temporary filtered result registers:
            loop_string.append(instr_str("clr", temp_reg2, 0, 0, "", "") + "\n");
            loop_string.append(instr_str("clr", fir_temp_reg0, 0, 0, "", "") + "\n");
            loop_string.append(instr_str("clr", fir_temp_reg1, 0, 0, "", "") + "\n");
            //copy base_reg0 to base_reg1 because we will need to modify base_reg1 for each sample:
            loop_string.append(instr_str("mov", base_reg1, base_reg0, 0, "", "") + "\n");

            //"multiply" all n_taps/2 samples by the two corresponding taps: (this will take at most 24 TCK)
            for (int i = 0; i < n_taps; i = i + 2) {
                //load sample x[n+i] into temp_reg1, fir_temp_reg0 and fir_temp_reg1:
                loop_string.append(instr_str("ld32", temp_reg1, base_reg1, 0, "", "") + "\n");
                loop_string.append(instr_str("mov", fir_temp_reg0, temp_reg1, 0, "", "") + "\n");
                loop_string.append(instr_str("mov", fir_temp_reg1, temp_reg1, 0, "", "") + "\n");
                //apply both taps to x[n+i]:

                //tap 1:
                //check that fir_taps[i] is not out of range:
                if (abs(fir_taps[i]) > 15) {
                    std::cout << ("Error: FIR taps out of range!");
                    return "-1";
                }
                //check if sample x[n+i] is negative:
                loop_string.append(instr_str("cmp", temp_reg1, temp_reg0, 0, "gg", "") + "\n");
                loop_string.append(instr_str("bro", -1, 0, 0, "true", ">sample_x" + std::to_string(i) + "_is_pos1_" + std::to_string(loop_id)) + "\n");
                loop_string.append("nop\n");
                //if so, negate it, because we don't have arithmetic right shift:
                loop_string.append(instr_str("sub", fir_temp_reg0, temp_reg0, fir_temp_reg0, "", "") + "\n");
                loop_string.append("sample_x" + std::to_string(i) + "_is_pos1_" + std::to_string(loop_id) + ":\n");
                //at this point fir_temp_reg0 is positive, so right shift it by abs(fir_taps[i]):
                loop_string.append(instr_str("rsh", fir_temp_reg0, fir_temp_reg0, abs(fir_taps[i]), "", "") + "\n");
                //check whether coefficient is supposed to add or subtract:
                if (fir_taps[i] < 0) {
                    //if so, we have to negate the previous result:
                    loop_string.append(instr_str("sub", fir_temp_reg0, temp_reg0, fir_temp_reg0, "", "") + "\n");
                }
                //if x[n+i] was negative, we have to reverse the first inversion:
                loop_string.append(instr_str("bro", -1, 0, 0, "true", ">sample_x" + std::to_string(i) + "_was_pos1_" + std::to_string(loop_id)) + "\n");
                loop_string.append("nop\n");
                loop_string.append(instr_str("sub", fir_temp_reg0, temp_reg0, fir_temp_reg0, "", "") + "\n");
                loop_string.append("sample_x" + std::to_string(i) + "_was_pos1_" + std::to_string(loop_id) + ":\n");
                //at this point, fir_temp_reg0 contains the sample x[i] shifted by fir_taps[i]


                //tap 2:
                //check that fir_taps[i] is not out of range:
                if (abs(fir_taps[i+1]) > 15) {
                    std::cout << ("Error: FIR taps out of range!");
                    return "-1";
                }
                //check if sample x[n+i] is negative:
                loop_string.append(instr_str("cmp", temp_reg1, temp_reg0, 0, "gg", "") + "\n");
                loop_string.append(instr_str("bro", -1, 0, 0, "true", ">sample_x" + std::to_string(i) + "_is_pos2_" + std::to_string(loop_id)) + "\n");
                loop_string.append("nop\n");
                //if so, negate it, because we don't have arithmetic right shift:
                loop_string.append(instr_str("sub", fir_temp_reg1, temp_reg0, fir_temp_reg1, "", "") + "\n");
                loop_string.append("sample_x" + std::to_string(i) + "_is_pos2_" + std::to_string(loop_id) + ":\n");
                //at this point fir_temp_reg1 is positive, so right shift it by abs(fir_taps[i+1]):
                loop_string.append(instr_str("rsh", fir_temp_reg1, fir_temp_reg1, abs(fir_taps[i+1]), "", "") + "\n");
                //check whether coefficient is supposed to add or subtract:
                if (fir_taps[i+1] < 0) {
                    //if so, we have to negate the previous result:
                    loop_string.append(instr_str("sub", fir_temp_reg1, temp_reg0, fir_temp_reg1, "", "") + "\n");
                }
                //if x[n+i] was negative, we have to reverse the first inversion:
                loop_string.append(instr_str("bro", -1, 0, 0, "true", ">sample_x" + std::to_string(i) + "_was_pos2_" + std::to_string(loop_id)) + "\n");
                loop_string.append("nop\n");
                loop_string.append(instr_str("sub", fir_temp_reg1, temp_reg0, fir_temp_reg1, "", "") + "\n");
                loop_string.append("sample_x" + std::to_string(i) + "_was_pos2_" + std::to_string(loop_id) + ":\n");
                //at this point, fir_temp_reg0 contains the sample x[n+i] shifted by fir_taps[i+1]

                //now we add both samples "multiplied" by the taps:
                loop_string.append(instr_str("add", temp_reg1, fir_temp_reg0, fir_temp_reg1, "", "") + "\n");
                //and add the partial result to y[n] (temp_reg2):
                loop_string.append(instr_str("add", temp_reg2, temp_reg2, temp_reg1, "", "") + "\n");
                //increment i:
                loop_string.append(instr_str("addi", base_reg1, 4, 0, "", "") + "\n");
            }
            //store array element from temp_reg2 to address [array_base + current_iteration]:
            loop_string.append(instr_str("st32", base_reg0, temp_reg2, 0, "", "") + "\n");

            //Increase loop count:
            loop_string.append(instr_str("addi", temp_reg3, 1, 0, "", "") + "\n");
            loop_string.append(instr_str("addi", base_reg0, 4, 0, "", "") + "\n");  //this is kinda inefficient, or is it?...
            //check if we reached n_loops:
            loop_string.append(instr_str("cmp", temp_reg3, n_loops_reg, 0, "neq", "") + "\n");
            //if not yet zero, jump back to loop start of loop (address 20):
            loop_string.append(instr_str("clr", temp_reg1, 0, 0, "", "") + "\n");
            loop_string.append(instr_str("addi", temp_reg1, 20, 0, "", "") + "\n");
            loop_string.append(instr_str("brr", temp_reg1, 0, 0, "true", "") + "\n");
            //insert dummy instruction with imm=1 to determine address of loop tail:
            loop_string.append(instr_str("trap", 1, 0, 0, "", "") + "\n");
            loop_string.append("end_" + std::to_string(loop_id) + ":\n");
            //after end, loop 4ever:
            loop_string.append(instr_str("bro", -1, 0, 0, "always", ">end_" + std::to_string(loop_id)) + "\n");
            loop_string.append("nop\n");

            //define array:
            loop_string.append(".align\n");
            loop_string.append(".address 0x300\n");
            loop_string.append(arrays_base[0] + ":\n");
			//fill array with some signal:
			double pi 		= acos(-1);
			int signal;
			for (int i = 0; i < n_loops + n_taps/2; i++) {
				signal = int(round( amplitude0*sin(i*2*pi*f0/fs) + amplitude1*sin(i*2*pi*f1/fs) ));
                loop_string.append(".word " + std::to_string(signal) + "\n");
			}
        }
    } else {
        std::cout <<("loop_type: " + loop_type + " is unsupported");
    }
    return (loop_string);
}

std::string loop_dependent(int loop_id, const std::string& loop_type, int n_loops, int n_loops_reg,
                           int temp_reg0, int temp_reg1, int temp_reg2, int temp_reg3,
                           std::vector<std::string>& arrays_base, int n_arrays,
                           int base_reg0, int base_reg1, int base_reg2,
                           int *iir_x_taps, int *iir_y_taps, int n_x_taps, int n_y_taps,
                           int iir_temp_reg0, int iir_temp_reg1
                           ) {
    std::string loop_string;
    if (n_loops > max_imm){
        std::cout <<("Error: number of loops exceeds maximum limit of 127");
    } else if (n_loops < 1){
        std::cout <<("Error: number of loops must be at least 1");
    } else if (loop_type == "fibonacci"){
        //############################//#
        //case loop_type is fibonacci:  #
        //this kind of loop calculates  #
        //the first n_loops numbers of  #
        //a fibonacci-like sequence and #
        //writes it on arrays_base. The	#
    	//number of previous results 	#
    	//added is given by n_x_taps.	#
        //############################//#

        //load number of loops into n_loops_reg:
        loop_string.append(instr_str("clr", n_loops_reg, 0, 0, "", "") + "\n");
        loop_string.append(instr_str("addi", n_loops_reg, n_loops, 0, "", "") + "\n");
        if (n_arrays != 1) {
            std::cout << ("Error: the number of arrays for this type of loop must be exactly 1.");
        } else {
        	//load array address into base_reg0:
            loop_string.append(instr_str("ldr", base_reg0, -1, 0, "", ">ptr_" + arrays_base[0]) + "\n");
        	//clear temp_reg0 to make comp(n_loops_reg,0):
            loop_string.append(instr_str("clr", temp_reg0, 0, 0, "", "") + "\n");
            //initialize first N (n_x_taps) values:
            loop_string.append(instr_str("clr", temp_reg1, 0, 0, "", "") + "\n");
            loop_string.append(instr_str("addi", temp_reg1, 1, 0, "", "") + "\n");
            for(int i = 0; i < n_x_taps; i++){
                loop_string.append(instr_str("st32", base_reg0, temp_reg1, 0, "", "") + "\n");
                loop_string.append(instr_str("addi", base_reg0, 4, 0, "", "") + "\n");
            }
            //reset array pointer:
            loop_string.append(instr_str("ldr", base_reg0, -1, 0, "", ">ptr_" + arrays_base[0]) + "\n");
            //insert dummy instruction with imm=0 to determine address of loop head:
            loop_string.append(instr_str("trap", 0, 0, 0, "", "") + "\n");
            //label the start of the loop with its id:
            loop_string.append("loop_" + std::to_string(loop_id) + ":\n");
            //clear partial sum register:
            loop_string.append(instr_str("clr", temp_reg1, 0, 0, "", "") + "\n");
            //calculate fibonacci-like value: x[n] = sum(1..N, x[n-i]):
            for(int i = 0; i < n_x_taps; i++){
                loop_string.append(instr_str("ld32", temp_reg2, base_reg0, 0, "", "") + "\n");
                loop_string.append(instr_str("add", temp_reg1, temp_reg1, temp_reg2, "", "") + "\n");
                loop_string.append(instr_str("addi", base_reg0, 4, 0, "", "") + "\n");
            }
            //store fibonacci value and update pointer:
            loop_string.append(instr_str("st32", base_reg0, temp_reg1, 0, "", "") + "\n");
            loop_string.append(instr_str("addi", base_reg0, -4*(n_x_taps-1), 0, "", "") + "\n");

            //decrease loop count:
            loop_string.append(instr_str("addi", n_loops_reg, -1, 0, "", "") + "\n");
            //check if we reached zero:
            loop_string.append(instr_str("cmp", temp_reg0, n_loops_reg, 0, "neq", "") + "\n");
            //if not yet zero, jump back to loop start:
            loop_string.append(instr_str("bro", -1, 0, 0, "true", ">loop_" + std::to_string(loop_id)) + "\n");
            //insert dummy instruction with imm=1 to determine address of loop tail:
            loop_string.append(instr_str("trap", 1, 0, 0, "", "") + "\n");
            //after main loop is done, keep looping forever in end_loop:
            loop_string.append("end_loop_" + std::to_string(loop_id) + ":\n");
            loop_string.append(instr_str("bro", -1, 0, 0, "always", ">end_loop_" + std::to_string(loop_id)) + "\n");
            //insert nop in branch delay slot:
            loop_string.append(instr_str("nop", 0, 0, 0, "", "") + "\n");
        	//create pointer to array:
            loop_string.append(".align\n");
            loop_string.append("ptr_" + arrays_base[0] + " :.word =" + arrays_base[0] +"\n");
            //define start of array:
            loop_string.append(arrays_base[0] + ":\n");
            //save memory for the array:
            for(int i=0;i<n_loops;i++){
                loop_string.append(".word 0x00000000\n");
            }
        }
    } else if (loop_type == "logistic_map"){
        //################################################################//#
        //case loop_type is logistic_map: this kind of loop calculates the  #
        //first n_loops number of the logistic map given by the following   #
        //recursion: x_(n+1) = r * x_(n)* (1 - x_(n)). Cannot be implemented#
        //without multiplier.                                               #
        //################################################################//#
        std::cout <<("loop_type: " + loop_type + " is currently not implemented");

    } else if (loop_type == "dep_array_sum") {
        //################################//#
        //case loop_type is dep_array_sum:  #
        //this kind of loop calculates the  #
        //sum of elements in an array, with #
        //each element being added or sub-  #
        //tracted depending on the sign of  #
        //the previous value. It's useless. #
        //################################//#

        //load number of loops into n_loops_reg:
        loop_string.append(instr_str("clr", n_loops_reg, 0, 0, "", "") + "\n");
        loop_string.append(instr_str("addi", n_loops_reg, n_loops, 0, "", "") + "\n");
        //initialize loop counter in temp_reg0:
        loop_string.append(instr_str("clr", temp_reg0, 0, 0, "", "") + "\n");
        //clear temp_reg3 for future comparations with 0:
        loop_string.append(instr_str("clr", temp_reg3,0 , 0, "", "") + "\n");
        //insert dummy instruction with imm=0 to determine address of loop head:
        loop_string.append(instr_str("trap", 0, 0, 0, "", "") + "\n");
        //label the start of the loop with its id:
        loop_string.append("loop_" + std::to_string(loop_id) + ":\n");
        for (int i = 0; i< n_arrays; i++){
            //load element n of arrays_base[i]
            loop_string.append(instr_str("ldr", base_reg0, -1, 0, "", ">" + arrays_base[i]) + "\n");
            //add iteration number:
            loop_string.append(instr_str("add", base_reg0, base_reg0, temp_reg0, "", "") + "\n");
            //load x[n] into temp_reg1:
            loop_string.append(instr_str("ld32", temp_reg1, base_reg0, 0, "", "") + "\n");
            //load x[n+1] into temp_reg2:
            loop_string.append(instr_str("addi", base_reg0, 4, 0, "", "") + "\n");
            loop_string.append(instr_str("ld32", temp_reg2, base_reg0, 0, "", "") + "\n");
            //check if x[n] is less than zero:
            loop_string.append(instr_str("cmp", temp_reg1, temp_reg3, 0, "ll", "") + "\n");
            //if true, add x[n+1] to x[n]:
            loop_string.append(instr_str("bro", -1, 0, 0, "true", ">add_" + arrays_base[i] + "_lid_" + std::to_string(loop_id)) + "\n");
            loop_string.append("nop\n");
            //if not, subtract x[n+1] from x[n] and continue:
            loop_string.append(instr_str("sub", temp_reg1, temp_reg1, temp_reg2, "", "") + "\n");
            loop_string.append(instr_str("bro", -1, 0, 0, "always", ">cont_" + arrays_base[i] + "_lid_" + std::to_string(loop_id)) + "\n");
            loop_string.append("nop\n");
            loop_string.append("add_" + arrays_base[i] + "_lid_" + std::to_string(loop_id) + ":\n");
            loop_string.append(instr_str("add", temp_reg1, temp_reg1, temp_reg2, "", "") + "\n");
            loop_string.append("cont_" + arrays_base[i] + "_lid_" + std::to_string(loop_id) + ":\n");
            //store x[n] +- x[n+1] into array[n+1]:
            loop_string.append(instr_str("st32", temp_reg1, base_reg0, 0, "", "") + "\n");
        }
        //increase loop count:
        loop_string.append(instr_str("addi", temp_reg0, 1, 0, "", "") + "\n");
        //check if we reached n_loops:
        loop_string.append(instr_str("cmp", temp_reg0, n_loops_reg, 0, "neq", "") + "\n");
        //if not yet zero, jump back to loop start:
        loop_string.append(instr_str("bro", -1, 0, 0, "true", ">loop_" + std::to_string(loop_id)) + "\n");
        //insert dummy instruction with imm=1 to determine address of loop tail:
        loop_string.append(instr_str("trap", 1, 0, 0, "", "") + "\n");
        //after main loop is done, keep looping forever in end_loop:
        loop_string.append("end_loop_" + std::to_string(loop_id) + ":\n");
        loop_string.append(instr_str("bro", -1, 0, 0, "always", ">end_loop_" + std::to_string(loop_id)) + "\n");
        //insert nop in branch delay slot:
        loop_string.append(instr_str("nop", 0, 0, 0, "", "") + "\n");
        //create arrays:
        loop_string.append(".align\n");
        for(int j=0; j < n_arrays; j++){
            //create pointer to array:
            loop_string.append("ptr_" + arrays_base[j] + " :.word =" + arrays_base[j] +"\n");
            //define start of array:
            loop_string.append(arrays_base[j] + ":\n");
            //save memory for the array:
            for(int i=0;i<n_loops;i++){
                loop_string.append(".word 0x" + std::to_string(j) + "\n");
            }
        }
    } else if (loop_type == "binom_coeffs"){
        //###############################################################################################
        //case loop_type is binom_coeffs: The binomial coefficients,  which count the number of ways	#
        //of selecting k elements out of a set of n elements, can be computed using the recurrence: 	#
    	// ( x )  = ( x-1 ) + ( x-1 )  ; with base cases: 	( x ) = ( x ) = 1  ; for all 1 <= y <= x-1	#
    	// ( y )	( y-1 )   (  y  )						( 0 )	( x )								#
        //Note that this function will imply loops with variable bounds, and recursive calls to itself.	#
    	//It receives n in n_x_taps, and k in n_y_taps and returns the calculated value in temp_reg3	#
    	//python code:																					#
		//    	def binomial(x,y):																		#
		//    	    if x == y:																			#
		//    	        return 1																		#
		//    	    elif y == 0:																		#
		//    	        return 1																		#
		//    	    else:																				#
		//    	        return binomial(x-1,y) + binomial(x-1, y-1) 									#
    	//###############################################################################################
        if ((n_x_taps < 1) | (n_x_taps > max_imm) | (n_y_taps < 1) | (n_y_taps > max_imm)  ){
			std::cout << ("Error: n or k out of range!");
        } else if (n_x_taps <= n_y_taps) {
        	std::cout << ("Error: x must be greater than y!");
        } else {
        	//initialize stack pointer:
			loop_string.append(instr_str("ldr",12, -1, 0, "", ">end_of_dmem") + "\n");
        	//branch to main program:
			loop_string.append(instr_str("bro", -1, 0, 0, "always", ">main_" + std::to_string(loop_id)) + "\n");
			loop_string.append("nop\n");
			loop_string.append(".align\n");
        	loop_string.append("end_of_dmem: 	.word 0x000004FC\n");
        	//start of the function:
        	loop_string.append("binomial_x_y_" + std::to_string(loop_id) + ":\n");
            //insert dummy instruction with imm=0 to determine address of "loop" head: (technically this is not a loop)
            loop_string.append(instr_str("trap", 0, 0, 0, "", "") + "\n");
        	//push temp_reg0:
        	loop_string.append(instr_str("addi", 12, -4, 0, "", "") + "\n");
			loop_string.append(instr_str("st32", 12, temp_reg0, 0, "", "") + "\n");
        	//push temp_reg1
        	loop_string.append(instr_str("addi", 12, -4, 0, "", "") + "\n");
			loop_string.append(instr_str("st32", 12, temp_reg1, 0, "", "") + "\n");
			//push n_loops_reg
        	loop_string.append(instr_str("addi", 12, -4, 0, "", "") + "\n");
			loop_string.append(instr_str("st32", 12, n_loops_reg, 0, "", "") + "\n");
			//push link register:
        	loop_string.append(instr_str("addi", 12, -4, 0, "", "") + "\n");
			loop_string.append(instr_str("st32", 12, 13, 0, "", "") + "\n");
        	//check if x and y are equal:
			loop_string.append(instr_str("cmp", temp_reg0, temp_reg1, 0, "eq", "") + "\n");
			loop_string.append(instr_str("bro", -1, 0, 0, "true", ">equals_or_y0" + std::to_string(loop_id)) + "\n");
			loop_string.append("nop\n");
			//if they are not equal, let's check if y = 0:
			loop_string.append(instr_str("cmp", temp_reg2, temp_reg1, 0, "eq", "") + "\n");
			loop_string.append(instr_str("bro", -1, 0, 0, "true", ">equals_or_y0" + std::to_string(loop_id)) + "\n");
			loop_string.append("nop\n");
			//if they're not equal or y is not 0, we must call the recursive function, first with (x-1,y):
        	loop_string.append(instr_str("addi", temp_reg0, -1, 0, "", "") + "\n");
        	loop_string.append(instr_str("callo", -1, 0, 0,  "", ">binomial_x_y_" + std::to_string(loop_id) ) + "\n");
            //insert dummy instruction with imm=1 to determine address of "loop" tail:
            loop_string.append(instr_str("trap", 1, 0, 0, "", "") + "\n");        	//copy result of function call to n_loops_reg:
        	loop_string.append(instr_str("mov", n_loops_reg, temp_reg3, 0, "", "") + "\n");
        	//now call function with (x-1,y-1):
        	loop_string.append(instr_str("addi", temp_reg1, -1, 0, "", "") + "\n");
        	loop_string.append(instr_str("callo", -1, 0, 0,  "", ">binomial_x_y_" + std::to_string(loop_id) ) + "\n");
            //insert dummy instruction with imm=1 to determine address of "loop" tail:
            loop_string.append(instr_str("trap", 1, 0, 0, "", "") + "\n");			//now let's add both call results into return register:
        	loop_string.append(instr_str("add", temp_reg3, temp_reg3, n_loops_reg, "", "") + "\n");
			loop_string.append(instr_str("bro", -1, 0, 0, "always", ">end_" + std::to_string(loop_id)) + "\n");
			loop_string.append("nop\n");
        	//if condition met, return 1 in temp_reg3:
			loop_string.append("equals_or_y0" + std::to_string(loop_id) + ":\n");
			loop_string.append(instr_str("clr", temp_reg3, 0, 0, "", "") + "\n");
        	loop_string.append(instr_str("addi", temp_reg3, 1, 0, "", "") + "\n");
			loop_string.append("end_" + std::to_string(loop_id) + ":\n");
			//pop link register:
			loop_string.append(instr_str("ld32", 13, 12, 0, "", "") + "\n");
        	loop_string.append(instr_str("addi", 12, 4, 0, "", "") + "\n");
			//pop n_loops_reg
			loop_string.append(instr_str("ld32", n_loops_reg, 12, 0, "", "") + "\n");
        	loop_string.append(instr_str("addi", 12, 4, 0, "", "") + "\n");
			//pop temp_reg1
			loop_string.append(instr_str("ld32", temp_reg1, 12, 0, "", "") + "\n");
        	loop_string.append(instr_str("addi", 12, 4, 0, "", "") + "\n");
			//pop temp_reg0
			loop_string.append(instr_str("ld32", temp_reg0, 12, 0, "", "") + "\n");
        	loop_string.append(instr_str("addi", 12, 4, 0, "", "") + "\n");
            //return:
        	loop_string.append("ret\n");

        	//Main program:
			loop_string.append("main_" + std::to_string(loop_id) + ":\n");
        	//use temp_reg0 to store x:
			loop_string.append(instr_str("clr", temp_reg0, 0, 0, "", "") + "\n");
        	loop_string.append(instr_str("addi", temp_reg0, n_x_taps, 0, "", "") + "\n");
        	//use temp_reg1 to store y:
			loop_string.append(instr_str("clr", temp_reg1, 0, 0, "", "") + "\n");
        	loop_string.append(instr_str("addi", temp_reg1, n_y_taps, 0, "", "") + "\n");
        	//use temp_reg2 as zero:
        	loop_string.append(instr_str("clr", temp_reg2, 0, 0, "", "") + "\n");
        	//call binomial function:
        	loop_string.append(instr_str("callo", -1, 0, 0,  "", ">binomial_x_y_" + std::to_string(loop_id) ) + "\n");
        	loop_string.append("end_main_" + std::to_string(loop_id) + ": nop\n");
			loop_string.append(instr_str("bro", -1, 0, 0, "always", ">end_main_" + std::to_string(loop_id)) + "\n");
        	loop_string.append("nop\n");
        }
    } else if (loop_type == "IIR_filter"){
        //####################################################################################//#
        //case loop_type is IIR_filter: here we follow the same concept as in the FIR filter,   #
        //where we use two hard-coded negative powers of 2 to define each coefficient value,    #
        //but we need two coefficient arrays since the IIR recursion is given by:               #
        //b0*y[n] = a0*x[n] + ... ap*x[n-p] + b1*y[n-1] + b2*y[n-2] + ... + bq*y[n-q]. 			#
        //The signal to be filtered must come in arrays_base[0] and the filtered values will be #
        //stored in arrays_base[1]. Because of limitations in representing multiplications, the	#
    	//last value in the iir_y_taps array is a positive exponent which will be used to		#
    	//multiply the value of y[n] calculated so far.	The second value of the tap must be 0.	#
    	// 								! ! ! W A R N I N G ! ! ! 								#
    	// This filter may run into stability problems depending on the position of the poles 	#
    	// (and zeros?), and the output signal might oscillate uncontrollably as a result.		#
    	// This is most likely due to the poor quality associated with representing the tap		#
    	// values of the filter with powers of two, and the recurrent nature of the filter.		#
        //####################################################################################//#

        if ((n_x_taps % 2 != 0) | (n_y_taps % 2 != 0)) {
            std::cout <<("Error: the number of taps must be even");
        } else if (n_x_taps + n_y_taps > 20) {
            std::cout << ("Error: too many taps (n_x_taps + n_y_taps must not be greater than 20");
        } else if (n_arrays != 2) {
            std::cout << ("Error: the number of arrays must be exactly 2");
        } else {
			//branch to start of program:
			loop_string.append(instr_str("bro", -1, 0, 0, "always", ">main_" + std::to_string(loop_id)) + "\n");
			loop_string.append("nop\n");
			//define pointer to array0:
			loop_string.append("ptr_" + arrays_base[0] + ":	.word 0x00000300\n");
			//define pointer to array1:
			loop_string.append("ptr_" + arrays_base[1] + ":	.word 0x00000500\n");
			//main prog:
			loop_string.append("main_" + std::to_string(loop_id) + ":\n");
			//load number of loops into n_loops_reg:
			loop_string.append(instr_str("clr", n_loops_reg, 0, 0, "", "") + "\n");
			loop_string.append(instr_str("addi", n_loops_reg, n_loops, 0, "", "") + "\n");
			//use temp_reg3 to count loop iterations:
			loop_string.append(instr_str("clr", temp_reg3, 0, 0, "", "") + "\n");
			//use temp_reg0 as zero for possible negations:
			loop_string.append(instr_str("clr", temp_reg0, 0, 0, "", "") + "\n");
			//load array_0 base address into base_reg0:
			loop_string.append(instr_str("ldr", base_reg0, -1, 0, "", ">ptr_" + arrays_base[0]) + "\n");
			//load array_0 base address into base_reg0:
			loop_string.append(instr_str("ldr", base_reg1, -1, 0, "", ">ptr_" + arrays_base[1]) + "\n");
			//forward to y[n]:
			loop_string.append(instr_str("addi", base_reg1, 4*(n_y_taps/2 -1), 0, "", "") + "\n");
            //insert dummy instruction with imm=0 to determine address of loop head:
            loop_string.append(instr_str("trap", 0, 0, 0, "", "") + "\n");
			//label the start of the loop with its id (which is in address 28):
			loop_string.append("loop_" + std::to_string(loop_id) + ":\n");
			//clear temporary filtered result registers:
			loop_string.append(instr_str("clr", temp_reg2, 0, 0, "", "") + "\n");
			loop_string.append(instr_str("clr", iir_temp_reg0, 0, 0, "", "") + "\n");
			loop_string.append(instr_str("clr", iir_temp_reg1, 0, 0, "", "") + "\n");

			//forward to x[n]:
			loop_string.append(instr_str("addi", base_reg0, 4*(n_x_taps/2 -1), 0, "", "") + "\n");

			//"multiply" all n_x_taps/2 samples by the two corresponding taps: (this will take at most NN TCK)
			for (int i = 0; i < n_x_taps; i = i + 2) {
				//load sample x[n-i] into temp_reg1, fir_temp_reg0 and fir_temp_reg1:
				loop_string.append(instr_str("ld32", temp_reg1, base_reg0, 0, "", "") + "\n");
				loop_string.append(instr_str("mov", iir_temp_reg0, temp_reg1, 0, "", "") + "\n");
				loop_string.append(instr_str("mov", iir_temp_reg1, temp_reg1, 0, "", "") + "\n");
				//apply both taps to x[n+i]:

				//tap 1:
				//check that iir_x_taps[i] is not out of range:
				if (abs(iir_x_taps[i]) > 15) {
                    std::cout << "Error: IIR x tap n" << std::to_string(i) << " out of range!";
                    return "-1";
				}
				//check if sample x[n-i] is negative:
				loop_string.append(instr_str("cmp", temp_reg1, temp_reg0, 0, "ge", "") + "\n");
				loop_string.append(instr_str("bro", -1, 0, 0, "true", ">sp_x" + std::to_string((n_x_taps - i)/2) + "_is_pos1_" + std::to_string(loop_id)) + "\n");
				loop_string.append("nop\n");
				//if so, negate it, because we don't have arithmetic right shift:
				loop_string.append(instr_str("sub", iir_temp_reg0, temp_reg0, iir_temp_reg0, "", "") + "\n");
				loop_string.append("sp_x" + std::to_string((n_x_taps - i)/2) + "_is_pos1_" + std::to_string(loop_id) + ":\n");
				//at this point iir_temp_reg0 is positive, so right shift it by abs(iir_x_taps[i]):
				if (abs(iir_x_taps[i]) != 0) {
					loop_string.append(instr_str("rsh", iir_temp_reg0, iir_temp_reg0, abs(iir_x_taps[i]), "", "") + "\n");
				}
				//check whether coefficient is supposed to add or subtract:
				if (iir_x_taps[i] < 0) {
					//if so, we have to negate the previous result:
					loop_string.append(instr_str("sub", iir_temp_reg0, temp_reg0, iir_temp_reg0, "", "") + "\n");
				}
				//if x[n-i] was negative, we have to reverse the first inversion:
				loop_string.append(instr_str("bro", -1, 0, 0, "true", ">sp_x" + std::to_string((n_x_taps - i)/2) + "_was_pos1_" + std::to_string(loop_id)) + "\n");
				loop_string.append("nop\n");
				loop_string.append(instr_str("sub", iir_temp_reg0, temp_reg0, iir_temp_reg0, "", "") + "\n");
				loop_string.append("sp_x" + std::to_string((n_x_taps - i)/2) + "_was_pos1_" + std::to_string(loop_id) + ":\n");
				//at this point, fir_temp_reg0 contains the sample x[n-i] shifted by iir_x_taps[i]


				//tap 2:
				//check that iir_x_taps[i+1] is not out of range:
				if (abs(iir_x_taps[i+1]) > 15) {
                    std::cout << "Error: IIR x tap n" << std::to_string(i+1) << " out of range!";
                    return "-1";
				}
				//check if sample x[n-i] is negative:
				loop_string.append(instr_str("cmp", temp_reg1, temp_reg0, 0, "ge", "") + "\n");
				loop_string.append(instr_str("bro", -1, 0, 0, "true", ">sp_x" + std::to_string((n_x_taps - i)/2) + "_is_pos2_" + std::to_string(loop_id)) + "\n");
				loop_string.append("nop\n");
				//if so, negate it, because we don't have arithmetic right shift:
				loop_string.append(instr_str("sub", iir_temp_reg1, temp_reg0, iir_temp_reg1, "", "") + "\n");
				loop_string.append("sp_x" + std::to_string((n_x_taps - i)/2) + "_is_pos2_" + std::to_string(loop_id) + ":\n");
				//at this point fir_temp_reg1 is positive, so right shift it by abs(iir_x_taps[i+1]):
				loop_string.append(instr_str("rsh", iir_temp_reg1, iir_temp_reg1, abs(iir_x_taps[i+1]), "", "") + "\n");
				//check whether coefficient is supposed to add or subtract:
				if (iir_x_taps[i+1] < 0) {
					//if so, we have to negate the previous result:
					loop_string.append(instr_str("sub", iir_temp_reg1, temp_reg0, iir_temp_reg1, "", "") + "\n");
				}
				//if x[n-i] was negative, we have to reverse the first inversion:
				loop_string.append(instr_str("bro", -1, 0, 0, "true", ">sp_x" + std::to_string((n_x_taps - i)/2) + "_was_pos2_" + std::to_string(loop_id)) + "\n");
				loop_string.append("nop\n");
				loop_string.append(instr_str("sub", iir_temp_reg1, temp_reg0, iir_temp_reg1, "", "") + "\n");
				loop_string.append("sp_x" + std::to_string((n_x_taps - i)/2) + "_was_pos2_" + std::to_string(loop_id) + ":\n");
				//at this point, iir_temp_reg0 contains the sample x[n-i] shifted by iir_x_taps[i+1]

				//now we add both samples "multiplied" by the taps:
				loop_string.append(instr_str("add", temp_reg1, iir_temp_reg0, iir_temp_reg1, "", "") + "\n");
				//and add the partial result to y[n] (temp_reg2):
				loop_string.append(instr_str("add", temp_reg2, temp_reg2, temp_reg1, "", "") + "\n");
				//decrement i:
				loop_string.append(instr_str("addi", base_reg0, -4, 0, "", "") + "\n");
			}
			//at this point, base_reg0 is pointing to n - (n_x_taps)/2, so we must correct and prepare for next loop iteration:
			loop_string.append(instr_str("addi", base_reg0, 8, 0, "", "") + "\n");

			//skip first tap (by decrementing i), corresponding to y[n]:
			loop_string.append(instr_str("addi", base_reg1, -4, 0, "", "") + "\n");



			//"multiply" all n_y_taps/2 - 1 samples by the two corresponding taps: (this will take at most MM TCK)
			for (int i = 2; i < n_y_taps; i = i + 2) {
				//load sample y[n-i] into temp_reg1, fir_temp_reg0 and fir_temp_reg1:
				loop_string.append(instr_str("ld32", temp_reg1, base_reg1, 0, "", "") + "\n");
				loop_string.append(instr_str("mov", iir_temp_reg0, temp_reg1, 0, "", "") + "\n");
				loop_string.append(instr_str("mov", iir_temp_reg1, temp_reg1, 0, "", "") + "\n");
				//apply both taps to y[n+i]:

				//tap 1:
				//check that iir_y_taps[i] is not out of range:
				if (abs(iir_y_taps[i]) > 15) {
                    std::cout << "Error: IIR y tap n" << std::to_string(i) << " out of range!\n ";
                    return "-1";
				}
				//check if sample y[n-i] is negative:
				loop_string.append(instr_str("cmp", temp_reg1, temp_reg0, 0, "ge", "") + "\n");
				loop_string.append(instr_str("bro", -1, 0, 0, "true", ">sp_y" + std::to_string((n_y_taps - i)/2) + "_is_pos1_" + std::to_string(loop_id)) + "\n");
				loop_string.append("nop\n");
				//if so, negate it, because we don't have arithmetic right shift:
				loop_string.append(instr_str("sub", iir_temp_reg0, temp_reg0, iir_temp_reg0, "", "") + "\n");
				loop_string.append("sp_y" + std::to_string((n_y_taps - i)/2) + "_is_pos1_" + std::to_string(loop_id) + ":\n");
				//at this point iir_temp_reg0 is positive, so right shift it by abs(iir_y_taps[i]):
				loop_string.append(instr_str("rsh", iir_temp_reg0, iir_temp_reg0, abs(iir_y_taps[i]), "", "") + "\n");
				//check whether coefficient is supposed to add or subtract:
				if (iir_y_taps[i] < 0) {
					//if so, we have to negate the previous result:
					loop_string.append(instr_str("sub", iir_temp_reg0, temp_reg0, iir_temp_reg0, "", "") + "\n");
				}
				//if y[n-i] was negative, we have to reverse the first inversion:
				loop_string.append(instr_str("bro", -1, 0, 0, "true", ">sp_y" + std::to_string((n_y_taps - i)/2) + "_was_pos1_" + std::to_string(loop_id)) + "\n");
				loop_string.append("nop\n");
				loop_string.append(instr_str("sub", iir_temp_reg0, temp_reg0, iir_temp_reg0, "", "") + "\n");
				loop_string.append("sp_y" + std::to_string((n_y_taps - i)/2) + "_was_pos1_" + std::to_string(loop_id) + ":\n");
				//at this point, fir_temp_reg0 contains the sample y[n-i] shifted by iir_y_taps[i]

				//tap 2:
				//check that iir_y_taps[i+1] is not out of range:
				if (abs(iir_y_taps[i+1]) > 15) {
                    std::cout << "Error: IIR y tap n" << std::to_string(i+1) << " out of range!\n";
					return "-1";
				}
				//check if sample y[n-i] is negative:
				loop_string.append(instr_str("cmp", temp_reg1, temp_reg0, 0, "ge", "") + "\n");
				loop_string.append(instr_str("bro", -1, 0, 0, "true", ">sp_y" + std::to_string((n_y_taps - i)/2) + "_is_pos2_" + std::to_string(loop_id)) + "\n");
				loop_string.append("nop\n");
				//if so, negate it, because we don't have arithmetic right shift:
				loop_string.append(instr_str("sub", iir_temp_reg1, temp_reg0, iir_temp_reg1, "", "") + "\n");
				loop_string.append("sp_y" + std::to_string((n_y_taps - i)/2) + "_is_pos2_" + std::to_string(loop_id) + ":\n");
				//at this point iir_temp_reg1 is positive, so right shift it by abs(iir_y_taps[i+1]):
				loop_string.append(instr_str("rsh", iir_temp_reg1, iir_temp_reg1, abs(iir_y_taps[i+1]), "", "") + "\n");
				//check whether coefficient is supposed to add or subtract:
				if (iir_y_taps[i+1] < 0) {
					//if so, we have to negate the previous result:
					loop_string.append(instr_str("sub", iir_temp_reg1, temp_reg0, iir_temp_reg1, "", "") + "\n");
				}
				//if y[n-i] was negative, we have to reverse the first inversion:
				loop_string.append(instr_str("bro", -1, 0, 0, "true", ">sp_y" + std::to_string((n_y_taps - i)/2) + "_was_pos2_" + std::to_string(loop_id)) + "\n");
				loop_string.append("nop\n");
				loop_string.append(instr_str("sub", iir_temp_reg1, temp_reg0, iir_temp_reg1, "", "") + "\n");
				loop_string.append("sp_y" + std::to_string((n_y_taps - i)/2) + "_was_pos2_" + std::to_string(loop_id) + ":\n");
				//at this point, fir_temp_reg0 contains the sample y[n-i] shifted by iir_y_taps[i+1]

				//now we add both samples "multiplied" by the taps:
				loop_string.append(instr_str("add", temp_reg1, iir_temp_reg0, iir_temp_reg1, "", "") + "\n");
				//and add the partial result to y[n] (temp_reg2):
				loop_string.append(instr_str("add", temp_reg2, temp_reg2, temp_reg1, "", "") + "\n");
				//decrement i:
				loop_string.append(instr_str("addi", base_reg1, -4, 0, "", "") + "\n");
			}

            //check that iir_y_taps[0] is not out of range:
            if ((iir_y_taps[0]) > 15) {
                std::cout << ("Error: IIR y tap 0 out of range!");
                return "-1";
            }
			//multiply temp_reg2 by iir_y_taps[0]; if zero, leave as is:
			if (iir_y_taps[0] > 0) {
				loop_string.append(instr_str("lsh", temp_reg2, temp_reg2, iir_y_taps[0], "", "") + "\n");
			}
			//forward to y[n]:
			loop_string.append(instr_str("addi", base_reg1, 4*(n_y_taps/2), 0, "", "") + "\n");
			//store array element from temp_reg2 to address [array_base1 + current_iteration]:
			loop_string.append(instr_str("st32", base_reg1, temp_reg2, 0, "", "") + "\n");
			//prepare pointer of y for next iteration:
			loop_string.append(instr_str("addi", base_reg1, 4, 0, "", "") + "\n");
			//Increase loop count:
			loop_string.append(instr_str("addi", temp_reg3, 1, 0, "", "") + "\n");
			//check if we reached n_loops:
			loop_string.append(instr_str("cmp", temp_reg3, n_loops_reg, 0, "neq", "") + "\n");
			//if not yet zero, jump back to loop start of loop (address 28):
			loop_string.append(instr_str("clr", temp_reg1, 0, 0, "", "") + "\n");
			loop_string.append(instr_str("addi", temp_reg1, 28, 0, "", "") + "\n"); // i dont like dis, but do we hav an option??...
			loop_string.append(instr_str("brr", temp_reg1, 0, 0, "true", "") + "\n");
            //insert dummy instruction with imm=1 to determine address of loop tail:
            loop_string.append(instr_str("trap", 1, 0, 0, "", "") + "\n");
            loop_string.append("end_" + std::to_string(loop_id) + ":\n");
			//after end, loop 4ever:
			loop_string.append(instr_str("bro", -1, 0, 0, "always", ">end_" + std::to_string(loop_id)) + "\n");
			loop_string.append("nop\n");

			//define array:
			loop_string.append(".align\n");
			loop_string.append(".address 0x300\n");
			loop_string.append(arrays_base[0] + ":\n");
			//fill array with some signal:
			double pi 		= acos(-1);
			int signal;
			for (int i = 0; i < n_loops; i++) {
				signal = int(round( amplitude0*sin(i*2*pi*f0/fs) + amplitude1*sin(i*2*pi*f1/fs)  + amplitude2*sin(i*2*pi*f2/fs) ));
				loop_string.append(".word " + std::to_string(signal) + "\n");
			}
		}
    } else {
        std::cout <<("loop_type: " + loop_type + " is unsupported");
    }
    return (loop_string);
}
