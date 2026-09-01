package com.cache.core;

import java.util.HashMap;
import java.util.Map;

public class LruCache<K,V> {
    protected int capacity;
    protected Map<K,Node<K,V>> map;
    protected DoublyLinkedList<K,V> list;

    public LruCache(int capacity) {
        if(capacity<=0) throw new IllegalArgumentException();
        this.capacity = capacity;
        this.map = new HashMap<>();
        this.list = new DoublyLinkedList<>();
    }

    public V get(K key){
        Node<K, V> node = map.get(key);
        if(node == null) return null;
        list.moveToHead(node);
        return node.value;
    }

    public void put(K key, V value){
        if(!map.containsKey(key)) {
            if(map.size() >= capacity) {
                Node<K,V> evictedNode = list.removeTail();
                if(evictedNode!=null) {
                    map.remove(evictedNode.key);
                }
            }
            Node<K,V> node = new Node<>(key, value);
            list.addFirst(node);
            map.put(key,node);
        }
        else {
            Node<K,V> node = map.get(key);
            node.value=value;
            list.moveToHead(node);
        }
    }

}
