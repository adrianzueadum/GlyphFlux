# GlyphFlux: A 2D Puzzle-Energy Strategy Game

## Overview
GlyphFlux is a unique 2D puzzle-strategy game built in C++ using the SFML library. Players inscribe glyphs on a grid to channel energy flows, stabilizing unstable nodes before they overload the system. The game combines pattern-based puzzle-solving with dynamic energy management, offering a fresh experience distinct from traditional puzzle or strategy games.

This open-source project is designed for developers, gamers, and educators interested in C++ game development, energy flow mechanics, and strategic puzzles. By sponsoring GlyphFlux via GitHub Sponsors, you support new features, level designs, and educational resources for the community.

## Features
- **Glyph-Based Energy Channeling**: Place glyphs to direct energy flows and stabilize nodes.
- **Dynamic Nodes**: Manage unstable nodes that generate energy surges.
- **Minimalist Visuals**: Clean 2D graphics with glowing glyph effects.
- **Cross-Platform**: Runs on Windows, macOS, and Linux via SFML.
- **Modular Codebase**: Well-structured C++ code for easy extension and learning.

## Getting Started

### Prerequisites
- **C++ Compiler**: GCC, Clang, or MSVC with C++17 support.
- **SFML Library**: Version 2.5.1 or later (install via [SFML's official site](https://www.sfml-dev.org/) or package manager).
- **CMake**: Version 3.10 or later for building.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/glyphflux.git
   cd glyphflux
   ```
2. Create a build directory:
   ```
   mkdir build && cd build
   ```
3. Configure with CMake:
   ```
   cmake .
   ```
4. Build the project:
   ```
   cmake --build .
   ```
5. Run the game:
   ```
   ./GlyphFlux
   ```

## Gameplay
- **Objective**: Stabilize all unstable nodes by channeling energy flows with glyphs before the system overloads.
- **Controls**:
  - **Arrow Keys**: Move the cursor on the grid.
  - **1/2/3**: Place horizontal, vertical, or cross glyphs.
  - **Space**: Trigger an energy surge to stabilize nodes.
  - **R**: Reset the level.
  - **Esc**: Pause or exit.
- **Mechanics**: Glyphs direct energy flows across the grid. Place glyphs to connect energy sources to unstable nodes. Trigger surges to stabilize nodes, but manage flow to avoid overloads.

## Project Structure
- `src/main.cpp`: Game entry point and main loop.
- `src/Entity.hpp`: Base class for game entities (glyphs, nodes, sources).
- `src/Game.hpp`: Core game logic, energy flow simulation, and rendering.
- `assets/`: Placeholder for textures/fonts (add your own or use SFML defaults).

## Contributing
Contributions are welcome! Fork the repo, create a feature branch, and submit a pull request. For major changes, open an issue to discuss your ideas.

## Sponsorship
Support GlyphFlux’s development through [GitHub Sponsors](https://github.com/sponsors/yourusername)! Your contributions fund:
- New glyph types and level designs.
- Enhanced energy flow mechanics and visuals.
- Tutorials for C++ and game development.
- Optimizations for broader platform support.

## License
Licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgments
- Built with [SFML](https://www.sfml-dev.org/) for graphics and input.
- Inspired by energy-based puzzles and strategic flow games.
- Thanks to the open-source community for feedback and inspiration.

---

**Sponsor GlyphFlux to channel the power of innovative puzzle design!**