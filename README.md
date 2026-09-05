# 🌍 Planet War

A 3D planet-based multiplayer game prototype built with **C++**, **Qt 6**, **Qt3D**, and **TCP networking**.

The project is currently in development. The main goal is to create a simple networked game where players interact with planets and launch meteors toward each other.

## ✨ Current Features

* 🌍 3D Earth model rendering
* ☄️ 3D meteor model rendering
* 🎨 Texture support for Earth and meteor models
* 🖥️ Qt3D-based 3D scene
* 🌐 TCP server/client communication
* 🔌 Custom server IP connection
* 📡 Sending and receiving data using `QDataStream`
* 🚀 Meteor movement animation using `QTimer`
* 🖱️ Basic game control interface using Qt Widgets
* 📦 Qt Resource System (`.qrc`) for 3D models and textures

## 🛠️ Technologies

* **C++17**
* **Qt 6**
* **Qt3D**
* **Qt Widgets**
* **Qt Network**
* **CMake**
* **TCP/IP**
* **QDataStream**
* **Blender** — 3D models and textures

## 📂 Project Structure

```text
planet-war-qt-main/
│
├── models/
│   ├── earth.obj
│   ├── earth.mtl
│   ├── earth.png
│   ├── metorate.obj
│   ├── metorate.mtl
│   └── meteor_texture.png
│
└── server/
    ├── main.cpp
    ├── mainwindow.cpp
    ├── mainwindow.h
    ├── resources.qrc
    ├── CMakeLists.txt
    └── build/
```

## 🎮 Current Gameplay

The current prototype contains a 3D Earth and a meteor.

When a meteor is created, it is placed in the scene and can be launched using the **Fire** button.

Meteor movement is currently handled locally using a `QTimer`, allowing the meteor to move smoothly along the X axis.

```cpp
QVector3D pos = meteoriteTransform->translation();

pos.setX(pos.x() + 0.05f);

meteoriteTransform->setTranslation(pos);
```

## 🌐 Networking

The project uses Qt's TCP networking classes:

```cpp
QTcpServer
QTcpSocket
QDataStream
```

The server listens on a TCP port and accepts incoming clients.

Currently, the project supports sending basic data such as `QString` between the client and server using `QDataStream`.

Example:

```cpp
QDataStream stream(socket);
stream << QString("Hello");
```

And on the receiving side:

```cpp
QDataStream stream(socket);

QString text;
stream >> text;
```

## 🖼️ 3D Models

The 3D models are created/exported using **Blender** and loaded into Qt3D using `QMesh`.

Example:

```cpp
Qt3DRender::QMesh *earthM = new Qt3DRender::QMesh();

earthM->setSource(
    QUrl("qrc:/models/earth.obj")
);
```

Textures are loaded through Qt3D's texture system:

```cpp
Qt3DRender::QTexture2D *texture =
    new Qt3DRender::QTexture2D();

Qt3DRender::QTextureImage *textureImage =
    new Qt3DRender::QTextureImage();

textureImage->setSource(
    QUrl("qrc:/models/meteor_texture.png")
);

texture->addTextureImage(textureImage);
```

## 🔨 Building

Make sure Qt 6, Qt3D and CMake are installed.

Clone the repository:

```bash
git clone https://github.com/USERNAME/planet-war-qt-main.git
cd planet-war-qt-main/server
```

Create a build directory:

```bash
mkdir build
cd build
```

Configure and build:

```bash
cmake ..
cmake --build .
```

Run the server:

```bash
./server
```

## 📌 Project Status

**Work in Progress 🚧**

The current version is mainly a prototype for learning and implementing:

* 3D rendering
* Qt3D
* TCP networking
* Client/server architecture
* Real-time object movement
* Basic game mechanics

Many gameplay and networking features are still planned.

## 🗺️ Planned Features

* [ ] Complete client-side gameplay
* [ ] Synchronize meteor movement between server and client
* [ ] Multiplayer gameplay
* [ ] Player/planet interaction
* [ ] Meteor collision detection
* [ ] Health/damage system
* [ ] Better camera and controls
* [ ] Multiple meteors
* [ ] Game state synchronization
* [ ] Improved UI
* [ ] Multiplayer game loop
* [ ] Better resource/material handling
* [ ] Game win/lose conditions

## 📚 Purpose

This project is being developed as a learning project to gain practical experience with **C++**, **Qt**, **Qt3D**, and **TCP networking**, while gradually building them into a playable multiplayer game.

## 📄 License

This project is currently intended for educational and personal development purposes.
