# Little Alchemy CE

The UI also uses Oxygen, vendored under `src/oxygen` as documented by that project. The current snapshot is upstream commit `497a9069ade9e44a577fd2323f6f33d8fc9036c6`. Oxygen provides the on-screen mouse, hover detection, selected inventory row, and rounded shapes, while GraphX handles the freeform workspace, alphabet rail, text, and AppVar-backed element sprites.

## Build

1. Install the latest CE Toolchain and CE Libraries. Oxygen is already included in `src/oxygen`.
2. Open a CEdev shell and change to this directory.
3. Run `make gfx` to create the generated sprite source and ten AppVars.
4. Run `make`.

The calculator program is written to `bin/ALCHEMY.8xp`. Install it together with every `src/gfx/ALCHM00.8xv` through `ALCHM09.8xv` file.

## Controls

- Arrow keys: move the Oxygen mouse.
- Hold Enter or 2nd: pick up the item under the pointer; release to drop it.
- Drag a drawer element into empty canvas space to place it.
- Drag one canvas element over another to combine them.
- Drag the scrollbar at the right edge of the drawer to browse discovered elements.
- Click an A-Z rail letter: jump the drawer to discovered elements in that section.
- Recycle button: clear all items from the workspace.
- Settings button: change item names, control hints, clean confirmation, and pointer speed.
- In Settings, use Up/Down and Enter/2nd. Press Mode to toggle pointer control; in pointer mode, move with the arrows and click with Enter/2nd. Use Left/Right to change pointer speed in keyboard mode.
- Plus/Minus: move the selected slot backward or forward ten discovered elements.
- Del twice: erase progress and return to the four starting elements.
- Clear: save and exit.

Progress is saved automatically in the archived `ALCHSAVE` AppVar. A new game starts with water, fire, earth, and air; only discovered elements are available for new combinations.

The project also uses generated sprite assets and AppVar packs for the game content, which are produced during the build workflow.
