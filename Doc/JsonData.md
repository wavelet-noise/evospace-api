# JSON data

Root folder may contain directories with JSON files.

Load order:
1) [Resources](#resources)
1) [Mixed](#mixed)
1) [Recipes](#recipes)
1) [Researches](#researches)
1) [Quests](#quests)
1) [Chapters](#chapters)
1) [Generators](#generators)
1) [Biomes](#biomes)
1) [BiomeFamilies](#biomefamilies)
1) [GlobalBiomFamily](#globalbiomfamily)

## Resources

## Mixed
#### StaticItem
```json 
{
    "Class": "Item",
    "Name": "CopperPlate",
    "Category": "Parts",
    "Image": "T_CopperPlate",
    "LabelParts": [
        [
            "CopperPlate",
            "parts"
        ]
    ],
    "LogicJson": {
        "Block": "CopperPlate"
    },
    "Materials": [
        "Materials/Copper"
    ],
    "Model": "Models/Plate",
    "MaxCount": 64,
    "Tag": "Misc"
}
```

#### ItemLogic

#### StaticBlock

#### BlockLogic

## Recipes

## Researches

## Quests

## Chapters

## Generators

## Biomes

## BiomeFamilies

## GlobalBiomFamily

```json
{
"name": "my_mod",
"version": "0.19",
"title": "My Mod",
"author": "mr. mod maker",
"evospace_version": "0.19",
"dependencies": ["vanilla >= 0.19"],
"description": "Example mod"
}
```
