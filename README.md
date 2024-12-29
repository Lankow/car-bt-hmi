# CAR-BT-HMI

## About  
CAR-BT-HMI is a Qt-based application designed to serve as a vehicle dashboard interface by connecting to an ELM327 OBD2 Bluetooth device. It extracts and displays real-time speed and RPM data, providing a functional and visually appealing interface. The application runs on Windows desktops and is optimized for Raspberry Pi with a 7-inch display running Raspbian, though it can operate on any Linux distribution with Bluetooth support.

![CAR-BT-HMI Demo](demo/car-bt-hmi-demo.gif)

---

### Key Features  

- **Real-Time Dashboard**  
  - Displays speed and RPM using custom-designed gauges.
  - Includes a digital clock and odometer for a complete dashboard experience.  

- **Custom Gauge Components**  
  - Fully implemented custom gauges using Qt’s QML and C++.
  - Designed for efficient rendering and responsiveness.

- **Bluetooth Connectivity**  
  - Pairs with an ELM327 OBD2 Bluetooth interface.
  - Fetches speed and RPM data using the OBD-II protocol.

- **Cross-Platform Compatibility**  
  - Tested on Windows desktops for development.
  - Intended for deployment on Raspberry Pi, with compatibility for other Linux systems featuring Bluetooth.

---

### Why Use CAR-BT-HMI?  
This application simplifies the process of visualizing vehicle data on custom hardware. By leveraging the ELM327 OBD2 interface and Raspberry Pi, it provides an affordable and accessible way to build a functional car dashboard interface. The modularity of the design allows for further expansion, such as adding more gauges or integrating additional data sources.

---

### Requirements  

#### Hardware  
- Raspberry Pi or any Linux-compatible device with Bluetooth.  
- ELM327 OBD2 Bluetooth adapter.  
- Optional: 7-inch display for Raspberry Pi.  

#### Software  
- Qt framework (version 5 or later).  
- Raspbian OS or another Linux distribution with Bluetooth support.  
- Windows (for desktop testing).  

---

### Installation  

1. **Clone the Repository:**  
   ```bash
   git clone https://github.com/lankow/CAR-BT-HMI.git
   cd CAR-BT-HMI
