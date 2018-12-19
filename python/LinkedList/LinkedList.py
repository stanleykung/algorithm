

class Node:
    def __init__(self,val):
        self.val = val;
        self.next = None; # inital point to null
    def traverse(self):
        node = self # start from header node
        while node != None:
            print(node.val)
            node = node.next

node1 = Node(10)
node2 = Node(20)
node3 = Node(30)
node4 = Node(40)

node1.next = node2
node2.next = node3
node3.next = node4

node1.traverse()

# https://medium.com/@kojinoshiba/data-structures-in-python-series-1-linked-lists-d9f848537b4d