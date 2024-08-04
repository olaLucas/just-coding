#include <cstddef>
#include <iostream>

class Node {
  private:
    int data;
    Node * prox;
    
  public:
    Node() : data(0), prox(NULL) {}
    Node(const int d) : data(d), prox(NULL) {}  
    Node(const Node &p) : data(p.data), prox(p.prox) {}

    int get_data() {return data;}
    Node * get_prox() {return prox;}

    void set_data(const int d) {data = d;}
    void set_prox(Node & p) {prox = &p;}
    void set_prox_null() {prox = NULL;}
};

class Stack {
  private:
    int len; 
    Node * beg;
    Node * end;

    int init(const int d);

  public:
    Stack() : len(0), beg(NULL), end(NULL) {}
    Stack(const int d) : len(0), beg(NULL), end(NULL) {init(d);} 
    Stack(const Stack &p) : len(p.len), beg(p.beg), end(p.end) {}

    int insert(const int data);
    int pop();
    
    bool empty();

    Node * get_beg() {return beg;}
    Node * get_end() {return end;}
    int get_len() {return len;}
    
    int clear();
};

int Stack::init(const int d) {
  if (beg != NULL) {
    std::cout << "stack not empty." << std::endl;
    return -1;
  } else {
    beg = new Node(d);
    end = beg;
    len++;
  }

  return 0;
}

int Stack::insert(const int d) {
  if (beg == NULL) {
    return init(d);
  } else {
    end->set_prox(*(new Node(d)));
    end = end->get_prox();
    len++;
  }

  return 0; 
}

int Stack::pop() {
  if (empty()) {
    return -1;
  } 

  int data = 0;
  Node * nav = beg;

  // first element
  if (beg->get_prox() == NULL) {
    data = beg->get_data();
    delete beg;
    beg = NULL;
    len--;
    
  } else {
    Node * ant = NULL;
    while (nav->get_prox() != NULL) { // procurando pelo ultimo elemento
      ant = nav;
      nav = nav->get_prox(); 
    }

    data = nav->get_data();
    delete nav;
    
    ant->set_prox_null();
  }



  return data;
}

bool Stack::empty() {
  if (beg == NULL) {
    return true;
  } else {
    return false;
  }
}

int Stack::clear() {
  if (beg == NULL) {
    return 0;
  }
  
  int removed = 0;
  for (int i = 0; i < len; i++) {
    if (pop() == 0) {
      removed++;
    } else {
      break;
    };  
  }

  return removed;  
}
