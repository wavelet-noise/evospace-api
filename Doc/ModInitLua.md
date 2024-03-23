### Lua mod init

```json
local EnergyDecayMod = {}

function EnergyDecayMod.init()
end

function EnergyDecayMod.pre_init()
end

function EnergyDecayMod.post_init()
    for index, proto in pairs(db:objects()) do
        local block = StaticBlock.cast(proto)
        if block ~= nil and block.logic ~= nil then
            if block.logic:is_child_of(AbstractCrafter.get_class()) then
                print('Energy decay in '..block:get_name())

                local oldF = block.block_init

                block.block_init = function(self)
                    oldF(self)
                    AbstractCrafter.cast(self).load_independent = true
                end
            end
        end
    end
end

db:mod(EnergyDecayMod)
```