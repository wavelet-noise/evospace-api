### LuaBlock logic customization

You can use 

```lua
local function_table = table()

-- self is Prototype object
function_table.proto_construction = function(self)
    local inventory = SingleSlotInventory.new()
    self:add_component(inventory, "inventory")
    local sides = {Vec3i.front, Vec3i.left, Vec3i.right. Vec3i.up, Vec3i.down, Vec3i.back}
    for _, side in pairs(sides) do
        local acc = ElecticOutputAccessor.new()
        acc.side, acc.pos = side, Vec3i.zero
        acc:bind(inventory)
        self:add_accessor(acc)
    end
end
print("Custom proto_construction function is registered")

--  self is Prototype object clone, cache is per instance Table to use in tick
function_table.proto_clone = function(self, cache)
    local inventory = SingleSlotInventory.cast(self:get_component("inventory"))
    cache.inventory = inventory

    local slot = ItemData.new()
    slot.item = Item.get("Electricity")
    slot.count = 100

    cache.slot = slot
end
print("Custom proto_clone function is registered")

--  self is Prototype object clone, cache is per instance Table to use in tick
function_table.tick = function(self, cache)
    cache.inventory.add_item(cache.slot)
end
print("Custom tick function is registered")
```
