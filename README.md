# 🏰 Dungeon Escape — A Tale Told in Stone

![Unreal Engine](https://img.shields.io/badge/Engine-Unreal%20Engine%205.6-blue)
![Status](https://img.shields.io/badge/Status-In%20Development-yellow)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)
![Architecture](https://img.shields.io/badge/Architecture-C%2B%2B%20%2F%20Blueprint%20Hybrid-orange)

---

## 📌 Overview

**Dungeon Escape — A Tale Told in Stone** is a first-person, medieval dark-fantasy puzzle game built solo in **Unreal Engine 5.6**. Players explore a dungeon, collect items, place them into locks, and progress through a series of escalating puzzle rooms toward a final escape sequence and credits roll.

This project was built as a **portfolio piece** to demonstrate professional-quality architecture, systems design, and technical breadth as a solo developer — for scholarship and mentorship review.

> This repository intentionally excludes large third-party Marketplace asset packs. See [Installation.md](Installation.md) for what's required and how to set them up.

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
- Actor Component–based architecture: `EscapeQuestManagerComponent`, `EscapeQuestAudioComponent`, `EscapeQuestUIComponent`
- `WBP_EscapeQuest` widget surfaces objective progress to the player
- Final quest completion is triggered by the last door's movement, chained through a delay into the credits sequence

### End-Game & Credits Sequence
- `WB_Credits` widget with an auto-close timer and keypress-skip support
- `BPC_PlayerMovementStop` component freezes player control during the sequence
- `WBP_EndGame` uses a widget-switcher architecture for clean state transitions
- `UDungeonGameInstance` (C++) manages `LoadMainMenu()` / `LoadGameLevel()` flow

### Main Menu
- Built on top of a Marketplace menu framework, with custom Blueprint wiring for game state transitions

### Character
- Hierarchy: `BP_Player → BP_FirstPersonCharacter → DungeonCharacter (C++)`
- First-person camera attachment handled at the C++ constructor level for stability

---

## 🗂️ Project Structure

```
Dungeon/
├── Content/
│   ├── MyStuff/              ← All original gameplay code & content (start here)
│   │   ├── Blueprints/
    
│   │   ├── Quests/
│   │   ├── MainMenu/
│   │   └── Maps/
│   ├── ContainerInventory/   ← Third-party inventory framework (see Installation.md)
│   ├── InteractionSystem/    ← Third-party interaction framework base (extended by MyStuff)
│   ├── DayNightCycle/        ← Third-party day/night system
│   ├── menuGameSystemPro/    ← Third-party menu framework
│   └── ...
├── Source/
│   └── Dungeon/              ← C++ gameplay classes (DungeonCharacter, DungeonDoor, etc.)
├── Config/
└── Dungeon.uproject
```

> 📁 **`Content/MyStuff/`** contains all of the game-specific design, blueprints, and content built for this project. Other top-level `Content/` folders are third-party frameworks that were extended or integrated — see below.

---

## 📦 External Dependencies

To keep this repository lean and to respect Marketplace licensing terms, several large asset packs used by the project are **not included** in this repo. See [Installation.md](Installation.md) for the full list and setup instructions, including:

- **Medieval Dungeon** (environment art pack)
- Marketplace menu, inventory, and audio frameworks

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
- **Explicit separation** between third-party framework content and original design work, to make authorship clear or reviewers

---

## 🚧 Roadmap

- [ ] Final main menu wiring pass (GameInstance hookup verification)
- [ ] Additional puzzle rooms
- [ ] Full playtest pass and polish
- [ ] Accompanying devlog / portfolio site

---

## 📸 Screenshots & Demo

*Coming soon.*

---

## 👤 Author

**Prashant Tamang**
Solo Developer — Unreal Engine 5

---

## 📄 License

This project is shared for portfolio and educational review purposes. Third-party assets referenced in [Installation.md](Installation.md) remain the property of their respective creators and are licensed separately.
