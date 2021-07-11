/*
 * SYNCHRONIZED
 * Version B: Synchronized instance method
 */

package demo14;

import java.util.stream.IntStream;



public class ProgramB02 {

    public static void main(String[] args) throws InterruptedException {
        final int NUM_THREADS = 3;


        var myTask = new MyTaskB02();


        var lstTh = IntStream.range(0, NUM_THREADS).mapToObj(i -> new Thread(myTask)).toList();


        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();


        System.out.println("counter = " + MyTaskB02.counter);
        /*
         * We are sure that counter = 3000
         */
    }

}



class MyTaskB02 implements Runnable {
    static int counter = 0;


    @Override
    public synchronized void run() {
        try { Thread.sleep(500); } catch (InterruptedException e) { }

        for (int i = 0; i < 1000; ++i) {
            ++counter;
        }
    }
}