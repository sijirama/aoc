const std = @import("std");

pub fn main() !void {
    // Open the file for reading

    const allocator = std.heap.page_allocator;

    const file = try std.fs.cwd().openFile("input/day1.txt", .{});
    defer file.close();

    // Create a buffered reader for efficient line-by-line reading
    const reader = std.io.bufferedReader(file.reader());
    var buf = reader.buffer();
    defer buf.deinit();

    while (try buf.readUntilDelimiterOrEof(allocator, '\n')) |line| {
        // `line` contains the current line as a slice
        std.debug.print("Read line: {s}\n", .{line});
        allocator.free(line); // Free memory allocated for the line
    }
}
