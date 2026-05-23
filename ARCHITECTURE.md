# Architecture

## The big picture

```
main.cpp
  └── GameStateManager
        └── PlayState  (active)
              ├── Tilemap
              ├── Player
              └── vector<Enemy>
```

`main.cpp` owns the window and runs the game loop. It knows nothing about players,
enemies, or tiles. Everything is delegated to the state manager.

---

## Game loop

Every frame, `main.cpp` does exactly three things:

```
1. poll events  →  gsm.handleEvent(event)
2. update       →  gsm.update(dt)
3. draw         →  gsm.draw(window)
```

`dt` is delta time — the number of seconds since the last frame. All movement
is multiplied by `dt` so the game runs at the same speed regardless of frame rate.

---

## GameStateManager — the stack

The manager holds a stack of states. Only the top state is active.

```
[ PlayState  ]  ← active, gets all calls
[ MenuState  ]  ← sleeping underneath (future)
```

**push(state)** — suspends the current state (onExit), makes the new one active (onEnter).  
**pop()** — destroys the current state (onExit), resumes the one below (onEnter).

This is how pause menus and dialogue work: push a new state on top, pop it when done.
The state below resumes exactly where it left off.

States are owned by the manager via `unique_ptr` — when a state is popped, it is
automatically destroyed. No manual memory management.

---

## GameState — the interface

Every state implements four methods:

```cpp
onEnter()              // called when state becomes active
onExit()               // called when state loses focus or is destroyed
handleEvent(event)     // called once per event (key press, mouse click, window close)
update(dt)             // called every frame — game logic
draw(target)           // called every frame — rendering
```

`handleEvent` vs `update`:
- Use `handleEvent` for one-shot triggers (press E to interact, press Escape to pause)
- Use `update` for continuous input (WASD movement — is the key held down right now?)

---

## PlayState — gameplay

Owns everything that exists during gameplay:

```
PlayState
  ├── Tilemap      — the room floor and walls
  ├── Player       — the character you control
  └── vector<Enemy> — all enemies in the room
```

Each frame:
1. Player moves based on keyboard input
2. Player position is clamped to window bounds
3. Each enemy chases the player
4. Collision is checked between player and each enemy
5. Draw order: tilemap first, then enemies, then player (last drawn = on top)

---

## Entities

### Player
Owns: `sf::Sprite` (visual), `health`, `damageCooldown`  
Knows how to: move on WASD input, take damage with a 1s cooldown, draw itself, clamp to bounds  
Does NOT know: where enemies are, what room it's in, anything about the window

### Enemy
Owns: `sf::RectangleShape` (visual), `speed`  
Knows how to: chase a target position, draw itself  
Does NOT know: who it's chasing — it just receives a `sf::Vector2f targetPos` each frame

### Tilemap
Owns: `sf::VertexArray` (all tile geometry), tile size  
Knows how to: build tile geometry from a 2D grid, draw the entire map in one GPU call  
Does NOT know: what the map means — it just renders what it's given

---

## Rendering

All rendering goes through `sf::RenderTarget` — an abstract base class that represents
"anything you can draw onto." The window is one kind of render target. An off-screen
texture is another. Passing `RenderTarget&` instead of `RenderWindow&` means draw
methods work everywhere without changing.

Draw order matters — whatever is drawn last appears on top:
```
1. Tilemap   (floor and walls — background)
2. Enemies   (on top of floor)
3. Player    (on top of everything)
```

The tilemap uses a single `sf::VertexArray` draw call for all tiles. Each tile is two
triangles (6 vertices). The GPU receives all geometry at once and renders in parallel.
This is dramatically faster than drawing individual shapes per tile.

---

## Ownership rules

- `GameStateManager` owns all states
- `PlayState` owns Player, Enemies, and Tilemap
- Each entity owns its own visual representation and internal state
- No entity reaches up to its owner — dependencies only flow downward

---

## What's coming next

| Ticket | What | Why |
|--------|------|-----|
| Wall collision | Player blocked by wall tiles | Tilemap renders but has no collision yet |
| Room system | Room struct, load maps from Tiled JSON | Replace hard-coded map data |
| Doors | Room transitions | Push a transition state, load next room |
| EventBus | Publish/subscribe messaging | Decouple systems (collision → health, pickup → inventory) |
| Enemy variants | Patrol, ranged AI | More interesting gameplay |
| Dialogue system | DialogueState, text box | NPC interaction |
| Artifact system | Pickup and inventory | Core game loop |
| Time-travel | State recording + rewind | Signature mechanic |
| Factions | Relationship tracking | Affects dialogue and enemy behavior |
