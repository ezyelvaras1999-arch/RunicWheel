# Runic Wheel LE — InventoryMenu vtable render probe

M3 toggles the wheel. When it opens while Inventory is already open and the cursor is over an item, it records that FormID. M1 adds the hovered item to the selected wheel slot; M2 removes the selected slot entry. Outside Inventory/Magic, M1 and M2 keep their normal right-hand and left-hand equip actions.

For capture, the probe verifies that `InventoryMenu` vtable slot 6 points to the expected LE `Render` routine, then verifies the routine's complete byte signature. It replaces the routine's verified tail jump after `view->Render()` with a bridge. The bridge saves the frame after Scaleform draws, clears it to magenta, and jumps to the original inventory 3D render target. At Present, the probe saves the candidate and restores the original frame before drawing the wheel. It does not call `Inventory3DManager::Render` from Present or change its model rows.

Each candidate is saved as a new numbered BMP. The FormID and path are recorded in `RunicWheelLE-diagnostic.log`. The default folder is `C:\Users\HP\Pictures\Skyrim\RunicWheelLE`; change `PreviewCaptureDirectory` under `[Debug]` in `RunicWheelLE.ini` to use another absolute path. If that folder cannot be created, the probe falls back to `%TEMP%\RunicWheelLE\Previews`.

## In-game procedure

1. Install this build as a separate MO2 mod and disable other Runic Wheel DLL copies.
2. Load a disposable save and open Inventory.
3. Hover an item and press M3 to open the wheel. Wait about two seconds for the queued preview capture.
4. Select a wheel slot and press M1 to add the item; M2 removes the selected slot entry. Press M3 again to close.
5. Check the numbered BMP and diagnostic log. A valid candidate should show the inventory model over magenta, not the game scene. Send the newest BMP and log.

This is still a probe and does not attach captured images to wheel sectors. The render patch remains fail-closed: a vtable, byte-signature, or jump-target mismatch disables only preview capture, while the normal wheel continues to use its existing input path. The log records which check rejected the bridge.

After installing the build, confirm the plugin log says `v0.26.0-InventoryMenu-vtable-render-probe`, open Inventory, hover an item, and press M3 once. Then send `RunicWheelLE.log` from `Data\SKSE\Plugins` and `RunicWheelLE-diagnostic.log` from `%TEMP%`. A successful bridge reports `InventoryMenu vtable[6] verified; Scaleform-to-3D render bridge installed`.
