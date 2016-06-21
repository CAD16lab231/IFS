//
//  circuit.hpp
//  IFS
//
//  Created by Don on 2016/4/20.
//  Copyright © 2016年 Chun-Yao Lab. All rights reserved.
//

#ifndef circuit_hpp
#define circuit_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Gate{
    Gate(){
        net.resize(3);
    }
    int type;
    //
    //
    vector<int> net;
};

struct Net{
    Net(){
        gate.push_back(-1);
    }
    int name;
    vector<int> gate;
    bool ISPO(){return(gate.size()==1);}
    bool ISPI(){return (gate[0]==-1);}
    bool ISNOFANOUTNET(){return (gate.size()==2);}
 //   bool ISEMPTY(){return(gate.size()==0);}
};


class Circuit {
public:
    void read_circuit_file(char*);
    
    
    
    unsigned numInput(){return _num_inputs;};
    unsigned numOutput(){return _num_outputs;};
    unsigned numGate(){return _num_gates;};
    unsigned numNet(){return (unsigned)_nets.size();};
    
    
    Gate& gate(unsigned index){return _gates[index];}
    Net&  net(unsigned index){return _nets[index];}
    
    
    
    pair<int,int> getFaninGates(int gate_index);
    pair<int,int> getFaninNets(int net_index);
    int           getDriveGateType(int net_index);
    vector<int>   getDFFFaninNets(int net_index);
    
	void write_verilog_file(char*);
    
protected:
    //              0     1    2    3    4    5    6   7     8
    enum GateType {BUFF, NOT, AND, NAND, OR, NOR, XOR, NXOR, DFF};
    int getNetIndex(int);
    

private:
    
    void addGate(int type,string output,string input1,string input2);
    void addGate(int type,string output,string input);
    void addDFF(string output, string clock,string reset, string enable, string input);
    
    vector <Gate> _gates;
    vector <Net>  _nets;
    vector <int> _inputs;
    vector <int> _outputs;
    
    map<int, int> _netmap;

    
    unsigned _num_inputs;
    unsigned _num_outputs;
    unsigned _num_dffs;
    unsigned _num_gates;





};




































#endif /* circuit_hpp */

