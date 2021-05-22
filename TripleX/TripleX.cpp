#include <iostream>

void PrintIntroduction(int Level)
{ // tell the use whats happening
  std::cout << "Level: " << Level << "\n";
  std::cout << "You are Ana trying to break into the North Mountain Castle where Elsa is hiding...\n";
  std::cout << "You need to get the numbers on the lock correct to continue...\n";
}


auto GenerateCodeNumbers()
{
  struct retVals
  { // Declare a local structure
    int sum, product;
  };
  /*
    declare some variables
    this is a multiline comment
  */
  const int CodeLockNum1 = 4;
  const int CodeLockNum2 = 3;
  const int CodeLockNum3 = 2;

  return retVals{CodeLockNum1 + CodeLockNum2 + CodeLockNum3, CodeLockNum1 * CodeLockNum2 * CodeLockNum3};
}


void PrintHints(int CodeSum, int CodeProduct)
{ // tell the user what the sum and product are
  std::cout << "\n- There are 3 numbers on the lock. \n";
  std::cout << "- The sum of the 3 numbers is: " << CodeSum;
  std::cout << "\n- The product of the 3 numbers is: " << CodeProduct << std::endl;
}


bool TakeInputAndCompare(int CodeSum, int CodeProduct, int *Lives)
{ // take players input
  int PlayerGuess1, PlayerGuess2, PlayerGuess3;
  std::cout << "Please enter the numbers, separated by a space...\n";
  std::cin >> PlayerGuess1 >> PlayerGuess2 >> PlayerGuess3;

  int PlayerGuessSum = PlayerGuess1 + PlayerGuess2 + PlayerGuess3;
  int PlayerGuessProduct = PlayerGuess1 * PlayerGuess2 * PlayerGuess3;

  // check if players numbers are correct
  if (PlayerGuessSum == CodeSum & PlayerGuessProduct == CodeProduct)
  {
    std::cout << "You got into the North Mountain Castle and found Elsa!!!\n";
    return true;
  }
  else
  {
    std::cout << "You did not get in to the North Mountain Castle. ";
    if (--*Lives > 0)
    {
      std::cout << "You have " << *Lives << " lives left. Please try again.\n";
    }
    else
    {
      std::cout << "You ran out of Lives :( Please start over and try again.\n";
    }
    return false;
  }
}


bool PlayLevel(int Level)
{
  int Lives = 3;
  bool bPlayerWon = false;
  PrintIntroduction(Level);
  auto [retval1, retval2] = GenerateCodeNumbers();
  const int CodeSum = retval1;
  const int CodeProduct = retval2;
  PrintHints(CodeSum, CodeProduct);
  while (!bPlayerWon && Lives > 0)
  {
    bPlayerWon = TakeInputAndCompare(CodeSum, CodeProduct, &Lives);
    std::cin.clear();
    std::cin.ignore();
  }
  return Lives > 0;
}


void PlayGame()
{ // loop the game while player has lives and all levels are not complete
  bool HasMoreLives = true;
  int Level = 0;
  const int MaxLevel = 5;
  while (Level < MaxLevel && HasMoreLives)
  {
    HasMoreLives = PlayLevel(++Level);
  }
  if (HasMoreLives)
  {
    std::cout << "You finished all the levels! Good job!\n";
  }
}


// main function
int main()
{
  PlayGame();
  return 0;
}