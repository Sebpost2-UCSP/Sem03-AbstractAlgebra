# Sem03-AbstractAlgebra

### Course Overview
This repository contains assignments and the final project for the **Abstract Algebra** course, taken during my third semester. Although traditionally a mathematics-focused subject, this course emphasized **cryptographic algorithms and cipher techniques** implemented in C++. Each assignment involved building and analyzing various encryption methods, culminating in a complete implementation of the RSA algorithm for the final project.

### Learning Outcomes
Through this course, I gained hands-on experience in:
- Developing and implementing classic encryption algorithms.
- Understanding fundamental principles of cryptography, especially through the lens of modular arithmetic.
- Building complex functions and applying them across cryptographic methods, particularly within RSA encryption.

### Project and Assignments
This repository is organized with individual `.cpp` files for each assignment and additional folders for the final project.

#### Assignments
- **String Exercises**: Initial exercises focused on string manipulations to prepare for cipher work.
- **Affine Cipher**: Implemented the Affine Cipher algorithm, which applies modular arithmetic to encrypt and decrypt text.
- **Caesar Cipher**: Created an encryption and decryption method using Caesar Cipher, a classic substitution cipher technique.
- **Rail Fence Cipher**: Developed the Rail Fence Cipher, a form of transposition cipher that arranges plaintext in a zigzag pattern.
- **Scythian Cipher**: Implemented the Scythian Cipher, a variant on columnar transposition ciphers.
- **Scythian Cipher (With Vectors)**: An alternative version of the Scythian Cipher, leveraging C++ vectors for more efficient data handling.
- **RSA First Advance**: Initial setup and testing of functions for RSA encryption, including modular exponentiation and prime checking.

#### Final Project - RSA Encryption
The final project implements a **complete RSA encryption system** with the following structure:
- **Folder Structure**:
  - `Headers/`: Contains header files defining RSA and math-related functions.
  - `RSAFunctions/`: Includes `RSA.cpp` for encryption and decryption functions and `functions.cpp` for supporting mathematical operations like modular exponentiation.
  - `main.cpp`: Demonstrates the usage of RSA and math functions, showcasing the complete encryption and decryption workflow.
- **Documentation**:
  - `Informe RSA (final).pdf`: A comprehensive PDF document explaining the structure, theory, and functionality of the RSA implementation, along with sample outputs.

### Usage Instructions
To run each assignment or the final RSA project:
1. **Compile** the `.cpp` file (or `main.cpp` for the RSA project) with a C++ compiler, such as `g++`.
   ```bash
   g++ -o rsa main.cpp libraries/RSA.cpp libraries/functions.cpp
   ```
2. **Execute** the compiled program:
   ```bash
   ./rsa
   ```
