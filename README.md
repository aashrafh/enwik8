# About
An attemt trying ot compress the first 100 MB of Wikipedia which is called [enwik8](https://en.wikipedia.org/wiki/Hutter_Prize) using LZW algorithm and BZip2 with variable length encoding.

# Results
* <strong>LZW</strong>:
  * Compression ratio: <strong>2.905</strong>
  * Compressed file size: <strong>32 MB</strong>
* <strong>BZip2</strong>:
  * Compression ratio: <strong>3.855</strong>
  * Compressed file size: <strong>24 MB</strong>
# How to run
* <strong>Compression</strong>
   1. Open a terminal on the directory containing the code
   2. Generate the binary file using command: ```g++ -o encoder.exe encoder.cpp```
   3. Run the binary file: ```./encoder.exe```
* <strong>Decompression</strong>
  1. Open a terminal on the directory containing the code
  2. Generate the binary file using command: ```g++ -o decoder.exe decoder.cpp```
  3. Run the binary file: ```./decoder.exe```
 
