const std = @import("std");
const path = "./input/day2.txt";
const ArrayList = std.ArrayList;

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();
    const file = try std.fs.cwd().openFile(path, .{});
    defer file.close();
    var buf_reader = std.io.bufferedReader(file.reader());
    var in_stream = buf_reader.reader();
    var buf: [5024]u8 = undefined;
    var safe_count_with_dampener: usize = 0;

    while (try in_stream.readUntilDelimiterOrEof(&buf, '\n')) |line| {
        const trimmed = std.mem.trim(u8, line, " \r\n");
        if (trimmed.len == 0) continue;

        // Parse the line into an array of integers
        var nums_iterator = std.mem.splitSequence(u8, trimmed, " ");
        var numbers = ArrayList(i32).init(allocator);
        defer numbers.deinit();

        while (nums_iterator.next()) |num_str| {
            const number = try std.fmt.parseInt(i32, num_str, 10);
            try numbers.append(number);
        }

        // Check safety with dampener
        safe_count_with_dampener += try checkSafetyWithDampener(numbers.items, allocator);
    }

    std.debug.print("Safe value with dampener: {} \n", .{safe_count_with_dampener});
}

fn checkSafetyWithDampener(numbers: []i32, allocator: std.mem.Allocator) !u8 {
    // First, check if the original sequence is safe
    if (try checkSafetyOfSequence(numbers)) return 1;

    for (numbers, 0..) |_, index| {
        const modified_numbers = try removeIndex(numbers, index, allocator);
        defer allocator.free(modified_numbers);

        if (try checkSafetyOfSequence(modified_numbers)) {
            return 1;
        }
    }

    return 0;
}

fn removeIndex(arr: []i32, index: usize, allocator: std.mem.Allocator) ![]i32 {
    var new_arr = try allocator.alloc(i32, arr.len - 1);
    var j: usize = 0;
    for (arr, 0..) |el, i| {
        if (i != index) {
            new_arr[j] = el;
            j += 1;
        }
    }
    return new_arr;
}

fn checkSafetyOfSequence(numbers: []i32) !bool {
    if (numbers.len <= 1) return true;

    var differences = std.ArrayList(i32).init(std.heap.page_allocator);
    defer differences.deinit();

    for (0..numbers.len - 1) |i| {
        const diff = numbers[i + 1] - numbers[i];
        try differences.append(diff);
    }

    const initial_sign = if (differences.items[0] > 0) @as(i32, 1) else if (differences.items[0] < 0) @as(i32, -1) else return false;

    for (differences.items) |diff| {
        if (diff == 0 or @abs(diff) > 3) return false;

        const current_sign = if (diff > 0) @as(i32, 1) else if (diff < 0) @as(i32, -1) else return false;

        if (initial_sign != current_sign) return false;
    }

    return true;
}
