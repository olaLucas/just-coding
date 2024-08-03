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

    Node * get_beg();
    Node * get_end();
    int get_len();
    
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
  if (beg == NULL) {
    std::cout << "stack empty." << std::endl;
    return -1;
  }

  Node * nav = beg;
  if (nav->get_prox() == NULL) { // first element
    delete nav;
    beg = NULL; end = NULL;
    len--;

    return 0;
  }

  while (nav->get_prox() != end) {
    nav = nav->get_prox();
  }

  if (end != NULL) {
    delete end;
    end = nav;
  }

  return 0;
}

Node * Stack::get_beg() {
  if (beg == NULL) {
    std::cout << "Stack::get_beg() > stack empty." << std::endl;
  }

  return beg;
}

Node * Stack::get_end() {
  if (end == NULL) {
    std::cout << "Stack::get_end() > stack empty." << std::endl;
  }

  return end;
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
