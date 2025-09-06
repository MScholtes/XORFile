# XORFile
XOR the first bytes of a file

## More of a fun project.

I find it very annoying that modern virus scanners unpack ZIP archives and scan them for viruses. This is a good thing in itself, but with large archives, the ZIP files are blocked for a long time. I have already managed to block files until the next system restart with trying to access them too early.

Renaming the archive is not enough because ZIP files have a known header (‘*PK*’).

For this reason, I wrote **XORFile**, which (by default) changes the first 32 bytes with the XOR operator so that virus scanners no longer recognise that it is an archive file. A second run of **XORFile** restores the original state (this also works with other file types).

And since this is a fun project, I paid attention to good performance in using ‘*Seek*’ (only the bytes to be changed are processed, not the entire file) and wrote it in 3 languages: C++, C# and Powershell.

## Powershell One Liner
One liner to copy and paste to your console window

First, set the name (and path) of the file you want to change in varable $N and the number of bytes you want to XOR in variable $B, e.g.
```powershell
$B = 32
$N = ".\VeryLargeArchiveFile.zip"
```
Then paste the following code to your Powershell console and execute
```powershell
$A=[byte[]]::new($B);$S=New-Object IO.FileStream($N,3,3);$B=$S.Read($A,0,$B);0..($B-1)|%{$A[$_]=$A[$_]-bxor 255};[VOID]$S.Seek(0,0);$S.Write($A,0,$B);$S.Close()
```

**You're done**

A second run will restore the file to its original state.

## C++
1. Download **CPP\XORFile.cpp**
2. Start a **Developer Command Prompt for Visual Studio**, change to the  directory you saved **XORFile.cpp**
3. Execute _**cl XORFile.cpp**_

or download **CPP\XORFILE.exe**

Then you can process a file with
```cmd
XORFile <FILENAME> [<COUNTOFBYTES>]
```
**&lt;COUNTOFBYTES&gt;** defaults to 32.
