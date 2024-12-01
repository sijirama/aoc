const std = @import("std");
const ArrayList = std.ArrayList;
const print = std.debug.print;
const path = "./input/day1.txt";

pub fn main() !void {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    var numberMap = std.AutoHashMap(u32, u32).init(allocator);
    var left = ArrayList(i32).init(allocator);
    var right = ArrayList(i32).init(allocator);

    const buffer = try std.fs.cwd().readFileAlloc(allocator, path, 20024);
    defer allocator.free(buffer);

    var rows = std.mem.splitSequence(u8, buffer, "\n");

    while (rows.next()) |row| {
        const trimmed = std.mem.trim(u8, row, " \t\r\n");

        var nums = std.mem.splitSequence(u8, trimmed, "   ");
        const num1 = nums.next() orelse continue;
        const num2 = nums.next() orelse continue;

        try left.append(try std.fmt.parseInt(i32, num1, 10));
        try right.append(try std.fmt.parseInt(i32, num2, 10));
    }

    std.mem.sort(i32, left.items, {}, std.sort.asc(i32));
    std.mem.sort(i32, right.items, {}, std.sort.asc(i32));

    var distance: i32 = 0;
    var length: i64 = @intCast(@max(right.items.len, left.items.len) - 1);

    while (length > 0) {
        // get distance
        const index: usize = @intCast(length);
        distance += @max(left.items[index], right.items[index]) - @min(left.items[index], right.items[index]);

        length -= 1;
    }

    if (length == 0) {
        const index: usize = @intCast(length);
        distance += @max(left.items[index], right.items[index]) - @min(left.items[index], right.items[index]);
    }

    print("Total distance is: {d}\n", .{distance});

    for (right.items) |item| {
        const key: u32 = @intCast(item);
        const v = try numberMap.getOrPut(key);
        if (!v.found_existing) {
            v.value_ptr.* = 0;
        }
        v.value_ptr.* += 1;
    }

    var similarity_score: u32 = 0;
    for (left.items) |item| {
        const key: u32 = @intCast(item);
        if (numberMap.get(key)) |count| {
            similarity_score += key * count;
        }
    }

    print("Similarity score is: {d}\n", .{similarity_score});
}
