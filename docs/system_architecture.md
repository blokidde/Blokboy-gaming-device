# System Architecture

## Introduction
This section provides an overview of the entire IoT Snake Game setup. It explains each hardware and software component and how they communicate.

## Legend
- Rectangles: Subsystems or containers  
- Components: Smaller software units (for example, code files and libraries)  
- Database symbol: Data storage  
- Cloud symbols: External systems (for instance, GitLab or the Internet)  
- Arrows: Show direction of data and the communication protocols (HTTP, MySQL, etc.)

## Architecture Diagram
The following image shows the System Architecture Diagram for the IoT Snake Game. Each subsystem is labeled, and communication lines show which protocols and ports are used.

![Architecture_Diagram](https://teemiixuujuu34-fa53a7.dev.hihva.nl/assets/PlantUml_arch_diagram.png)

## Subsystems and Components

1. User Device (Mobile / Laptop)  
   - Runs a Browser that displays the frontend (HTML, CSS, JavaScript).  
   - Sends HTTP debug requests to the ESP32.  
   - Receives pages and data from the NGINX web server (HTTPS).

2. Host System (PC / Laptop)  
   - Runs the Docker Host with multiple containers (NGINX, PHP, MariaDB, phpMyAdmin).  
   - Connects to GitLab (external repository) and the Docker Registry (external system) to pull Docker images.  
   - Uses the Host OS (Windows/Linux) as the operating system.

3. Web Server (NGINX)  
   - Main entry point for HTTPS traffic from the browser.  
   - Hosts the Frontend (HTML, CSS, JS files).  
   - Routes API calls to the Backend (PHP scripts).

4. Backend (PHP API)  
   - Handles requests via API PHP files (for example, insert.php, get.php).  
   - Uses Backend Libraries (native PHP functions or extensions) to process data.  
   - Connects to the database for storing and retrieving game information.

5. Database System  
   - Runs inside the MariaDB Container.  
   - Holds the MariaDB Database and the Database Instance (actual data).  
   - Stores player scores and any other relevant game data.

6. Embedded System (ESP32)  
   - Written in C++ with Arduino Libraries.  
   - Contains the Game Logic for the Snake Game and an HTTP Client for sending and receiving data.  
   - Interfaces with the Joystick, Button, Buzzer, and TFT Display.

7. External Systems  
   - Internet / Intranet: Used for network communication (HTTPS, etc.).  
   - GitLab Repository: Stores the project code (external system).  
   - Docker Registry: Hosts Docker images (external system).

## Communication Protocols
- HTTPS (443): Browser to NGINX (secure)  
- HTTP (80): ESP32 to Backend or for debug requests  
- MySQL (3306): Backend (API) to database  
- SPI: ESP32 to TFT display  
- Analog / Digital: Joystick and button inputs  
- PWM: Buzzer output from ESP32

## Conclusion
This System Architecture diagram meets all assignment requirements (SAD#01–SAD#16). Each subsystem is clearly separated, and the communication protocols are indicated with arrows. The architecture clarifies how the IoT Snake Game works, from the embedded device to the Docker-based environment and the database.
