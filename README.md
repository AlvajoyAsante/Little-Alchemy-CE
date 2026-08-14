![Little Alchemy CE Icon](docs/title_logo.png)
# Little Alchemy CE
Little Alchemy CE is a TI-84 Plus CE game that recreates the classic item-combination gameplay using Oxygen for UI input and GraphX for rendering.

Play the original game online: [Little Alchemy](https://littlealchemy.com/)

## Build

1. Install the latest CE Toolchain and CE Libraries. Oxygen is already included in `src/oxygen`.
2. Open a CEdev shell and change to this directory.
3. Run `make gfx` to create the generated sprite source and ten AppVars.
4. Run `make`.

The calculator program is written to `bin/ALCHEMY.8xp`. Install it together with every `src/gfx/ALCHM00.8xv` through `ALCHM09.8xv` file.

## Controls

| Action | Input |
| --- | --- |
| Move the Oxygen mouse | ``[Up]`` / ``[Down]`` / ``[Left]`` / ``[Right]`` |
| Pick up the item under the pointer | Hold ``[Enter]`` or ``[2nd]`` |
| Drop the picked-up item | Release ``[Enter]`` or ``[2nd]`` |
| Place a drawer element into empty canvas space | Drag a drawer element into empty canvas space |
| Combine two canvas elements | Drag one canvas element over another |
| Browse discovered elements | Drag the scrollbar at the right edge of the drawer |
| Jump to discovered elements in a letter section | Click an A-Z rail letter |
| Clear all items from the workspace | ``[Recycle]`` |
| Change item names, control hints, clean confirmation, and pointer speed | ``[Settings]`` |
| Move through Settings | ``[Up]`` / ``[Down]`` |
| Confirm a Settings option | ``[Enter]`` or ``[2nd]`` |
| Toggle pointer control | Press ``[Mode]`` |
| Move the pointer in pointer mode | ``[Up]`` / ``[Down]`` / ``[Left]`` / ``[Right]`` |
| Click in pointer mode | ``[Enter]`` or ``[2nd]`` |
| Change pointer speed in keyboard mode | ``[Left]`` / ``[Right]`` |
| Move the selected slot backward or forward ten discovered elements | ``[Plus]`` / ``[Minus]`` |
| Erase progress and return to the four starting elements | ``[Del]`` twice |
| Save and exit | ``[Clear]`` |

See [docs/controls.md](docs/controls.md) for the full control reference.

Progress is saved automatically in the archived `ALCHSAVE` AppVar. A new game starts with water, fire, earth, and air; only discovered elements are available for new combinations.

The project also uses generated sprite assets and AppVar packs for the game content, which are produced during the build workflow.



## Screenshot

|  |  |
| --- | --- |
| ![Little Alchemy CE Screenshot](docs/screenshot.png) | ![Little Alchemy CE Screenshot](docs/screenshot.png) |