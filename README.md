# BinaryStream
**Part of [Bedrock Procotol Library](https://github.com/GlacieTeam/ProtocolLib).**  
A BinaryStream Library written in C++

## Usage
```C++
using namespace bedrock_protocol;

// Read
std::string inputBuffer; // Buffer to read

ReadOnlyBinaryStream inputStream(inputBuffer);
uint8_t     byte   = inputStream.getByte();
int         varint = inputStream.getVarInt();
std::string str    = inputStream.getString();
// ... 


// Write
BinaryStream outputStream;
outputStream.writeFloat(3.1415f);
outputStream.writeUnsignedVarInt64(1234567890);
outputStream.writeSignedShort(16384);
//...

std::string outputBuffer = outputStream.getAndReleaseData();
std::string outputBuffer = outputStream.getAndReleaseData();
```

## Install
```xmake
add_repositories("groupmountain-repo https://github.com/GroupMountain/xmake-repo.git")

add_requires("binarystream")
```

## Build
- Build with Xmake
```bash
xmake --all
```
- If you want to use Cmake build system, you can generate CmakeLists.txt
```bash
xmake project -k cmake
```

## License
- Please note that this project is licensed under the LGPLv3.
- If you modify or distribute this project, you must comply with the requirements of the LGPLv3 license, including but not limited to providing the complete source code and retaining the copyright notices. For more detailed information, please visit the GNU Official Website.

### Copyright © 2025 GlacieTeam. All rights reserved.