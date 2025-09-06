Param([STRING]$fileName, [INT]$numBytes = 32)
# Markus Scholtes 2025
# XOR of the first n bytes of a file
# A second call with the same parameters restores the file to its original state
# Invocation: XORFile.ps1 <FILENAME> [<COUNTOFBYTES>]
# <COUNTOFBYTES> defaults to 32

if ([STRING]::IsNullOrEmpty($fileName))
{
	Write-Output "Invocation: XORFile <FILENAME> [<COUNTOFBYTES>]"
	return
}
if ($numBytes -le 0)
{
	Write-Output "Count of bytes must be positive."
	return
}

try {
	$dataArray = New-Object byte[] $numBytes

	$filestream = New-Object System.IO.FileStream($fileName, "Open", "ReadWrite")

	$numBytes = $fileStream.Read($dataArray, 0, $numBytes)

	[VOID]$fileStream.Seek(0, [System.IO.SeekOrigin]::Begin)

	Write-Host -NoNewline "Original value(s): "
	for ($i = 0; $i -lt $numBytes; $i++)
	{
		Write-Host -NoNewline "[$($dataArray[$i].ToString('X2'))]"
		$dataArray[$i] = $dataArray[$i] -bxor 0xFF
	}

	Write-Host -NoNewline "`r`nNew value(s): "
	for ($i = 0; $i -lt $numBytes; $i++)
	{
		Write-Host -NoNewline "[$($dataArray[$i].ToString('X2'))]"
	}
	$fileStream.Write($dataArray, 0 , $numBytes)

	$fileStream.Close()
}
catch
{
	Write-Output "Error processing file '$fileName'"
	$_.Exception.Message
}
