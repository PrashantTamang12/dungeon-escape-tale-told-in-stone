<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0f172a,100:7dd3fc&height=180&section=header&text=Dungeon%20Escape&fontSize=44&fontColor=ffffff&animation=twinkling&fontAlignY=40&desc=A%20Tale%20Told%20in%20Stone&descAlignY=62&descSize=20" width="100%"/>

</div>

# 🛠️ Installation Guide — Dungeon Escape: A Tale Told in Stone

This project depends on a small number of third-party Marketplace/Fab asset packs that are **intentionally excluded** from this repository — both to keep the repo size reasonable and to respect the licensing terms of paid Marketplace content (redistribution of raw asset files is typically not permitted).

Follow the steps below to get a fully working local build.

---

## ✅ Requirements

- **Unreal Engine 5.6**
- **Visual Studio 2022** (with "Game Development with C++" workload)
- **Git** with **Git LFS** installed (`git lfs install`)

---

## 📦 Required External Asset Pack

Only **one** external asset pack needs to be installed separately for this project to run correctly:

| Asset Pack | Purpose | Install Path |
|---|---|---|
| **Medieval Dungeon** | Core environment art (walls, props, architecture) used throughout the dungeon levels | `Content/MedievalDungeon/` |

### Steps
1. Download **Medieval Dungeon** via the Epic Games Launcher or Fab. Link: https://fab.com/s/494a7622e1be
2. In the Unreal Editor, use **Add to Project** (or manually copy the extracted folder) so contents land at `Content/MedievalDungeon/`
3. Restart the Unreal Editor

---

## 📁 Other Asset Packs (Not Required)

During development, several other Marketplace/sample packs were used for prototyping, reference, and testing:

- Weapons Pack
- Interface & Item Sounds
- Level Prototyping Pack
- FPS Menu Music Vol. 1
- Free Sounds Pack
- Variant_Horror / Variant_Shooter (Unreal sample content)

**These do not need to be downloaded.** Any assets from these packs that actually ended up in the final game (specific sound cues, meshes, etc.) were copied directly into `Content/MyStuff/` during development, so they're already included in this repository. The original pack folders themselves were excluded from version control simply to avoid re-uploading large libraries of unused source files.

If you don't plan to edit those specific migrated assets at the source level, you can safely ignore this section entirely.

---

## 📁 Other Content Included in This Repo

A few additional folders are versioned in this repo alongside `MyStuff/`:

- `Content/menuGameSystemPro/` — main menu / pause / save-load UI framework, **actively used** by the shipping game
- `Content/ContainerInventory/` — inventory framework explored during development; **not used** in the final game, kept for reference only
- `Content/DayNightCycle/` — day/night cycle system explored during development; **not used** in the final game, kept for reference only

These will pull down automatically with `git clone` (via Git LFS) — no manual setup required. The unused folders don't affect gameplay and can be safely ignored or deleted from a local checkout if you want a leaner working copy.

---

## 📥 Cloning This Repository

This repo uses **Git LFS** for binary assets (`.uasset`, `.umap`, textures, audio). Make sure LFS is installed *before* cloning:

```powershell
git lfs install
git clone https://github.com/PrashantTamang12/dungeon-escape-tale-told-in-stone.git
```

If you already cloned without LFS installed, run:
```powershell
git lfs pull
```

---

## ❗ Common Errors & Fixes

| Error / Symptom | Cause | Solution |
|---|---|---|
| `Failed to load Outer` | Medieval Dungeon pack is missing | Install **Medieval Dungeon** (see above) |
| `Skipped package (BP_Candle)` / similar | Missing Medieval Dungeon blueprint references | Install **Medieval Dungeon** |
| `Skipped package (SM_Floor)` | Missing Medieval Dungeon mesh | Install **Medieval Dungeon** |
| Character falls through the floor | Floor mesh/collision missing (Medieval Dungeon not installed) | Install **Medieval Dungeon** |
| Blueprint compile errors on open | Broken references from the missing pack | Install **Medieval Dungeon**, then restart the editor |
| Missing-reference warnings tied to `Weapons/`, `LevelPrototyping/`, etc. | These folders were prototyping-only and intentionally excluded | Safe to ignore — see "Other Asset Packs" section above |

---

## 🧹 Troubleshooting: Cache Reset

If the project still misbehaves after installing all required packs, clear Unreal's local cache and let it rebuild:

```powershell
Remove-Item -Recurse -Force DerivedDataCache
Remove-Item -Recurse -Force Intermediate
Remove-Item -Recurse -Force Saved
```

Then reopen the project in Unreal Editor. The first load after this will take longer as shaders and derived data rebuild.

---

## 🧭 Quick Start Summary

1. Install Unreal Engine 5.6 + Visual Studio 2022
2. `git lfs install` → clone this repo
3. Install **Medieval Dungeon** into `Content/MedievalDungeon/` (the only required external pack)
4. Open `Dungeon.uproject`
5. If prompted to rebuild modules, allow it
6. If anything looks broken, run the cache reset steps above and reopen
