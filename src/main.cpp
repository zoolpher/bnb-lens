#include <iostream>
#include "OrderBook.hpp"
#include "CSVWriter.hpp"

int main() {
    std::cout << "Starting bnb-lens market data capture..." << std::endl;
    
    while (true) {

        // Create our CSV Writer. It will immediately open the file and write the Header.
        bnb::CSVWriter writer("output/market_data_spot_BTCUSDT_2026-09-09_orderbook.csv");

        // Create our Order Book in memory
        bnb::OrderBook book;
        
        // Simulate some fake WebSocket data arriving from Binance
        std::cout << "Simulating live data from Binance..." << std::endl;
        
        // Let's pretend Binance tells us about 3 Buyers (Bids)
        // Remember, we multiply everything by 10^8. 
        // Price = 64500.50 -> 6450050000000
        // Quantity = 1.5 -> 150000000
        book.updateLevel(true, 6450050000000, 150000000); // Bid 1
        book.updateLevel(true, 6450040000000, 200000000); // Bid 2
        book.updateLevel(true, 6450030000000, 300000000); // Bid 3
        
        // Let's pretend Binance tells us about 3 Sellers (Asks)
        book.updateLevel(false, 6450060000000, 100000000); // Ask 1
        book.updateLevel(false, 6450070000000, 250000000); // Ask 2
        book.updateLevel(false, 6450080000000, 500000000); // Ask 3
        
        // Take a snapshot of the Order Book
        // Fake metadata: tsec=1690000000, tnsec=500000, seqNo=1, type='d' (depth), side='N'
        bnb::OrderBookSnapshot snap = book.getSnapshot(1690000000, 500000, 1, 'd', 'N');
        
        // Write that snapshot to the CSV file
        writer.writeSnapshot(snap);
        
        
        return 0;
    }
    std::cout << "Done! Snapshot saved to output/ folder." << std::endl;
}
