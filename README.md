![regs_hlsdk_bg](https://user-images.githubusercontent.com/51358194/207906388-6c4a5609-b7a8-4a35-bdb8-905460f16ebe.png)

**Only for Windows.**

# reGS

reGS is a result of reverse engineering of `hw.dll` (build 8684) using DWARF debug info embedded into linux version of hardware engine, `hw.so`.

Status: WIP.

## reGS HL SDK

In short, it's HL Updated SDK with some parts of changeable hardware engine code. Hooks were used.

Used libraries:
- SPTLib
- MinHook

### Building

#### Visual Studio 2019
1. Install [Visual Studio 2019](https://my.visualstudio.com/Downloads?q=Visual%20Studio%20Community%202019). In the Visual Studio Installer, select Desktop Development for C++.
2. Open Visual Studio.
3. On the starting screen, click "Clone or check out code".
4. Enter `https://github.com/ScriptedSnark/reGS_hlsdk.git` and press the Clone button. Wait for the process to finish.
5. Choose Debug or Release. You can build the workspace using Build→Build All. If you want to build only client or something else, right click on wanted project (for example, `hl_cdll`) and select Build.