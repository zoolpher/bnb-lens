# Q&A Log

This file maintains a list of all the questions asked during the development of the `bnb-lens` project.

1. **What does `CMakeLists.txt` do?**
   It is a blueprint for the CMake tool. It finds external libraries (like Boost/OpenSSL), sets compiler rules (like C++17 and optimizations), and tells the compiler how to combine our source code into a runnable program.

2. **Why is it named `CMakeLists.txt` instead of `CMake.txt`?**
   The CMake tool is hard-coded to look for a file with the exact name `CMakeLists.txt`. If it is named anything else, the tool will throw an error and won't build the project.

3. **How and from where are we going to fetch the data?**
   We fetch data from Binance's public WebSocket servers (`wss://stream.binance.com:9443/stream`). We open a continuous pipeline to receive live updates.

4. **Where can I get the information about the data like number and type of columns?**
   The project specification (PDF) strictly defines this. There are two files: a raw data dump (9 columns) and an order book snapshot (exactly 26 columns, using scaled integers instead of decimals).

5. **Why doesn't `wss://stream.binance.com:9443/stream` work when typed into a web browser?**
   Web browsers use HTTP/HTTPS to request static web pages. `wss://` is the WebSocket protocol, used for raw, continuous bidirectional data streaming. Our C++ program will act as a specialized client to connect to it.

6. **How can we make a call to that server for live data without deploying the app online?**
   Your local computer can act as a client and "dial out" to Binance's public server over your home internet, just like your browser dials out to YouTube. You don't need a public IP or a cloud server to request data.

7. **Is it necessary to stay online to fetch live data?**
   Yes. WebSocket is a continuous live stream. If your internet drops or you turn off your computer, the connection drops and the data stops flowing. Cloud deployment is only needed if you want to capture data 24/7 without keeping your personal PC turned on.

8. **Can we handle decimals by splitting them into separate integers, or using bit manipulation?**
   Instead of splitting the whole number and decimal part, the industry standard (required by the PDF) is **Integer Scaling (Fixed-Point Arithmetic)**. We take the decimal (e.g., `64500.12345`), multiply it by a fixed scale (like $10^8$), and store it as one giant integer (`6450012345000`). This perfectly preserves the exact value without needing complex bit manipulation, and it is incredibly fast for computers to process.

9. **What is the maximum number of digits after the decimal for a Binance price level?**
   It depends on the coin, but the maximum is **8 decimal places**. For example, Bitcoin (BTC) usually only has 2 decimal places, but "meme coins" like Shiba Inu (SHIB) can have prices like `0.00001234`. Because the maximum is 8, we use a fixed multiplier of $10^8$ (100,000,000) for our integer scaling so it can safely handle any coin Binance throws at it.

10. **What is the point of using a `namespace` when we already have classes and structs?**
    A namespace acts like a "surname" (last name) for your code. It prevents naming collisions. If you name a class `OrderBook`, and you later import an external trading library that also has an `OrderBook` class, the C++ compiler will crash with a "name conflict" error. By wrapping your code in `namespace bnb`, your class's full name becomes `bnb::OrderBook`. It keeps your code safely isolated from the rest of the C++ universe.

11. **Will calling `updateLevel()` 100 times per second cause memory or performance overhead?**
    No, 100 times per second is actually incredibly slow for a modern CPU, which executes billions of operations per second. Furthermore, because we use the `-O2` optimization flag in CMake, the C++ compiler will likely "inline" the function. This means the compiler secretly removes the function call entirely and pastes the raw logic directly where it's needed, resulting in absolutely zero function-call overhead.

12. **What exactly is "inlining" at the OS and CPU level?**
    Normally, calling a function forces the CPU to pause, save its current state to a memory area called the "Stack", physically jump to a different location in RAM to execute the function, and then jump back. "Inlining" is a compiler trick where it replaces the function call with the actual raw instructions of the function itself. This eliminates the jump and the Stack usage, allowing the CPU to execute the networking or processing logic in one continuous, lightning-fast stream.
