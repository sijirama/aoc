const std = @import("std");
const path = "./input/fakeday2.txt";
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

    var safe_count: usize = 0;
    //const safe_count_with_dampener: usize = 0;
    var last_line: []const u8 = undefined;

    // 7 6 4 2 1
    while (try in_stream.readUntilDelimiterOrEof(&buf, '\n')) |line| {
        const trimmed = std.mem.trim(u8, line, " \r\n");
        if (trimmed.len == 0) continue;
        last_line = trimmed;

        var rows_iterator = std.mem.splitSequence(u8, trimmed, " ");
        var differences = ArrayList(i32).init(allocator);
        defer differences.deinit();

        var first_number: ?i32 = null;

        while (rows_iterator.next()) |row| {
            const record_number = try std.fmt.parseInt(i32, row, 10);

            if (first_number) |prev_number| {
                const value = record_number - prev_number;
                try differences.append(value);
            }

            first_number = record_number;
        }

        const data = differences.items;
        safe_count += checkSafety(data);

        // INFO: issue here is tha
        //safe_count_with_dampener += try checkSafetyWithDampenerWrapper(line, allocator);
    }

    std.debug.print("Safe value: {} \n", .{safe_count});
    //std.debug.print("Safe value with dampener: {} \n", .{safe_count_with_dampener});
}

fn checkSafetyWithDampener(diffs: []i32, allocator: std.mem.Allocator) !u8 {
    if (checkSafety(diffs) == 1) {
        return 1; // No need to modify if already safe
    }

    for (diffs, 0..) |_, index| {
        // Recursively check the new sequence
        const modified_diffs = try removeIndex(diffs, index, allocator);
        std.debug.print("\t\t Modified Array: {any}\n", .{modified_diffs});
        if (checkSafety(modified_diffs) == 1) {
            std.debug.print("\t\t Safe after removing index {}: {any}\n", .{ index, modified_diffs });
            allocator.free(modified_diffs); // Free memory after usage
            return 1; // Safe after removing one level
        }
        allocator.free(modified_diffs); // Free memory if not needed
    }

    return 0;
}

// Helper to remove an element at a specific index
fn removeIndex(arr: []i32, index: usize, allocator: std.mem.Allocator) ![]i32 {
    var new_arr = try allocator.alloc(i32, arr.len - 1);

    // Copy elements except the one at `index`
    var j: usize = 0;
    for (arr, 0..) |el, i| {
        if (i != index) {
            new_arr[j] = el;
            j += 1;
        }
    }

    return new_arr;
}

fn checkSafety(diffs: []i32) u8 {
    if (diffs.len == 0) return 0;

    const initial_sign = if (diffs[0] > 0) @as(i32, 1) else if (diffs[0] < 0) @as(i32, -1) else return 0;

    for (diffs) |num| {
        if (num == 0 or @abs(num) > 3) return 0; // flat or too large difference
        const current_sign = if (num > 0) @as(i32, 1) else if (num < 0) @as(i32, -1) else return 0;
        if (initial_sign != current_sign) return 0;
    }

    return 1;
}
