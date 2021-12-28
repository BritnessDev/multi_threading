/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE B: USING SEMAPHORE
 *      Version B03: 2 fast producers, 1 slow consumer
 */

package exer02;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;



public class AppB03 {

    public static void main(String[] args) {
        var semFill = new Semaphore(0);     // item produced
        var semEmpty = new Semaphore(1);    // remaining space in queue

        Queue<Integer> qProduct = new LinkedList<>();

        new Thread(() -> funcProducer(semFill, semEmpty, qProduct, 0)).start();
        new Thread(() -> funcProducer(semFill, semEmpty, qProduct, 1000)).start();

        new Thread(() -> funcConsumer(semFill, semEmpty, qProduct)).start();
    }


    private static void funcProducer(Semaphore semFill, Semaphore semEmpty,
                                     Queue<Integer> qProduct, int startValue) {
        int i = 1;

        for (;; ++i) {
            try {
                semEmpty.acquire();
                qProduct.add(i + startValue);
                semFill.release();
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }


    private static void funcConsumer(Semaphore semFill, Semaphore semEmpty, Queue<Integer> qProduct) {
        for (;;) {
            try {
                semFill.acquire();

                int data = qProduct.remove();
                System.out.println("Consumer " + data);
                Thread.sleep(1000);

                semEmpty.release();
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

}
