class Program
{
    static void Main()
    {
        InputFileReader reader = new("input.txt");
        string[] lines = reader.Lines;

        List<int> allGamesPoints = new();
        
        foreach (var line in lines)
        {
            Card card = Parser.GetCard(line);
            // Console.WriteLine(
            //     $"Card({card.Id}, [{string.Join(',', card.WinningNumbers)}], [{string.Join(',', card.Numbers)}])"
            // );

            IEnumerable<int> matchingNumbers = card.WinningNumbers.Intersect(card.Numbers);
            int points = (int)Math.Pow(2, matchingNumbers.Count() - 1);
            allGamesPoints.Add(points);
        }

        Console.WriteLine("Part 1: " + allGamesPoints.Sum());
    }

    class InputFileReader
    {
        private readonly List<string> lines = new();

        public InputFileReader(string filePath)
        {
            StreamReader sr = new(filePath);
            
            string? line = sr.ReadLine();

            while (line != null)
            {
                lines.Add(line);
                line = sr.ReadLine();
            }
            
            sr.Close();

            Lines = lines.ToArray();
        }

        public string[] Lines { get; private set; }
    }

    class Card
    {
        public int Id { get; }
        public int[] WinningNumbers { get; }
        public int[] Numbers { get; }

        public Card(int id, int[] winningNumbers, int[] numbers)
        {
            Id = id;
            WinningNumbers = winningNumbers;
            Numbers = numbers;
        }
    }

    class Parser
    {
        public Parser() { }

        private static int[] ParseNumbers(string numbers)
        {
            string[] parsedNumbers = numbers.Split(" ", StringSplitOptions.RemoveEmptyEntries);

            return Array.ConvertAll(parsedNumbers, x => int.Parse(x));
        }

        public static Card GetCard(string line)
        {
            string[] parts = line.Split(": ");
            string name = parts[0];
            string card = parts[1];

            parts = card.Split(" | ");
            string winningNumbersString = parts[0];
            string numbersString = parts[1];

            int cardId = int.Parse(name[5..]);
            int[] winningNumbers = ParseNumbers(winningNumbersString);
            int[] numbers = ParseNumbers(numbersString);

            return new Card(cardId, winningNumbers, numbers);
        }
    }
}
