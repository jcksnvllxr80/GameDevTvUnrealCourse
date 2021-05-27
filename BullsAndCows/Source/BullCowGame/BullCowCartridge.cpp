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
        PrintLine(TEXT("You entered: ") + Input);
        if (Input == HiddenWord)
        {
            PrintLine(TEXT("Correct! You win!"));
            EndGame();
        }
        else
        {
            if (Input.Len() != HiddenWord.Len())
            {
                PrintLine(TEXT("You entered %i characters."), Input.Len());
            }
            PrintLine(TEXT("Wrong! You lose!"));
            // remove a life
            EndGame();
        }
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
    PrintLine(TEXT("Guess the %i letter isogram..."), HiddenWord.Len());
    PrintLine(TEXT("Use TAB to access the terminal and then enter some text and press ENTER!"));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press ENTER to play again."));
}