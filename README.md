# 🎒 RPG Stalker Backpack & Crafting System

A modern text-based inventory and weapon modification simulator written in **C++**. This project demonstrates how to handle complex data structures, dynamic memory, and safe user input validation.

## 📝 Project Overview
The program simulates a stalker's backpack with a limited capacity of 5 slots. Unlike simple string arrays, this system handles full item profiles with multiple attributes and includes a gameplay loop where players can find randomly generated loot and upgrade their gear.

## 🛠️ C++ Core Concepts Used
* **Custom Structs (`struct`):** Used to bundle multiple attributes (`modyfy` counter, `name`, `power`, and `rarity`) into a single object type.
* **Dynamic Arrays (`std::vector<Item>`):** Manages the inventory dynamically using `.push_back()` and `.erase()` to add or remove complex structures.
* **Advanced `<random>` Library:** Utilizes `std::mt19937` and `std::uniform_int_distribution` for professional, non-deterministic generation of item power levels.
* **Robust Input Validation (`try-catch`):** Features custom integer parsing via `std::stoi` to catch invalid arguments or out-of-range inputs, preventing console crashes.
* **Stream & Buffer Management:** Correctly handles `std::cin.ignore()` and `std::getline()` to allow item names with spaces.

## 🎮 Gameplay Features
1. **Show Items:** Displays all current weapons showing their upgrade levels `[+X]`, damage power, and rarity status.
2. **Scavenge for Loot:** Generates a new weapon with a custom name and a randomized base power from 1 to 10.
3. **Weapon Modification (Crafting):** Upgrades any chosen item, adding `+10` to its power, incrementing its modification level, and changing its status to "модифікована".
4. **Discarding:** Safely throws away items by their index number, automatically shifting the remaining vector elements in memory.
