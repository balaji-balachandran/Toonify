# Report

## Algorithms and Data Structures
Huffman - Encodes and decodes image data.
Our Huffman algorithm accesses an image and converts it between a png file and raw binary data

SLIC - Uses the data given by the Huffman algorithm to process the image and output the toonified image. Uses edge weights and determines what parts of an image should be turned into superpixels and outputs a newly created image using an input of a 2D array of pixels. 

Splay - Finds the average color in the algorithm. Utilized splay property which enabled faster runtimes when accessing pixels.


## Leading Question
Our target goal from this project would be to successfully cartoonify a PNG Image by employing an algorithm to subdivide the image into superpixels, based on the SLIC algorithm. There were numerous steps we took to ensure that we were successful in achieving the goal we sought out to accomplish. The first step was properly handling the processing of the inputted image. In order to do this, we ensured that the received image was a PNG image by having our website reject any non-PNG files. We then used a Huffman algorithm to encode the image based on the frequency of bytes within the PNG's byte data. The next step was to convert the PNG's raw data to a 2D vector of pixels. This step required use of Huffman's algorithm to decode the data and to create a vector of unsigned characters based on the binary sequence generated and mapping substrings of the sequence to its corresponding unsigned character. Then, the byteData (outputted vector of unsigned characters) was further decoded in lodepng to get a 2D vector of pixels. The final step was modify our image's 2D vector of pixels to output the cartoonified version. We needed to utilize the SLIC algorithm on 2D vector of pixels to get the 2D vector of pixels of its cartoonified version and convert that to a PNG image. This was done by making the nodes of a graph correspond with pixels in the 2D vector. We finally used the coordinate pixels to produce a png image of the cartoonified image, which provides the user with the desired output.
