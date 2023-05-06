# Report

## Algorithms and Data Structures
Huffman - Encodes and decodes image data.
Our Huffman algorithm accesses an image and converts it between a png file and raw binary data

SLIC - Uses the data given by the Huffman algorithm to process the image and output the toonified image

Splay - Finds the average color in the algorithm


## Leading Question
Our target goal from this project would be to successfully cartoonify a PNG Image by employing an algorithm to subdivide the image into superpixels, based on the SLIC algorithm. The were numerous steps we took to ensure that we were successful in achieving the goal we sought out to accomplish. The first step was properly handling the processing of the inputted image. In order to do this, we ensured that the recieved image was a PNG image by having our website reject any non-PNG files. We then huffman encoded the image based on the frequency of bytes within the PNG's bytedata. The second step was to convert the PNG's raw data to 2d vector of pixels. This step required use to decode the Huffman tree we encoded and to create a vector of unsigned characters based on the binary sequence generated & mapping substrings of the sequence to its corresponding unsigned character. Then, the byteData (outputted vector of unsigned characters) was further decoded in lodepng to get the 2d vector of pixels. The final step was modify our image's 2d vector of pixels to output the cartoonified version. We need to utilize the SLIC algorithm on 2d vector of pixels to get the 2D vector of pixels of its cartoonified version and convert that to a PNG image. This is done by making the nodes of a graph correspond with pixels in the 2d vector. The weights of each 
