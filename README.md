# EF101-P20-Client-Server
Mini Client-Server Data Communication System - EF101 Fall 2026 (C++, TCP). 

# EF101-P20: Mini Client-Server Data Communication System

EF101 Fall 2026 | C++ (Winsock), TCP

**Group members:** Muneeb Ahmed (EE-017), Amna Athar (EE-014), Khizer (EE-026)

## What it does

A client sends temperature data and text messages to a server over a LAN.
The server displays them, saves them to `data.csv` and replies `ACK`.

## Protocol

TCP, port 5000. TCP is used because it is reliable and ordered, so no record is lost.

## How to run

1. Compile:
   - `g++ server_final.cpp -o server_final.exe -lws2_32`
   - `g++ client_final.cpp -o client_final.exe -lws2_32`
2. Run `server_final.exe` on the server laptop.
3. Find the server IP with `ipconfig`.
4. Run `client_final.exe`, then enter the server IP, port `5000` and token `abc123`.

## Features

- The client can send either a text message or temperature data, chosen from a menu.
- The server saves every record to `data.csv` and replies `ACK` to confirm.
- A token (`abc123`) works as a password. The server rejects clients with a wrong token.
- If a client disconnects, the server does not crash and keeps waiting for a new client.
- If the client enters a wrong IP or port, it shows an error because no server is found there.

## Files

- `server_final.cpp`: server source code
- `client_final.cpp`: client source code
- `data.csv`: sample saved data
- `screenshots/ (attached in the repository)

## Screenshots

![Client disconnected, server still running]
![Wrong IP/port gives an error]
![Messages and temperature data]
![Token check]
