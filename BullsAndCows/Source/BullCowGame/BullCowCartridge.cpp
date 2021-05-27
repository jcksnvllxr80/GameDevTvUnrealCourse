// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
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

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("uncopyrightable");
    Lives = HiddenWord.Len();
    bGameOver = false;
    DisplayStartInfo();
}

void UBullCowCartridge::DisplayStartInfo()
{
    PrintLine(TEXT("Mooooo! Welcome to the bull & cow game!"));
    // PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord);
    PrintLine(TEXT("Guess the %i letter isogram with %i lives."), HiddenWord.Len(), Lives);
    PrintLine(TEXT("Use TAB to access the terminal and then enter some text and press ENTER!"));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press ENTER to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
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
            PrintLine(TEXT("Guess the %i letter isogram with %i lives."), HiddenWord.Len(), Lives);
        }
        else
        {
            EndGame();
        }
    }
}