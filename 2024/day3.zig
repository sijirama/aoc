const std = @import("std");
const print = std.debug.print;
const path = "./input/fakeday3.txt";

pub fn main() !void {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    const input = try std.fs.cwd().readFileAlloc(allocator, path, 20024);
    defer allocator.free(input);

    var position: u32 = 0;
    //var final_multiplication: i32 = 0;

    while (position < input.len) {
        const current_char = input[position];
        //std.debug.print("{}", .{current_char});

        switch (current_char) {
            'm' => {
                if (position + 3 < input.len and
                    input[position + 1] == 'u' and
                    input[position + 2] == 'l' and
                    input[position + 3] == '(')
                {
                    var start_pos = position + 4; // Skip "mul("
                    var end_pos = start_pos;

                    while (end_pos < input.len and input[end_pos] != ',') {
                        end_pos += 1;
                    }

                    const first_value = input[start_pos..end_pos];

                    start_pos = end_pos + 1; // Skip comma
                    end_pos = start_pos;

                    while (end_pos < input.len and input[end_pos] != ')') {
                        end_pos += 1;
                    }
                    const second_value = input[start_pos..end_pos];

                    print("{s} * {s}\n", .{ first_value, second_value });
                }
                position += 1; // head to the next bracket
            },
            else => {
                position += 1;
            },
        }
    }
}
