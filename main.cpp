//
//  main.cpp
//  IFS
//
//  Created by Don on 2016/4/20.
//  Copyright © 2016年 Chun-Yao Lab. All rights reserved.
//

#include <iostream>


#include "circuit.hpp"
#include "fault.hpp"



using namespace std;

int main(int argc,  char * argv[]) {
    
    
    Fault ckt;
    
    ckt.read_circuit_file(argv[1]);
    
    ckt.read_fault_file(argv[2]);
    
    cout<<"#fault_group="<<ckt.num_fault_group()<<endl;
	
	
	cout<<"neg_RDOB_fault_collapsing..."<<endl;
    ckt.neg_RDOB_fault_collapsing();
    cout<<"#fault_group="<<ckt.num_fault_group()<<endl;
	
	
	
	cout<<"stuck_at_fault_collapsing..."<<endl;
    ckt.stuck_at_fault_collapsing();
    cout<<"#fault_group="<<ckt.num_fault_group()<<endl;
	
	
	cout<<"neg_fault_collapsing..."<<endl;
    ckt.neg_fault_collapsing();
    cout<<"#fault_group="<<ckt.num_fault_group()<<endl;
	
    
    
    
    
    ckt.write_verilog_file(argv[1]);
    ckt.write_output_fault_file(argv[3]);
    return 0;
}
