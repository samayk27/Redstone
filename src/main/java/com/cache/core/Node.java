package com.cache.core;

public class Node<K, V> {
    protected K key;
    protected V value;
    protected Node<K,V> next;
    protected Node<K,V> previous;

    public Node(K key, V value) {
        this.key=key;
        this.value=value;
        next = null;
        previous = null;
    }
}
