PART B - INDIVIDUAL PROJECT: Railway Management (Lab 4 + Lab 5 + Lab 6)

Lab 4: Priority Queue   -> dispatch the highest-priority train first
Lab 5: Linked List      -> train timetable (insert, remove, swap, sort, reverse)
Lab 6: Circular Linked List -> station departure board that keeps rotating

------------------------------------------------------------
LAB 6 - CIRCULAR LINKED LIST
------------------------------------------------------------
1) REAL-WORLD PROBLEM
   A railway station has a digital departure board. It must show the trains
   one after another, and after the last train it must automatically return
   to the first train and keep going, all day, without ever stopping.

2) WHY A CIRCULAR LINKED LIST IS APPROPRIATE
   - The board repeats the same trains in a cycle, so there is no "end".
   - In a normal linked list the last node points to nullptr and we would have
     to write extra code to jump back to the start.
   - In a circular list the last node already points to the first node, so
     "move to next" works the same way for every train, including the last.
   - Trains can still be added or removed at any position without shifting.

3) NODE STRUCTURE (self-referential)
   struct TrainNode { int trainID; string trainName; string destination;
                      int priority; TrainNode* next; };
   head points to the LAST node (pivot) and head->next is the FIRST node.

4) CLASS: CircularLinkedList
   Insert / Remove (node next to head), InsertAt, RemoveAt, Swap, Sort,
   Reverse, Print, IsEmpty, IsNotEmpty, MoveToNext, IsCircular.
   Indexes wrap around the circle (negative and too-large indexes are allowed).

5) DEMONSTRATION
   Main Menu -> 3 (Departure Board) -> option 12 loads sample trains.
   - Option 9  moves to the next train, one step at a time.
   - Option 10 rotates N times (try 10 with 4 trains) to show it never stops.
   - Option 11 shows the first train, the last train and confirms that the
     last train links back to the first train.

COMPILE (run inside this folder):
   g++ main.cpp Input.cpp TrainNode.cpp PriorityQueue.cpp LinkedList.cpp CircularLinkedList.cpp -o program
RUN:
   .\program.exe
