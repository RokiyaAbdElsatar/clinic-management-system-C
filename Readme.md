# Clinic Control System

A GTK-based desktop application for managing clinic operations, including patient management and appointment slots.

## Features

- Admin and Client modes with separate interfaces
- Secure admin login
- Add, edit, and view patient records
- Reserve and cancel appointment slots
- Modern UI with custom styles and background images

## Project Structure

```
.
├── build/                # Compiled binaries
├── images/               # UI background and assets
├── include/              # Header files
├── modes/                # Source files for different modes (admin, client)
├── src/                  # Core source files
└── .vscode/              # VSCode settings
```

## Installing Dependencies

### On Windows

1. **Install MSYS2:**  
   Download and install from [https://www.msys2.org/](https://www.msys2.org/).

2. **Open MSYS2 MinGW terminal** and run:
   ```sh
   pacman -Syu
   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gtk3 pkg-config
   ```

### On Linux (Ubuntu/Debian)

```sh
sudo apt update
sudo apt install build-essential libgtk-3-dev pkg-config
```

## Build Instructions

1. **Dependencies:**  
   - GTK 3 development libraries  
   - GCC or compatible C compiler

2. **Build and run:**  
   Open a terminal in the project root and run:
   ```sh
   gcc -o build/clinic.exe src/*.c modes/*.c `pkg-config --cflags --libs gtk+-3.0`
   ./build/clinic.exe
   ```

## Usage

- Launch the application.
- Choose "Admin" or "Client" mode.
- In Admin mode, log in with password `1234`.
- Manage patients and appointments via the dashboard.

## Notes

- All patient data is stored in memory (not persistent).
- Images for backgrounds are in the `images/` folder.

## Authors

- Rokiya Abd Elsatar
