local vec = Vector2(1.0, 2.0)
local vec2 = Vector2(5.0, 5.0)

function initialize()
    print("Original Vector:")
    print(vec.x, vec.y)
    vec = vec:Multiply(vec2)
    print("New Vector:")
    print(vec.x, vec.y)
end

function update()

end