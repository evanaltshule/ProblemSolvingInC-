//Evan Altshule, Kelly Wang
#include "entry.h"
#include "table.h"
#include <iostream>
#include <sstream>


using namespace std;


Table::Table(unsigned int max_entries):entries(max_entries), capacity(2*max_entries), used(0){
  //initialize an empty table
  for (int i=0; i<capacity; i++) {
    Entry empty;
    table_entries.push_back(empty);
  }
}

Table::Table(unsigned int entries, std::istream &input) : entries(entries), capacity(2*entries), used(0) {

  int count = 0;

  for (int i=0; i<capacity; i++) {
    Entry empty;
    thisTable.push_back(empty);
  }
  for (int i=0; i<entries; i++) {
    Entry newEntry;
    input >> newEntry;
    put(newEntry);
  }
}

void Table::put(unsigned int key, std::string data) {
  Entry newEntry;
  newEntry.set_key(key);
  newEntry.set_data(data);
  put(newEntry);
}

void Table::put(Entry e) {
  int quad = 5;
  int keyIndex = hash(e.get_key(), capacity);
  while(((thisTable[keyIndex]).get_data() != "") && ((thisTable[keyIndex]).get_data() != "removed")){
    if(e.get_key() == (thisTable[keyIndex]).get_key()){
      thisTable[keyIndex] = e;
      return;
    }
    keyIndex = hash(keyIndex + quad^2, capacity);
    quad++;
  }  
  thisTable[keyIndex] = e;
  used++;
}

string Table::get(unsigned int key) const {
  int quad = 5;
  int keyIndex = hash(key, capacity);
  while((thisTable[keyIndex]).get_data() != "" ) {
    if( (thisTable[keyIndex]).get_key() == key ) {
      if( (thisTable[keyIndex]).get_data() == "removed" ) {
    return "";
      }
      else {
    return (thisTable[keyIndex]).get_data();
      }
    }
    keyIndex = hash(keyIndex + quad^2, capacity);
    quad++;
  }
  return "";
}

bool Table::remove(unsigned int key) {
  Entry delEnt(key, "removed");
  int quad = 5;
  int remKey = hash(key, capacity);
  if((thisTable[remKey]).get_data() == "") {
    return false;
  }
  while((thisTable[remKey]).get_key() != key){
    if(((thisTable[remKey]).get_data() == "")) {
      return false;
    }
    remKey = hash(remKey + quad^2, capacity);
    quad++;
  }
  if((thisTable[remKey]).get_data() == "removed") {
    return false;
  }
  thisTable[remKey] = delEnt;
  used--;
  return true;
}

int Table::hash(unsigned int key, int mod_value) const {
  return key*611953 % (mod_value);
}

void Table::print_table() {
  string s = "";
  for(int i =0; i < entries; i++) {
    s += toString(thisTable[i]) + "\n";
  }
  cout << s << endl;
}

string Table::toString(Entry e) {
  stringstream s;
  s << e;
  return s.str();
}

int Table::getCapacity() const {
  return capacity;
}

Entry Table::getEntryAt(int i) const {
  return thisTable[i];
}

int Table::split(vector<Entry>& v, int left, int right, int who) {
  for (int i = left; i < right; ++i) {
    if (v[i] <= who) {
      swap(v[i], v[left]);
      left ++;
    }
  }
  return left - 1;
}

void Table::quickSort(vector<Entry>& v, int left, int right) {
  if (left >= right) {
    return;
  }
  int middle = left + (right - left) / 2;
  swap(v[middle], v[left]);
  int midpoint = split(v, left + 1, right, v[left]);
  swap(v[left], v[midpoint]);
  quickSort(v, left, midpoint);
  quickSort(v, midpoint + 1, right);
}

int Table::getUsed() const {
  return used;
}

ostream& operator<<(ostream &out, const Table &t) {
  
  int next = 0;
  Table h = t;
  vector<Entry> tmp;
  for(int i = 0; i < h.getCapacity(); i++) {
    if(((h.thisTable[i]).get_data() != "") && ((h.thisTable[i]).get_data() != "removed")){
      tmp.push_back(h.thisTable[i]);
    }
  }
  h.quickSort(tmp, 0, h.getUsed());
  
  for(int j = 0; j <h.getUsed(); j++) {
    Entry e = tmp[j];
    out << e << endl;
  }
  return out;
}
