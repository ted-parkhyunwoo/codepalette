function printArray(array)
    local sz = #array
    io.write("{ ")
    if sz >= 1 then
        io.write(tostring(array[1]))
    end
    for i=2, sz do
        io.write(", ")
        io.write(tostring(array[i]))
    end
    print(" }")
end

function printTypeArray(array)
    local sz = #array
    io.write("{ ")
    if sz >= 1 then
        io.write("(type:")
        io.write(type(array[1]))
        io.write(", val:")
        io.write(tostring(array[1]))
        io.write(")")
    end
    for i=2, sz do
        io.write(", ")
        io.write("(type:")
        io.write(type(array[i]))
        io.write(" val:")
        io.write(tostring(array[i]))
        io.write(")")
    end
    print(" }")
end

function printMap(map)
    print("\n{")
    for k, v in pairs(map) do
        io.write("\t")
        io.write(tostring(k))
        io.write(": ")
        print(tostring(v))
    end
    print("}")

end

local print_sample = { 1, 2, 3 }
printArray(print_sample)

local a = 'a'
local b = 3
local c = "hello world"
my_array2 = { a, b, c }
table.insert(my_array2, true)               -- add element
table.insert(my_array2, nil)                -- pass
table.insert(my_array2, 1, 3.141592)        -- insert elem to index

my_array2[5] = false                        -- edit

table.insert(my_array2, "isajjfos")
table.remove(my_array2, 6)                  -- remove index

printArray(my_array2)
printTypeArray(my_array2)


local my_map = { a = 1, b = 2 }
my_map.c = 3;   -- add
my_map["d"] = 4;
my_map.e = 999; 

my_map.e = 5;   -- edit
my_map.e = nil  -- delete


printMap(my_map)


