from typing import List
from functools import reduce
from time import perf_counter


def count_ways_to_win(time: int, distance: int) -> List[int]:
    min_time = distance // time
    max_time = time
    return sum((1 for x in range(min_time, max_time + 1) if (time - x) * x > distance))


file_content = None
with open("input.txt", "r") as f:
    file_content = f.read()

times, distances = map(
    lambda s: [int(x) for x in s[11:].split(" ") if x], file_content.split("\n")[:-1]
)

time, distance = map(
    lambda s: int("".join([x for x in s[11:].split(" ") if x])),
    file_content.split("\n")[:-1],
)

start = perf_counter()

part_1 = reduce(
    lambda x, y: x * y,
    [count_ways_to_win(times[i], distances[i]) for i in range(len(times))],
)

part_2 = count_ways_to_win(time, distance)

print(perf_counter() - start)

print(part_1)
print(part_2)
