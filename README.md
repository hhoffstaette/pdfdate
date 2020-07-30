# pdfdate
Retrieves the creation/modification date of a PDF document.

# The problem
You enjoy reading technical reports and downloaded a bunch of PDF files, but
their time stamps are all wrong - it's the time of the download, not the
CreationDate/ModificationDate of the document, which is likely to be in the
past. But having proper timestamps is useful to know when a report was
actually written. What can you do?
```
$ll
total 8.2M
-rw-r--r-- 1 holger users 632K Jul 30 13:18 A Glimpse of the Matrix - Scalability Issues of a New Message-Oriented Data Synchronization Middleware.pdf
-rw-r--r-- 1 holger users 458K Jul 30 13:18 Analyzing the Performance of WebAssembly vs. Native Code.pdf
-rw-r--r-- 1 holger users 2.2M Jul 30 13:18 Avoiding Scalability Collapse by Restricting Concurrency.pdf
-rw-r--r-- 1 holger users 365K Jul 30 13:18 Bipartisan Paxos - A Modular State Machine Replication Protocol.pdf
-rw-r--r-- 1 holger users 646K Jul 30 13:18 Exploiting Commutativity For Practical Fast Replication - Slides.pdf
-rw-r--r-- 1 holger users 811K Jul 30 13:18 Exploiting Commutativity For Practical Fast Replication.pdf
-rw-r--r-- 1 holger users 1.3M Jul 30 13:18 Exploiting a Natural Network Effect for Scalable, Fine-grained Clock Synchronization.pdf
```

# A nonsolution
You open every document, manually inspect its properties and use ```touch``` to fix every timestamp individually.

Just kidding, of course you don't.

# The solution
```
$for f (*.pdf) d=$(pdfdate $f) && touch -d "$d" "$f"
$ll                                                 
total 8.2M
-rw-r--r-- 1 holger users 632K Dec  2  2019 A Glimpse of the Matrix - Scalability Issues of a New Message-Oriented Data Synchronization Middleware.pdf
-rw-r--r-- 1 holger users 458K Jan 29  2019 Analyzing the Performance of WebAssembly vs. Native Code.pdf
-rw-r--r-- 1 holger users 2.2M Jul 15  2019 Avoiding Scalability Collapse by Restricting Concurrency.pdf
-rw-r--r-- 1 holger users 365K Mar  3 01:49 Bipartisan Paxos - A Modular State Machine Replication Protocol.pdf
-rw-r--r-- 1 holger users 646K Feb 28  2019 Exploiting Commutativity For Practical Fast Replication - Slides.pdf
-rw-r--r-- 1 holger users 811K Feb 23  2019 Exploiting Commutativity For Practical Fast Replication.pdf
-rw-r--r-- 1 holger users 1.3M Apr 30  2019 Exploiting a Natural Network Effect for Scalable, Fine-grained Clock Synchronization.pdf
```
This will fix up all timestamps. Invalid documents or missing ```CreationDate/ModificationDate``` properties are ignored.

# Building
- Install ```poppler``` and - depending on your distribution - ```poppler-dev```
- ```c++ -pipe -Os -Wall pdfdate.cpp -o pdfdate -lpoppler-cpp```
- install ```pdfdate``` to ```/usr/local/bin``` or some other part of your ```$PATH```.

## Enjoy! :)

