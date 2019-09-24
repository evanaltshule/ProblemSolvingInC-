//Evan Altshule, Kelly Wang
#ifndef TABLE_H
#define TABLE_H
#include <string>
#include <iosfwd>
#include "entry.h"
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Table {

public:


    Table(unsigned int max_entries = 100);
    Table(unsigned int entries, istream &input);

    void put(unsigned int key, string data);
    void put(Entry e); 
    string get(unsigned int key) const;
    bool remove(unsigned int key); 

    void print_table();
    string toString(Entry e);

    friend ostream& operator<< (ostream &out, const Table &t);
    int getUsed() const;

    //O(nlogn) sorting
    void quickSort(vector<Entry>& v, int left, int right);
    int getCapacity() const;
    Entry getEntryAt(int i) const;
    int split(vector<Entry>& v, int left, int right, int who);
  
private:
    unsigned int max_entries;
    unsigned int entries;
    string input;
    vector<Entry> table_entries;
    unsigned int used;
    unsigned int capacity;
    string data;
    static unsigned int accesses;

    //private hash function
    int hash(unsigned int key, int mod_value) const; 
};

#endif
