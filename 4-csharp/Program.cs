class Program
{
    static void Main()
    {
        InputFileReader reader = new("input.txt");
        string[] lines = reader.Lines;
        Card[] cards = Array.ConvertAll(lines, line => Parser.GetCard(line));

        List<int> originalCardsPoints = new();
        Dictionary<int, int> copiedCardsMap = new();
        int copiedCards = 0;
        
        foreach (var card in cards)
        {
            IEnumerable<int> matchingNumbers = card.WinningNumbers.Intersect(card.Numbers);
            int points = (int)Math.Pow(2, matchingNumbers.Count() - 1);
            originalCardsPoints.Add(points);

            int copiesToGrant = 1 + copiedCardsMap.GetValueOrDefault(card.Id, 0);

            (int, int) range = (
                card.Id + 1,
                Math.Min(card.Id + 1 + matchingNumbers.Count(), cards.Length)
            );

            for (int i = range.Item1; i < range.Item2; i++)
            {
                int currentCardId = i;
                if (!copiedCardsMap.ContainsKey(currentCardId))
                {
                    copiedCardsMap.Add(currentCardId, copiesToGrant);
                }
                else
                {
                    copiedCardsMap[currentCardId] += copiesToGrant;
                }

                copiedCards += copiesToGrant;
            }
        }

        Console.WriteLine($"Part 1: {originalCardsPoints.Sum()}");
        Console.WriteLine($"Part 2: {originalCardsPoints.Count + copiedCards}");
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
