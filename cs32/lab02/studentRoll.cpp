//Evan Altshule
#include <string>
#include "studentRoll.h"

StudentRoll::StudentRoll() {
  head = tail = NULL;
}

void StudentRoll::insertAtTail(const Student &s) {
  Node* curr = new Node;

  curr->s = new Student(s);
  curr->next = NULL;

  if(head==NULL){
    head = curr;
    tail = curr;
  }
  else{
    // Node* temp = new Node;
    // temp = head;
    // while(temp->next != NULL){
    //   temp = temp -> next;
    // }
    tail->next = curr;
    tail = curr;
  }
  curr = NULL;
}

std::string StudentRoll::toString() const {
  Node* temp = head;
  std::string rollStud = "[";
  while(temp!=NULL)
  {
    rollStud += temp ->s ->toString();
    if(temp->next != NULL){
      rollStud+= ",";
    }
    temp=temp->next;
  }

  rollStud = rollStud + "]";
  return rollStud;
}

StudentRoll::StudentRoll(const StudentRoll &orig) {
  head = tail = NULL;
  Node* temp = orig.head;
  while(temp!=NULL){
    this->insertAtTail(*(temp->s));
    temp = temp->next;
  }
}

StudentRoll::~StudentRoll() {
  Node* temp = head;
  while(temp!=NULL){
    Node* oneAfter = temp -> next;
    delete temp->s;
    delete temp;
    temp = oneAfter;
  }
  head = NULL;
}

StudentRoll & StudentRoll::operator =(const StudentRoll &right ) {
  // The next two lines are standard, and you should keep them.
  // They avoid problems with self-assignment where you might free up 
  // memory before you copy from it.  (e.g. x = x)

  if (&right == this) 
    return (*this);

   Node* temp = head;
  while(temp!=NULL){
    Node* oneAfter = temp -> next;
    delete temp->s;
    delete temp;
    temp = oneAfter;
  }
  head = NULL;
  

  Node* assigner = right.head;
  while(assigner!=NULL){
    this->insertAtTail(*(assigner->s));
    assigner = assigner-> next;
  }

  // KEEP THE CODE BELOW THIS LINE
  // Overloaded = should end with this line, despite what the textbook says.
  return (*this); 
  
}




