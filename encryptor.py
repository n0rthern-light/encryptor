#!/usr/bin/env python3

import os
import subprocess
import sys
import tempfile

# Get the current script's directory
SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))
CRYPTOR_BINARY = os.path.join(SCRIPT_DIR, 'encryptor/bin/cryptor')

def run_cryptor(mode, data, key):
    """Execute the cryptor binary for encryption or decryption using temporary files."""

    try:
        with tempfile.NamedTemporaryFile(delete=False, mode="wb") as data_file, tempfile.NamedTemporaryFile(delete=False, mode="wb") as key_file:
            data_file.write(data)
            data_file.flush()
            key_file.write(key)
            key_file.flush()

            #print(data_file.name, key_file.name)
            result = subprocess.run(
                [CRYPTOR_BINARY, mode, data_file.name, key_file.name],
                stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True
            )

            data_file.close()
            key_file.close()
            os.unlink(data_file.name)
            os.unlink(key_file.name)

            if result.returncode != 0:
                print(f"Cryptor execution failed with error:\n{result.stderr}", file=sys.stderr)
                sys.exit(1)

            buffer = b""
            with open(data_file.name + ".out", "rb") as f:
                buffer = f.read()

            os.unlink(data_file.name + ".out")
            return buffer

    except Exception as e:
        print(f"Error executing cryptor: {e}", file=sys.stderr)
        sys.exit(1)

def encrypt(data, key):
    """Encrypt using the cryptor binary."""
    encrypted = run_cryptor("-e", data, key)
    
    # Verify encryption correctness by decrypting
    decrypted = decrypt(encrypted, key)
    if decrypted != data:
        print(decrypted)
        print(data)
        print("FAILURE: Encryption verification failed!", file=sys.stderr)
        sys.exit(1)
    
    return encrypted

def decrypt(data, key):
    """Decrypt using the cryptor binary."""
    return run_cryptor("-d", data, key)

