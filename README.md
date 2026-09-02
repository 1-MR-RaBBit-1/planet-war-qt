# Planet War 🚀

A C++/Qt project that combines **TCP networking** with **Qt3D** to build the foundation of a simple 3D Planet War game.

This project is currently in the early development stage and focuses on learning and implementing Qt networking, Qt3D entities, materials, transformations, and GUI controls.

## 🛠️ Technologies

- C++
- Qt 6
- Qt Widgets
- Qt Network
- Qt3D
- CMake
- TCP
- QDataStream

## 🎮 Current Features

### TCP Server

The project currently includes a TCP server using:

- `QTcpServer`
- `QTcpSocket`
- `QDataStream`

The server listens on:

```text
127.0.0.1:5000

It can receive a QString from a TCP client and display the received message in the GUI.

Qt3D Scene

A basic Qt3D scene has been created with:

Qt3DWindow
QEntity
QSphereMesh
QTransform
QPhongMaterial

The camera is positioned to view the 3D scene.

Meteorite System

A basic meteorite creation system has been started.

Clicking Add Meteorite creates a red sphere inside the Qt3D scene.

Current structure:

Meteorite Entity
├── QSphereMesh
├── QTransform
└── QPhongMaterial
🖥️ GUI

The current interface contains:

Qt3D scene
Received message display
IP address input
Connect button
Add Meteorite button
Meteorite name input
Fire button

The controls are arranged using QGridLayout.

📚 What I'm Learning

This project is also a learning project for understanding:

TCP client/server communication
Qt signals and slots
QTcpServer and QTcpSocket
QDataStream
Qt layouts and widgets
Qt3D entities and components
3D meshes
Materials
Transforms
Camera positioning
Connecting GUI controls to 3D objects
🚧 Current Status

The project is under active development.

The current implementation is a prototype and several systems are not implemented yet.

Planned Features
 Connect to a remote server using an IP address
 Meteorite naming
 Multiple meteorites
 Meteorite positioning
 Meteorite movement
 Fire system
 Projectile system
 Collision detection
 Planet objects
 Player system
 Network synchronization
 Multiple clients
 Proper TCP message framing
 Connection and error handling
 Game logic
📁 Project Structure
planet-war-qt/
├── client/
│   └── ...
├── server/
│   ├── main.cpp
│   ├── mainwindow.cpp
│   ├── mainwindow.h
│   └── ...
├── CMakeLists.txt
└── README.md
⚠️ Note

This project is currently experimental and primarily intended for learning C++, Qt networking, and Qt3D.

The architecture and implementation will change significantly as development continues.

📜 License

This project is for educational purposes.