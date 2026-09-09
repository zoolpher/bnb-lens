#pragma once

#include <string>
#include <fstream>
#include "MarketData.hpp"

namespace bnb {

    class CSVWriter {
    public:
        // When we create this writer, we give it a filename. 
        // It will open the file and immediately write the mandatory Header row.
        CSVWriter(const std::string& filename);
        
        // The destructor automatically closes the file when we are done.
        ~CSVWriter();

        // This function takes our snapshot and formats it into a single line of CSV text.
        void writeSnapshot(const OrderBookSnapshot& snap);

    private:
        // std::ofstream is C++'s standard way to write output to a file on the hard drive.
        std::ofstream file_;
    };

} // namespace bnb
