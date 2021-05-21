#include <iostream>

int main()
{
  std::cout << "You are Ana trying to break into the North Mountain Castle where Elsa is hiding...";
  std::cout << std::endl;
  std::cout << "You need to get the numbers correct in order to continue...";
  std::cout << std::endl;

  int a = 4;
  int b = 3;
  int c = 2;

  int sum = a + b + c;
  std::cout << "the sum of a, b, and c is ";
  std::cout << sum;
  std::cout << std::endl;

  int product = a * b * c;
  std::cout << "the product of a, b, and c is ";
  std::cout << product;
  std::cout << std::endl;
  return 0;
}