using System;
using System.Collections.Generic;
using System.Text;
using Sys = Cosmos.System;
using BaboscOS.commands;

namespace BaboscOS
{
    public class Kernel : Sys.Kernel
    {
        private shutdownCmd shutdownCmd = new shutdownCmd();
        private restartCmd restartCmd = new restartCmd();

        protected override void BeforeRun()
        {
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Clear();
            AsciiLogo();
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.WriteLine("Welcome to BaboscOS. Type 'help' for available commands.");
            Console.ResetColor();
        }

        protected override void Run()
        {
            Console.ForegroundColor = ConsoleColor.Green;
            Console.Write("user@BaboscOS$ ");
            Console.ResetColor();
            var input = Console.ReadLine();
            HandleCommand(input);
        }

        private void HandleCommand(string input) {
            var cmd = input.ToLower().Trim();
            switch (cmd) {
                case "help":
                    ShowHelp();
                    break;
                case "shutdown":
                    shutdownCmd.Execute();
                    break;;
                case "restart":
                    restartCmd.Execute();
                    break;
                case "fetch":
                    FetchSystemInfo();
                    break;
                case "clear":
                    Console.Clear();
                    break;
                case "":
                    break;
                default:
                    Console.WriteLine("Unknown command. Type 'help' for a list of commands.\n");
                    break;
            }
        }

        private void ShowHelp()
        {
            Console.WriteLine(@"Available commands:
help - Show this help message.
shutdown - Shutdown the system.
restart - Restart the system.
fetch - Fetch and display system information.");
        }

        private void FetchSystemInfo() {
            Console.ForegroundColor = ConsoleColor.Cyan;
            AsciiLogo();
            Console.WriteLine(@$"OS Name: BaboscOS
Version: 0.0.1");
            var datetime = DateTime.Now;
            Console.WriteLine(datetime);
            Console.ResetColor();
        }

        private void AsciiLogo()
        {
            Console.WriteLine(@"______         __                      _______ _______ 
|   __ \.---.-.|  |--.-----.-----.----.|       |     __|
|   __ <|  _  ||  _  |  _  |__ --|  __||   -   |__     |
|______/|___._||_____|_____|_____|____||_______|_______|v0.0.1");
        }

    }
}
