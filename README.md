# Werewolves: Age of Night

A first-person game built in Unreal Engine 5.8 around a two-phase loop, where daylight is
preparation and night is the consequence.

**Day.** You walk your land in first person and place traps — some that kill, some that only make a
path expensive enough that the pack takes a different one. You know where they will come from,
because tonight's attack is announced before it happens. Hours and money are a single pool that also
buys your own kit, so every trap placed is a bullet not bought.

**Night.** You defend what you prepared, in first person, against exactly the waves that were
promised.

The central idea is owed to *Sang-Froid: Tales of Werewolves* (Artifice Studio, 2013).

## Status

Early. The repository currently holds the stock Unreal first person template, and the game's own
systems are being built one milestone at a time. Nothing here plays as the game yet.

## Requirements

- Unreal Engine **5.8.1**
- Windows, with Visual Studio 2022 and its C++ desktop toolchain
- **Git LFS** — required, not optional

## Getting the source

Binary assets live in Git LFS. Cloning without it leaves you with pointer files and an editor that
cannot load the content:

```sh
git lfs install
git clone https://github.com/vetnem1lk/Age-of-Night.git
```

## Building

```powershell
# Editor build
& "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\Build.bat" `
    age_of_nightEditor Win64 Development -Project="<path>\age_of_night.uproject" -WaitMutex

# Regenerate project files after adding or removing source files
& "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\GenerateProjectFiles.bat" `
    -Project="<path>\age_of_night.uproject" -Game
```

## Layout

```
Source/age_of_night/
  age_of_night{Character,GameMode,PlayerController,CameraManager}   base first person layer
  Variant_Horror/     horror variant (template)
  Variant_Shooter/    shooter variant (template): weapons, AI, UI
Content/              assets, tracked in Git LFS
Config/               project configuration
```

Every C++ gameplay class is `abstract`: the classes actually loaded at runtime are Blueprints in
`Content/`, so a new C++ class needs a Blueprint subclass before a level can use it.

The shooter variant's AI runs on StateTree rather than Behavior Trees, and input goes through
Enhanced Input throughout.

## Working with binary assets

`.uasset` and `.umap` neither merge nor diff, which drives two rules:

- they are marked `lockable` — run `git lfs lock <file>` before editing one,
- a commit carries at most one binary asset, so every binary change stays individually reviewable
  and revertable.

The second rule is enforced by a hook, installed per clone:

```sh
cp .githooks/pre-commit .git/hooks/pre-commit && chmod +x .git/hooks/pre-commit
```

## Licensing

The project's own code and design are © the author, all rights reserved. Template material under
`Content/` belongs to Epic Games and is used under the Unreal Engine EULA.
