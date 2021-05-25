// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    HiddenWord = TEXT("uncopyrightable");
    PrintLine(TEXT("Mooooo! Welcome to the bull & cow game!"));
    PrintLine(TEXT("Guess the 16 letter isogram..."));  // Magic Number Remove
    PrintLine(TEXT("Use TAB to access the terminal and then enter some text and press ENTER!"));
}

void UBullCowCartridge::OnInput(const FString& Input)  // When the player hits enter
{
    ClearScreen();
    PrintLine(TEXT("You entered: ") + Input);

    if (Input == HiddenWord)
    {
        PrintLine(TEXT("Correct! You win!"));
    }
    else
    {
        PrintLine(TEXT("Wrong! You lose!"));
    }
}