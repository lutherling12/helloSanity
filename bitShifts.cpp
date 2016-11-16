#include <sys/types.h>

#include <iostream>
#include <iomanip>

#define question(q) \
  std::cout << std::setw(60) << std::left << q;

#define assert(yn) \
  yn ? std::cout << "Yes" << std::endl \
     : std::cout << "No" << std::endl; 

int main ()
{
  const int32_t myInt = 0xFFF1FFF1;
  float myFloat = 0;

  question("Does masking the lower 16 bits make 0xFFF1?")
  assert ((myInt & 0xFFFF) == 0xFFF1)

  question("Well, is it the same after a static cast to float?")
  myFloat = static_cast<float>(myInt & 0xFFF1);
  assert ((myFloat == 0xFFF1))

  question("Can I shift the upper 16 bits down?")
  assert ((myInt >> 16) == 0xFFF1)

  question("And can I cast that to a float?")
  myFloat = static_cast<float>(myInt >> 16);
  assert ((myFloat == 0xFFF1))

  question("Well, what the hell is it when shifted down?")
  std::cout << std::hex << (myInt >> 16) << std::endl;

  question("I'm done.")
  assert (true);

  return 0;
}

// Sanity check brought to you by Luther.

#undef question
#undef assert