//
//  fault.cpp
//  IFS
//
//  Created by Don on 2016/5/17.
//  Copyright © 2016年 Chun-Yao Lab. All rights reserved.
//

#include "fault.hpp"

#include <iostream>
#include <assert.h>
#include <fstream>
#include <algorithm>

using namespace std;

void Fault::neg_RDOB_fault_collapsing(){
    
    
    
    
    // enum FaultType {SA0, SA1, NEG, RDOB_AND, RDOB_NAND, RDOB_OR, RDOB_NOR,RDOB_XOR,RDOB_NXOR,RDOB_NOT,RDOB_BUFF};
    
    for (int net_index=0; net_index<numNet(); net_index++) {
        if(!net(net_index).ISPI()){
            switch (getDriveGateType(net_index)) {
                case BUFF:
                    link_faults(net_index*_numFaultType+RDOB_NOT, net_index*_numFaultType+NEG);
                    break;
                case NOT:
                    link_faults(net_index*_numFaultType+RDOB_BUFF, net_index*_numFaultType+NEG);
                    break;
                case AND:
                    link_faults(net_index*_numFaultType+RDOB_NAND, net_index*_numFaultType+NEG);
                    break;
                case NAND:
                    link_faults(net_index*_numFaultType+RDOB_AND, net_index*_numFaultType+NEG);
                    break;
                case OR:
                    link_faults(net_index*_numFaultType+RDOB_NOR, net_index*_numFaultType+NEG);
                    break;
                case NOR:
                    link_faults(net_index*_numFaultType+RDOB_OR, net_index*_numFaultType+NEG);
                    break;
                case XOR:
                    link_faults(net_index*_numFaultType+RDOB_NXOR, net_index*_numFaultType+NEG);
                    break;
                case NXOR:
                    link_faults(net_index*_numFaultType+RDOB_XOR, net_index*_numFaultType+NEG);
                    break;
                case DFF:
                    
                    break;
                default:
                    assert(0);
                    break;
            }
        }
        
    }
    return;
}



void Fault::stuck_at_fault_collapsing(){
    
    //int fst,scd;
    pair <int,int> faninnet;
    
    
    for(int net_index=0; net_index<numNet(); net_index++){
        
        if( !net(net_index).ISPI() ){//&& net(net_index).ISNOFANOUTNET() ){
            
            faninnet = getFaninNets(net_index);
            //cout<<"fanin "<<faninnet.first<<endl;
            
            switch (getDriveGateType(net_index)) {
                case BUFF:
                    if( net(faninnet.first).ISNOFANOUTNET() ){
                        link_faults(net_index, SA0, faninnet.first, SA0);
                        link_faults(net_index, SA1, faninnet.first, SA1);
                    }
                    break;
                case NOT:
                    if( net(faninnet.first).ISNOFANOUTNET() ){
                        link_faults(net_index, SA0, faninnet.first, SA1);
                        link_faults(net_index, SA1, faninnet.first, SA0);
                    }
                    break;
                case AND:
                    if( net(faninnet.first).ISNOFANOUTNET() )
                        link_faults(net_index, SA0, faninnet.first, SA0);
                    if( net(faninnet.second).ISNOFANOUTNET() )
                        link_faults(net_index, SA0, faninnet.second, SA0);
                    break;
                case NAND:
                    if( net(faninnet.first).ISNOFANOUTNET() )
                        link_faults(net_index, SA1, faninnet.first, SA0);
                    if( net(faninnet.second).ISNOFANOUTNET() )
                        link_faults(net_index, SA1, faninnet.second, SA0);
                    break;
                case OR:
                    if( net(faninnet.first).ISNOFANOUTNET() )
                        link_faults(net_index, SA1, faninnet.first, SA1);
                    if( net(faninnet.second).ISNOFANOUTNET() )
                        link_faults(net_index, SA1, faninnet.second, SA1);
                    break;
                case NOR:
                    if( net(faninnet.first).ISNOFANOUTNET() )
                        link_faults(net_index, SA0, faninnet.first, SA1);
                    if( net(faninnet.second).ISNOFANOUTNET() )
                        link_faults(net_index, SA0, faninnet.second, SA1);
                    break;
                case XOR:
                    break;
                case NXOR:
                    break;
                case DFF:
                    if( net(faninnet.first).ISNOFANOUTNET() ){
                        link_faults(net_index, SA0, faninnet.first, SA0);
                        link_faults(net_index, SA1, faninnet.first, SA1);
                    }
                    break;
                default:
                    assert(0);
                    break;
            }
            
        }
    }
    
    
    
    
    
}





void  Fault::neg_fault_collapsing(){
    
    //int fst,scd;
    pair <int,int> faninnet;
    
    
    for(int net_index=0; net_index<numNet(); net_index++){
        
        if( !net(net_index).ISPI() ){//&& net(net_index).ISNOFANOUTNET() ){
            
            faninnet = getFaninNets(net_index);
            //cout<<"fanin "<<faninnet.first<<endl;
            
            switch (getDriveGateType(net_index)) {
                case BUFF:
                    if( net(faninnet.first).ISNOFANOUTNET() ){
                        link_faults(net_index, NEG, faninnet.first, NEG);
                    }
                    break;
                case NOT:
                    if( net(faninnet.first).ISNOFANOUTNET() ){
                        link_faults(net_index, NEG, faninnet.first, NEG);
                    }
                    break;
                case AND:
                    
                    break;
                case NAND:
                    
                    break;
                case OR:
                    
                    break;
                case NOR:
                    break;
                case XOR:
                    if( net(faninnet.first).ISNOFANOUTNET() )
                        link_faults(net_index, NEG, faninnet.first, NEG);
                    if( net(faninnet.second).ISNOFANOUTNET() )
                        link_faults(net_index, NEG, faninnet.second, NEG);
                    break;
                case NXOR:
                    if( net(faninnet.first).ISNOFANOUTNET() )
                        link_faults(net_index, NEG, faninnet.first, NEG);
                    if( net(faninnet.second).ISNOFANOUTNET() )
                        link_faults(net_index, NEG, faninnet.second, NEG);
                    break;
                case DFF:
                    if( net(faninnet.first).ISNOFANOUTNET() ){
                        link_faults(net_index, NEG, faninnet.first, NEG);
                    }
                    break;
                default:
                    assert(0);
                    break;
            }
            
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
}

void Fault::link_faults(int wire_index1,int faultType1,int wire_index2,int faultType2){
    link_faults(wire_index1*_numFaultType+faultType1,wire_index2*_numFaultType+faultType2);
    
    
    
    
}
void Fault::link_faults(int fault_index1, int fault_index2){
    assert(fault_index1<_all_faults.size()&&fault_index2<_all_faults.size());
    if (same_group(fault_index1,fault_index2)) {
        return;
    }
    
    
    _all_faults[_all_faults[fault_index2].first] .second =_all_faults[fault_index1].second;
    _all_faults[_all_faults[fault_index1].second] .first =_all_faults[fault_index2].first;
    _all_faults[fault_index1].second=fault_index2;
    _all_faults[fault_index2].first=fault_index1;
    if (!same_group(fault_index1,fault_index2)) {
        cout<<"ERROR"<<endl;
        getchar();
    }
    _num_groups--;
    
}


bool Fault::same_group(int fault_index1, int fault_index2){
    
    unsigned current = _all_faults[  fault_index1].second;
    while (current!=fault_index1) {
        if (current==fault_index2) {
            return true;
        }
        current = _all_faults[  current].second;
        
    }
    
    
    
    return false;
    
}


unsigned Fault::num_fault_group(){
    unsigned counter=0;
    vector<bool> visited;
    
    visited.resize(_numFaultType*numNet());
    for (unsigned i=0; i<_numFaultType*numNet(); i++) {
        visited[i] = false;
    }
    vector<unsigned> group;
    
    
    for (unsigned i=0; i<_numFaultType*numNet(); i++) {
        
        unsigned start = i;
        if(_isgiven[start]==-1||visited[start]){
            continue;
        }
        
        unsigned current = _all_faults[  start].second;
        group.push_back(start);
        while (current!=start) {
            if(_isgiven[current]>=0)
                group.push_back(current);
            
            current = _all_faults[  current].second;
            
        }
        
        for (int j=0; j<group.size(); j++) {
            visited[group[j]]=1;
        }
        
        counter++;
        
        
        
        group.clear();
    }
    
    
    
    
    
    
    
    
    
    return counter;
    
}


void Fault::read_fault_file(char* filename){
    _all_faults.resize(_numFaultType*numNet());
    _isgiven.resize(_numFaultType*numNet());
    for (int i=0; i<_numFaultType*numNet(); i++) {
        _all_faults[i].first = i;
        _all_faults[i].second = i;
        _isgiven[i] = -1;
    }
    _num_groups =0;
    ifstream fin;
    fin.open(filename,ios::in);
    int faultindex;
    int faultnet;
    string faulttype;
    while(fin>>faultindex>>faultnet>>faulttype){
        _num_groups++;
        int fault_type_index;
        //enum FaultType {SA0, SA1, NEG, RDOB_AND, RDOB_NAND, RDOB_OR, RDOB_NOR,RDOB_XOR,RDOB_NXOR,RDOB_NOT,RDOB_BUFF};
        if(faulttype=="SA0"){
            fault_type_index = SA0;
        }
        else if(faulttype=="SA1"){
            fault_type_index = SA1;
        }
        else if(faulttype=="NEG"){
            fault_type_index = NEG;
        }
        else if(faulttype=="RDOB_AND"){
            fault_type_index = RDOB_AND;
        }
        else if(faulttype=="RDOB_NAND"){
            fault_type_index = RDOB_NAND;
        }
        else if(faulttype=="RDOB_OR"){
            fault_type_index = RDOB_OR;
        }
        else if(faulttype=="RDOB_NOR"){
            fault_type_index = RDOB_NOR;
        }
        else if(faulttype=="RDOB_XOR"){
            fault_type_index = RDOB_XOR;
        }
        else if(faulttype=="RDOB_NXOR"){
            fault_type_index = RDOB_NXOR;
        }
        else if(faulttype=="RDOB_NOT"){
            fault_type_index = RDOB_NOT;
        }
        else if(faulttype=="RDOB_BUFF"){
            fault_type_index = RDOB_BUFF;
        }
        else{
            assert(0);
        }
        
        
        _isgiven[getNetIndex(faultnet)*_numFaultType+fault_type_index]=faultindex;
        
        
        
        
        
    }
    
    
    
}


void Fault::write_output_fault_file(char* filename){
    ofstream fout;
    fout.open(filename,ios::out);
    vector<bool> visited;
    
    visited.resize(_numFaultType*numNet());
    for (unsigned i=0; i<_numFaultType*numNet(); i++) {
        visited[i] = false;
    }
    vector<unsigned> group;
    
    
    for (unsigned i=0; i<_numFaultType*numNet(); i++) {
        
        unsigned start = i;
        if(_isgiven[start]==-1||visited[start]){
            continue;
        }
        
        unsigned current = _all_faults[  start].second;
        group.push_back(start);
        while (current!=start) {
            if(_isgiven[current]>=0)
                group.push_back(current);
            
            current = _all_faults[  current].second;
            
        }
        
        for (int j=0; j<group.size(); j++) {
            visited[group[j]]=1;
        }
        int min = (int)_isgiven.size();
        if(group.size()>1){
            for (int j=0; j<group.size(); j++) {
                if (min>_isgiven[group[j]]&&_isgiven[group[j]]>=0) {
                    min=_isgiven[group[j]];
                }
            }
            for (int j=0; j<group.size(); j++) {
                if (min!=_isgiven[group[j]]&&_isgiven[group[j]]>=0) {
                    fout<<min<<"  "<<_isgiven[group[j]]<<endl;
                }
            }
            
            
            
            
        }
        
        
        
        
        
        
        
        
        
        group.clear();
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}









void Fault::write_another_format(){
    
    
    
    ofstream fout2;
    fout2.open("another_format",ios::out);
    
    //int fault1;
    //int fault2;
    int fault1_net;
    int fault2_net;
    int fault1_type=0;
    int fault2_type=0;
    string  ssssssssssssssssssss[11]={"SA0", "SA1", "NEG", "RDOB_AND", "RDOB_NAND", "RDOB_OR", "RDOB_NOR","RDOB_XOR", "RDOB_NXOR", "RDOB_NOT", "RDOB_BUFF"};
    
    for(int fault1=1;fault1<2000;fault1++){
        //cout<<fault1<<endl;
        fault1_net=-1;
        for (int i=0; i<_isgiven.size(); i++) {
            if (_isgiven[i]==fault1) {
                fault1_net=i/_numFaultType;
                fault1_type=i%_numFaultType;
                break;
            }
        }
        if(fault1_net==-1){
            break;
        }
        for(int fault2=fault1+1;fault2<2000;fault2++){
            fault2_net=-1;
            
            
            for (int i=0; i<_isgiven.size(); i++) {
                if (_isgiven[i]==fault2) {
                    fault2_net=i/_numFaultType;
                    fault2_type=i%_numFaultType;
                    break;
                }
            }
            if(fault1_net==-1||fault2_net==-1){
                break;
                
            }
            if(same_group(fault1_net*11+fault1_type,fault2_net*11+fault2_type)){
                
                
                fout2<<net(fault1_net).name<<"   "<<ssssssssssssssssssss[fault1_type]<<"  "<<net(fault2_net).name<<"   "<<ssssssssssssssssssss[fault2_type]<<endl;
                
                
                
            }
            
            
            
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}

