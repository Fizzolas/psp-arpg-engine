# Windows Setup Guide - PSP ARPG Engine

**Complete guide for Windows 10/11 users to set up PSP development**

---

## 🪟 Three Ways to Build on Windows

### **Option 1: WSL (Recommended)** ⭐
- **Officially supported** by PSPSDK team
- Always up-to-date with latest toolchain
- Easy setup, full Linux compatibility
- **Best for: Everyone, especially beginners**

### **Option 2: MinPSPW (Native Windows)**
- No WSL required, fully native
- **Outdated** (last updated 2015)
- May have missing dependencies
- **Best for: Advanced users who can't use WSL**

### **Option 3: Docker**
- Cross-platform container
- Always up-to-date
- Requires Docker Desktop
- **Best for: Users familiar with Docker**

---

## ✅ Option 1: WSL Setup (RECOMMENDED)

### Prerequisites
- Windows 10 version 2004+ or Windows 11
- Administrator access
- ~2GB free disk space

### Step 1: Install WSL

**Open PowerShell as Administrator:**
1. Press `Win + X`
2. Select "Windows PowerShell (Admin)" or "Terminal (Admin)"
3. Run:

```powershell
wsl --install
```

4. **Restart your computer** when prompted

### Step 2: Set Up Ubuntu

After reboot, Ubuntu will open automatically:

1. Create a UNIX username (lowercase, no spaces)
2. Create a password (won't show when typing - this is normal)

### Step 3: Update Ubuntu

In the Ubuntu terminal:

```bash
sudo apt-get update
sudo apt-get upgrade -y
```

### Step 4: Install Dependencies

```bash
sudo apt-get install build-essential cmake pkgconf libreadline8 libusb-0.1-4 libgpgme11 libarchive-tools fakeroot wget git -y
```

### Step 5: Download PSPSDK

```bash
cd ~
wget https://github.com/pspdev/pspdev/releases/latest/download/pspdev-ubuntu-latest-x86_64.tar.gz
```

### Step 6: Extract PSPSDK

```bash
sudo tar -xvf pspdev-ubuntu-latest-x86_64.tar.gz -C /
```

(This extracts to `/usr/local/pspdev` - takes ~2 minutes)

### Step 7: Set Environment Variables

```bash
nano ~/.bashrc
```

**Add these lines at the bottom:**

```bash
export PSPDEV=/usr/local/pspdev
export PATH=$PATH:$PSPDEV/bin
```

**Save and exit:**
- Press `Ctrl + O` (save)
- Press `Enter` (confirm)
- Press `Ctrl + X` (exit)

### Step 8: Reload Configuration

```bash
source ~/.bashrc
```

### Step 9: Verify Installation

```bash
psp-config --pspdev-path
```

✅ **Should output:** `/usr/local/pspdev`

---

## 🏗️ Building the PSP ARPG Engine (WSL)

### Clone the Repository

```bash
cd ~
git clone https://github.com/Fizzolas/psp-arpg-engine.git
cd psp-arpg-engine
```

### Build

```bash
make clean
make
```

✅ **Success:** You should see `EBOOT.PBP` created (~500KB)

Verify:
```bash
ls -lh EBOOT.PBP
```

---

## 📁 Accessing Windows Files from WSL

Your Windows drives are mounted at `/mnt/`:

```bash
# C: drive
cd /mnt/c/Users/YourName/

# D: drive
cd /mnt/d/

# List your Windows user folder
ls /mnt/c/Users/
```

### Copy EBOOT to Windows

```bash
# Example: Copy to your Downloads folder
cp EBOOT.PBP /mnt/c/Users/YourName/Downloads/
```

---

## 💾 Deploying to PSP (from Windows)

### Connect PSP via USB

1. On PSP: Settings → USB Connection
2. PSP appears as drive (e.g., `E:\`)

### Create Directory Structure

**Open File Explorer (Win + E):**

Navigate to your PSP drive, then create:

```
E:\PSP\GAME\psparpg\
```

### Copy Files

1. **Engine:**
   - Copy `EBOOT.PBP` to `E:\PSP\GAME\psparpg\`

2. **Game Data Folders** (create these):
   ```
   E:\PSP\GAME\psparpg\gamedata\
   E:\PSP\GAME\psparpg\userdata\
   ```

3. **Your Diablo II Files:**
   - Copy your MPQ files to `E:\PSP\GAME\psparpg\gamedata\`

### Required Diablo II Files

Copy these from your Diablo II installation (usually `C:\Program Files (x86)\Diablo II\`):

```
d2data.mpq   → E:\PSP\GAME\psparpg\gamedata\d2data.mpq
d2char.mpq   → E:\PSP\GAME\psparpg\gamedata\d2char.mpq
d2sfx.mpq    → E:\PSP\GAME\psparpg\gamedata\d2sfx.mpq
d2music.mpq  → E:\PSP\GAME\psparpg\gamedata\d2music.mpq
d2video.mpq  → E:\PSP\GAME\psparpg\gamedata\d2video.mpq
d2exp.mpq    → E:\PSP\GAME\psparpg\gamedata\d2exp.mpq
```

---

## 🔧 Windows-Specific Tips

### Opening Ubuntu Terminal in a Folder

1. Navigate to folder in File Explorer
2. **Shift + Right-click** in empty space
3. Select "Open Linux shell here"

### Editing Files with VS Code (from WSL)

```bash
# Install VS Code in Windows first, then from WSL:
code .
```

VS Code will open with full WSL integration!

### Performance Tips

- Store project files in WSL filesystem (`~/psp-arpg-engine`) not Windows (`/mnt/c/...`)
- **Why:** 10x faster compilation due to filesystem differences

---

## 🪟 Option 2: MinPSPW (Native Windows)

### ⚠️ Warning
- Outdated (2015)
- May have dependency issues
- Not recommended unless you have specific reasons

### Download

1. Go to: [MinPSPW SourceForge](https://sourceforge.net/projects/minpspw/)
2. Download **version 0.10.0** (most reliable)

### Install

1. Run installer
2. Install to `C:\pspsdk` (or your preferred location)
3. Add to PATH:
   - Right-click "This PC" → Properties
   - Advanced System Settings → Environment Variables
   - Edit `Path`, add: `C:\pspsdk\bin`

### Build

Open Command Prompt in project folder:

```cmd
cd C:\path\to\psp-arpg-engine
make
```

### Known Issues

- **Missing DLLs:** Download Visual C++ Redistributable 2013
- **make: command not found:** Add MinGW to PATH
- **Library errors:** Version 0.10.0 is most stable

---

## 🐳 Option 3: Docker (Windows)

### Prerequisites

1. Install [Docker Desktop for Windows](https://www.docker.com/products/docker-desktop/)
2. Enable WSL 2 backend (default on Windows 11)

### Pull Image

```powershell
docker pull pspdev/pspdev
```

### Build Project

```powershell
cd C:\path\to\psp-arpg-engine
docker run --rm -v ${PWD}:/build pspdev/pspdev make
```

Output: `EBOOT.PBP` in current directory

---

## 🐛 Troubleshooting (Windows-Specific)

### WSL Issues

#### "WSL 2 requires an update to its kernel component"

**Fix:**
```powershell
wsl --update
```

#### "The WSL optional component is not enabled"

**Fix:**
1. Open PowerShell as Admin
2. Run:
```powershell
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```
3. Restart computer

#### Ubuntu terminal won't open

**Fix:**
```powershell
wsl --set-default Ubuntu
wsl ~
```

#### Can't find files copied from Windows

**Remember:** Windows paths in WSL are `/mnt/c/` not `C:\`

```bash
# Wrong
cd C:\Users\YourName

# Correct
cd /mnt/c/Users/YourName
```

### MinPSPW Issues

#### "cannot find -lpspgu"

**Cause:** Incomplete installation

**Fix:** Reinstall MinPSPW 0.10.0 or switch to WSL

#### "psp-gcc: command not found"

**Fix:** Add to PATH:
- `C:\pspsdk\bin`
- `C:\pspsdk\psp\bin`

### Docker Issues

#### "Hardware assisted virtualization and data execution protection must be enabled"

**Fix:** Enable VT-x/AMD-V in BIOS

#### "error during connect"

**Fix:** Start Docker Desktop application

---

## 📚 Additional Resources

- [Official PSPSDK Docs](https://pspdev.github.io/)
- [WSL Documentation](https://learn.microsoft.com/en-us/windows/wsl/)
- [MinPSPW Project](https://sourceforge.net/projects/minpspw/)
- [Docker Desktop](https://www.docker.com/products/docker-desktop/)

---

## ✅ Quick Verification Checklist

After setup, verify these work:

```bash
# Check PSPSDK path
psp-config --pspdev-path

# Check compiler
psp-gcc --version

# Check make
make --version

# Clone and build test
cd ~
git clone https://github.com/Fizzolas/psp-arpg-engine.git
cd psp-arpg-engine
make clean && make
ls -lh EBOOT.PBP
```

All commands should complete without errors!

---

**Need more help?** Check [QUICKSTART.md](QUICKSTART.md) for general usage or [README.md](README.md) for full documentation.

**Windows 11 users:** WSL comes pre-configured and updated - you have the smoothest experience!
