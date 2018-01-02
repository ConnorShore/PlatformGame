local input = nil

function initalize()
    input = InputManager()
end

function update()
    if(input:KeyDown(KEY_SPACE)) then
        print("Random before: ", input.random)
        input.random = input.random + 10
        print("Random after: ", input.random)
    end
end