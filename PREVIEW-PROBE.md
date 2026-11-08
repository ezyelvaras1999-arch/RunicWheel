# Runic Wheel LE — InventoryMenu callsite diagnostic

M3 toggles the wheel. When it opens while Inventory is already open and the cursor is over an item, it records that FormID. M1 adds the hovered item to the selected wheel slot; M2 removes the selected slot entry. Outside Inventory/Magic, M1 and M2 keep their normal right-hand and left-hand equip actions.

For capture, the probe intercepts the byte-verified call from LE `InventoryMenu::Render` to the base menu render. It saves the frame after Scaleform draws, clears that frame to magenta, then lets the original InventoryMenu continue through its own 3D render. At Present, the probe saves the resulting candidate and restores the original frame before drawing the wheel. It does not manually invoke `Inventory3DManager::Render` from Present or change its model rows.

Each candidate is saved as a new numbered BMP. The FormID and path are recorded in `RunicWheelLE-diagnostic.log`. The default folder is `C:\Users\HP\Pictures\Skyrim\RunicWheelLE`; change `PreviewCaptureDirectory` under `[Debug]` in `RunicWheelLE.ini` to use another absolute path. If that folder cannot be created, the probe falls back to `%TEMP%\RunicWheelLE\Previews`.

## In-game procedure

1. Install this build as a separate MO2 mod and disable other Runic Wheel DLL copies.
2. Load a disposable save and open Inventory.
3. Hover an item and press M3 to open the wheel. Wait about two seconds for the queued preview capture.
4. Select a wheel slot and press M1 to add the item; M2 removes the selected slot entry. Press M3 again to close.
5. Check the numbered BMP and diagnostic log. A valid candidate should show the inventory model over magenta, not the game scene. Send the newest BMP and log.

This diagnostic build does not attach captured images to wheel sectors. Its purpose is to explain why the render bridge previously rejected the callsite. At startup it logs the observed and expected bytes at the candidate InventoryMenu callsite, and, when the candidate begins with a `CALL`, the resolved destination. It remains fail-closed: a mismatch disables only preview capture, and the normal wheel continues to use its existing input path.

After installing the build, confirm the plugin log says `v0.26.0-InventoryMenu-callsite-diagnostic`, open Inventory, and press M3 once. Then send `RunicWheelLE.log` from `Data\SKSE\Plugins` and `RunicWheelLE-diagnostic.log` from `%TEMP%`. Search for `preview callsite diagnostic` in those logs.
