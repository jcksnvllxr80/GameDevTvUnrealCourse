// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include <time.h>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/IsogramList.txt");
    FFileHelper::LoadFileToStringArray(IsogramList, *WordListPath);
    srand(time(NULL)); // initialize the random seed
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input)  // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }
}

FString UBullCowCartridge::GetRandomIsogram() const
{
    int32 RandIndex = rand() % IsogramList.Num();  // generates a random number between 0 and len of IsogramList
    PrintLine(TEXT("// The random number is: %i."), RandIndex);
    return IsogramList[RandIndex];
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = GetRandomIsogram();
    Lives = HiddenWord.Len();
    bGameOver = false;
    DisplayStartInfo();
}

void UBullCowCartridge::DisplayStartInfo()
{
    PrintLine(TEXT("Mooooo! Welcome to the bull & cow game!"));
    PrintLine(TEXT("// The HiddenWord is: %s"), *HiddenWord);
    PrintLine(TEXT("Guess the %i letter isogram with %i lives."), HiddenWord.Len(), Lives);
    PrintLine(TEXT("Use TAB to access the terminal and then enter some text and press ENTER!"));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press ENTER to play again."));
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    int32 CharFoundAt;
    if (Word.Len() > 1)
    {
        FString Substring = Word.RightChop(1);
        // PrintLine(TEXT("Searching for character %c in substring %s of string %s."), Guess[0], *Substring, *Guess);
        if (Substring.FindChar(Word[0], CharFoundAt))
        {
            // PrintLine(TEXT("Found character %c in substring %s of string %s."), Guess[0], *Substring, *Guess);
            return false;
        }
        else
        {
            return IsIsogram(Substring);
        }
    }
    else
    {
        return true;
    }
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    PrintLine(TEXT("You entered: ") + Guess);
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("Correct! You win!"));
        EndGame();
    }
    else
    {
        if (Guess.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("You entered %i characters."), Guess.Len());
        }
        if (!IsIsogram(Guess))
        {
            PrintLine(TEXT("You entered %s, which is not an isogram."), *Guess);
        }
        PrintLine(TEXT("Wrong! You lost a life!"));
        if (--Lives > 0)
        {
            PrintLine(TEXT("Guess the %i letter isogram with %i lives."), HiddenWord.Len(), Lives);
        }
        else
        {
            EndGame();
        }
    }
}