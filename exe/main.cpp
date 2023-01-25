#include "InlineVector.hpp"
#include <iostream>

int
main ()
{
  InlineVector<int, 5> vec;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i)
    {
      char type;
      std::cin >> type;
      switch (type)
        {
        case 'a': // push_back
          {
            int value;
            std::cin >> value;
            vec.push_back (value);
            break;
          }
        case 'b': // pop_back

          {
            vec.pop_back ();
            break;
          }
        case 'p': // print vec
          {
            for (auto x : vec)
              {
                std::cout << x << " ";
              }
            std::cout << std::endl;
            break;
          }
        case 'i': // insert
          {
            int value, pos;
            std::cin >> value >> pos;
            vec.insert (vec.begin () + pos, value);
            break;
          }
        }
    }
}