#include <iostream>
struct Node {
  int data;
  Node * nxt;
};

class Queue {
private:
  int len = 0;
  Node * beg;
  Node * end;

  int init(int d) {
    beg = new Node{d, nullptr};
    end = beg;
    len++;
  }

public:
  Queue(int d) : len(1), beg(new Node(d)), end(beg) {}
  int len() {
    return len;
  }

  bool empty() {
    if (beg == nullptr)
      return true;
    else
      return false;
  }

  int insert(int d) {
    if (empty()) {
      return init(d);
    } else {
      end->nxt = new Node{d, nullptr};
      end = end->nxt;
      len++;
      
      return 0;
    }
  }

  int remove() {
    
  }
};
