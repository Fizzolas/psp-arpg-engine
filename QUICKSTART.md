# Quick Start Guide - PSP ARPG Engine

**Get running in 5 minutes!**

---

## What You'll Need

1. **PSP-3001** (or compatible) with **6.61 PRO-C Infinity** CFW
2. **PSPSDK toolchain** installed on your computer
3. **Your legally owned Diablo II game files** (MPQ archives)

---

## Step 1: Build the Engine (Linux/macOS/WSL)

```bash
# Install PSPSDK first if you haven't
# See: https://github.com/pspdev/psptoolchain

# Clone the repo
git clone https://github.com/Fizzolas/psp-arpg-engine.git
cd psp-arpg-engine

# Build
make clean
make

# You should now have EBOOT.PBP in the directory
ls -lh EBOOT.PBP
```

**If build fails**, check:
- Is `psp-config` in your PATH? Try: `psp-config --version`
- Did PSPSDK install completely? Verify libraries exist in `$PSPDEV/psp/sdk/lib/`

---

## Step 2: Create PSP Directory Structure

Connect your PSP via USB (USB mode), then:

```bash
# On your computer (assuming PSP is mounted at /media/psp or E:\)
PSP_ROOT="/media/psp"  # Change this to match your system

# Create directories
mkdir -p "${PSP_ROOT}/PSP/GAME/psparpg/gamedata"
mkdir -p "${PSP_ROOT}/PSP/GAME/psparpg/userdata"

# Copy the engine
cp EBOOT.PBP "${PSP_ROOT}/PSP/GAME/psparpg/"
```

**Windows users:**
```cmd
REM Assuming PSP is drive E:
mkdir E:\PSP\GAME\psparpg\gamedata
mkdir E:\PSP\GAME\psparpg\userdata
copy EBOOT.PBP E:\PSP\GAME\psparpg\
```

---

## Step 3: Copy Your Diablo II Files

**Find your Diablo II installation** (usually `C:\Program Files (x86)\Diablo II\` on Windows)

**Copy these 6 files to your PSP:**

```
Source (Your PC)              →  Destination (PSP)
──────────────────────────────────────────────────────────────
Diablo II/d2data.mpq          →  ms0:/PSP/GAME/psparpg/gamedata/d2data.mpq
Diablo II/d2char.mpq          →  ms0:/PSP/GAME/psparpg/gamedata/d2char.mpq
Diablo II/d2sfx.mpq           →  ms0:/PSP/GAME/psparpg/gamedata/d2sfx.mpq
Diablo II/d2music.mpq         →  ms0:/PSP/GAME/psparpg/gamedata/d2music.mpq
Diablo II/d2video.mpq         →  ms0:/PSP/GAME/psparpg/gamedata/d2video.mpq
Diablo II/d2exp.mpq           →  ms0:/PSP/GAME/psparpg/gamedata/d2exp.mpq
```

**Command line example (Linux/macOS):**
```bash
D2_PATH="/path/to/DiabloII"  # Update this
PSP_GAMEDATA="${PSP_ROOT}/PSP/GAME/psparpg/gamedata"

cp "${D2_PATH}/d2data.mpq" "${PSP_GAMEDATA}/"
cp "${D2_PATH}/d2char.mpq" "${PSP_GAMEDATA}/"
cp "${D2_PATH}/d2sfx.mpq" "${PSP_GAMEDATA}/"
cp "${D2_PATH}/d2music.mpq" "${PSP_GAMEDATA}/"
cp "${D2_PATH}/d2video.mpq" "${PSP_GAMEDATA}/"
cp "${D2_PATH}/d2exp.mpq" "${PSP_GAMEDATA}/"
```

---

## Step 4: Run on PSP

1. Disconnect PSP from USB
2. Navigate: **XMB → Game → Memory Stick**
3. You should see **"PSP ARPG Engine"**
4. Press **X** to launch

---

## What You Should See

1. **Splash Screen** - "PSP ARPG Engine" with "Bring Your Own Diablo II Files"
2. **Main Menu** with 5 options:
   - Start Game
   - Controls
   - Data Check  ← **Try this first!**
   - Test Scene
   - Quit

---

## Verify Installation

### Use the Data Check Screen

1. From main menu, select **"Data Check"** (option 3)
2. You'll see a list of required files with status:
   - `[OK]` in green = file found
   - `[MISSING]` in red = file not found

**All files should show `[OK]`**

If any show `[MISSING]`:
- Double-check filenames (case matters on some systems)
- Ensure files are in `ms0:/PSP/GAME/psparpg/gamedata/`
- Verify files aren't in a subfolder
- Check that MPQ files copied completely (they're ~50-200MB each)

---

## Test the Controls

### Option 1: Controls Reference

Main Menu → **Controls** (option 2)

Shows default button mappings.

### Option 2: Input Test Scene

Main Menu → **Test Scene** (option 4)

**Try these actions:**
- Move analog stick → Should show "MOVE_UP/DOWN/LEFT/RIGHT active"
- Press X → Shows "PRIMARY pressed"
- Press O → Shows "CANCEL pressed" (also returns to menu)
- Press D-pad → Navigation works in menus

---

## Troubleshooting

### "Corrupted Data" error on PSP

**Cause:** EBOOT.PBP didn't build correctly

**Fix:**
```bash
make clean
make

# Verify EBOOT.PBP exists and is >100KB
ls -lh EBOOT.PBP
```

### Black screen on launch

**Causes:**
1. CFW not installed properly
2. Wrong PSP directory structure

**Fix:**
- Verify CFW: Settings → System Settings → System Information → Should show "6.61 PRO-C"
- Recreate directory structure (see Step 2)
- Try rebooting PSP

### No files detected in Data Check (all red)

**Causes:**
1. Files in wrong directory
2. Directory name mismatch

**Fix:**
```bash
# Verify exact path on PSP (USB mode)
ls /media/psp/PSP/GAME/psparpg/gamedata/

# Should show:
d2char.mpq  d2data.mpq  d2exp.mpq  d2music.mpq  d2sfx.mpq  d2video.mpq

# Check directory name is EXACTLY "psparpg" (lowercase)
```

### Build error: "psp-gcc: command not found"

**Cause:** PSPSDK not in PATH

**Fix:**
```bash
# Add to ~/.bashrc or ~/.zshrc
export PSPDEV=/usr/local/pspdev
export PATH=$PATH:$PSPDEV/bin

# Reload shell
source ~/.bashrc

# Test
psp-gcc --version
```

### Build error: "cannot find -lpspgu"

**Cause:** PSPSDK libraries missing

**Fix:**
```bash
# Reinstall PSPSDK or rebuild toolchain
cd /path/to/psptoolchain
./toolchain.sh
```

---

## Where Are My Files?

### On PSP Memory Stick:

```
ms0:/PSP/GAME/psparpg/
├── EBOOT.PBP           ← The engine executable
├── userdata/           ← Auto-created on first run
│   ├── bindings.ini    ← Input configuration
│   └── engine.log      ← Debug log (check if crashes)
└── gamedata/           ← YOU create and fill this
    ├── d2data.mpq
    ├── d2char.mpq
    ├── d2sfx.mpq
    ├── d2music.mpq
    ├── d2video.mpq
    └── d2exp.mpq
```

### On Your Computer (Source):

```
psp-arpg-engine/
├── EBOOT.PBP           ← Build output (copy to PSP)
├── Makefile
├── README.md
├── QUICKSTART.md       ← You are here
├── include/
├── src/
└── *.o, *.elf          ← Intermediate build files
```

---

## What Works Now?

✅ **Boots and runs on PSP**
✅ **Main menu navigation**
✅ **File validation (Data Check screen)**
✅ **Input testing (Test Scene)**
✅ **Controls reference viewer**
✅ **Logging to userdata/engine.log**

⏳ **Coming Soon** (see main README):
- MPQ file parsing
- Sprite rendering (DCC/DC6)
- Map loading (DS1)
- Game logic

---

## Next Steps

1. **Verify everything works** using Data Check and Test Scene
2. **Read the full README.md** for architecture details
3. **Check engine.log** on PSP if you encounter issues
4. **Report bugs** via GitHub Issues

---

## Getting Help

**Before asking for help**, gather this info:

1. PSP model and CFW version
2. PSPSDK version: `psp-config --version`
3. Build log (full output of `make`)
4. Contents of `userdata/engine.log` from PSP
5. Screenshot of error (if visual)

**GitHub Issues:** [https://github.com/Fizzolas/psp-arpg-engine/issues](https://github.com/Fizzolas/psp-arpg-engine/issues)

---

**Happy hacking! 🎮**
