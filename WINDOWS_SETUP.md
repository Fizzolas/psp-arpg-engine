# Windows Setup Guide - PSP ARPG Engine

**Complete guide for building PSP homebrew on Windows using WSL**

---

## ✅ Your Installation Status

Based on your log, PSPSDK is **already installed correctly**! You just need to configure your shell environment.

---

## Quick Fix (If you just installed PSPSDK)

Your installation succeeded, but the PATH isn't set yet. Run these commands:

```bash
# Set environment variables
echo 'export PSPDEV=/usr/local/pspdev' >> ~/.bashrc
echo 'export PATH=$PATH:$PSPDEV/bin' >> ~/.bashrc

# Reload shell configuration
source ~/.bashrc

# Test installation
psp-config --pspdev-path
# Should output: /usr/local/pspdev
```

**If that works, skip to [Building the Engine](#building-the-engine) below.**

---

## Full Windows Setup (From Scratch)

### Option 1: WSL (Recommended) ⭐

**Advantages:**
- Official PSPSDK support
- Latest toolchain updates
- Same commands as Linux/macOS
- Works alongside Windows tools

#### Step 1: Install WSL

**On Windows 10/11:**

1. Open **PowerShell as Administrator**
2. Run:
   ```powershell
   wsl --install
   ```
3. Restart your computer when prompted
4. After reboot, Ubuntu will auto-launch and ask for username/password

**Already have WSL?** Skip to Step 2.

**Troubleshooting:**
- If `wsl --install` fails, enable "Virtual Machine Platform" in Windows Features
- Settings → Apps → Optional Features → More Windows Features → ✅ Virtual Machine Platform

#### Step 2: Install PSPSDK in WSL

**Open Ubuntu from Start Menu, then run:**

```bash
# Download latest PSPSDK
wget https://github.com/pspdev/pspdev/releases/latest/download/pspdev-ubuntu-latest-x86_64.tar.gz

# Extract to /usr/local
sudo tar -xvf pspdev-ubuntu-latest-x86_64.tar.gz -C /

# Add to PATH
echo 'export PSPDEV=/usr/local/pspdev' >> ~/.bashrc
echo 'export PATH=$PATH:$PSPDEV/bin' >> ~/.bashrc

# Reload shell
source ~/.bashrc

# Verify installation
psp-config --pspdev-path
# Expected output: /usr/local/pspdev

psp-gcc --version
# Should show: psp-gcc (GCC) ...
```

**If you see version numbers, installation succeeded!** ✅

#### Step 3: Access Windows Files from WSL

Your Windows drives are mounted at `/mnt/`:

```bash
# Navigate to your Windows user folder
cd /mnt/c/Users/YourName/

# List Windows files
ls

# Example: Clone repo to Windows Desktop
cd /mnt/c/Users/YourName/Desktop
git clone https://github.com/Fizzolas/psp-arpg-engine.git
cd psp-arpg-engine
```

**Why this matters:** You can edit files in Windows (VS Code, Notepad++) and compile in WSL!

---

### Option 2: Docker (Advanced)

**Use if you:**
- Already have Docker Desktop
- Want isolated build environment
- Need reproducible builds

#### Setup

1. Install [Docker Desktop for Windows](https://www.docker.com/products/docker-desktop/)
2. Enable WSL 2 backend in Docker settings
3. Open PowerShell or Command Prompt:

```powershell
# Pull PSPSDK image
docker pull pspdev/pspdev

# Navigate to your project
cd C:\Users\YourName\psp-arpg-engine

# Build using Docker
docker run --rm -v ${PWD}:/build pspdev/pspdev make
```

**Output:** `EBOOT.PBP` in current directory

---

### Option 3: MinPSPW (Native Windows - Not Recommended)

**⚠️ WARNING:** MinPSPW is outdated (last updated 2015) and may have missing libraries.

**Only use if WSL/Docker don't work for you.**

1. Download [MinPSPW 0.11.2](https://sourceforge.net/projects/minpspw/files/)
2. Extract to `C:\pspsdk\`
3. Add to Windows PATH:
   - Search → "Environment Variables"
   - Edit "Path" → New → `C:\pspsdk\bin`
4. Open Command Prompt:
   ```cmd
   psp-gcc --version
   ```

**Known Issues:**
- Missing `psplink` libraries
- Outdated GCC version (4.x instead of 11.x)
- May fail on modern Windows 11

---

## Building the Engine

### Using WSL (Recommended)

```bash
# Clone repo (if not done already)
cd /mnt/c/Users/YourName/Desktop
git clone https://github.com/Fizzolas/psp-arpg-engine.git
cd psp-arpg-engine

# Build
make clean
make

# Verify output
ls -lh EBOOT.PBP
# Should show ~200-300KB file
```

### Using Windows File Explorer + WSL

1. Open File Explorer
2. Navigate to `\\wsl$\Ubuntu\home\YourName\psp-arpg-engine\`
3. Double-click `EBOOT.PBP` to view (or copy to PSP)

**Pro Tip:** Pin this location to Quick Access for easy access!

---

## Deploying to PSP

### Method 1: Direct USB Copy (Easiest)

1. Connect PSP via USB (USB mode)
2. Wait for Windows to detect as drive (e.g., `E:\`)
3. Using File Explorer:
   - Navigate to PSP drive
   - Create folders: `PSP\GAME\psparpg\`
   - Copy `EBOOT.PBP` from WSL location (see above)

**WSL Command Line Method:**

```bash
# Find PSP drive letter (check File Explorer)
PSP_DRIVE="/mnt/e"  # Change 'e' to match your PSP drive

# Create directory structure
mkdir -p "${PSP_DRIVE}/PSP/GAME/psparpg/gamedata"
mkdir -p "${PSP_DRIVE}/PSP/GAME/psparpg/userdata"

# Copy EBOOT
cp EBOOT.PBP "${PSP_DRIVE}/PSP/GAME/psparpg/"

# Verify
ls "${PSP_DRIVE}/PSP/GAME/psparpg/"
```

### Method 2: Network Transfer (WiFi)

**If you have PSP WiFi set up:**

1. Install [FTP Server homebrew](https://github.com/xerpi/ftpvita) on PSP
2. In WSL:
   ```bash
   # Install FTP client
   sudo apt install lftp
   
   # Connect to PSP (replace IP)
   lftp ftp://PSP_IP_ADDRESS
   
   # Upload
   cd /PSP/GAME/psparpg/
   put EBOOT.PBP
   ```

---

## Copy Diablo II Files (Windows → PSP)

### Finding Your Diablo II Installation

**Common locations:**
- `C:\Program Files (x86)\Diablo II\`
- `C:\Program Files\Diablo II\`
- Battle.net client install folder

**WSL Path Conversion:**
```bash
# Windows: C:\Program Files (x86)\Diablo II
# WSL:     /mnt/c/Program Files (x86)/Diablo II
```

### Copy Using Windows Explorer (Easiest)

1. Connect PSP via USB
2. Navigate to PSP drive (e.g., `E:\`)
3. Open: `E:\PSP\GAME\psparpg\gamedata\`
4. Open Diablo II folder in another window
5. Copy these 6 files:
   - `d2data.mpq`
   - `d2char.mpq`
   - `d2sfx.mpq`
   - `d2music.mpq`
   - `d2video.mpq`
   - `d2exp.mpq`

### Copy Using WSL Command Line

```bash
# Set paths
D2_PATH="/mnt/c/Program Files (x86)/Diablo II"
PSP_DRIVE="/mnt/e"
PSP_GAMEDATA="${PSP_DRIVE}/PSP/GAME/psparpg/gamedata"

# Create directory
mkdir -p "${PSP_GAMEDATA}"

# Copy all MPQ files
cp "${D2_PATH}/d2data.mpq" "${PSP_GAMEDATA}/"
cp "${D2_PATH}/d2char.mpq" "${PSP_GAMEDATA}/"
cp "${D2_PATH}/d2sfx.mpq" "${PSP_GAMEDATA}/"
cp "${D2_PATH}/d2music.mpq" "${PSP_GAMEDATA}/"
cp "${D2_PATH}/d2video.mpq" "${PSP_GAMEDATA}/"
cp "${D2_PATH}/d2exp.mpq" "${PSP_GAMEDATA}/"

# Verify
ls -lh "${PSP_GAMEDATA}"
# Should show 6 .mpq files totaling ~700MB
```

---

## Development Workflow

### Recommended Setup

**Editor:** VS Code on Windows  
**Compiler:** WSL Ubuntu  
**File Location:** Windows filesystem (accessible from both)

#### Install VS Code Extensions

1. [Remote - WSL](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl)
2. [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

#### Open Project in VS Code

**From WSL:**
```bash
cd psp-arpg-engine
code .
```

**From Windows:**
- File → Open Folder → `\\wsl$\Ubuntu\home\YourName\psp-arpg-engine`

#### Build from VS Code Terminal

1. Terminal → New Terminal
2. Select "Ubuntu (WSL)"
3. Run:
   ```bash
   make
   ```

---

## Troubleshooting

### "psp-config: command not found" (AFTER installation)

**Cause:** PATH not set in current shell session

**Fix:**
```bash
# Reload .bashrc
source ~/.bashrc

# OR restart WSL
exit
# Then reopen Ubuntu from Start Menu
```

### "Cannot find -lpspgu" or similar linker errors

**Cause:** PSPSDK libraries not in expected location

**Fix:**
```bash
# Verify library location
ls /usr/local/pspdev/psp/sdk/lib/ | grep libpspgu
# Should show: libpspgu.a

# If missing, reinstall PSPSDK
sudo rm -rf /usr/local/pspdev
# Then repeat installation steps
```

### "tar: Removing leading `/` from member names"

**This is NORMAL.** It's a safety warning from tar, not an error. Installation succeeded.

### WSL network issues downloading PSPSDK

**Try alternative mirror:**
```bash
wget https://github.com/pspdev/pspdev/releases/download/v20251201/pspdev-ubuntu-latest-x86_64.tar.gz
```

### "make: command not found" in WSL

**Install build tools:**
```bash
sudo apt update
sudo apt install build-essential git
```

### PSP drive not showing in Windows

**Solutions:**
1. Disconnect/reconnect USB cable
2. On PSP: Settings → USB Connection
3. Try different USB port (USB 2.0, not 3.0)
4. Restart PSP

### Files copy slowly to PSP

**Normal.** PSP uses USB 2.0 (max ~10MB/s). Copying 700MB of Diablo II files takes ~2-3 minutes.

**Progress bar stuck?** Wait 30 seconds before canceling.

### "Access denied" copying to PSP

**Cause:** PSP memory stick write-protected

**Fix:** Check physical write-protect switch on Memory Stick Pro Duo card.

---

## Performance Tips

### Speed Up WSL Builds

**Clone to WSL filesystem (not `/mnt/c/`):**

```bash
# SLOW (Windows filesystem)
cd /mnt/c/Users/YourName/Desktop/psp-arpg-engine
make  # ~15 seconds

# FAST (WSL filesystem)
cd ~/psp-arpg-engine
make  # ~3 seconds
```

**Why?** `/mnt/c` has file system translation overhead.

**Access from Windows:** `\\wsl$\Ubuntu\home\YourName\psp-arpg-engine`

### Parallel Compilation

```bash
# Use multiple CPU cores
make -j$(nproc)
# Compiles ~3x faster on quad-core systems
```

---

## Comparison: Build Methods

| Method | Setup Time | Build Speed | Updates | Recommended |
|--------|-----------|-------------|---------|-------------|
| **WSL** | 10 min | Fast | Auto | ✅ Yes |
| Docker | 15 min | Medium | Auto | ⚠️ Advanced users |
| MinPSPW | 5 min | Slow | Manual | ❌ No (outdated) |

---

## Next Steps

Once your environment is set up:

1. ✅ Build the engine: `make`
2. ✅ Copy EBOOT.PBP to PSP
3. ✅ Copy Diablo II MPQ files
4. ✅ Test on PSP (Main Menu → Data Check)
5. 📖 Read [QUICKSTART.md](QUICKSTART.md) for usage guide
6. 🔧 Start modding! Check [README.md](README.md) for architecture

---

## Getting Help

**Before asking:**
- ✅ Run `psp-gcc --version` and `psp-config --version`
- ✅ Check `engine.log` on PSP at `ms0:/PSP/GAME/psparpg/userdata/`
- ✅ Try `make clean && make`

**Where to ask:**
- [GitHub Issues](https://github.com/Fizzolas/psp-arpg-engine/issues)
- [PSP Homebrew Discord](https://discord.gg/bePrj9W)

**Include in bug reports:**
```bash
# System info
uname -a
psp-gcc --version
make --version

# Build output
make 2>&1 | tee build.log
# Attach build.log
```

---

**Happy coding! 🎮🔧**
