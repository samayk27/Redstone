package com.cache.core;

import org.jetbrains.annotations.NotNull;
import java.time.Duration;
import java.util.concurrent.locks.ReentrantLock;

public class StripedLruCache<K,V> {
    private final int numStripes;
    private final ReentrantLock[] locks;
    private final LruCache<K,V>[] shards;
    private final long entryttlMillis;
    @SuppressWarnings("unchecked")
    public StripedLruCache(int numStripes, int totalCapacity, long ttlMillis) {
        if (numStripes <= 0) throw new IllegalArgumentException("Stripes must be > 0");
        this.numStripes = numStripes;
        this.locks = new ReentrantLock[numStripes];
        this.shards = new LruCache[numStripes];
        entryttlMillis = ttlMillis;

        int shardCapacity = Math.max(1, totalCapacity/numStripes);
        for (int i = 0; i < numStripes; i++) {
            this.locks[i] = new ReentrantLock();
            this.shards[i] = new LruCache<>(shardCapacity);
        }
    }

    private int getShardIndex(@NotNull K key){
        int hash = key.hashCode();
        int spreadHash = hash^(hash>>>16);
        return (spreadHash & 0x7FFFFFFF) % numStripes;
    }

    public V get(K key) {
        int index = getShardIndex(key);
        locks[index].lock();
        try {
            return shards[index].get(key);
        } finally {
            locks[index].unlock();
        }
    }

    public void put(K key, V value) {
        int index = getShardIndex(key);
        locks[index].lock();
        try{
            shards[index].put(key, value, entryttlMillis);
        }
        finally {
            locks[index].unlock();
        }
    }
}
