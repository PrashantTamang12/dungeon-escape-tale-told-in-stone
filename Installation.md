# 🛠️ Installation Guide — Dungeon Escape: A Tale Told in Stone

This project depends on a small number of third-party Marketplace/Fab asset packs that are **intentionally excluded** from this repository — both to keep the repo size reasonable and to respect the licensing terms of paid Marketplace content (redistribution of raw asset files is typically not permitted).

Follow the steps below to get a fully working local build.

---

## ✅ Requirements

- **Unreal Engine 5.6**
- **Visual Studio 2022** (with "Game Development with C++" workload)
- **Git** with **Git LFS** installed (`git lfs install`)

---

## 📦 Required External Asset Packs

The following packs are used by the project but **not included** in this repository. Install each one via the **Epic Games Launcher** or **Fab**, then place its contents at the specified path.

| Asset Pack | Purpose | Install Path |
|---|---|---|
| **Medieval Dungeon** | Core environment art (walls, props, architecture) | `Content/MedievalDungeon/` |
| **Weapons Pack** | First-person weapon meshes/materials (used for early prototyping references) | `Content/Weapons/` |
| **Interface & Item Sounds** | UI and item interaction sound cues | `Content/Interface_And_Item_Sounds/` |
| **Level Prototyping Pack** | Greybox prototyping meshes/materials used during early level blockout | `Content/LevelPrototyping/` |
| **FPS Menu Music Vol. 1** | Background music used on the main menu | `Content/FPS_Menu_Music_Vol_1/` |
| **Free Sounds Pack** | Miscellaneous ambient/SFX audio | `Content/Free_Sounds_Pack/` |
| **Variant_Horror** *(Unreal sample content)* | Referenced during early prototyping | `Content/Variant_Horror/` |
| **Variant_Shooter** *(Unreal sample content)* | Referenced during early prototyping | `Content/Variant_Shooter/` |

> ℹ️ Exact source links depend on where each pack was originally sourced (Fab / Epic Marketplace). Search each pack name on [fab.com](https://www.fab.com) if you don't already own it. `Variant_Horror` and `Variant_Shooter` are Unreal's free sample content packs, available via the Epic Games Launcher's Learn/Samples tab.
>
> ⚠️ These last four packs were used only during early prototyping and are not required for the core gameplay loop to function — you can typically skip them unless the editor throws missing-reference errors tied to those folders.

### Steps
1. Download each pack above via Epic Games Launcher or Fab
2. In the Unreal Editor, use **Add to Project** (or manually copy the extracted folder) so contents land at the exact `Content/` path listed in the table
3. Restart the Unreal Editor after all packs are in place

---

## 📁 Frameworks Already Included in This Repo

Some third-party systems were small enough (or integrated deeply enough into gameplay) to keep versioned directly in this repo — no separate download needed:

- `Content/ContainerInventory/` — inventory framework, extended for item/lock interactions
- `Content/DayNightCycle/` — day/night cycle system
- `Content/menuGameSystemPro/` — main menu / pause / save-load UI framework

These will pull down automatically with `git clone` (via Git LFS) — no manual setup required.

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
| `Failed to load Outer` | A required external asset pack is missing | Install the relevant pack from the table above |
| `Skipped package (BP_Candle)` / similar | Missing MedievalDungeon blueprint references | Install **Medieval Dungeon** pack |
| `Skipped package (SM_Floor)` | Missing MedievalDungeon mesh | Install **Medieval Dungeon** pack |
| Character falls through the floor | Floor mesh/collision missing (MedievalDungeon not installed) | Install **Medieval Dungeon** pack |
| UI sounds don't play | Interface & Item Sounds pack missing | Install **Interface & Item Sounds** pack |
| Blueprint compile errors on open | Broken references from a missing pack | Install the missing pack(s), then restart the editor |

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
3. Install the 4 external asset packs listed above into their exact `Content/` paths
4. Open `Dungeon.uproject`
5. If prompted to rebuild modules, allow it
6. If anything looks broken, run the cache reset steps above and reopen
