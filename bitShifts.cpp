#include <sys/types.h>

#include <iostream>
#include <iomanip>

#define question(q) \
  std::cout << std::setw(60) << std::left << q;

#define assert(yn) \
  yn ? std::cout << "Yes" << std::endl \
     : std::cout << "No" << std::endl; 

int main (int argc, char* argv[])
{
  const int32_t myInt = 0xFFFFFFFF;
  float myFloat = 0;

  question("Does masking the lower 16 bits of (2^31)-1 == (2^16) - 1?")
  assert ((myInt & 0xFFFF) == 0xFFFF)

  question("Well, is it the same after a static cast to float?")
  myFloat = static_cast<float>(myInt & 0xFFFF);
  assert ((myFloat == 0xFFFF))

  question("Can I shift the lower 16 bits down?")
  assert ((myInt >> 16) == 0xFFFF)

  question("And can I cast that to a float?")
  myFloat = static_cast<float>(myInt >> 16);
  assert ((myFloat == 0xFFFF))

  question("Well, what the hell is it when shifted down?")
  std::cout << static_cast<float>(myInt >> 16) << std::endl;

  question("I'm done.")
  assert (true);

  return 0;
}

// Sanity check brought to you by Luther.

#undef question
#undef assert