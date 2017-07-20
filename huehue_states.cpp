#include <string>
#include <vector>
#include <list>
#include <iostream>

template<typename keyT, typename keysV, typename keysL>
class parsifier_state;

template<typename keyT, typename keysV, typename keysL>
class compare;

template<typename keyT, typename keysV, typename keysL>
class enqueue;

template<typename keyT, typename keysV, typename keysL>
class discard;

template<typename keyT, typename keysV, typename keysL>
class parsifier_context
{
  public:
  keyT* key;
  keysV* vec;
  keysL* que;

  parsifier_state<keyT, keysV, keysL>* current;

  parsifier_context (keyT* k, keysV* v, keysL* q);
  ~parsifier_context(){
    delete current;
    std::cout << "hasta luego" << std::endl;
  };

  void set_state (parsifier_state<keyT, keysV, keysL>* s) {
    if (current != nullptr) {
      delete current;
    }
    current = s;
  };

  void next() {
    if (current == nullptr) {
      std::cout << "not initialized" << std::endl;
      return;
    }
    if (this != nullptr)
      current->next(*this);
  };
};

template<typename keyT, typename keysV, typename keysL>
class parsifier_state {
  public:
  virtual void next (parsifier_context<keyT, keysV, keysL>&) = 0;
  virtual ~parsifier_state(){};
};

template<typename keyT, typename keysV, typename keysL>
class compare : public parsifier_state<keyT, keysV, keysL> {
  public:
  compare(){std::cout << "compare state" << std::endl;}
  ~compare(){}

  void next (parsifier_context<keyT, keysV, keysL>& context) {
    if (!is_match(*context.key, context.vec->front()))
      context.set_state(new enqueue<keyT, keysV, keysL>());
    else
      context.set_state(new discard<keyT, keysV, keysL>());
  }

  private:
  bool is_match (const keyT &lhs, const keyT& rhs) {
    return lhs == rhs;
  }
};

template<typename keyT, typename keysV, typename keysL>
class enqueue : public parsifier_state<keyT, keysV, keysL> {
  public:
  enqueue() {std::cout << "enqueue state" << std::endl;}
  ~enqueue(){};
  void next (parsifier_context<keyT, keysV, keysL>& context) {
    if (context.vec->size() >= 1);
    // context.que->insert(context.que->end(), context.vec->begin(), context.vec->begin()+1);
      context.que->insert(context.que->end(), context.vec->front());
    context.set_state(new discard<keyT, keysV, keysL>());
  }
};

template<typename keyT, typename keysV, typename keysL>
class discard : public parsifier_state<keyT, keysV, keysL> {
  public:
  discard() {std::cout << "discard state" << std::endl;}
  ~discard(){};
  void next (parsifier_context<keyT, keysV, keysL>& context) {
    if (context.vec->size() >= 1)
      context.vec->erase(context.vec->begin(), context.vec->begin()+1);
    context.set_state(new compare<keyT, keysV, keysL>());
  }
};

template<typename keyT, typename keysV, typename keysL>
parsifier_context<keyT, keysV, keysL>::
parsifier_context (keyT* k, keysV* v, keysL* q) :
  key(k), vec(v), que(q), current (nullptr)
{
  std::cout << "init state" << std::endl;
  set_state (new compare<keyT, keysV, keysL>());
}

int main(int argc, char* argv[])
{
  std::string hue ("hue");
  std::vector<std::string> sentence
    {"hue", "hue", "hue", "mordekaiser", "is", "numero", "uno"};
  std::list<std::string> filtered;

  // parsifier_context<decltype(hue), decltype(sentence), decltype(filter)> no_laughing (&hue, &sentence, &filter);
  // parsifier_context no_laughing (&hue, &sentence, &filter);
  parsifier_context<std::string, std::vector<std::string>, std::list<std::string>> no_laughing (&hue, &sentence, &filtered);


  while (sentence.size() > 0)
    no_laughing.next();

  for (const auto& word : filtered)
    std::cout << word << " ";
  std::cout << std::endl;

  return 0;
}
