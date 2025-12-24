# PSP ARPG Engine

**A Diablo II-inspired ARPG engine scaffold for PSP-3001 homebrew**

> **Legal Notice**: This engine ships with **zero copyrighted assets**. You must provide your own legally obtained Diablo II game files. This is a bring-your-own-files (BYO) engine implementation.

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/Fizzolas/psp-arpg-engine)
[![PSP](https://img.shields.io/badge/platform-PSP--3001-blue)](https://en.wikipedia.org/wiki/PlayStation_Portable)
[![CFW](https://img.shields.io/badge/CFW-6.61%20PRO--C-orange)](https://wololo.net/downloads/index.php/download/6355)
[![License](https://img.shields.io/badge/license-check_repo-lightgrey)](LICENSE)

---

## 📋 Quick Links

- 🪟 **[Windows Setup Guide](WINDOWS_SETUP.md)** - Complete WSL installation & troubleshooting
- 🚀 **[Quick Start Guide](QUICKSTART.md)** - 5-minute setup (for Linux/macOS/WSL)
- 📖 **[Full Documentation](#table-of-contents)** - This README

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Quick Start](#quick-start)
- [Prerequisites](#prerequisites)
- [Building](#building)
  - [Windows](#building-on-windows)
  - [Linux/macOS](#building-on-linuxmacos)
- [Installation & Deployment](#installation--deployment)
- [Directory Structure](#directory-structure)
- [Controls](#controls)
- [File Requirements](#file-requirements)
- [Troubleshooting](#troubleshooting)
- [Development Roadmap](#development-roadmap)
- [Architecture](#architecture)
- [Contributing](#contributing)
- [License](#license)

---

## Overview

This project provides a complete, compilable PSP homebrew ARPG engine scaffold designed for PSP-3001 running **6.61 PRO-C Infinity**. It implements:

- **Engine-only distribution**: No copyrighted Diablo II assets included
- **Runtime asset loading**: Detects and loads user-copied game files from Memory Stick
- **Full PSP input mapping**: All ARPG functions accessible via PSP controls with modifiers and context-sensitive bindings
- **Modular architecture**: Cleanly separated Core, Renderer, Input, Audio, UI, Game, and Asset subsystems
- **Isometric rendering support**: Framework for Diablo II-style isometric view
- **Data validation**: On-device file check screen showing exactly what's missing

**🪟 Windows User?** Start with **[WINDOWS_SETUP.md](WINDOWS_SETUP.md)** for WSL installation!

**🚀 Already have PSPSDK?** Jump to **[QUICKSTART.md](QUICKSTART.md)** for 5-minute setup!

---

## Features

### Core Engine
- ✅ PSP-specific initialization and callbacks
- ✅ Delta-time based game loop (60 FPS target)
- ✅ Logging system (writes to `userdata/engine.log`)
- ✅ Platform abstraction for directory management

### Rendering
- ✅ GU-based renderer (480×272 native resolution)
- ✅ Software text rendering with bitmap font
- ✅ Isometric projection utilities
- ✅ Sprite and rectangle primitives
- ✅ Double-buffered VRAM rendering

### Input System
- ✅ Complete PSP button enumeration (35 game actions)
- ✅ Action mapping layer (gameplay binds to actions, not raw buttons)
- ✅ Modifier support (L, R, L+R chord combos)
- ✅ Analog stick with configurable deadzone
- ✅ Context-sensitive button meanings
- ✅ INI-based config persistence

### UI
- ✅ Main menu system with D-pad navigation
- ✅ Data check screen (validates required files)
- ✅ Controls configuration viewer
- ✅ Test scene for input verification
- ✅ HUD framework (health/mana/gold bars)

### Asset Pipeline
- ✅ DataRoot resolver for user-supplied files
- ✅ File existence validation at runtime
- ✅ Virtual filesystem abstraction
- ✅ MPQ archive interface (stub - ready for StormLib integration)
- ✅ Graceful degradation (runs with placeholders if data missing)

### Game Logic
- ✅ Entity system scaffold (256 entity pool)
- ✅ World/level management stub
- 🔲 Full Diablo II asset parsers (planned - see [Roadmap](#development-roadmap))

---

## Quick Start

### Windows Users

**See [WINDOWS_SETUP.md](WINDOWS_SETUP.md) for complete WSL installation guide.**

**TL;DR:**
```powershell
# In PowerShell (Administrator)
wsl --install
# Restart, then in Ubuntu:
wget https://github.com/pspdev/pspdev/releases/latest/download/pspdev-ubuntu-latest-x86_64.tar.gz
sudo tar -xvf pspdev-ubuntu-latest-x86_64.tar.gz -C /
echo 'export PSPDEV=/usr/local/pspdev' >> ~/.bashrc
echo 'export PATH=$PATH:$PSPDEV/bin' >> ~/.bashrc
source ~/.bashrc
```

### Linux/macOS/WSL Users

**See [QUICKSTART.md](QUICKSTART.md) for detailed step-by-step instructions.**

**TL;DR:**
```bash
# 1. Build
git clone https://github.com/Fizzolas/psp-arpg-engine.git
cd psp-arpg-engine
make

# 2. Copy to PSP
cp EBOOT.PBP /path/to/psp/PSP/GAME/psparpg/

# 3. Copy your Diablo II MPQ files to:
# /path/to/psp/PSP/GAME/psparpg/gamedata/

# 4. Run from PSP XMB → Game → Memory Stick
```

---

## Prerequisites

### Development Environment

#### Windows

**Option 1: WSL (Recommended)** ⭐
- Windows 10/11 with WSL 2
- Ubuntu from Microsoft Store
- [Full setup guide](WINDOWS_SETUP.md)

**Option 2: Docker**
- Docker Desktop with WSL 2 backend
- [Instructions](WINDOWS_SETUP.md#option-2-docker-advanced)

**Option 3: MinPSPW** (Not recommended - outdated)

#### Linux

**Install PSPSDK:**
```bash
wget https://github.com/pspdev/pspdev/releases/latest/download/pspdev-ubuntu-latest-x86_64.tar.gz
sudo tar -xvf pspdev-ubuntu-latest-x86_64.tar.gz -C /
export PSPDEV=/usr/local/pspdev
export PATH=$PATH:$PSPDEV/bin
```

#### macOS

**Use Docker** (native toolchain compilation is complex):
```bash
brew install docker
docker pull pspdev/pspdev
```

### Runtime Requirements

- **PSP-3001** (or compatible PSP-1000/2000/3000)
- **Custom Firmware**: 6.61 PRO-C Infinity or equivalent (6.60 PRO-B, 6.61 ME)
- **Memory Stick** with ~2GB free (for Diablo II files + saves)

---

## Building

### Building on Windows

**See [WINDOWS_SETUP.md](WINDOWS_SETUP.md) for complete instructions.**

**Using WSL:**
```bash
# In Ubuntu/WSL terminal
cd psp-arpg-engine
make clean
make
```

**Using Docker:**
```powershell
# In PowerShell
cd C:\Users\YourName\psp-arpg-engine
docker run --rm -v ${PWD}:/build pspdev/pspdev make
```

### Building on Linux/macOS

```bash
# Clone the repository
git clone https://github.com/Fizzolas/psp-arpg-engine.git
cd psp-arpg-engine

# Clean build
make clean
make

# Output: EBOOT.PBP
```

### Build Output

- `EBOOT.PBP` - PSP executable (ready to deploy)
- `psparpg.elf` - Intermediate ELF binary (for debugging with psplink)
- `*.o` - Object files (in `src/` subdirectories)

### Troubleshooting Build Errors

See [WINDOWS_SETUP.md#troubleshooting](WINDOWS_SETUP.md#troubleshooting) or [BUILD_VERIFICATION.md](BUILD_VERIFICATION.md).

---

## Installation & Deployment

### On Windows

**See [WINDOWS_SETUP.md - Deploying to PSP](WINDOWS_SETUP.md#deploying-to-psp)**

**Quick method:**
1. Connect PSP via USB
2. Copy `EBOOT.PBP` from `\\wsl$\Ubuntu\home\YourName\psp-arpg-engine\` to `E:\PSP\GAME\psparpg\`
3. Create `gamedata` and copy Diablo II MPQs

### On Linux/macOS

See [QUICKSTART.md - Installation](QUICKSTART.md#step-2-create-psp-directory-structure)

### Directory Structure on PSP

```
ms0:/PSP/GAME/psparpg/
├── EBOOT.PBP           # (Copy from build output)
├── userdata/           # (Auto-created on first run)
│   ├── bindings.ini    # (Input configuration)
│   └── engine.log      # (Runtime log)
└── gamedata/           # (YOU must create this)
    ├── d2data.mpq      # (Copy from your Diablo II install)
    ├── d2char.mpq
    ├── d2sfx.mpq
    ├── d2music.mpq
    ├── d2video.mpq
    └── d2exp.mpq
```

---

## Controls

See full control mapping in [QUICKSTART.md - Controls](QUICKSTART.md#controls).

**Summary:**
- **Analog Stick**: Movement
- **D-Pad**: UI navigation
- **X**: Primary action
- **O**: Cancel/Secondary
- **L/R + Buttons**: Skills 1-8
- **L+R + Buttons**: Advanced functions (map, town portal, etc.)

---

## File Requirements

See [WINDOWS_SETUP.md - Copy Diablo II Files](WINDOWS_SETUP.md#copy-diablo-ii-files-windows--psp) for Windows-specific instructions.

**Required files** (copy to `gamedata/`):
- `d2data.mpq` (~60MB)
- `d2char.mpq` (~180MB)
- `d2sfx.mpq` (~50MB)
- `d2music.mpq` (~65MB)
- `d2video.mpq` (~100MB)
- `d2exp.mpq` (~250MB)

---

## Troubleshooting

### Windows-Specific Issues

See [WINDOWS_SETUP.md - Troubleshooting](WINDOWS_SETUP.md#troubleshooting)

### General Issues

See [QUICKSTART.md - Troubleshooting](QUICKSTART.md#troubleshooting) and [BUILD_VERIFICATION.md](BUILD_VERIFICATION.md)

---

## Development Roadmap

See [QUICKSTART.md - Development Roadmap](QUICKSTART.md#development-roadmap)

---

## Architecture

See [QUICKSTART.md - Architecture](QUICKSTART.md#architecture)

---

## Contributing

Contributions welcome! See [QUICKSTART.md - Contributing](QUICKSTART.md#contributing)

---

## License

See [QUICKSTART.md - License](QUICKSTART.md#license)

---

## Support

**Windows Users:** [WINDOWS_SETUP.md](WINDOWS_SETUP.md)  
**Quick Setup:** [QUICKSTART.md](QUICKSTART.md)  
**Build Issues:** [BUILD_VERIFICATION.md](BUILD_VERIFICATION.md)  
**GitHub Issues:** [Report bugs](https://github.com/Fizzolas/psp-arpg-engine/issues)

---

**May your loot be legendary! 🎮⚔️**
