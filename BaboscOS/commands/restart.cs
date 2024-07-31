using System;
using Sys = Cosmos.System;

namespace BaboscOS.commands
{
    public class restartCmd
    {
        public void Execute()
        {
            Console.Write("Are you sure you want to restart? (y/n): ");
            var confirmation = Console.ReadLine().ToLower().Trim();
            if (confirmation == "y")
            {
                Console.WriteLine("Restarting...");
                Sys.Power.Reboot();
            }
            else
            {
                Console.WriteLine("Restart cancelled.");
            }
        }
    }
}