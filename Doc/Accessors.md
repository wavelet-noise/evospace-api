Default syntax
```lua
self:add_component(KineticOutputAccessor.new(), "KineticOutput")
```

With string and new syntax
```lua
self:add_component(_G["KineticInputAccessor"].new(), "KineticInputAccessor")
```

Legacy from 0.18.3
```lua
local accessor = crafter:create_accessor(Class.find("HeatInputAccessor")) 
```