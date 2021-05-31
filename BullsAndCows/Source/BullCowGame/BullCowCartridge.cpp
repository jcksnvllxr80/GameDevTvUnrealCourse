// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/IsogramList.txt");
    FFileHelper::LoadFileToStringArray(IsogramList, *WordListPath);
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
    int32 RandIndex = FMath::RandRange(0, IsogramList.Num() - 1);  // generates a random number between 0 and len of IsogramList
    // PrintLine(TEXT("// The random number is: %i."), RandIndex);
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
    PrintLine(TEXT("You will guess the isogram with number of\nlives equal to the length of the word."));
    PrintLine(TEXT("You will be given the length of the word on start\nand hints after you guess wrong."));
    PrintLine(TEXT("The hints are:\n\tBulls: number of correct letters in the correct position"));
    PrintLine(TEXT("\tCows: number of correct letters but in the incorrect position."));
    PrintLine(TEXT("Mooooo! Welcome to the bull & cow game!"));
    // PrintLine(TEXT("// The HiddenWord is: %s"), *HiddenWord);
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
        // PrintLine(TEXT("Searching for character %c in substring %s of string %s."), Word[0], *Substring, *Word);
        if (Substring.FindChar(Word[0], CharFoundAt))
        {
            // PrintLine(TEXT("Found character %c in substring %s of string %s."), Word[0], *Substring, *Word);
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
        PrintLine(TEXT("Wrong! You lost a life!"));
        if (--Lives > 0)
        {
            if (!IsIsogram(Guess))
            {
                PrintLine(TEXT("You entered %s, which is not an isogram."), *Guess);
            }
            else
            {
                FBullCowCount BullCowCount = GetBullCows(Guess);
                PrintLine(TEXT("You have %i bulls and %i cows."), BullCowCount.Bulls, BullCowCount.Cows);
            }
            PrintLine(TEXT("Guess the %i letter isogram with %i lives."), HiddenWord.Len(), Lives);
        }
        else
        {
            EndGame();
        }
    }
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString &Guess) const
{
    FBullCowCount Count;
    int32 CharFoundAt;
    for (int32 i = 0; i < Guess.Len(); i++)
    {
        if (HiddenWord[i] == Guess[i])
        {
            Count.Bulls++;
        }
        else
        {
            if (HiddenWord.FindChar(Guess[i], CharFoundAt))
            {
                Count.Cows++;
            }
        }
    }
    return Count;
}