# Technical Documentation

## System Overview

This project connects an ESP32-based game device to a backend system using a RESTful API built in PHP. The backend stores gameplay and sensor data in a MySQL database, while the frontend displays game statistics and allows for remote interaction with the device.

### Components

| Component       | Technology            | Reason for Use                                          |
|----------------|------------------------|----------------------------------------------------------|
| Embedded Device | ESP32 Microcontroller  | Lightweight, powerful, and WiFi-capable                 |
| Frontend        | HTML, CSS, JavaScript  | Simple and accessible web interface                     |
| Backend API     | PHP                    | Lightweight, widely supported, and easy to integrate    |
| Database        | MySQL/MariaDB          | Robust, relational storage with easy PHP integration     |

## Design Decisions

- Technology choice: PHP was chosen because it's easy to use and works well with ESP32 POST requests. MySQL was selected for its reliability and widespread use.
- REST structure: Each endpoint performs one action only (POST to insert, GET to fetch, etc.), following RESTful principles.
- Modular schema: The database is designed with normalized, extensible tables to allow easy addition of future sensor types.

## Problems Encountered and Solutions

- issues during development: Solved by adding appropriate headers in PHP (Access-Control-Allow-Origin:).
- HTTPS certificate verification: ESP32 had trouble with HTTPS, solved by using client.setInsecure() for development.
- Data mismatch: Validations were added in PHP to ensure JSON data contains all required fields before insertion.



