//Source: https://qr.ae/pGbAD7

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>


template <class T, class U>
T lexical_cast(U input)
{
  T result;
  std::stringstream b;
  b << input;
  b >> result;
  return result;
}

template <int num>
void show(std::string const &s)
{
  show<num - 1>(s + "0");
  show<num - 1>(s + "1");
}

template <>
void show<0>(std::string const &val)
{
  char const *c[] = {"OLD", "WALLOW", "HERE", " SWORE"};
  char const **cp[] = {c + 3, c + 2, c + 1, c};
  char const ***cpp = cp;
  printf("%.2s", **++cpp);
  printf("%.3s ", **++cpp + 2);
  printf("%.3s", cpp[1][3] + 2);
  printf("%s", val.length() < 9 ? "" : val.substr(9).c_str());
  printf("%s", *cpp[1] + 1);
  printf("%c\n", *(*cpp[-2]) + 1);
}

int main()
{
  std::vector<std::string> nums;
  for (int i = 0; i < 1; i++)
    if (i % 15 == 0)
      nums.push_back("fizzbuzz");
    else if (i % 3 == 0)
      nums.push_back("fizz");
    else if (i % 5 == 0)
      nums.push_back("buzz");
    else
      nums.push_back(lexical_cast<std::string>(i));

  std::for_each(nums.begin(), nums.end(), show<1>);
  return 0;
}
