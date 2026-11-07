# Runic Wheel LE — M3 isolated inventory preview probe

Opening the wheel with M3 while hovering an item in Inventory queues a render of that item's 3D model. It does not save the visible game screenshot. M1 adds/confirms the hovered item in the selected wheel slot; M2 removes the selected slot entry.

Each successful capture is saved as a new numbered BMP. Its FormID and full path are recorded in the diagnostic log. The default folder is `C:\Users\HP\Pictures\Skyrim\RunicWheelLE`; change `PreviewCaptureDirectory` under `[Debug]` in `RunicWheelLE.ini` to use another absolute Windows path. If the requested folder cannot be created, the probe falls back to `%TEMP%\RunicWheelLE\Previews`. Existing captures are never overwritten. The game frame is restored before Present.

## In-game procedure

1. Install this build as a separate MO2 mod and disable other Runic Wheel DLL copies.
2. Load a disposable save, open Inventory, hover a weapon or armor, then press M3 to open the wheel.
3. Wait about two seconds. Select a wheel slot and press M1 to add the item; M2 removes the selected slot entry.
4. Close Skyrim and inspect the newest BMPs in `C:\Users\HP\Pictures\Skyrim\RunicWheelLE`. Send the diagnostic log and one or more BMPs.

The renderer only attempts a capture when one Inventory3DManager row uniquely matches the hovered FormID. It temporarily reduces that manager's render list to the matching item and restores the list after rendering. Supported backbuffers must be X8R8G8B8/A8R8G8B8 and non-multisampled. This probe still does not attach image files to wheel sectors; that comes after the isolated model render is confirmed.
