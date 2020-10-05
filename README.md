# DVDAuth
This is a CSS or CPPM or CPRM authentication tool

## Usage
        DVDAuth.exe <DriveLetter> <ProtectType> <OutFile>
        ProtectType: css or cppm or cprm

## Development Tool
- Windows  
  Visual Studio 2019 (Visual C++ 2019)  
  - Windows build
    - [Windows Driver Kit (WDK) 7.1.0](https://www.microsoft.com/en-us/download/details.aspx?id=11800)

  - Linux build
    - Windows Subsystem for Linux (WSL)
      https://devblogs.microsoft.com/cppblog/targeting-windows-subsystem-for-linux-from-visual-studio/  
      https://docs.microsoft.com/en-us/windows/wsl/install-win10

- Linux
  - gcc, make

## License
 See LICENSE  
 Original source (libdvdcpxm) is DVD-Audio Explorer of Adam Sampson 
  https://offog.org/git/dvdaexplorer/  
 Or foo_input_dvda-0.4.11  
  https://sourceforge.net/projects/dvdadecoder/files/foo_input_dvda/
