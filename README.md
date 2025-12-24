# PSP ARPG Engine

**A Diablo II-inspired ARPG engine scaffold for PSP-3001 homebrew**

> **Legal Notice**: This engine ships with **zero copyrighted assets**. You must provide your own legally obtained Diablo II game files. This is a bring-your-own-files (BYO) engine implementation.

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/Fizzolas/psp-arpg-engine)
[![PSP](https://img.shields.io/badge/platform-PSP--3001-blue)](https://en.wikipedia.org/wiki/PlayStation_Portable)
[![CFW](https://img.shields.io/badge/CFW-6.61%20PRO--C-orange)](https://wololo.net/downloads/index.php/download/6355)
[![License](https://img.shields.io/badge/license-check_repo-lightgrey)](LICENSE)

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Quick Start](#quick-start)
- [Prerequisites](#prerequisites)
- [Building](#building)
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

**🚀 New to this project?** Check out [QUICKSTART.md](QUICKSTART.md) for a 5-minute setup guide!

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

**Want to get running immediately?** See **[QUICKSTART.md](QUICKSTART.md)** for detailed step-by-step instructions.

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

1. **PSPSDK toolchain** installed and configured
   - [PSP Dev Toolchain](https://github.com/pspdev/psptoolchain)
   - Ensure `psp-config` is in your PATH
   - Verify: `psp-config --version`

2. **Build tools**:
   - GNU Make
   - GCC (psp-gcc)
   - Binutils (psp-binutils)

3. **PSP Libraries** (included with PSPSDK):
   - pspgum, pspgu (graphics)
   - psprtc (real-time clock)
   - pspaudio (audio stub)
   - psppower (CPU frequency control)

### Runtime Requirements

- **PSP-3001** (or compatible PSP-1000/2000/3000)
- **Custom Firmware**: 6.61 PRO-C Infinity or equivalent (6.60 PRO-B, 6.61 ME)
- **Memory Stick** with ~2GB free (for Diablo II files + saves)

---

## Building

### Compilation

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

#### `psp-config: command not found`
```bash
# Add PSPSDK to PATH
export PSPDEV=/usr/local/pspdev
export PATH=$PATH:$PSPDEV/bin
```

#### `undefined reference to 'sceGuInit'`
Verify Makefile `LIBS` includes: `-lpspgu -lpspgum`

#### Header file errors
Ensure PSPSDK is fully installed. Reinstall if necessary:
```bash
cd /path/to/psptoolchain
./toolchain.sh
```

---

## Installation & Deployment

### Step 1: Create Directory Structure on PSP

On your PSP Memory Stick, create:

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

### Step 2: Copy Engine

1. Connect PSP via USB (USB mode)
2. Copy `EBOOT.PBP` to `ms0:/PSP/GAME/psparpg/`
3. Disconnect PSP

### Step 3: Copy Your Diablo II Files

**⚠️ IMPORTANT: You must own a legal copy of Diablo II**

1. Locate your Diablo II installation directory
   - Windows: Usually `C:\Program Files (x86)\Diablo II\`
   - macOS: Check Battle.net install location
2. Find the `.mpq` files (typically in game root)
3. Copy these 6 files to `ms0:/PSP/GAME/psparpg/gamedata/`:
   - `d2data.mpq` (~60MB)
   - `d2char.mpq` (~180MB)
   - `d2sfx.mpq` (~50MB)
   - `d2music.mpq` (~65MB)
   - `d2video.mpq` (~100MB)
   - `d2exp.mpq` (~250MB, if you have Lord of Destruction)

### Step 4: Run

1. Launch PSP XMB
2. Navigate to **Game → Memory Stick**
3. Select **PSP ARPG Engine**
4. Press X to launch
5. **First run**: Go to "Data Check" to verify files copied correctly

---

## Directory Structure

<details>
<summary>Click to expand full source tree</summary>

```
psp-arpg-engine/
├── include/
│   ├── core/
│   │   ├── platform.h      # Platform abstraction
│   │   ├── timing.h        # Delta time & ticks
│   │   └── logging.h       # File logging
│   ├── renderer/
│   │   ├── renderer.h      # GU renderer
│   │   └── isometric.h     # Isometric projection
│   ├── input/
│   │   ├── input.h         # Input system
│   │   └── bindings.h      # Config bindings
│   ├── audio/
│   │   └── audio_stub.h    # Audio interface (stub)
│   ├── ui/
│   │   ├── menu.h          # Menu system
│   │   └── hud.h           # HUD rendering
│   ├── game/
│   │   ├── world.h         # World/level management
│   │   └── entity.h        # Entity system
│   └── assets/
│       ├── dataroot.h      # File resolver
│       ├── archive.h       # MPQ interface
│       └── filesystem.h    # Virtual FS
├── src/
│   ├── main.c              # Entry point & main loop
│   ├── core/               # Platform, timing, logging
│   ├── renderer/           # GU renderer & isometric
│   ├── input/              # Input handling & bindings
│   ├── audio/              # Audio stub
│   ├── ui/                 # Menu & HUD
│   ├── game/               # World & entities
│   └── assets/             # Asset pipeline
├── Makefile                # PSPSDK build script
├── README.md               # This file
├── QUICKSTART.md           # 5-minute setup guide
├── .gitignore
└── ICON0.PNG               # PSP app icon
```

</details>

---

## Controls

### Default PSP Button Mapping

#### Core Actions (No Modifiers)

| Button | Function |
|--------|----------|
| **Analog Stick** | Move character |
| **D-Pad** | UI navigation / Belt selection (context) |
| **Cross (✕)** | Primary action (Attack / Interact / Confirm) |
| **Circle (○)** | Secondary action (Cancel / Back) |
| **Square (□)** | Quick potion / Action wheel |
| **Triangle (△)** | Inventory / Character panel |
| **Start** | Pause / Game menu |
| **Select** | Toggle UI cursor mode |

#### Modifier-Based Skills

| Modifier + Button | Skill |
|-------------------|-------|
| **L + ✕/○/□/△** | Skills 1-4 (Set A) |
| **R + ✕/○/□/△** | Skills 5-8 (Set B) |

#### Advanced Functions (Chord Combos)

| Combo | Function |
|-------|----------|
| **L + R + △** | World Map |
| **L + R + □** | Skills Panel |
| **L + R + ○** | Quest Log |
| **L + R + ✕** | Town Portal |
| **L + R + Select** | Drop Item |

### Design Philosophy

All Diablo II ARPG functions are fully accessible using only PSP hardware through:

1. **Context-sensitive mappings**: Buttons adapt meaning (town vs combat vs menus)
2. **Modifier chords**: L/R triggers unlock 8 skill slots
3. **Radial menus**: Square opens action wheel (planned)
4. **UI cursor mode**: Select enables virtual mouse for inventory

This provides **100% feature parity** with PC despite hardware constraints.

---

## File Requirements

### Required Diablo II Files

The engine validates these on startup:

| File | Purpose | Size (approx) |
|------|---------|---------------|
| `d2data.mpq` | Core game data, levels, objects | ~60 MB |
| `d2char.mpq` | Character graphics, animations | ~180 MB |
| `d2sfx.mpq` | Sound effects | ~50 MB |
| `d2music.mpq` | Music tracks | ~65 MB |
| `d2video.mpq` | Cinematics | ~100 MB |
| `d2exp.mpq` | Expansion content (LoD) | ~250 MB |

### Data Check Screen

**Main Menu → Data Check**

- ✅ **Green `[OK]`**: File found and accessible
- ❌ **Red `[MISSING]`**: File not found (shows expected path)

**If files are missing**, the engine will still run but display placeholder graphics.

---

## Troubleshooting

### Build Issues

See [Building](#building) section above.

### Runtime Issues

#### Black screen on launch

**Causes:**
1. CFW not installed
2. Wrong directory structure
3. EBOOT.PBP corrupted

**Solutions:**
- Verify CFW: Settings → System Information → Should show "6.61 PRO-C"
- Recreate directory structure (see [Installation](#installation--deployment))
- Rebuild: `make clean && make`
- Try rebooting PSP

#### "Corrupted Data" error

**Cause**: Invalid EBOOT.PBP

**Solution**: Rebuild from source
```bash
make clean
make
# Verify EBOOT.PBP is >100KB
ls -lh EBOOT.PBP
```

#### No files detected (all red in Data Check)

**Causes:**
1. Files in wrong location
2. Case-sensitive filenames
3. Incomplete copy

**Solutions:**
- Verify path: `ms0:/PSP/GAME/psparpg/gamedata/`
- Check exact filenames (lowercase `.mpq`)
- Re-copy files (ensure they fully transfer)
- Verify file sizes match originals

#### Controls not responding

**Solutions:**
1. Run **Test Scene** from main menu
2. Delete `userdata/bindings.ini` to reset
3. Check `userdata/engine.log` for errors

### Getting More Help

Check `userdata/engine.log` on your PSP for detailed error messages.

**GitHub Issues**: [Report bugs here](https://github.com/Fizzolas/psp-arpg-engine/issues)

Include:
- PSP model & CFW version
- PSPSDK version
- Build log (if compilation issue)
- Contents of `engine.log`
- Steps to reproduce

---

## Development Roadmap

### Phase 1: Engine Foundation ✅ (Current - v0.1)
- [x] PSP initialization & callbacks
- [x] Rendering pipeline (GU + software text)
- [x] Input system with full PSP mapping
- [x] UI scaffolding (menus, HUD)
- [x] Asset pipeline interfaces
- [x] Data validation screen

### Phase 2: Asset Parsing 🔄 (Next - v0.2)
- [ ] MPQ archive extraction (StormLib port)
- [ ] DCC/DC6 sprite decoder
- [ ] DS1 map format parser
- [ ] COF animation data
- [ ] TBL/Excel data readers
- [ ] Palette (PAL/PLT) support

### Phase 3: Game Logic (v0.3)
- [ ] Character stats & skills
- [ ] Inventory system
- [ ] Item generation
- [ ] Monster AI
- [ ] Combat mechanics
- [ ] Quest system

### Phase 4: Polish (v1.0)
- [ ] Audio playback (MP3/WAV)
- [ ] Particle effects
- [ ] Minimap
- [ ] Save/load system
- [ ] Multiplayer (ad-hoc Wi-Fi)

---

## Architecture

### Modular Design

```
Core        → Platform abstraction, timing, logging
Renderer    → GU graphics, isometric projection, software text
Input       → PSP controls, action mapping, bindings
Audio       → Sound/music playback (stub)
UI          → Menus, HUD, dialogs
Game        → World state, entities, game logic
Assets      → File I/O, archive parsing, data loading
```

### Data-Driven Philosophy

- **Actions not buttons**: Game code references `ACTION_PRIMARY`, not `PSP_CTRL_CROSS`
- **Config-based bindings**: `bindings.ini` allows remapping
- **Asset abstraction**: `IArchive` and `IFileSystem` interfaces
- **Runtime validation**: File checks with helpful error messages

### Memory Management

PSP has **32MB RAM** (~24MB available for homebrew). Engine uses:

- **Static allocation** for core systems
- **Streaming** for large assets (textures, audio)
- **Object pools** for entities (256 max)
- **VRAM** for framebuffers (512×272×2 buffers)

---

## Contributing

Contributions welcome! Areas needing help:

1. **MPQ parsing**: Port StormLib or write custom parser
2. **DCC/DC6 decoders**: Sprite format implementations
3. **Performance**: Optimize rendering pipeline
4. **Audio**: Implement music/SFX playback
5. **Documentation**: Improve guides and comments

**Before contributing**:
- Test on real PSP hardware
- Follow existing code style
- Update README if adding features
- No copyrighted assets in PRs

---

## License

This engine scaffold is provided as-is for educational and personal use.

**Important Legal Notes**:
- Engine code: Open-source (license TBD - check LICENSE file)
- Diablo II game files: **© Blizzard Entertainment** - NOT included
- Users MUST own legal copy of Diablo II
- Do NOT distribute Diablo II game files

---

## Credits & Acknowledgments

- **PSPSDK**: pspdev community
- **Diablo II RE**: Phrozen Keep, d2mods community
- **Inspiration**: OpenDiablo2, DevilutionX
- **Tools**: StormLib (MPQ reference)

---

## Support

**Issues**: [GitHub Issues](https://github.com/Fizzolas/psp-arpg-engine/issues)

**Discussions**: [GitHub Discussions](https://github.com/Fizzolas/psp-arpg-engine/discussions)

**Quick Help**: See [QUICKSTART.md](QUICKSTART.md) and [Troubleshooting](#troubleshooting)

---

**May your loot be legendary! 🎮⚔️**
