local input = InputManager()

function initalize()
    print("Init2 called")
end

function update()
    if(input:KeyDown(KEY_5)) then
        print("F1 IS DOWN")
    end
end