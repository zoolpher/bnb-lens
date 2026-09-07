#include "OrderBook.hpp"

namespace bnb {

    void OrderBook::updateLevel(
        bool isBid, 
        int64_t price, 
        int64_t quantity
    ) {
        
        if (isBid) {
            if (quantity == 0) {
                bids_.erase(price);      // The buyer canceled their order or it was filled
            } else {
                bids_[price] = quantity; // Update the existing price, or add it if it's new
            }
        } else {
            // Exact same above logic, but for Sellers (Asks)
            if (quantity == 0) {
                asks_.erase(price);
            } else {
                asks_[price] = quantity;
            }
        }
    }

    OrderBookSnapshot OrderBook::getSnapshot(
        int64_t tsec, 
        int32_t tnsec, 
        uint64_t seqNo, 
        char type, 
        char side
    ) const {
        
        // The {} automatically initializes all numbers to 0, so if there are less than 5 prices,
        // the remaining slots will safely default to 0.
        OrderBookSnapshot snap{}; 
        
        // Fill in the metadata
        snap.tsec = tsec;
        snap.tnsec = tnsec;
        snap.seqNo = seqNo;
        snap.id = 1;    // Arbitrary stable ID for this session
        snap.type = type;
        snap.side = side;

        // Grab the Top 5 Bids (Buyers)
        int i = 0;
        // Iterate through the map from the beginning. 
        for (auto it = bids_.begin(); it != bids_.end() && i < 5; ++it) {
            snap.bids[i].price = it->first;       // 'first' is the key (Price)
            snap.bids[i].quantity = it->second;   // 'second' is the value (Quantity)
            i++;
        }

        // Grab the Top 5 Asks (Sellers)
        i = 0;
        for (auto it = asks_.begin(); it != asks_.end() && i < 5; ++it) {
            snap.asks[i].price = it->first;
            snap.asks[i].quantity = it->second;
            i++;
        }

        return snap;
    }

} // namespace bnb
