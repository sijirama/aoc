const std = @import("std");
const print = std.debug.print;
const path = "./input/day3.txt";

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    const allocator = gpa.allocator();
    defer {
        _ = gpa.deinit();
    }

    const input = try std.fs.cwd().readFileAlloc(allocator, path, 20000);
    defer allocator.free(input);

    var position: u32 = 0;
    var final_multiplication: i32 = 0;
    var mul_enabled = true;

    while (position < input.len) {
        const current_char = input[position];

        switch (current_char) {
            'd' => {
                // Check for do() or don't()
                if (position + 4 < input.len and
                    std.mem.startsWith(u8, input[position..], "do()"))
                {
                    mul_enabled = true;
                } else if (position + 7 < input.len and
                    std.mem.startsWith(u8, input[position..], "don't()"))
                {
                    mul_enabled = false;
                }
                position += 1;
            },
            'm' => {
                if (position + 3 < input.len and
                    input[position + 1] == 'u' and
                    input[position + 2] == 'l' and
                    input[position + 3] == '(')
                {
                    if (!mul_enabled) {
                        position += 1;
                        continue;
                    }

                    var start_pos = position + 4; // Skip "mul("
                    var end_pos = start_pos;

                    // Validate and find first value
                    while (end_pos < input.len and input[end_pos] != ',') {
                        if (!std.ascii.isDigit(input[end_pos]) and input[end_pos] != '-') break;
                        end_pos += 1;
                    }

                    if (end_pos > start_pos and input[end_pos] == ',') {
                        const first_value = input[start_pos..end_pos];

                        start_pos = end_pos + 1; // Skip comma
                        end_pos = start_pos;

                        // Validate and find second value
                        while (end_pos < input.len and input[end_pos] != ')') {
                            if (!std.ascii.isDigit(input[end_pos]) and input[end_pos] != '-') break;
                            end_pos += 1;
                        }

                        // Ensure proper termination and valid second value
                        if (end_pos > start_pos and input[end_pos] == ')') {
                            const second_value = input[start_pos..end_pos];
                            const mutiplication = try std.fmt.parseInt(i32, first_value, 10) * try std.fmt.parseInt(i32, second_value, 10);
                            final_multiplication += mutiplication;
                            position = end_pos;
                            continue;
                        }
                    }
                }
                position += 1;
            },
            else => {
                position += 1;
            },
        }
    }

    std.debug.print("Final value is: {d}\n", .{final_multiplication});
}
