package com.cache;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import com.cache.core.StripedLruCache;

public class StripedLruCacheTest {
    private static final int THREAD_COUNT = 20;
    private static final int OPS_PER_THREAD = 10000;
    private StripedLruCache<String, String> cache;

    @BeforeEach
    void setUp(){
        cache=new StripedLruCache<>(4,100);
    }

    @Test
    @DisplayName("High contention: Parallel reads and writes across multiple threads")
    void testConcurrentPutAndGet() throws InterruptedException {
        ExecutorService executor = Executors.newFixedThreadPool(THREAD_COUNT);

        CountDownLatch startLatch = new CountDownLatch(1);
        CountDownLatch endLatch = new CountDownLatch(THREAD_COUNT);

        AtomicInteger exceptionCount = new AtomicInteger(0);

        for(int i=0;i<THREAD_COUNT;i++){
            final int threadId = i;
            executor.submit(() -> {
                try{
                    startLatch.await();
                    for (int j=0;j<OPS_PER_THREAD;j++){
                        String key = "key_" + (j % 50);
                        String value = "value_" + threadId + "_" + j;
                        cache.put(key, value);
                        cache.get(key);
                    }
                }catch (Exception e) {
                    exceptionCount.incrementAndGet();
                    e.printStackTrace();
                } finally {
                    endLatch.countDown();
                }
            });
        }
        startLatch.countDown();
        boolean completedTime = endLatch.await(10, TimeUnit.SECONDS);
        executor.shutdown();

        assertTrue(completedTime, "Test timed out — potential deadlock occurred!");
        assertEquals(0, exceptionCount.get(), "Exceptions were thrown during multi-threaded operation!");

        cache.put("sanity_check", "value");
        assertEquals("value", cache.get("sanity_check"));
    }
}
