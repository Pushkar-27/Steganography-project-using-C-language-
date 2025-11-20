# Steganography-project-using-C-language-
This project implements Image Steganography using the Least Significant Bit (LSB) method in C. It hides a secret message inside an uncompressed BMP image without visible changes. The system supports encoding text into pixel data and decoding it back using bit-level manipulation.

🧠 LSB Steganography – C Implementation
📘 Overview

This project implements LSB (Least Significant Bit) Image Steganography using the C programming language.
It enables hiding secret data (such as text files) inside 24-bit BMP images without causing any visible distortion.

The project demonstrates practical use of file handling, bitwise operations, and data security, following a clean and modular C design.

✨ Features

🔐 Encode (hide) any text file inside a 24-bit BMP image

🔓 Decode (extract) hidden data from the stego image

🧩 Supports 24-bit uncompressed BMP format

⚙️ Validates file formats and checks image capacity

🧠 Maintains original image quality

🪶 Provides detailed logs during encoding and decoding

⚙️ How to Compile and Run
1️⃣ Clone the Repository
git clone https://github.com/yourusername/LSB-Steganography-C-Implementation.git

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

📁 Project Structure
LSB-Steganography-C-Implementation/
│
├── main.c
├── encode.c
├── decode.c
├── types.h
├── encode.h
├── decode.h
├── Makefile
├── README.md
└── sample/
    ├── input.bmp
    ├── secret.txt
    └── stego.bmp

🧮 Concept Behind LSB Steganography

LSB steganography hides secret bits inside the least significant bits of pixel values.
Because these bits contribute minimally to the pixel's visible color, the change is undetectable.

Example:

Original Pixel: 10010110  
Modified Pixel: 10010111  ← (1 secret bit embedded)

This project performs reliable bit-level embedding and extraction, ensuring accurate recovery of the hidden file.

🔮 Future Enhancements

Add encryption before embedding data
Support PNG/JPEG formats
Develop a GUI using C++/Python
Add audio/video steganography

👨‍💻 Author

Pushkar Kadam
Electronics and Telecommunication Engineer
📫 https://www.linkedin.com/in/pushkar-kadam-97455432b
