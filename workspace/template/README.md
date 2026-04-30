# **Harbour Masters C Mod Template**

A streamlined template for creating C-based mods for games utilizing the libultraship engine (e.g., Super Mario 64 PC ports).

This template utilizes a Unity Build (amalgamation) pipeline. It allows you to write clean, modular C code organized across multiple directories, and automatically compiles them down into a single, portable mod.c file. This single-file output is perfectly formatted for dynamic compilation and loading via TCC (Tiny C Compiler) or for easy distribution.

## **🌟 Features**

* **Automated Amalgamation:** Uses a custom Python script hooked into CMake to safely merge all your .c and .h files, preventing redefinition errors.  
* **Cross-Platform Exports:** Includes HM_API macros to handle the exact ABI export rules so the engine's dynamic linker can always find your ModInit function.  
* **Event Hooking:** Includes a working boilerplate for tapping into the engine's event system (e.g., GameFrameUpdate, RenderGamePost).

## **📂 Directory Structure**

```
├── CMakeLists.txt        # The build configuration  
├── include/  
│   └── mod.h              # Core macros (MOD_INIT, MOD_EXIT, HM_API)  
├── src/  
│   └── demo.c             # Your actual mod logic and event listeners  
└── output/  
    ├── dist/             # The final c files goes here after building
    ├── build.gen         # The list of how to build the mod (auto-generated)
    └── manifest.json      # Metadata for the mod loader
```

## **🚀 Getting Started**

### **Prerequisites**

* **CMake** (3.10 or higher)  
* **Python 3** (used for the amalgamation step)  
* The libultraship source headers available in your parent directory structure.

### **Building the Mod**

We use an out-of-source build to keep the working directory clean. The CMake script will automatically grab all files in the src/ directory and generate the single mod.c in the output/ folder.

1. Open your terminal in the project root.  
2. Create a build directory and configure the project:  
   ```Bash  
   mkdir build  
   cd build  
   cmake ..
   ```

3. Run the build process:  
   ```Bash
   cmake --build .
   ```

4. Your fully amalgamated mod will be available at output/mod.c, ready to be packaged alongside manifest.json.

## **🛠️ Writing Your Mod**

### **The Entry and Exit Points**

Every mod requires an entry point so the engine knows how to initialize it. Use the provided macros from mod.h:

```C
#include "mod.h"

MOD_INIT() {  
    // Called when the mod is dynamically loaded.  
    // Register your engine listeners here.  
}

MOD_EXIT() {  
    // Called when the mod is unloaded or the game closes.  
    // Unregister your listeners and free memory here.  
}
```

### **Hooking into Engine Events**

The template includes a demo.c file showing how to hook into the engine's game loop.

* **GameFrameUpdate**: Ideal for gameplay logic (e.g., modifying gMarioState).  
* **RenderGamePost**: Ideal for drawing custom UI (e.g., using print_text_centered).

Make sure to store your ListenerIDs globally so you can properly unregister them in MOD_EXIT().

### **⚠️ Important Note on Unity Builds (Amalgamation)**

Because all of your .c files are ultimately merged into a single mod.c file, everything shares the same global scope.

* **Use static:** If you write a helper function that should only be used internally, **always** prefix it with static. This ensures it won't accidentally collide with functions of the same name in the game engine or other mods once loaded into memory.