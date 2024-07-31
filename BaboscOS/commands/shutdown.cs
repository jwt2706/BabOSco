using System;
using Sys = Cosmos.System;

namespace BaboscOS.commands
{
    public class shutdownCmd
    {
        public void Execute()
        {
            Console.Write("Are you sure you want to shutdown? (y/n): ");
            var confirmation = Console.ReadLine().ToLower().Trim();
            if (confirmation == "y")
            {
                Console.WriteLine("Shutting down...");
                Sys.Power.Shutdown();
            }
            else
            {
                Console.WriteLine("Shutdown cancelled.");
            }
        }
    }
}