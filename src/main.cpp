#include <iostream>
#include <csignal>
#include <atomic>
#include <thread>
#include <chrono>
#include "OrderBook.hpp"
#include "CSVWriter.hpp"

// We use an "atomic" boolean. Atomic means it is thread-safe and can be safely 
// flipped by the Operating System even while our main loop is running.
std::atomic<bool> keep_running{true};

// This function is triggered by the OS when the user presses Ctrl+C
void handle_sigint(int signum) {
    std::cout << "\n[Signal] Ctrl+C detected! Gracefully shutting down..." << std::endl;
    // We simply flip the switch to false. The while-loop will see this and exit cleanly.
    keep_running = false;
}

int main() {
    std::cout << "Starting bnb-lens market data capture..." << std::endl;
    
    // Tell the Operating System: "If the user presses Ctrl+C (SIGINT), call my handle_sigint function!"
    std::signal(SIGINT, handle_sigint);

    // 1. Create the CSV file ONLY ONCE when the program starts.
    bnb::CSVWriter writer("output/market_data_spot_BTCUSDT_2026-09-09_orderbook.csv");

    // 2. Create the Order Book in memory
    bnb::OrderBook book;

    std::cout << "Entering infinite loop. Press Ctrl+C to stop." << std::endl;
    
    // We will use this to simulate changing prices
    int64_t fake_price = 6450050000000;

    // 3. The Infinite Loop
    while (keep_running) {
        // --- THIS IS WHERE WE WILL EVENTUALLY WAIT FOR BINANCE DATA ---
        
        // For now, we simulate receiving 1 new packet every 100 milliseconds
        book.updateLevel(true, fake_price, 150000000); 
        fake_price += 100000000; // Increment price slightly just to show it changing

        // Get snapshot and write to CSV
        bnb::OrderBookSnapshot snap = book.getSnapshot(1690000000, 500000, 1, 'd', 'N');
        writer.writeSnapshot(snap);

        // Sleep for 100ms so we don't spam your hard drive with millions of rows per second during this test
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // 4. Safe Shutdown
    // Because we broke out of the loop cleanly, the program will naturally hit the end.
    // The CSVWriter's Destructor will automatically be called here, safely closing and saving the file!
    std::cout << "Clean shutdown complete. File saved!" << std::endl;

    return 0;
}
