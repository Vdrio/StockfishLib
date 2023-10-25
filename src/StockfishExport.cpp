#include "StockfishExport.h"

#include <iostream>
#include <sstream>
#include <string>

#include "bitboard.h"
#include "position.h"
#include "evaluate.h"
#include "search.h"
#include "search.h"
#include "syzygy/tbprobe.h"
#include "thread.h"
#include "tt.h"
#include "uci.h"

#include <queue>
#include <vector>

using namespace Stockfish;

const char* StartFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

std::queue<std::string> myQueue;

Position pos;

StateListPtr states(new std::deque<StateInfo>(1));

static void(*savedCallback)(const char*) = nullptr;

extern "C" {
    __declspec(dllexport) void InitializeEngineCpp() {
        // ... existing code ...
        //std::cout << engine_info() << std::endl;
        UCI::init(Options);
        Tune::init();
        Bitboards::init();
        Position::init();
        Threads.set(size_t(Options["Threads"]));
        Search::clear(); // After threads are up
        Eval::NNUE::init();
        states = std::make_unique<std::deque<StateInfo>>(1);
        pos.set(StartFEN, false, &states->back(), Threads.main());
        if (Stockfish::IsLibrary)
        {
            NotifyCSharp("Initialization success");
        }

    }

    __declspec(dllexport) void UCICpp() {        
        UCI::uciWrap();
    }

    __declspec(dllexport) void QuitCpp() {        
        UCI::quitWrap();
    }
    __declspec(dllexport) void StopCpp() {        
        UCI::stopWrap();
    }
    __declspec(dllexport) void PonderHitCpp() {        
        UCI::ponderhitWrap();
    }
    __declspec(dllexport) void BenchCpp(char* parameters) {  
        std::string str = parameters;
        std::istringstream is(str);      
        UCI::benchWrap(pos, is, states);
    }
    __declspec(dllexport) void DCpp() {        
        UCI::dWrap(pos);
    }

    __declspec(dllexport) void EvalCpp() {        
        UCI::evalWrap(pos);
    }

     __declspec(dllexport) void FlipCpp() {        
        UCI::flipWrap(pos);
    }
    

    __declspec(dllexport) void SetOptionCpp(char* name, char* value) {
        // Implement the setoption command
        std::string strName = name;
        std::string strValue = value;
        std::string str = "name " + strName + " value " + strValue;
        std::istringstream is(str);
        UCI::setoptionWrap(is);
    }

    __declspec(dllexport) void GoCpp(char* parameters) {
        // Implement the go command
        std::string str = parameters;
        std::istringstream is(str);
        UCI::goWrap(pos, is, states);
        //go()
    }

    __declspec(dllexport) void SetPositionCpp(char* fen) {
        // Implement the position command
        std::string str = fen;
        std::istringstream is(str);
        UCI::positionWrap(pos, is, states);

    }

    __declspec(dllexport) void UcinewgameCpp() {
        UCI::ucinewgameWrap();
    }

    __declspec(dllexport) void IsReadyCpp() {

        UCI::isreadyWrap();
    }

    __declspec(dllexport) void SetIsLibraryCpp(bool value) {

        UCI::setIsLibrary(value);
    }
    // ... and so on for other commands ...

    __declspec(dllexport) void RegisterCallback(void(*callback)(const char*)) {
        savedCallback = callback; // Save the callback for later use
    }

    __declspec(dllexport) void NotifyCSharp(const char* message) {
        Notify(std::string(message));
    }
}

void Notify(std::string message) {
    if (savedCallback != nullptr) {
        savedCallback(message.c_str());
    }
}