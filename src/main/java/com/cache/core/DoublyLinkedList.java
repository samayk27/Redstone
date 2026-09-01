package com.cache.core;

public class DoublyLinkedList<K,V> {
    protected Node<K,V> head;
    protected Node<K,V> tail;

    public DoublyLinkedList(){
        head=new Node<>(null,null);
        tail=new Node<>(null,null);
        head.next=tail;
        tail.previous=head;
    }
    public void addFirst(Node<K,V> node){
        node.next=head.next;
        node.previous=head;
        head.next.previous=node;
        head.next=node;
    }
    public void unlink(Node<K,V> node){
        node.previous.next=node.next;
        node.next.previous=node.previous;
        node.next=null;
        node.previous=null;
    }
    public void moveToHead(Node<K,V> node){
        unlink(node);
        addFirst(node);
    }
    public Node<K,V> removeTail(){
        if(tail.previous==head) return null;
        Node<K,V> node = tail.previous;
        unlink(node);
        return node;
    }
}
