﻿/*
 * THE VOLATILE KEYWORD
 */
using System;
using System.Threading;



class Demo24 : IRunnable
{
    public void run()
    {
        new Thread(routine).Start();
        Thread.Sleep(6000);
        Global.stopped = true;
    }


    private void routine()
    {
        while (false == Global.stopped)
        {
            Console.WriteLine("Running...");
            Thread.Sleep(2000);
        }
    }


    class Global
    {
        public static volatile bool stopped = false;
    }
}
