# Little Alchemy CE
Little Alchemy CE is a TI-84 Plus CE game that recreates the classic item-combination gameplay using Oxygen for UI input and GraphX for rendering. The game's progress is stored in the archived `ALCHSAVE` AppVar, and new runs begin with the four classic starter elements: water, fire, earth, and air.

## Build

The UI also uses Oxygen, vendored under `src/oxygen` as documented by that project. The current snapshot is upstream commit `497a9069ade9e44a577fd2323f6f33d8fc9036c6`. Oxygen provides the on-screen mouse, hover detection, selected inventory row, and rounded shapes, while GraphX handles the freeform workspace, alphabet rail, text, and AppVar-backed element sprites.

1. Install the latest CE Toolchain and CE Libraries. Oxygen is already included in `src/oxygen`.
2. Open a CEdev shell and change to this directory.
3. Run `make gfx` to create the generated sprite source and ten AppVars.
4. Run `make`.

The calculator program is written to `bin/ALCHEMY.8xp`. Install it together with every `src/gfx/ALCHM00.8xv` through `ALCHM09.8xv` file.

## Controls

| Action | Input |
| --- | --- |
| Move the Oxygen mouse | Arrow keys |
| Pick up the item under the pointer | Hold Enter or 2nd |
| Drop the picked-up item | Release Enter or 2nd |
| Place a drawer element into empty canvas space | Drag a drawer element into empty canvas space |
| Combine two canvas elements | Drag one canvas element over another |
| Browse discovered elements | Drag the scrollbar at the right edge of the drawer |
| Jump to discovered elements in a letter section | Click an A-Z rail letter |
| Clear all items from the workspace | Recycle button |
| Change item names, control hints, clean confirmation, and pointer speed | Settings button |
| Move through Settings | Up/Down |
| Confirm a Settings option | Enter or 2nd |
| Toggle pointer control | Press Mode |
| Move the pointer in pointer mode | Arrow keys |
| Click in pointer mode | Enter or 2nd |
| Change pointer speed in keyboard mode | Left/Right |
| Move the selected slot backward or forward ten discovered elements | Plus/Minus |
| Erase progress and return to the four starting elements | Del twice |
| Save and exit | Clear |

See [docs/controls.md](docs/controls.md) for the full control reference.

Progress is saved automatically in the archived `ALCHSAVE` AppVar. A new game starts with water, fire, earth, and air; only discovered elements are available for new combinations.

The project also uses generated sprite assets and AppVar packs for the game content, which are produced during the build workflow.
