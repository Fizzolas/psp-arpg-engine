# PSP ARPG Engine

**A Diablo II-inspired ARPG engine scaffold for PSP-3001 homebrew**

> **Legal Notice**: This engine ships with **zero copyrighted assets**. You must provide your own legally obtained Diablo II game files. This is a bring-your-own-files (BYO) engine implementation.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Building](#building)
- [Installation & Deployment](#installation--deployment)
- [Directory Structure](#directory-structure)
- [Controls](#controls)
- [File Requirements](#file-requirements)
- [Troubleshooting](#troubleshooting)
- [Development Roadmap](#development-roadmap)
- [Architecture](#architecture)
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

---

## Features

### Core Engine
- ✅ PSP-specific initialization and callbacks
- ✅ Delta-time based game loop
- ✅ Logging system (writes to `userdata/engine.log`)
- ✅ Platform abstraction for directory management

### Rendering
- ✅ GU-based renderer (480×272 native resolution)
- ✅ Software text rendering with bitmap font
- ✅ Isometric projection utilities
- ✅ Sprite and rectangle primitives

### Input System
- ✅ Complete PSP button enumeration
- ✅ Action mapping layer (gameplay binds to actions, not raw buttons)
- ✅ Modifier support (L, R, L+R chord combos)
- ✅ Analog stick with deadzone
- ✅ Context-sensitive button meanings
- ✅ INI-based config persistence

### UI
- ✅ Main menu system with navigation
- ✅ Data check screen
- ✅ Controls configuration viewer
- ✅ Test scene for input verification
- ✅ HUD framework (health/mana/gold)

### Asset Pipeline
- ✅ DataRoot resolver for user-supplied files
- ✅ File existence validation
- ✅ Virtual filesystem abstraction
- ✅ MPQ archive interface (stub - ready for implementation)

### Game Logic
- ✅ Entity system scaffold
- ✅ World/level management stub
- 🔲 Full Diablo II asset parsers (planned)

---

## Prerequisites

### Development Environment

1. **PSPSDK toolchain** installed and configured
   - [PSP Dev Toolchain](https://github.com/pspdev/psptoolchain)
   - Ensure `psp-config` is in your PATH

2. **Build tools**:
   - GNU Make
   - GCC (psp-gcc)
   - Binutils (psp-binutils)

3. **PSP Libraries** (included with PSPSDK):
   - pspgum
   - pspgu
   - psprtc
   - pspaudio
   - psppower

### Runtime Requirements

- **PSP-3001** (or compatible model)
- **Custom Firmware**: 6.61 PRO-C Infinity (or equivalent)
- **Memory Stick** with sufficient space (~2GB recommended for Diablo II files)

---

## Building

```bash
# Clone the repository
git clone https://github.com/Fizzolas/psp-arpg-engine.git
cd psp-arpg-engine

# Build the project
make clean
make

# Output: EBOOT.PBP in the project root
```

### Build Output

- `EBOOT.PBP` - The PSP executable
- `psparpg.elf` - Intermediate ELF binary (debug)
- `*.o` - Object files (in src/ subdirectories)

---

## Installation & Deployment

### Step 1: Create Directory Structure on PSP

On your PSP Memory Stick, create:

```
ms0:/PSP/GAME/psparpg/
├── EBOOT.PBP           # (Copy from build output)
├── ICON0.PNG           # (Optional app icon)
├── userdata/           # (Created automatically on first run)
│   ├── bindings.ini
│   └── engine.log
└── gamedata/           # (You must create this)
    ├── d2data.mpq      # (Copy from your Diablo II installation)
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

1. Locate your **legally obtained** Diablo II installation directory
2. Find the `.mpq` files (typically in the game root)
3. Copy the following files to `ms0:/PSP/GAME/psparpg/gamedata/`:
   - `d2data.mpq`
   - `d2char.mpq`
   - `d2sfx.mpq`
   - `d2music.mpq`
   - `d2video.mpq`
   - `d2exp.mpq` (if you have Lord of Destruction expansion)

### Step 4: Run

1. Launch PSP XMB
2. Navigate to **Game → Memory Stick**
3. Select **PSP ARPG Engine**
4. Press X to launch

---

## Directory Structure

```
psp-arpg-engine/
├── include/
│   ├── core/
│   │   ├── platform.h
│   │   ├── timing.h
│   │   └── logging.h
│   ├── renderer/
│   │   ├── renderer.h
│   │   └── isometric.h
│   ├── input/
│   │   ├── input.h
│   │   └── bindings.h
│   ├── audio/
│   │   └── audio_stub.h
│   ├── ui/
│   │   ├── menu.h
│   │   └── hud.h
│   ├── game/
│   │   ├── world.h
│   │   └── entity.h
│   └── assets/
│       ├── dataroot.h
│       ├── archive.h
│       └── filesystem.h
├── src/
│   ├── main.c
│   ├── core/
│   ├── renderer/
│   ├── input/
│   ├── audio/
│   ├── ui/
│   ├── game/
│   └── assets/
├── Makefile
├── README.md
└── ICON0.PNG
```

---

## Controls

### Default PSP Button Mapping

#### Movement & Camera
- **Analog Stick**: Move character
- **D-Pad**: UI navigation / Belt selection (context-dependent)

#### Combat & Interaction
- **Cross (✕)**: Primary action (Attack / Interact / Pickup)
- **Circle (○)**: Secondary action (Alternate skill / Cancel / Back)
- **Square (□)**: Quick potion / Action wheel
- **Triangle (△)**: Inventory / Character panel

#### Skills (Modifier-Based)
- **L + Cross**: Skill 1 (Skill Set A)
- **L + Circle**: Skill 2
- **L + Square**: Skill 3
- **L + Triangle**: Skill 4
- **R + Cross**: Skill 5 (Skill Set B)
- **R + Circle**: Skill 6
- **R + Square**: Skill 7
- **R + Triangle**: Skill 8

#### Advanced Functions (Chorded)
- **L + R + Triangle**: World Map
- **L + R + Square**: Skills Panel
- **L + R + Circle**: Quest Log
- **L + R + Cross**: Town Portal
- **L + R + Select**: Drop Item

#### System
- **Start**: Game Menu / Pause
- **Select**: Toggle UI cursor mode
- **Select (Hold)**: Show items on ground

### Design Philosophy

All ARPG functions are accessible using PSP controls through:

1. **Context-sensitive mappings**: Buttons change meaning based on game state (in-town vs combat vs UI)
2. **Modifier chords**: L/R triggers unlock additional skill sets
3. **Radial menus**: Square button opens action wheel for quick item/skill access (planned)
4. **UI cursor mode**: Select toggles a virtual cursor for inventory management

This ensures **100% feature parity** with PC controls despite hardware limitations.

---

## File Requirements

### Required Diablo II Files

The engine validates these files on startup:

| File | Purpose | Required |
|------|---------|----------|
| `d2data.mpq` | Core game data, levels, objects | ✅ |
| `d2char.mpq` | Character graphics, animations | ✅ |
| `d2sfx.mpq` | Sound effects | ✅ |
| `d2music.mpq` | Music tracks | ✅ |
| `d2video.mpq` | Cinematics | ✅ |
| `d2exp.mpq` | Expansion content (LoD) | ✅ |

### Data Check Screen

Navigate to **Main Menu → Data Check** to see:
- ✅ Green `[OK]` for found files
- ❌ Red `[MISSING]` for missing files with exact expected paths

**If files are missing**, the engine will **not crash** but will display placeholder graphics until you provide the data.

---

## Troubleshooting

### Build Issues

#### `psp-config: command not found`
**Solution**: PSPSDK not in PATH. Add to `.bashrc`/`.zshrc`:
```bash
export PSPDEV=/usr/local/pspdev
export PATH=$PATH:$PSPDEV/bin
```

#### `undefined reference to 'sceGuInit'`
**Solution**: Missing GU libraries. Verify Makefile `LIBS` line includes `-lpspgu -lpspgum`.

#### Compilation fails with header errors
**Solution**: Ensure PSPSDK is fully installed. Rebuild toolchain if necessary.

### Runtime Issues

#### Black screen on launch
**Solution**: 
1. Verify CFW is installed (6.61 PRO-C or similar)
2. Check `EBOOT.PBP` is in correct directory (`ms0:/PSP/GAME/psparpg/`)
3. Try rebooting PSP

#### "Corrupted Data" error
**Solution**: EBOOT.PBP is invalid. Rebuild from source or re-download.

#### No files detected in Data Check
**Solution**: 
1. Verify files are in `ms0:/PSP/GAME/psparpg/gamedata/`
2. Check filenames are **exactly** as listed (case-sensitive on some systems)
3. Ensure files are not in a subfolder

#### Controls not responding
**Solution**:
1. Run **Test Scene** from main menu to verify input detection
2. Delete `userdata/bindings.ini` to reset to defaults
3. Check `engine.log` for input errors

### Performance Issues

#### Low FPS / Stuttering
**Solution**: 
- This scaffold runs at fixed 333MHz CPU. Future optimizations needed for full game loop.
- Reduce asset loading (streaming vs full load)
- Profile using `psp-gprof` if available

---

## Development Roadmap

### Phase 1: Engine Foundation ✅ (Current)
- [x] PSP initialization & callbacks
- [x] Rendering pipeline
- [x] Input system with full PSP mapping
- [x] UI scaffolding
- [x] Asset pipeline interfaces
- [x] Data validation

### Phase 2: Asset Parsing 🔄 (Next)
- [ ] MPQ archive extraction (StormLib port or custom)
- [ ] DCC/DC6 sprite decoder
- [ ] DS1 map format parser
- [ ] COF animation data parser
- [ ] TBL/Excel data readers
- [ ] Palette (PAL/PLT) support

### Phase 3: Game Logic
- [ ] Character stats & skills
- [ ] Inventory system
- [ ] Item generation
- [ ] Monster AI
- [ ] Combat mechanics
- [ ] Quest system

### Phase 4: Polish
- [ ] Audio playback (music/SFX)
- [ ] Particle effects
- [ ] Minimap
- [ ] Save/load system
- [ ] Multiplayer (ad-hoc Wi-Fi)

---

## Architecture

### Modular Design

The engine is split into independent subsystems:

```
Core        → Platform abstraction, timing, logging
Renderer    → GU graphics, isometric projection
Input       → PSP controls, action mapping, bindings
Audio       → Sound/music playback (stub)
UI          → Menus, HUD, dialogs
Game        → World state, entities, game logic
Assets      → File I/O, archive parsing, data loading
```

### Data-Driven Philosophy

- **Actions not buttons**: Game code references `ACTION_PRIMARY`, not `PSP_CTRL_CROSS`
- **Config-based bindings**: `bindings.ini` allows remapping without recompilation
- **Asset abstraction**: `IArchive` and `IFileSystem` interfaces support multiple formats

### Memory Management

PSP has **32MB RAM** (24MB for homebrew). Engine uses:
- Static allocation for core systems
- Streaming for large assets (textures, audio)
- Object pools for entities

---

## License

This engine scaffold is provided as-is for educational and personal use. 

**Important**:
- The engine code is open-source (specify license in future commits)
- Diablo II game files are **copyrighted by Blizzard Entertainment**
- Users must own a legal copy of Diablo II to use this engine
- Do not distribute Diablo II game files

---

## Credits

- **PSP SDK**: pspdev community
- **Diablo II reverse engineering**: Phrozen Keep, d2mods community
- **Inspiration**: OpenDiablo2, DevilutionX projects

---

## Support

For issues, feature requests, or contributions:
- GitHub Issues: [https://github.com/Fizzolas/psp-arpg-engine/issues](https://github.com/Fizzolas/psp-arpg-engine/issues)
- Pull requests welcome!

---

**Happy brewing! May your loot be legendary. 🎮⚔️**
