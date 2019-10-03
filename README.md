# DungeonCrawler
## Terminal Based Dungeon Crawling Game (for Linux/Unix environments)

Type `make` to compile
Type `./cc3k` to run

## Symbols:
@: You! The player character
<: The stairs leading to the next floor. There are 5 floors until you reach the end.

|Enemy | Display | HP | Atk | Def | Item Dropped | Special Abilities |
| --- | --- | --- | --- | --- | --- | --- |
| Grid Bug | X | 50 | 20 | 10 | Random Potion | Cannot move or attack diagonally |
| Goblin | g | 75 | 30 | 20 | Gold Pile | Can drink potions |
| Merchant | M | 100 | 75 | 5 | Gold Pile | Ignores player by default |
| Orc | O | 120 | 30 | 30 | Gold Pile | None |
| Dragon | D | 150 | 50 | 10 | None | Guards a Dragon Hoard |


## Commands:

Directions: no, ne, ea, se, so, sw, we, nw

Move: (direction)

Attack: a (direction)

Grab/Consume (Potion or Gold Pile): u (direction)

Quit: q

## Cheats:

Invincibility: `stopdeath`
Stop enemies from moving: `stopwander`

## Classes:

### Knight:
The Knight (100 HP, 50 Atk, 50 Def), an all-around versatile fighter who lacks in special abilities and
instead relies solely on her stats to defeat enemies.

### Wizard:
The Wizard (60 HP, 25 Atk, 0 Def), who is weak but has a powerful long-range attack, able to hit
the first unit in a straight line in front of him.

### Samurai:
The Samurai (80 HP, 50 Atk, 15 Def), whose grace allows him to go unnoticed by the denizens of the
dungeon until he attacks an enemy. All enemies behave similarly to the merchant: once the first enemy
of a particular type is attacked, all enemies of that type become hostile.