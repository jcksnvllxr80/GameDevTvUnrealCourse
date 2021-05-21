#include <iostream>

// main function
int main()
{
  // tell the use whats happening
  std::cout << "You are Ana trying to break into the North Mountain Castle where Elsa is hiding..." << std::endl;
  std::cout << "You need to get the numbers on the lock correct to continue..." << std::endl;

  /*
    declare some variables
    this is a multiline comment
  */
  const int CodeLockNum1 = 4;
  const int CodeLockNum2 = 3;
  const int CodeLockNum3 = 2;
  const int CodeSum = CodeLockNum1 + CodeLockNum2 + CodeLockNum3;
  const int CodeProduct = CodeLockNum1 * CodeLockNum2 * CodeLockNum3;

  // tell the user what the sum and product are
  std::cout << std::endl << "There are 3 numbers on the lock. " << std::endl;
  std::cout << "the sum of the 3 numbers is: " << CodeSum << std::endl;
  std::cout << "the product of the 3 numbers is: " << CodeProduct << std::endl;
  std::cout << "Please enter the code..." << std::endl;

  int PlayerGuess1, PlayerGuess2, PlayerGuess3;
  std::cout << "Enter the first number..." << std::endl;
  std::cin >> PlayerGuess1;
  std::cout << "Enter the second number..." << std::endl;
  std::cin >> PlayerGuess2;
  std::cout << "Enter the third number..." << std::endl;
  std::cin >> PlayerGuess3;

  int PlayerGuessSum = PlayerGuess1 + PlayerGuess2 + PlayerGuess3;
  int PlayerGuessProduct = PlayerGuess1 * PlayerGuess2 * PlayerGuess3;

  if (PlayerGuessSum == CodeSum & CodeProduct == PlayerGuessProduct)
  {
    std::cout << "You win!!!" << std::endl;
  }

  return 0;
}