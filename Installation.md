# 🏰 Dungeon Project (Unreal Engine 5)

![Unreal Engine](https://img.shields.io/badge/Engine-Unreal%20Engine%205-blue)
![Status](https://img.shields.io/badge/Status-Completed-success)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)


## 📦 Required Asset

* **Asset Name:** Medieval Dungeon
* **Source:** Fab / Epic Games Marketplace
---

## 🛠️ Installation Steps

1. Download the **Medieval Dungeon** asset pack from the Marketplace
2. Install it via:

   * Epic Games Launcher **or**
   * Fab application
3. Place the asset in the following directory:

```
ProjectRoot/Content/MedievalDungeon/
```

4. Verify the folder contains:

   * `Blueprints/`
   * `Meshes/`
   * `Materials/`

5. Restart the Unreal Engine Editor

---

## ❗ Common Errors & Fixes

| Error / Symptom               | Cause                             | Solution                      |
| ----------------------------- | --------------------------------- | ----------------------------- |
| Failed to load Outer          | Missing dependencies              | Install asset pack            |
| Skipped package (BP_Candle)   | Missing blueprint references      | Install asset pack            |
| Skipped package (SM_Floor)    | Missing mesh                      | Install asset pack            |
| Character falls through floor | No collision (missing floor mesh) | Install asset pack            |
| Blueprint compile errors      | Broken asset references           | Install pack & restart editor |

---

## 📂 Project Structure

```
MyProject/
│── Content/
│   ├── MedievalDungeon/    <-- REQUIRED ASSET (Install here)
│   │   ├── Blueprints/
│   │   ├── Materials/
│   │   ├── Meshes/
│   │   └── ...
│   │
│   ├── MyStuff/            <-- Custom project content
│   │   ├── Blueprints/
│   │   ├── Maps/
│   │   └── ...
│
├── Config/
├── Source/
└── ...
```

---

## 🧹 Troubleshooting (Cache Reset)

If the project still fails after installing assets, clear Unreal cache files:

### PowerShell

```powershell
Remove-Item -Recurse -Force DerivedDataCache
Remove-Item -Recurse -Force Intermediate
Remove-Item -Recurse -Force Saved
```

Then restart Unreal Engine.

---
