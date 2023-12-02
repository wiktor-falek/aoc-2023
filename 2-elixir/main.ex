content = File.read!("input.txt")
lines = content |> String.split("\n", trim: true)

defmodule Parsing do
  @spec parse_line(line :: String.t()) :: String.t()
  def parse_line(line) do
    [_gameIdStr, rest] = String.split(line, ": ")
    rest
  end

  @spec parse_entries(line :: String.t()) :: list(String.t())
  def parse_entries(line) do
    games_data = String.split(line, "; ")
    Enum.map(games_data, &String.split(&1, ", "))
  end

  @spec parse_games(list(String.t())) :: {integer, integer, integer}
  def parse_games(entries) do
    Enum.map(entries, fn entry ->
      Enum.reduce(entry, {0, 0, 0}, fn item, {max_r, max_g, max_b} ->
        parse_cube(item, {max_r, max_g, max_b})
      end)
    end)
  end

  @spec parse_cube(item :: String.t(), {r, g, b} :: {integer, integer, integer}) :: {integer, integer, integer}
  def parse_cube(item, {r, g, b}) do
    [strAmount, color] = String.split(item, " ")
    amount = String.to_integer(strAmount)

    case color do
      "red" -> {r + amount, g, b}
      "green" -> {r, g  + amount, b}
      "blue" -> {r, g, b + amount}
      _ -> raise(ArgumentError, message: "Invalid color: #{color}")
    end
  end
end

defmodule Cubes do
  @spec max_cubes(cubes :: list({r, g, b} :: {integer, integer, integer})) :: {integer, integer, integer}
  def max_cubes(cubes) do
    Enum.reduce(cubes, {0, 0, 0}, fn {r, g, b}, {acc_r, acc_g, acc_b} ->
      {max(acc_r, r), max(acc_g, g), max(acc_b, b)}
    end)
  end

  @spec is_cube_within_bounds({integer, integer, integer}) :: boolean
  def is_cube_within_bounds({r, g, b}) do
    r <= 12 and g <= 13 and b <= 14
  end
end


lines = (Enum.map(lines, &Parsing.parse_line/1))

entries = Enum.map(lines, &Parsing.parse_entries/1)

games = Enum.map(entries, &Parsing.parse_games/1)

games_max_cubes = Enum.map(games, &Cubes.max_cubes/1)

predicated_games =
  games_max_cubes
  |> Enum.with_index()
  |> Enum.filter(fn {{r, g, b}, index} -> Cubes.is_cube_within_bounds({r, g, b}) end)

sum_of_game_ids = Enum.sum(Enum.map(predicated_games, fn {_, index} -> index + 1 end))

sum_powers = Enum.sum(Enum.map(games_max_cubes, fn {r, g, b} -> r * g * b end))

IO.puts("Part 1: #{sum_of_game_ids}")
IO.puts("Part 2: #{sum_powers}")
