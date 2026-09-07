# Falling Engine

A small and performant data-oriented C++ game engine with:
1. Centralized Asset Database
2. Sparse-Set Entity Component System
3. A (mostly) Stateless OpenGL Rendering Backend

I've been working on Falling Engine for many weeks now, really trying
to understand the design principles behind game engines and high-performance
realtime software overall instead of just one-shotting this with an LLM.

And also it's just really cool to be able to say that I'm making a game engine!

Now that I've finished the renderer, completing the big 3 systems required to
put a mesh on the screen, I'm probably gonna split my attention across a
couple other projects I've been wanting to make.

For now, you can run the demo shown in the clip above with these steps:

## How to Run the Demo

These instructions target Debian/Ubuntu Linux. I haven't tried it on a Windows machine yet (sorry!).

You will need:

- Git, CMake 3.16 or newer, Ninja, and a C++20-compatible compiler
- [vcpkg](https://github.com/microsoft/vcpkg) (for library dependencies)
- A machine with OpenGL 3.3 support
- Linux dev. packages used by GLFW and OpenGL

Install the system dependencies:

```bash
sudo apt update
sudo apt install build-essential cmake ninja-build git curl zip unzip tar \
  pkg-config libgl1-mesa-dev libglu1-mesa-dev libxinerama-dev \
  libxcursor-dev xorg-dev
```

Install vcpkg if you do not already have it, then set `VCPKG_ROOT` to its
absolute path:

```bash
git clone https://github.com/microsoft/vcpkg.git
./vcpkg/bootstrap-vcpkg.sh
export VCPKG_ROOT=/absolute/path/to/vcpkg
```

Clone, configure, and build the game target:

```bash
git clone https://github.com/ng-daniel/falling-dngine.git falling-engine
cd falling-engine
cmake --preset vcpkg
cmake --build build --target game --parallel
```

*To build all executables (such as the asset browser/inspector and some
engine tests), just run this instead of targetting game specifically:*

```bash
cmake --build build
```

The configure step reads `vcpkg.json` and installs the C++ dependencies
(OpenGL, GLFW, GLAD, GLM, and Dear ImGui) automatically. Then, from the
repository root, run:

```bash
./build/game/game
```

Run the executable from the repository root because the demo loads assets from
`./game/assets`. Use <kbd>W</kbd>/<kbd>A</kbd>/<kbd>S</kbd>/<kbd>D</kbd> to move,
<kbd>Q</kbd>/<kbd>E</kbd> to move vertically, and the arrow keys to look around.
Close the window to exit.


## Roadmap

Goal
- make a minimum viable engine with solid fundamentals and expandability
- make some example projects
- develop a small singleplayer FPS game with this engine

Completed
- asset manager + serialization (BASICALLY DONE!!!)
- scenes, ECS, components (ALSO DONE!!!)
- renderer, (debug) camera (DONE!!!)

MVP Remaining Items
- input system
- scripting and custom game logic
- physics

QOL Features (in the order of how much I want to do them...)
- visual post-processing
- particle system
- audio system
-
-
- UI system

Really Cool Stuff (probably not anytime soon)
- vulkan graphics backend
- scriptable runtime
- networking/multiplayer
