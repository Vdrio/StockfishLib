// StockfishExport.h
#pragma once

#include "types.h"
#include <string>

using namespace Stockfish;

void Notify(std::string message);

extern "C" {
    __declspec(dllexport) void InitializeEngineCpp();
    __declspec(dllexport) void UCICpp();
    __declspec(dllexport) void SetOptionCpp(char* name, char* value);
    __declspec(dllexport) void GoCpp(char* parameters);
    __declspec(dllexport) void SetPositionCpp(char* fen);
    __declspec(dllexport) void UcinewgameCpp();
    __declspec(dllexport) void IsReadyCpp();
    __declspec(dllexport) void QuitCpp();
    __declspec(dllexport) void StopCpp();
    __declspec(dllexport) void PonderHitCpp();
    __declspec(dllexport) void FlipCpp();
    __declspec(dllexport) void BenchCpp(char* parameters);
    __declspec(dllexport) void DCpp();
    __declspec(dllexport) void EvalCpp();
    __declspec(dllexport) void SetIsLibraryCpp(bool value);


    __declspec(dllexport) void RegisterCallback(void(*callback)(const char*));
    __declspec(dllexport) void NotifyCSharp(const char* message);
}

