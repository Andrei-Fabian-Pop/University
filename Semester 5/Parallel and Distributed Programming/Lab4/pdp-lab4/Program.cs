using Lab4.Parser;
using pdp_lab4.Parser;

namespace pdp_lab4
{
    class Program
    {
        private static readonly List<string> Urls = new()
        {
            "www.dspcluj.ro/HTML/promovarea_sanatatii/promovare.html",
            "filesamples.com/samples/code/html/sample2.html",
            "filesamples.com/samples/code/html/sample1.html"
        };

        static void Main()
        {
            Console.WriteLine("1. Callback Parser");
            Console.WriteLine("2. Task Parser");
            Console.WriteLine("3. Async Await Parser");
            string choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    var callbackSolution = new CallbackSolution(Urls);
                    break;
                case "2":
                    var taskSolution = new TaskSolution(Urls);
                    break;
                case "3":
                    var asyncAwaitSolution = new AsyncAwaitSolution(Urls);
                    break;
                default:
                    Console.WriteLine("Invalid choice");
                    break;
            }
        }
    }
}