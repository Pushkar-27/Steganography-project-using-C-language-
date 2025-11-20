# Steganography-project-using-C-language-
This project implements Image Steganography using the Least Significant Bit (LSB) method in C. It hides a secret message inside an uncompressed BMP image without visible changes. The system supports encoding text into pixel data and decoding it back using bit-level manipulation.

🧠 LSB Steganography – C Implementation
📘 Overview

This project implements LSB (Least Significant Bit) Image Steganography using the C programming language. It hides secret data (like text files) inside 24-bit BMP images without creating any visible distortion.

The project demonstrates effective use of file handling, bitwise operations, and data-hiding concepts, following a clean and modular C design.

✨ Features

🔐 Encode (hide) any text file inside a 24-bit BMP image

🔓 Decode (extract) hidden data from the stego image

🧩 Supports uncompressed 24-bit BMP format

⚙️ Validates file formats and checks image capacity

🧠 Maintains original image quality after encoding

🪶 Shows detailed logs during encoding and decoding

⚙️ How to Compile and Run

1️⃣ Clone the Repository

2️⃣ Navigate to the Project Directory
cd LSB-Steganography-C-Implementation

3️⃣ Build the Project
make

4️⃣ Encode Mode (Hide Secret Data)
./a.out -e <source_image.bmp> <secret.txt> <stego_image.bmp>


Example:

./a.out -e sample/input.bmp sample/secret.txt sample/stego.bmp

5️⃣ Decode Mode (Extract Hidden Data)
./a.out -d <stego_image.bmp> <output.txt>


Example:

./a.out -d sample/stego.bmp sample/output.txt

🧮 Concept Behind LSB Steganography

LSB steganography hides secret bits inside the least significant bits of each pixel value.
These bits have minimal effect on color, making the change invisible to the human eye.

Example:
Original Pixel: 10010110  
Modified Pixel: 10010111   ← (1 secret bit embedded)


This method ensures reliable embedding and extraction of data while preserving image quality.

🔮 Future Enhancements

Add encryption before embedding

Support PNG and JPEG formats

Develop a GUI using C++ or Python

Extend to audio/video steganography

👨‍💻 Author

Pushkar Kadam
Electronics and Telecommunication Engineer
📫 https://www.linkedin.com/in/pushkar-kadam-97455432b
