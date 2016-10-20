#!/usr/bin/python
import sys
import base64

# Define constants
CHALLENGE_NUMBER_KEY      = "challengeNum"
CHALLENGE_DESCRIPTION_KEY = "challengeDescription"
CHALLENGE_FUNCTION_KEY    = "challengeFunction"
CHALLENGES_MAXIMUM_NUM    = 64
CHALLENGES_COMPLETED_NUM  = 2

# Initialize global variables
challengeMap = {}


def challenge01():
  """
  Challenge 01: "Convert hex to base64"  
  
  The string:
    49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
  Should produce:
    SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t
  """
  hexString = None
  try:
    hexString = getSysArg(2)
    if not isHex(hexString):
      raise Exception("Input is not valid hex.")
  except Exception as e:
    raise Exception(str(e))

  b64String = hexToBase64(hexString)
  print "[+] HEX: {0}".format(hexString)
  print "[+] B64: {0}".format(b64String)


def challenge02():
  """
    Challenge 02: "Fixed XOR"
    
    Write a function that takes two equal-length buffers and produces their XOR 
    combination.
    
    If your function works properly, then when you feed it the string:
      1c0111001f010100061a024b53535009181c
    After hex decoding, and when XOR'd against:
      686974207468652062756c6c277320657965
    Should produce:
      746865206b696420646f6e277420706c6179
  """
  hexInput01 = None
  hexInput02 = None
  try:
    hexInput01 = getSysArg(2)
    hexInput02 = getSysArg(3)
    if not isHex(hexInput01):
      raise Exception("input 1 is not valid hex.")
    if not isHex(hexInput02):
      raise Exception("input 2 is not valid hex.")
    if len(hexInput01) is not len(hexInput02):
      raise Exception("input 1 is not the same length as input 2")
  except Exception as e:
    raise Exception(str(e))

  hexOutput = "%x" % (int(hexInput01, 16) ^ int(hexInput02, 16))
  print "[+] INPUT1:  {0}".format(hexInput01)
  print "[+] INPUT2:  {0}".format(hexInput02)
  print "[+] OUTPUT:  {0}".format(hexOutput)


# Populate challengeMap with details for challenges
challenge01Map = {
  CHALLENGE_NUMBER_KEY      : 1, 
  CHALLENGE_DESCRIPTION_KEY : "Convert hex to base64",
  CHALLENGE_FUNCTION_KEY    : challenge01
}

challenge02Map = {
  CHALLENGE_NUMBER_KEY      : 2,
  CHALLENGE_DESCRIPTION_KEY : "Fixed XOR",
  CHALLENGE_FUNCTION_KEY    : challenge02
}

challengeMap[1] = challenge01Map
challengeMap[2] = challenge02Map


def hexToBase64(hexString):
  """
  Convert a hexadecimal string into a base64 string representing the same data.

  Parameters:
    hexString -- String of hexadecimal characters

  Returns:
    base64 string representing the same data as the hexString input.
  """
  return hexString.decode("hex").encode("base64")


def getSysArg(argNum):
  """
  Obtain the command line argument at the position specified as input.

  Parameters:
    argNum - The argument number to retrieve from argv

  Returns:
    The user-provided command-line argument at the requested index of argv

  Raises:
    Exception - If no argument was provided at the specified index
  """
  try:
    result = sys.argv[argNum]
    return result
  except Exception as e:
    raise Exception("Missing Argument")



def isHex(hexString):
  """
  Determine if a string is a valid hexadecimal representation of data.

  Parameters:
    hexString - The string to test for valid hexadecimal representation of data.

  Returns:
    True  - If the string provided contains only valid hexadecimal characters. 
    False - If the string provided contains invalid hexadecimal characters.
  """
  try:
    hexValue = int(hexString, 16)
    return True
  except Exception as e:
    return False



def banner(challengeString):
  """
  Display a simple banner to the user indicating the challenge being completed.

  Parameters:
    challengeString - The description of the challenge
  """
  progName = None
  try:
    progName = getSysArg(0).split("/")[-1].rstrip(".py")  
  except:
    progName = "$PROGRAM_NAME"

  lineLength = len(challengeString)
  print "=" * lineLength
  print "{0}{1}{0}".format(" " * ((lineLength - len(progName)) / 2), progName)
  print "-" * lineLength
  print challengeString
  print "=" * lineLength


def usage():
  """
  Display a simple message to the user with usage instructions.
  """
  print "usage: {0} [challenge #] [input]".format(sys.argv[0])


def exitWithError(errorMessage):
  """
  Exit the program with an exit code of -1 and a message describing the failure.

  Parameters:
    errorMessage - The error message describing the failure of the program.
  """
  print "[!] {0}".format(errorMessage)
  exit(-1)


def main():
  """
  The main entry-point into the program.
  """
  challengeNum = None

  # Check that argument 1 exists
  try:
    challengeNum = getSysArg(1)
  except Exception as e:
    usage()
    exit(-1)

  # Check that the specified challenge is between 1 and CHALLENGES_MAXIMUM_NUM
  try:
    challengeNum = int(challengeNum)
    if (0 >= challengeNum) or (challengeNum > CHALLENGES_MAXIMUM_NUM):
      raise Exception()
  except:
    exitWithError("Challenge number must be between 1 and {0}".format(CHALLENGES_MAXIMUM_NUM))

  # Check that the specified challenge has been completed
  if challengeNum > CHALLENGES_COMPLETED_NUM:
    exitWithError("Challenge {0} has not been completed yet.".format(challengeNum))

  #  Send a banner to the user describing what they have selected.
  challengeString = "Challenge {0}: {1}".format(challengeNum, challengeMap[challengeNum].get(CHALLENGE_DESCRIPTION_KEY))
  banner(challengeString)

  # Execute the challenge
  try:
    challengeMap[challengeNum].get(CHALLENGE_FUNCTION_KEY)()
  except Exception as ex:
    print "[!] Could not execute challenge {0}!".format(challengeNum)
    exitWithError(str(ex))


# Execute main() if this script is called directly.
if __name__ == "__main__":
  main()
