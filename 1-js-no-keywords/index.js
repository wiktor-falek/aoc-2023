console.log(
  require("fs")
    .readFileSync("input.txt")
    .toString()
    .split("\n")
    .slice(0, -1)
    .map((line) => [...line].filter((c) => /^\d+$/.test(c)))
    .map((line) => [line[0], line[line.length - 1]])
    .reduce((acc, curr) => acc + +(curr[0] + curr[1]), 0)
);

console.log(
  require("fs")
    .readFileSync("input.txt")
    .toString()
    .split("\n")
    .slice(0, -1)
    .map((line) =>
      line.matchAll(/one|two|three|four|five|six|seven|eight|nine|[1-9]/g)
    )
    .map((matches) => [...matches].map((match) => match[0]))
    .map((line) =>
      line.map(
        (entry) =>
          ({
            one: "1",
            two: "2",
            three: "3",
            four: "4",
            five: "5",
            six: "6",
            seven: "7",
            eight: "8",
            nine: "9",
          }[entry] ?? entry)
      )
    )
    .map((line) => [line[0], line[line.length - 1]])
    .reduce((acc, curr) => acc + +(curr[0] + curr[1]), 0)
);
