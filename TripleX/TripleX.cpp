#include <iostream>

int main()
{
  std::cout << "You are Ana trying to break into the North Mountain Castle where Elsa is hiding..." << std::endl;
  std::cout << "You need to get the numbers correct in order to continue..." << std::endl;

  int a = 4;
  int b = 3;
  int c = 2;

  int sum = a + b + c;
  int product = a * b * c;

  std::cout << "the sum of a, b, and c is " << sum << std::endl;
  std::cout << "the product of a, b, and c is " << product << std::endl;
  return 0;
}