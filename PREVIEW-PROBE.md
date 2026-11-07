# Runic Wheel LE v0.26 — M1 isolated item render probe

This probe no longer copies the visible game frame as the item image. With the wheel open over Inventory, M1 queues the highlighted FormID, waits until the LE `Inventory3DManager` has exactly one matching loaded model, temporarily paints the backbuffer magenta, asks the game's `Inventory3DManager::Render` to draw the model, copies the candidate frame, and restores the saved game frame before Present. This stage checks isolated rendering only; it does not yet attach a persistent thumbnail to wheel sectors.

M2 keeps its current editor behavior: remove the selected entry from the active sector. Persistent thumbnail removal will be wired when per-sector image storage is added.

## In-game procedure

1. Install this build as a separate MO2 mod and disable other Runic Wheel DLL copies.
2. Load a disposable save, open Inventory, highlight a weapon or armor, then open the wheel while Inventory stays open.
3. Hover the item and press M1. M1 adds the item (or requests a fresh preview for a duplicate) and queues the isolated render. Wait about two seconds.
4. Close Skyrim and find `RunicWheelLE-preview.bmp` and `RunicWheelLE-diagnostic.log` in `%TEMP%`.
5. Send both files. The BMP should show the model against a magenta field; the live game frame should remain unchanged.

The render path is intentionally limited to one matching loaded model and non-multisampled X8R8G8B8/A8R8G8B8 backbuffers. The capture is opt-in through `[Debug] CaptureInventoryPreview=1`. M2 removes a wheel entry but does not yet manage a thumbnail file because this probe has no persistent per-sector image cache.
