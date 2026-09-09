#include "CSVWriter.hpp"
#include <iostream>

namespace bnb {

    CSVWriter::CSVWriter(const std::string& filename) {

        // Open the file
        file_.open(filename);
        
        // If it opened successfully, write the exact header required by the PDF
        if (file_.is_open()) {
            file_ << "tsec,tnsec,seqNo,id,type,side,"
                << "bid0,bid1,bid2,bid3,bid4,"
                << "bid_size0,bid_size1,bid_size2,bid_size3,bid_size4,"
                << "ask0,ask1,ask2,ask3,ask4,"
                << "ask_size0,ask_size1,ask_size2,ask_size3,ask_size4\n";
        } else {
            std::cerr << "CRITICAL ERROR: Failed to open CSV file: " << filename << "\n";
        }
    }

    CSVWriter::~CSVWriter() {

        // Always safely close the file to ensure data is saved to the hard drive
        if (file_.is_open()) {
            file_.close();
        }
    }

    void CSVWriter::writeSnapshot(const OrderBookSnapshot& snap) {

        if (!file_.is_open()) return;

        // Write the metadata first (tsec, tnsec, seqNo, id, type, side)
        file_ << snap.tsec << ","
            << snap.tnsec << ","
            << snap.seqNo << ","
            << snap.id << ","
            << snap.type << ","
            << snap.side << ",";

        // Write the Top 5 Bid Prices
        for (int i = 0; i < 5; ++i) { file_ << snap.bids[i].price << ","; }
        
        // Write the Top 5 Bid Quantities
        for (int i = 0; i < 5; ++i) { file_ << snap.bids[i].quantity << ","; }
        
        // Write the Top 5 Ask Prices
        for (int i = 0; i < 5; ++i) { file_ << snap.asks[i].price << ","; }
        
        // Write the Top 5 Ask Quantities
        for (int i = 0; i < 5; ++i) { 
            file_ << snap.asks[i].quantity;
            
            // The very last item in a CSV row should NOT have a comma after it
            if (i < 4) file_ << ",";
        }
        
        // End the row with a newline character so the next snapshot goes on a new line
        file_ << "\n"; 
    }

} // namespace bnb
