//
//  fault.hpp
//  IFS
//
//  Created by Don on 2016/5/17.
//  Copyright © 2016年 Chun-Yao Lab. All rights reserved.
//

#ifndef fault_hpp
#define fault_hpp

#include "circuit.hpp"

#include <stdio.h>






class Fault :public Circuit{
public:
    Fault(){};
    void read_fault_file(char*);
    void write_output_fault_file(char*);
    void write_another_format();
    
    void neg_RDOB_fault_collapsing();
    void stuck_at_fault_collapsing();
    void  neg_fault_collapsing();
    
    void link_faults(int fault_index1,int fault_index2);
    void link_faults(int wire_index1,int faultType1,int wire_index2,int faultType2);

    unsigned num_fault_group();
    
    bool same_group(int fault_index1,int fault_index2);
    unsigned num_groups(){return _num_groups;}

    unsigned _num_groups;

private:
    //               0    1    2      3           4        5         6        7         8       9        10
    enum FaultType {SA0, SA1, NEG, RDOB_AND, RDOB_NAND, RDOB_OR, RDOB_NOR,RDOB_XOR,RDOB_NXOR,RDOB_NOT,RDOB_BUFF};
    
    
    vector< pair<int,int> > _all_faults;
    vector<int> _isgiven;

    unsigned _numFaultType = 11;



};










#endif /* fault_hpp */
































