//
//  circuit.cpp
//  IFS
//
//  Created by Don on 2016/4/20.
//  Copyright © 2016年 Chun-Yao Lab. All rights reserved.
//

#include "circuit.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <assert.h>

using namespace std;

void Circuit ::read_circuit_file(char* filename){
    ifstream fin;
    fin.open(filename,ios::in);
    
    
    string strbuf;
    char chararybuf[256];
    char charbuf;
    Net netbuf;
    
    
    fin>>strbuf>>_num_inputs;
    fin.getline(chararybuf,256);
    fin>>strbuf>>_num_outputs;
    fin.getline(chararybuf,256);
    fin>>strbuf>>_num_dffs;
    fin.getline(chararybuf,256);
    fin>>strbuf>>_num_gates;
    fin.getline(chararybuf,256);
    
    while (fin>>charbuf) {
        if (charbuf == 'I') {         //INPUT
            for (int i=0; i<5; i++) {
                fin>>charbuf;
            }
            fin>>strbuf;
            strbuf.pop_back();
            _inputs.push_back(getNetIndex(stoi(strbuf)));
        }
        else if(charbuf == 'O'){   //OUTPUT
            for (int i=0; i<6; i++) {
                fin>>charbuf;
            }
            fin>>strbuf;
            strbuf.pop_back();
            _outputs.push_back(getNetIndex(stoi(strbuf)));
        }
        else{
            Gate gatebuf;
            string output_net;
            string input_net1;
            string input_net2;
            fin>>output_net;
            chararybuf[0]=charbuf;
            chararybuf[1]='\0';
            output_net.insert(0,chararybuf);//get output net name
            
            fin >> charbuf;
            fin >> input_net1;
            
            if(input_net1[0]=='B'){//BUFF BUFF(*)
                input_net1.erase(0,5);
                input_net1.pop_back();
                addGate(BUFF,output_net,input_net1);
            
            }
            else if(input_net1[0]=='N'&&input_net1[1]=='O'&&input_net1[2]=='T'){//NOT  NOT(*)
                input_net1.erase(0,4);
                input_net1.pop_back();
                addGate(NOT,output_net,input_net1);
            }
            else if(input_net1[0]=='A'){//AND  AND(*, *)
                input_net1.erase(0,4);
                input_net1.pop_back();
                fin>>input_net2;
                input_net2.pop_back();
                addGate(AND,output_net,input_net1,input_net2);
            }
            else if(input_net1[0]=='N'&&input_net1[1]=='A'&&input_net1[2]=='N'){//NAND  NAND(*, *)
                input_net1.erase(0,5);
                input_net1.pop_back();
                fin>>input_net2;
                input_net2.pop_back();
                addGate(NAND,output_net,input_net1,input_net2);
            }
            else if(input_net1[0]=='O'){//OR      OR(*, *)
                input_net1.erase(0,3);
                input_net1.pop_back();
                fin>>input_net2;
                input_net2.pop_back();
                addGate(OR,output_net,input_net1,input_net2);
            }
            else if(input_net1[0]=='N'&&input_net1[1]=='O'&&input_net1[2]=='R'){//NOR      NOR(*, *)
                input_net1.erase(0,4);
                input_net1.pop_back();
                fin>>input_net2;
                input_net2.pop_back();
                addGate(NOR,output_net,input_net1,input_net2);
            }
            else if(input_net1[0]=='X'){//XOR      XOR(*, *)
                input_net1.erase(0,4);
                input_net1.pop_back();
                fin>>input_net2;
                input_net2.pop_back();
                addGate(XOR,output_net,input_net1,input_net2);
            }
            else if(input_net1[0]=='N'&&input_net1[1]=='X'&&input_net1[2]=='O'){//NXOR      NXOR(*, *)
                input_net1.erase(0,5);
                input_net1.pop_back();
                fin>>input_net2;
                input_net2.pop_back();
                addGate(NXOR,output_net,input_net1,input_net2);
            }
            else if(input_net1[0]=='D'&&input_net1[1]=='F'&&input_net1[2]=='F'){//DFF     NXOR(*, *)
                input_net1.erase(0,4);
                input_net1.pop_back();
                string clock = input_net1;
                
                fin>>input_net2;
                input_net2.pop_back();
                string reset = input_net2;
                
                fin>>input_net2;
                input_net2.pop_back();
                string enable = input_net2;
                
                fin>>input_net2;
                input_net2.pop_back();
                string input = input_net2;
                //cout<<output_net<<" = DFF("<<clock<<", "<<reset<<", "<<enable<<", "<<input<<")"<<endl;
                //getchar();
                addDFF(output_net,clock,reset,enable,input);
            }
            else {
                assert(0);
                
            }
        }
    }
    
    assert(_num_inputs==_inputs.size());
    assert(_num_outputs==_outputs.size());
    //assert(_num_gates==_gates.size());

    fin.close();

    return;
}




int Circuit ::getNetIndex(int name){
    auto it = _netmap.find(name);
    if (it==_netmap.end()) {
        _netmap.insert(pair<int,int>(name,(int)_nets.size()));
        Net nettemp;
        nettemp.name = name;
        _nets.push_back(nettemp);
        return (int)_nets.size()-1;
    }
    return it->second;
}


void Circuit ::addGate(int type,string output,string input1,string input2){
    Gate gatebuf;
    gatebuf.type =type;
    gatebuf.net[0]=getNetIndex(stoi(output));
    gatebuf.net[1]=getNetIndex(stoi(input1));
    gatebuf.net[2]=getNetIndex(stoi(input2));
    
    _nets[gatebuf.net[0]].gate[0] =int(_gates.size());
    _nets[gatebuf.net[1]].gate.push_back(int(_gates.size()));
    _nets[gatebuf.net[2]].gate.push_back(int(_gates.size()));
    _gates.push_back(gatebuf);


    return;


}


void Circuit ::addGate(int type,string output,string input){
    Gate gatebuf;
    gatebuf.type =type;
    gatebuf.net[0]=getNetIndex(stoi(output));
    gatebuf.net[1]=getNetIndex(stoi(input));
    gatebuf.net[2]=-1;
    
    _nets[gatebuf.net[0]].gate[0] =int(_gates.size());
    _nets[gatebuf.net[1]].gate.push_back(int(_gates.size()));
    _gates.push_back(gatebuf);
    
    return;
    
    
    
}


void Circuit ::addDFF(string output, string clock,string reset, string enable, string input){
    Gate gatebuf;
    gatebuf.net.resize(5);
    gatebuf.type =DFF;
    gatebuf.net[0]=getNetIndex(stoi(output));
    gatebuf.net[1]=getNetIndex(stoi(clock));
    gatebuf.net[2]=getNetIndex(stoi(reset));
    gatebuf.net[3]=getNetIndex(stoi(enable));
    gatebuf.net[4]=getNetIndex(stoi(input));
    
    _nets[gatebuf.net[0]].gate[0] =int(_gates.size());
    _nets[gatebuf.net[1]].gate.push_back(int(_gates.size()));
    _nets[gatebuf.net[2]].gate.push_back(int(_gates.size()));
    _nets[gatebuf.net[3]].gate.push_back(int(_gates.size()));
    _nets[gatebuf.net[4]].gate.push_back(int(_gates.size()));
    _gates.push_back(gatebuf);
    
    return;
    
    
    
}




pair<int,int> Circuit ::getFaninGates(int index){
    assert(index>=0&&index<_gates.size());
    int fanin_net2=_gates[index].net[2];
    if (fanin_net2==-1) {
        return pair<int,int> (_nets[ _gates[index].net[1]].gate[0],-1);
    }    return pair<int,int> (_nets[ _gates[index].net[1]].gate[0],_nets[ fanin_net2].gate[0]);
}

pair<int,int> Circuit ::getFaninNets(int index){
    assert(index>=0&&index<_nets.size());
    
    int gate_index=_nets[index].gate[0];
    if(_gates[gate_index].type==DFF){
        return pair<int,int> (_gates[gate_index].net[4],-1);
    }
    
    return pair<int,int> (_gates[gate_index].net[1],_gates[gate_index].net[2]);
}


vector<int>   Circuit ::getDFFFaninNets(int index){
    assert(index>=0&&index<_nets.size());
    vector<int> temp;
    int gate_index=_nets[index].gate[0];
    temp.push_back(_gates[gate_index].net[1]);
    temp.push_back(_gates[gate_index].net[2]);
    temp.push_back(_gates[gate_index].net[3]);
    temp.push_back(_gates[gate_index].net[4]);

    return temp;



}


int Circuit ::getDriveGateType(int index){
    assert(index>=0&&index<_nets.size());
    
    return _gates[ _nets[index].gate[0] ].type;
}




void Circuit ::write_verilog_file(char* filename){
	string nametemp(filename);
	nametemp.push_back('.');
	nametemp.push_back('v');
	char *cstr = new char[nametemp.length() + 1];
	strcpy(cstr, nametemp.c_str());
	ofstream fout;
	fout.open(cstr,ios::out);
	fout<<"module top("<<endl;
	for(int i=0;i<numInput();i++){
		fout<<"	input net_"<<net(_inputs[i]).name<<","<<endl;
		
		
	}
	for(int i=0;i<numOutput()-1;i++){
		fout<<"	output  net_"<<net(_outputs[i]).name<<","<<endl;
		
		
	}
	fout<<"	output  net_"<<net(_outputs[numOutput()-1]).name<<endl;
	fout<<");"<<endl;
	
	for(int net_index=0; net_index<numNet(); net_index++){
		
		if( !net(net_index).ISPI()&& !net(net_index).ISPO() ){
            if(getDriveGateType(net_index)==DFF){
                fout<<"reg net_"<<net(net_index).name<<";"<<endl;
            
            }
            else
			fout<<"wire net_"<<net(net_index).name<<";"<<endl;
		}
	}
	pair<int,int> faninnet;
	for(int net_index=0; net_index<numNet(); net_index++){
		
		if( !net(net_index).ISPI() ){//&& net(net_index).ISNOFANOUTNET() ){
            vector<int> DFF_Fanin;
            if(getDriveGateType(net_index)==DFF)
                DFF_Fanin = getDFFFaninNets(net_index);
			faninnet = getFaninNets(net_index);
			//cout<<"fanin "<<faninnet.first<<endl;
			
			switch (getDriveGateType(net_index)) {
				case BUFF:
					fout<<"assign "<<"net_"<<net(net_index).name<<" = "<<"net_"<<net(faninnet.first).name<<";"<<endl;
					break;
				case NOT:
					fout<<"assign "<<"net_"<<net(net_index).name<<"= ~"<<"net_"<<net(faninnet.first).name<<";"<<endl;
					break;
				case AND:
					fout<<"assign "<<"net_"<<net(net_index).name<<" = "<<"net_"<<net(faninnet.first).name<<"&"<<"net_"<<net(faninnet.second).name<<";"<<endl;
					
					break;
				case NAND:
					fout<<"assign "<<"net_"<<net(net_index).name<<" = ~("<<"net_"<<net(faninnet.first).name<<"&"<<"net_"<<net(faninnet.second).name<<");"<<endl;
					
					break;
				case OR:
					fout<<"assign "<<"net_"<<net(net_index).name<<" = "<<"net_"<<net(faninnet.first).name<<"|"<<"net_"<<net(faninnet.second).name<<";"<<endl;
					
					break;
				case NOR:
					fout<<"assign "<<"net_"<<net(net_index).name<<" = ~("<<"net_"<<net(faninnet.first).name<<"|"<<"net_"<<net(faninnet.second).name<<");"<<endl;
					
					break;
				case XOR:
					fout<<"assign "<<"net_"<<net(net_index).name<<" = "<<"net_"<<net(faninnet.first).name<<"^"<<"net_"<<net(faninnet.second).name<<";"<<endl;
				
					break;
				case NXOR:
					fout<<"assign "<<"net_"<<net(net_index).name<<" = ~("<<"net_"<<net(faninnet.first).name<<"^"<<"net_"<<net(faninnet.second).name<<");"<<endl;
				
					break;
                case DFF:
                    
                    
                    
                    fout<<"always @ ( posedge net_"<<net(DFF_Fanin[0]).name<<" ) begin"<<endl;
                    fout<<"if( net_"<<net(DFF_Fanin[1]).name<<"    ==1'b0)"<<endl;
                    fout<<"   net_"<<net(net_index).name<<" <= 1'b0;"<<endl;
                    fout<<"else begin"<<endl;
                    fout<<"   if(net_"<<net(DFF_Fanin[2]).name<<"==1'b0)"<<endl;
                    fout<<"     net_"<<net(net_index).name<<"<=net_"<<net(net_index).name<<";"<<endl;
                    fout<<"   else"<<endl;
                    fout<<"     net_"<<net(net_index).name<<"<=net_"<<net(DFF_Fanin[3]).name<<";"<<endl;
                    fout<<"end"<<endl;
                    fout<<"end"<<endl;
                    
                    
                    
                    break;
				default:
					assert(0);
					break;
                    
                    
				}
			
		}
	}
	
	
	
	
	fout<<"endmodule"<<endl<<endl;
	
	
	
	
}
































