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
