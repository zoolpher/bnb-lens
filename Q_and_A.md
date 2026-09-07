# Q&A Log

This file maintains a list of all the questions asked during the development of the `bnb-lens` project.

1. **How and from where are we going to fetch the data?**
   We fetch data from Binance's public WebSocket servers (`wss://stream.binance.com:9443/stream`). We open a continuous pipeline to receive live updates.

2. **Where can I get the information about the data like number and type of columns?**
   The project specification (PDF) strictly defines this. There are two files: a raw data dump (9 columns) and an order book snapshot (exactly 26 columns, using scaled integers instead of decimals).

3. **Why doesn't `wss://stream.binance.com:9443/stream` work when typed into a web browser?**
   Web browsers use HTTP/HTTPS to request static web pages. `wss://` is the WebSocket protocol, used for raw, continuous bidirectional data streaming. Our C++ program will act as a specialized client to connect to it.

4. **How can we make a call to that server for live data without deploying the app online?**
   Your local computer can act as a client and "dial out" to Binance's public server over your home internet, just like your browser dials out to YouTube. You don't need a public IP or a cloud server to request data.

5. **Is it necessary to stay online to fetch live data?**
   Yes. WebSocket is a continuous live stream. If your internet drops or you turn off your computer, the connection drops and the data stops flowing. Cloud deployment is only needed if you want to capture data 24/7 without keeping your personal PC turned on.
