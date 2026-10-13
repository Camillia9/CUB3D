*This project has been created as part of the 42 curriculum by camansou, makoon.*

# cub3D

A first-person 3D maze renderer written in C with the MiniLibX, inspired by *Wolfenstein 3D* (1992). The 3D view is drawn with **raycasting**: one ray per screen column, no 3D engine involved.

## Description

The goal of cub3D is to build a "realistic" 3D view of the inside of a maze from a simple 2D map, using only basic math, a pixel buffer and the MiniLibX graphics library. The program reads a scene file (`.cub`), validates it, then lets you walk through the maze in real time.

### Features

- 3D rendering with the **DDA raycasting** algorithm
- **Four wall textures** depending on which side the wall faces (North, South, East, West)
- Separate **floor and ceiling colors**
- **Smooth movement**: several keys can be held at the same time
- **Wall collision**: the player slides along walls instead of going through them
- Full **`.cub` file validation** with explicit error messages
- Clean exit with `ESC` or the window's close button, with no memory leaks

### Controls

| Key | Action |
|---|---|
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| `←` / `→` | Look left / right |
| `ESC` or close button | Quit |

### How it works

**1. Parsing and validation** (`parsing/`)

The `.cub` file is read line by line, then checked:

- the six elements (`NO`, `SO`, `WE`, `EA`, `F`, `C`) are present, in any order, and valid
- RGB values are in the `[0, 255]` range
- the map only contains `0`, `1`, spaces, and exactly one player (`N`, `S`, `E` or `W`)
- the map is **closed**: a flood fill starts from the player and fails as soon as it reaches a space or the edge of the map

Any problem stops the program with `Error` followed by an explicit message.

**2. Raycasting** (`raycasting/`)

For each column of the screen:

1. A ray is cast from the player, between the direction vector and the camera plane.
2. The **DDA** (Digital Differential Analysis) algorithm walks the grid one cell at a time, always stepping to the closest next grid line on X or Y, until it hits a wall.
3. The **perpendicular distance** to the wall gives the height of the wall slice. Using the perpendicular distance instead of the real one avoids the "fisheye" effect.
4. The hit side (X or Y) and the ray direction select the texture. The exact hit point selects the texture column to draw.
5. The column is drawn into an image buffer: ceiling color, textured wall, floor color.

When all columns are drawn, the image is pushed to the window in one call, which keeps the display smooth.

**3. Game loop** (`mlx/`)

Key presses and releases only update a table of pressed keys. The movement itself happens in the MiniLibX loop hook, every frame. This is what allows smooth, simultaneous movement (for example moving forward while turning).

### Team

| | Part |
|---|---|
| **camansou** | Raycasting, rendering, textures, movement |
| **makoon** | `.cub` file parsing and map validation |

## Instructions

### Requirements

- Linux with X11
- `cc` and `make`
- X11 development libraries (on Debian/Ubuntu: `sudo apt install libx11-dev libxext-dev`)

The MiniLibX sources are included in the repository and compiled by the Makefile.

### Build and run

```bash
git clone https://github.com/Camillia9/CUB3D.git
cd CUB3D
make
./cub3d maps/maptest.cub
```

### Scene file format

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

- `NO`, `SO`, `WE`, `EA`: paths to the wall textures (`.xpm`)
- `F`, `C`: floor and ceiling colors in RGB
- The map is always last: `1` wall, `0` empty space, `N` / `S` / `E` / `W` player start and orientation

The `maps/` folder contains a valid map (`maptest.cub`) and several invalid ones (`break_*.cub`) to test error handling, for example:

```bash
./cub3d maps/break_mapnotclose.cub
Error
Map not closed: some empty spaces can escape
```

### Makefile rules

| Rule | Effect |
|---|---|
| `make` | Builds the MiniLibX, `libft` and `cub3d` |
| `make clean` | Removes object files |
| `make fclean` | Removes object files and the binary |
| `make re` | Full rebuild |

## Resources

- [Lode's Computer Graphics Tutorial: Raycasting](https://lodev.org/cgtutor/raycasting.html), the main reference for the DDA algorithm and textured walls
- [MiniLibX documentation (harm-smits)](https://harm-smits.github.io/42docs/libs/minilibx)
- [Wolfenstein 3D, playable in the browser](http://users.atw.hu/wolf3d/)

### AI usage

AI (Claude) was used as a learning aid, not to write the project's code:

- **Understanding concepts**: asking for explanations of the math behind raycasting, such as the direction vector and camera plane, how DDA steps through the grid, and why the perpendicular distance removes the fisheye effect.
- **Understanding the MiniLibX**: clarifying how images, pixel buffers and event hooks work.
- **README**: help with structuring this README and with the English wording.

All code was written, tested and debugged by the team.
