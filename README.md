## Simple python module wrapper around C++ ChaCha20-Sha256 cryptor binary.
The encryption algorithm uses the chacha20 cipher with a 32-byte key for encryption and sha-256 for built-in integrity checking.
Due to the random nonce, it provides a unique output on every run.

## Usage
1. Compile cryptor bin
```sh
chmod +x compile.sh
./compile.sh
```
2. Use cryptor as module in other Python projects
```python3
import encryptor
```
3. To encrypt data
```python3
key = b"\x3d\xaf\x1c\x42\x8b\x07\x9a\x59\xc6\x11\xde\x3a\x8e\x29\x74\xec" \
      b"\xa1\x32\xb9\x44\x5f\x98\x20\xcd\x6e\xf4\x1d\x77\x02\x65\xab\x8c"
input = b"Hello, this is a test input for encryption!"

# -- First run

output = encryptor.encrypt(input, key)

print(f"Encrypted: {output.hex(sep=" ")}")
# Encrypted: e3 4e 9a 8f 5f f1 e9 f6 2a fb 43 c6 da 6d 24 98 0e 19 c2 13 ef 93 ea 4e 4d 7f 0f 7f 68 ae c5 1b ea fa 77 5a a4 d1 83 66 67 bb 77 c0 33 07 10 17 17 54 87 d3 23 0d 52 f3 d1 45 2c 04 0c c5 48 1d f6 be 0d 0c 00 1a 0d 49 0c b6 b9 00 04 bf db 23 93 4b 2a

## -- Second run, completely different output

output = encryptor.encrypt(input, key)

print(f"Encrypted: {output.hex(sep=" ")}")
# Encrypted: 80 29 a3 47 fa 05 d1 2d e8 6e d9 af 70 fa 1b 01 7f 6a d1 dc ca 7b c2 63 b4 6c 4c f4 00 3c f3 ea 00 d8 b8 ca 40 e1 ba 75 85 4c 2f b2 b7 ef b0 4d 46 4c f9 d3 23 0d 52 f3 d1 45 2c 04 0c c5 48 1d f6 be 0d 0c 00 1a 0d 49 0c b6 b9 00 04 bf db 23 93 4b 2a
```
3. To decrypt 
```python3
key = b"\x3d\xaf\x1c\x42\x8b\x07\x9a\x59\xc6\x11\xde\x3a\x8e\x29\x74\xec" \
      b"\xa1\x32\xb9\x44\x5f\x98\x20\xcd\x6e\xf4\x1d\x77\x02\x65\xab\x8c"

input = b"".fromhex("e3 4e 9a 8f 5f f1 e9 f6 2a fb 43 c6 da 6d 24 98 0e 19 c2 13 ef 93 ea 4e 4d 7f 0f 7f 68 ae c5 1b ea fa 77 5a a4 d1 83 66 67 bb 77 c0 33 07 10 17 17 54 87 d3 23 0d 52 f3 d1 45 2c 04 0c c5 48 1d f6 be 0d 0c 00 1a 0d 49 0c b6 b9 00 04 bf db 23 93 4b 2a")

output = encryptor.decrypt(input, key)

print(f"Decrypted: {output}")
# Decrypted: b'Hello, this is a test input for encryption!'
```

