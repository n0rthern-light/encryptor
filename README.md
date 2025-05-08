## Simple python module wrapper around C++ ChaCha20-Sha256 cryptor binary.

The encryption algorithm uses chacha20 cipher with 32 byte key for encryption and sha256 for built-in integrity check.
Due to random nonce it provides an unique output every run.

## Usage

1. Compile cryptor bin
```sh
chmod +x compile.sh
./compile.sh
```
2. Use cryptor as module in other Python projects
```python3
import encryptor

key = b"\x3d\xaf\x1c\x42\x8b\x07\x9a\x59\xc6\x11\xde\x3a\x8e\x29\x74\xec" \
      b"\xa1\x32\xb9\x44\x5f\x98\x20\xcd\x6e\xf4\x1d\x77\x02\x65\xab\x8c"
input = b"Hello, this is a test input for encryption!"

output = encryptor.encrypt(input, key)

print(f"Encrypted: {output.hex(sep=" ")}")
```
