import sys
import re

def main():
    if len(sys.argv) < 2:
        print("Usage: python filter-tests.py <filename>")
        sys.exit(1)

    filename = sys.argv[1]

    try:
        with open(filename, 'r', encoding='ISO-8859-1') as file:
            lines = file.readlines()
    except FileNotFoundError:
        print(f"Error: File '{filename}' not found.")
        sys.exit(1)

    blocks = []
    current_block = []

    # Split lines into blocks separated by empty or whitespace-only lines
    for line in lines:
        current_block.append(line)
        if line.strip() == "":
            blocks.append(current_block)
            current_block = []
    if current_block:
        blocks.append(current_block)

    # Process each block
    for block in blocks:
        if all(re.match(r'^\s*#', line) for line in block):
            # Comment block
            sys.stdout.buffer.write("".join(block).encode('ISO-8859-1'))
        elif any(re.match(r'^Failed: error \d+', line) for line in block):
            # Fail block - print all lines except the "Failed" lines
            for line in block:
                if not re.match(r'^Failed:', line) and not re.match(r'^\s*\*\*', line):
                    sys.stdout.buffer.write(line.encode('ISO-8859-1'))
        else:
            # Other block - print only comment lines
            for line in block:
                if re.match(r'^\s*#', line) or line.strip() == "":
                    sys.stdout.buffer.write(line.encode('ISO-8859-1'))

if __name__ == "__main__":
    main()