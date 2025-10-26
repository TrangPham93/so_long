# so_long

So_long project's purpose is to learn how to create a simple 2D game, including 1 player, 1 exit, at least 1 collectible items.

## Features

- Player character: A cow that moves around the map.

- Objective: Collect all items (milk bottles) before the cow can exit.

- Movement controls:
  - W / ↑ => Move Up
  - S / ↓ => Move Down
  - A / ← => Move Left
  - D / → => Move Right

- Map boundaries:
  - The player cannot move through walls.
  - The map is completely surrounded by walls to prevent leaving the play area.
-  Move counter: Each move you make is printed to the standard output, so you can track your progress.
-  Winning condition: Once all items are collected, moving to the exit displays a winning message.
<img width="800" height="316" alt="image" src="https://github.com/user-attachments/assets/35600da2-8cf3-4958-b481-4982a08612eb" />

---
## Usage

### Requirement: 
-  Linux OS
-  Graphical library: MiniLibX. If it's not installed, MiniLibX will be downloaded automatically when run `make`

---

### Installment:
#### 1. Clone the Repository
   ```bash
   git clone https://github.com/TrangPham93/so_long.git so_long
   cd so_long
   ```
#### 2. Compile the Project

```bash 
make
```
#### 3. Run
A folder of testing maps is included.
```bash 
./so_long maps/map_name
```


