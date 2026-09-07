#pragma once

#include <map>
#include <cstdint>
#include "MarketData.hpp" // We include the file we made earlier!

namespace bnb {

    class OrderBook {

    public:

        // This function will be called every time Binance sends us a new price.
        // If the quantity is 0, it means we need to remove that price from the book.
        void updateLevel(
            bool isBid, 
            int64_t price, 
            int64_t quantity
        );

        // This function will grab the top 5 bids and top 5 asks and pack 
        // them into the OrderBookSnapshot struct created in MarketData.hpp
        OrderBookSnapshot getSnapshot(
            int64_t tsec, 
            int32_t tnsec, 
            uint64_t seqNo, 
            char type, 
            char side
        ) const;

    private:

        // std::map is a dictionary that automatically keeps its "keys" (the prices) SORTED!
        // The key is the Price, the value is the Quantity.
        
        // Bids (Buyers): The BEST buyer is the one willing to pay the HIGHEST price.
        // std::greater tells the map to sort from Highest to Lowest.
        std::map<int64_t, int64_t, std::greater<int64_t>> bids_;
        
        // Asks (Sellers): The BEST seller is the one offering the LOWEST price.
        // std::map sorts from Lowest to Highest by default.
        std::map<int64_t, int64_t> asks_;
    };

} // namespace bnb
