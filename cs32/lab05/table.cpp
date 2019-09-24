//Evan Altshule 5233234
#include <string>
#include <iosfwd>
#include <vector>
#include <iostream>
#include <sstream>
#include "entry.h"
#include "table.h"
using namespace std;
Table::Table(unsigned int entries, std::istream &input){
	this->entries = entries;
	capacity = 2*entries;
	used = 0;
  	for (int i = 0; i < capacity; i++) {
    	Entry n;
    	tableEntries.push_back(n);
  	}
  	for (int i = 0; i < entries; i++) {
    	Entry entries;
    	input >> entries;
    	put(entries);
  	}
}
Table::Table(unsigned int max_entries){
	this->entries = max_entries;
	capacity = 2*max_entries;
	used = 0;
  	for (int i = 0; i < capacity; i++) {
  		Entry n;
    	tableEntries.push_back(n);
  	}
}

Table::Table(const Table &orig){
  *this = orig;
}

Table::~Table(){

}

Table& Table::operator=(const Table &cpy){
  if(&cpy == this){
    return *this;
  }

this->entries = cpy.entries;
this->used = cpy.used;
this->capacity = cpy.capacity;
this->tableEntries = cpy.tableEntries;
this->accesses = cpy.accesses;
this->max_entries = cpy.max_entries;
this->data = cpy.data;
this->input = cpy.input;
return(*this);


}

void Table::put(Entry e) {
	int probe = 5;
  	int index = (e.get_key()*611957)%capacity;
  	while(((tableEntries[index]).get_data() != "") && ((tableEntries[index]).get_data() != "gone")){
    	if(e.get_key() == (tableEntries[index]).get_key()){
      		tableEntries[index] = e;
      		return;
    	}
    index = (index+probe^2)*611957 % (capacity);
    probe++;
  	}  
  	tableEntries[index] = e;
  	used++;
}
void Table::put(unsigned int key, std::string data) {
  	Entry n;
  	n.set_key(key);
  	n.set_data(data);
 	put(n);
}
string Table::get(unsigned int key) const {
  	int probe = 5;
  	int index = key*611957 % capacity;
  	while((tableEntries[index]).get_data() != "" ) {
    	if( (tableEntries[index]).get_key() == key ) {
      		if( (tableEntries[index]).get_data() == "gone" )
				return "";
			else 
				return (tableEntries[index]).get_data();
      		
    	}
    	index = (index+probe^2)*611957 % capacity;
    	probe++;
  	}
  	return "";
}

bool Table::remove(unsigned int key) {
  	Entry delEnt(key, "gone");
  	int probe = 5;
  	int remKey = key*611957 % capacity;
  	if((tableEntries[remKey]).get_data() == "") {
    	return false;
  	}
  	while((tableEntries[remKey]).get_key() != key){
    	if(((tableEntries[remKey]).get_data() == "")) 
      		return false;
    	remKey = (remKey+probe^2)*611957 %capacity;
    	probe++;
  	}
  	if((tableEntries[remKey]).get_data() == "gone") 
    	return false;
  	tableEntries[remKey] = delEnt;
  	used--;
  	return true;
}
int Table::getCapacity() const {
  	return capacity;
}

int Table::getUsed() const {
  	return used;
}

Entry Table::getEntryAt(int i) const {
  	return tableEntries[i];
}

string Table::toString(Entry e) {
  	stringstream strr;
  	strr << e;
  	return strr.str();
}

vector<Entry> merge(vector<Entry> &l, vector<Entry> &r)
{
   vector<Entry> result;

   while (l.size() > 0 && r.size() > 0)
   {
       if (l[0] <= r[0])
       {                  
		   result.push_back(l[0]);
		   l.erase(l.begin());
       }
	   else
	   { 
		   result.push_back(r[0]);
		   r.erase(r.begin());
       }
   }
   
   if (l.size() > 0)
   {
	   for (int x = 0; x < (int) l.size(); x++)
		   result.push_back(l[x]);
   }
   else if (r.size() > 0)
   {
       for (int x = 0; x < (int)r.size(); x++)
		   result.push_back(r[x]);
   }

   return result;
}

vector<Entry> mergeSort (vector<Entry> &arrV){            
	int mid; 
    vector<Entry> left;
    vector<Entry> right;
	vector<Entry> result;


    if (arrV.size() <= 1)
		return arrV;
	else
	{
        mid = (int)arrV.size() / 2;
    

	    for (int x = 0; x < mid; x++)
			left.push_back(arrV[x]);
		for (int x = mid; x < (int)arrV.size(); x++)
			right.push_back(arrV[x]);

		left = mergeSort(left);
		right = mergeSort(right);
   
		 result = merge(left, right);

		 return result;
	}
}


void Table::print() {
  	string s = "";
  	for(int i =0; i < entries; i++) {
    	s += toString(tableEntries[i]) + "\n";
  	}
  	cout << s << endl;
}

ostream& operator<<(ostream &out, const Table &t) {
  	int next = 0;
  	Table h = t;
  	vector<Entry> entries2;
  	for(int i = 0; i < h.getCapacity(); i++) {
    	if(((h.tableEntries[i]).get_data() != "") && ((h.tableEntries[i]).get_data() != "gone")){
      		entries2.push_back(h.tableEntries[i]);
    	}
  	}
  	entries2 = mergeSort(entries2);
  
  	for(int j = 0; j <h.getUsed(); j++) {
    	Entry e = entries2[j];
    	out << e << endl;
  	}
  	return out;
}