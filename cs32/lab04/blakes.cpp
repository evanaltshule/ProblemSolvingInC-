#include <stdio.h>
#include <iostream>
#include <vector>
#include "table.h"
#include "entry.h"
#include <stdlib.h>
#include <algorithm>


using namespace std;

Table::Table(unsigned int maxentries): count(maxentries*3 - 7, 0), length(3*maxentries-7){
    data.resize(length);
}

Table::Table(int entries, std::istream& input){
    length = 3*entries - 7;
    count.resize(length);
    data.resize(length);
    for(int i = 0; i<entries; i++){
        Entry temp;
        input >> temp;
        put(temp);
    }
}

void Table::put(unsigned int key, std::string data){
    Entry temp(key, data);
    put(temp);
    return;
}

void Table::put(Entry e){
    int key = e.get_key();
    int index = hash(key);
    if(count[index]==0){
        data[index].push_back(e);
        count[index]++;
        return;
    }
    else{
        bool a = true;
        int repeat= 0;
        for (int i=0; (i< count[index]); i++) {
            if(data[index][i].get_key()==key){
                data[index][i].set_data(e.get_data());
                return;
            }
        }
        data[index].push_back(e);
        count[index]++;
        return;
    }
}

std::string Table::get(unsigned int key){
    int index = hash(key);
    if(data[index].size() == 0){
        return "";
    }
    else{
        for(int i=0; i< count[index]; i++){
            if(data[index][i].get_key() == key){
                return data[index][i].get_data();
            }
        }
    }
    return "";
}

bool Table::remove(unsigned int key){
    int index = hash(key);
    if(data[index].size() == 0){
        return false;
    }
    else{
        for (int i =0; i<data[index].size(); i++) {
            if(data[index][i].get_key() == key){
                data[index].erase(data[index].begin() + i);
                count[i]--;
                return true;
            }
        }
    }
    return false;
}

int Table::hash(int key){
    return (103 * key) % length;
}

