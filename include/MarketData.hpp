#pragma once

#include <cstdint>
#include <string>

namespace bnb {

    // Represents a single price level in the order book.
    // We use 64-bit integers instead of floating-point numbers (decimals) 
    // to ensure perfect precision and avoid rounding errors.
    struct PriceLevel {
        int64_t price;
        int64_t quantity;
    };

    // Represents a snapshot of the Order Book at a given moment in time.
    // This structure directly maps to the columns required by the *_orderbook.csv file.
    struct OrderBookSnapshot {
        int64_t tsec;       // Timestamp in seconds
        int32_t tnsec;      // Timestamp nanosecond remainder
        uint64_t seqNo;     // Application sequence number
        int32_t id;         // Stable numeric ID for the symbol
        char type;          // ASCII letter for last applied event class
        char side;          // 'B' (Bid), 'S' (Ask), or 'N' (N/A)
        
        PriceLevel bids[5]; // Top 5 buying prices and quantities
        PriceLevel asks[5]; // Top 5 selling prices and quantities
    };

} // namespace bnb
