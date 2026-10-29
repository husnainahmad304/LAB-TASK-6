PART A - LIBRARY MANAGEMENT (Lab 4 + Lab 5 + Lab 6)

Lab 4: Priority Queue for book requests        (BookRequestNode, PriorityQueue)
Lab 5: Linked List for the book collection      (BookNode, LinkedList)
Lab 6: Circular Linked List for the featured    (BookNode, CircularLinkedList)
       book display screen

Main Menu: 1 = Lab 4, 2 = Lab 5, 3 = Lab 6, 4 = Exit

Lab 6 notes:
 - head points to the LAST node (pivot); head->next is the FIRST node.
 - "9. Move to Next Book" shows the next featured book. After the last book
   it goes back to the first book (it never reaches nullptr).
 - "10. Check Collection Status" shows the first book, the last book and
   confirms that the last book links back to the first one.

COMPILE (run inside this folder):
   g++ main.cpp Input.cpp PriorityQueue.cpp LinkedList.cpp CircularLinkedList.cpp BookNode.cpp -o program
RUN:
   .\program.exe
