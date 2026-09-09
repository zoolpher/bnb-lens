# bnb-lens (Binance LOB Capture)

A high-performance C++17 application designed to capture live market data from Binance's public WebSocket streams, maintain a deterministic Local Order Book (LOB), and emit highly precise CSV snapshots.

## 🚀 Getting Started

If you wish to experiment with or contribute to this project, you can fork and run it locally.

### Prerequisites
- **Compiler**: GCC 12 (or any compiler supporting C++17)
- **Build System**: CMake (v3.10+) and Ninja
- **Libraries**: Boost (system, thread), OpenSSL, ZLIB, Threads

### Installation & Running

1. **Fork & Clone**
   Fork the repository on GitHub, then clone your fork locally:
   ```bash
   git clone https://github.com/<your-username>/bnb-lens.git
   cd bnb-lens
   ```

2. **Build the Project**
   ```bash
   # Generate build scripts
   cmake -B build
   
   # Compile the executable
   cmake --build build
   ```

3. **Run the Executable**
   ```bash
   ./build/binance_capture
   ```
   *Note: Press `Ctrl+C` to gracefully shut down the application and safely save output files.*

## 📂 File Structure

```text
bnb-lens/
├── src/                  # C++ Source files (.cpp)
│   ├── main.cpp          # Application entry point, signal handling, and loop
│   ├── OrderBook.cpp     # LOB logic and snapshot generation
│   └── CSVWriter.cpp     # High-performance CSV output
├── include/              # Header files (.hpp)
│   ├── MarketData.hpp    # Data structures (PriceLevel, OrderBookSnapshot)
│   ├── OrderBook.hpp     # OrderBook class definition
│   └── CSVWriter.hpp     # CSVWriter class definition
├── output/               # Generated .csv files are stored here
├── build/                # Ignored compiler scratchpad directory
├── CMakeLists.txt        # CMake build configuration
└── Q_and_A.md            # Development FAQ and design decisions log
```

## 🏗️ Architecture & Design

This application is designed with **performance, scalability, and determinism** in mind.

- **Integer Scaling (Determinism)**: To completely avoid floating-point inaccuracies, all prices and quantities are scaled by a deterministic factor of **$10^8$** (e.g., `64500.50` is stored as `6450050000000` inside an `int64_t`).
- **Order Book State**: The Local Order Book utilizes C++ `std::map` (with `std::greater` for bids) to automatically and perfectly sort incoming price levels with O(log N) efficiency. 
- **I/O Buffering**: The CSV writing process leverages `std::ofstream` internal buffering. Instead of flushing to the physical hard drive on every single message (which would cause massive CPU blocking), it flushes data in optimized chunks to maximize throughput.
- **Memory Safety**: Leverages zero-initialization (`{}`) to guarantee that all snapshot memory is actively wiped clean, preventing corrupted data arrays.
- **Graceful Shutdown**: Integrates `<csignal>` to catch `SIGINT` (`Ctrl+C`), safely flipping a thread-safe `std::atomic<bool>` flag. This allows the event loop to exit cleanly and close all file streams without data loss.

## 🏁 Conclusion

`bnb-lens` provides a rock-solid, deterministic foundation for capturing and formatting high-frequency market data. By prioritizing memory safety, strict RFC 4180 CSV compliance, and fixed-point arithmetic, the application guarantees mathematically exact representations of the financial data streamed from the exchange.

## 🔮 Further Improvements

While the core Local Order Book logic and I/O handling are fully implemented, the project roadmap includes:
1. **Live Networking**: Integrating `Boost.Asio` and `Boost.Beast` wrapped in OpenSSL to consume live `wss://stream.binance.com:9443/stream` feeds rather than internal data simulations.
2. **CLI Argument Parsing**: Adding support for dynamically passing `--venue` and `--symbols` via command-line arguments.
3. **Dedicated Writer Thread**: Offloading the CSV writing process to a completely separate background thread with a thread-safe ring buffer, ensuring the network thread is never blocked by disk I/O.

---


*Architected and engineered by **-zoolpher**.*