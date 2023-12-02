content = File.read!("example.txt")

lines = String.split(content, "\n")

defmodule Parsing do
  def parse_line(line) do
    splits = String.split(line, ": ")
    lists = :lists.sublist(splits, 2, length(splits) - 1)
    Enum.join(lists)
  end

  def parse_entries(entry) do
    # parse amount of r g b
  end

end


entries = Enum.map(lines, &Parsing.parse_line/1) # -> 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green

entries = Enum.map(lines, &Parsing.parse_line/1) # -> [(1, 4, 9)]

# map entries to index + 1 where r > 12 || g > 13 || b > 14

# sum indices

Enum.each(sets, &IO.puts/1)
