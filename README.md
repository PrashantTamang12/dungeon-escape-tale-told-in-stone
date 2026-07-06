# 🏰 Dungeon Escape — A Tale Told in Stone

![Unreal Engine](https://img.shields.io/badge/Engine-Unreal%20Engine%205.6-blue)
![Status](https://img.shields.io/badge/Status-In%20Development-yellow)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)
![Architecture](https://img.shields.io/badge/Architecture-C%2B%2B%20%2F%20Blueprint%20Hybrid-orange)

---

## 📌 Overview

**Dungeon Escape — A Tale Told in Stone** is a first-person, medieval dark-fantasy puzzle game built solo in **Unreal Engine 5.6**. Players explore a dungeon, collect items, place them into locks, and progress through a series of escalating puzzle rooms toward a final escape sequence and credits roll.

This project was built as a **portfolio piece** to demonstrate professional-quality architecture, systems design, and technical breadth as a solo developer — for scholarship and mentorship review.

> This repository has one external dependency (Medieval Dungeon). See [Installation.md](Installation.md) for setup — most other third-party content is already included.

---

## 🧩 Core Systems

This project uses a **hybrid C++ / Blueprint architecture**: C++ handles core gameplay logic, interfaces, and systems, while Blueprint child classes handle visuals, animation, and audio. This split keeps performance-critical logic in native code while allowing rapid iteration on presentation.

### Interaction System
- `IInteractableInterface` — a shared interface for anything the player can interact with
- Timer-driven sphere-sweep detection (`DoInteractionSweep()`) rather than per-tick raycasting, for better performance and cleaner profiling
- Actor tagging (`"Collectable Item"`, `"Lock"`, `"Door"`) to drive interaction behavior
- `BlueprintImplementableEvent` hooks (`OnInteractableFound`, `OnInteractableLost`) so Blueprint visuals/UI can react to C++-driven detection

### Inventory
- `TArray<FString> ItemList` tracks collected items
- Items are validated against locks to gate progression

### Door System
- `ADungeonDoor` — a C++ base class handling hinge-rotation door mechanics
- Blueprint variants (`BP_CellDoor_Rotate`, `BP_ChainDoor`) extend the base for specific visual/animation behavior
- Integrated into the interaction system via the `"Door"` actor tag

### Quest / Objective System
- Actor Component–based architecture: `EscapeQuestManagerComponent`, `EscapeQuestAudioComponent`, `EscapeQuestUIComponent`, plus earlier iterations `QuestManagerComponent`, `QuestAudioComponent`, `QuestUIComponent`
- `WBP_EscapeQuest` widget surfaces objective progress to the player
- Final quest completion is triggered by the last door's movement, chained through a delay into the credits sequence

### End-Game & Credits Sequence
- `WB_Credits` widget with an auto-close timer and keypress-skip support
- `BPC_PlayerMovementStop` component freezes player control during the sequence
- `UDungeonGameInstance` (C++) manages `LoadMainMenu()` / `LoadGameLevel()` flow

### Main Menu
- Built on `WBP_SimpleMenu`, an original menu widget, alongside select Marketplace framework pieces (settings widget, loading screen), tied together with custom Blueprint wiring for game state transitions

### Character
- Hierarchy: `BP_Player → BP_FirstPersonCharacter → DungeonCharacter (C++)`
- First-person camera attachment handled at the C++ constructor level for stability

---

## 🗂️ Project Structure

```
Dungeon/
├── Content/
│   ├── MyStuff/                    ← All original gameplay code & content (start here)
│   │   ├── Blueprints/
│   │   ├── BP-derivedClass/
│   │   ├── Crosshair/
│   │   ├── MainMenu/
│   │   ├── Maps/
│   │   ├── Quests/
│   │   ├── Sounds/
│   │   ├── UI_PAUSEMENU/
│   │   └── USED_SOUNDS/
│   ├── menuGameSystemPro/          ← Third-party main menu / pause / save-load UI framework (actively used)
│   ├── InteractionSystem/          ← Third-party interaction framework base, extended by MyStuff
│   ├── ContainerInventory/         ← Explored during development, not used in final game
│   ├── DayNightCycle/              ← Explored during development, not used in final game
│   ├── Characters/                 ← Shared character assets (Mannequins, etc.)
│   ├── FirstPerson/                ← First-person template assets
│   ├── Input/                      ← Enhanced Input actions & mapping contexts
│   ├── Developers/                 ← Personal sandbox/testing content (not part of shipping game)
│   ├── MedievalDungeon/            ← ⚠️ External asset pack — not included, see Installation.md
│   ├── Weapons/                    ← ⚠️ Not included; used assets migrated into MyStuff, see Installation.md
│   ├── Interface_And_Item_Sounds/  ← ⚠️ Not included; used assets migrated into MyStuff, see Installation.md
│   ├── LevelPrototyping/           ← ⚠️ Not included; used assets migrated into MyStuff, see Installation.md
│   ├── FPS_Menu_Music_Vol_1/       ← ⚠️ Not included; used assets migrated into MyStuff, see Installation.md
│   ├── Free_Sounds_Pack/           ← ⚠️ Not included; used assets migrated into MyStuff, see Installation.md
│   ├── Variant_Horror/             ← ⚠️ Unreal sample content, not included, see Installation.md
│   ├── Variant_Shooter/            ← ⚠️ Unreal sample content, not included, see Installation.md
│   └── ...
├── Source/
│   └── Dungeon/                    ← C++ gameplay classes (DungeonCharacter, DungeonDoor, etc.)
├── Config/
└── Dungeon.uproject
```

> 📁 **`Content/MyStuff/`** contains all of the game-specific design, blueprints, and content built for this project. Folders marked ⚠️ above are external asset packs excluded from this repo — see [Installation.md](Installation.md). `ContainerInventory/` and `DayNightCycle/` are included but unused legacy exploration, kept for reference only.

---

## 📦 External Dependencies

This repository only has **one true external dependency**: the **Medieval Dungeon** environment art pack, which the dungeon levels are built on. See [Installation.md](Installation.md) for setup.

Several other Marketplace/sample packs (Weapons, Interface & Item Sounds, Level Prototyping, menu music, free sounds, Unreal's Variant_Horror/Variant_Shooter samples) were used during early prototyping. Any assets from those packs that actually made it into the final game were copied directly into `Content/MyStuff/`, so nothing further needs to be downloaded for those — the original pack folders were simply excluded from version control to keep the repo lean.

---

## 🛠️ Tech Stack

- **Engine:** Unreal Engine 5.6
- **Languages:** C++, Blueprint Visual Scripting
- **IDE:** Visual Studio 2022
- **Version Control:** Git + Git LFS

---

## 🎯 Design Principles Behind This Build

- **Timer-driven detection over Tick** for interaction systems — chosen deliberately for performance and reviewability
- **Interface-driven interaction** (`IInteractableInterface`) so any actor type can become interactable without duplicating logic
- **Component-based quest architecture** to keep quest logic decoupled from level-specific actors
- **Explicit separation** between third-party framework content and original design work, to make authorship clear for reviewers

---

## 🚧 Roadmap

- [ ] Final main menu wiring pass (GameInstance hookup verification)
- [ ] Additional puzzle rooms
- [ ] Full playtest pass and polish
- [ ] Accompanying devlog / portfolio site

---

## 📸 Screenshots

*From an earlier development build — updated screenshots of the final version coming soon.*

<!-- Example once images are added to Media/Screenshots/:
![Dungeon corridor](Media/Screenshots/corridor.png)
![Puzzle room](Media/Screenshots/puzzle-room.png)
-->

---

## 🎮 Gameplay Demo

*A full gameplay video will be published on [YouTube](#) after the current build is finalized. This section will be updated with the link once available.*

---

## 👤 Author

**Prashant Tamang**
Solo Developer — Unreal Engine 5

---

## 📄 License

This project is shared for portfolio and educational review purposes. Third-party assets referenced in [Installation.md](Installation.md) remain the property of their respective creators and are licensed separately.
