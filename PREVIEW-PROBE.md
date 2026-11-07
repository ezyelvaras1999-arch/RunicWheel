# Runic Wheel LE v0.26 — inventory preview capture probe

This experimental build captures the current game backbuffer once after an item is selected in the Inventory menu. It does not change the item catalogue, co-save, controls, or equip actions.

## In-game procedure

1. Install this build as a separate MO2 mod and disable the other Runic Wheel DLL copies.
2. Load a disposable save and open Inventory.
3. Highlight one weapon or piece of armor and wait about two seconds.
4. Close Skyrim and find `RunicWheelLE-preview.bmp` in the Windows temporary folder (usually `%TEMP%`).
5. Send the BMP and `RunicWheelLE-diagnostic.log` from the same folder.

The BMP is a full-screen diagnostic image, not yet an isolated item thumbnail. The next step depends on locating the inventory model region and checking whether the captured frame has usable pixels. Magic is intentionally excluded because the Magic menu has no corresponding 3D item preview.

`CaptureInventoryPreview=0` disables the probe. It captures once per game session and only from the Inventory menu.
