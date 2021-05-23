// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Mooooo! Welcome to the bull & cow game!"));
    PrintLine(TEXT("Use TAB to access the terminal and then enter some text and press ENTER!"));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    FString HiddenWord = TEXT("uncopyrightable");
    ClearScreen();
}