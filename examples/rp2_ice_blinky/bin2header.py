# Convert a binary file to a C header

import sys

# Read the input file
binary_data = open(sys.argv[1], 'rb').read()

# Print it as hexadecimal
print(', '.join(map(hex, binary_data)))
