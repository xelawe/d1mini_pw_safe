#include "FS.h"

String confnbr;
String sealnbr = "123456";
boolean conf_void = false;

boolean fileWrite(String name, String content) {
  //open the file for writing.
  //Modes:
  //"r"  Opens a file for reading. The file must exist.
  //"w" Creates an empty file for writing. If a file with the same name already exists, its content is erased and the file is considered as a new empty file.
  //"a" Appends to a file. Writing operations, append data at the end of the file. The file is created if it does not exist.
  //"r+"  Opens a file to update both reading and writing. The file must exist.
  //"w+"  Creates an empty file for both reading and writing.
  //"a+"  Opens a file for reading and appending.:

  //choosing w because we'll both write to the file and then read from it at the end of this function.
  File file = SPIFFS.open(name.c_str(), "w");

  //verify the file opened:
  if (!file) {
    //if the file can't open, we'll display an error message;
    String errorMessage = "Can't open '" + name + "' !\r\n";
    Serial.println(errorMessage);
    return false;
  } else {
    //To all you old school C++ programmers this probably makes perfect sense, but to the rest of us mere mortals, here is what is going on:
    //The file.write() method has two arguments, buffer and length. Since this example is writing a text string, we need to cast the
    //text string (it's named "content") into a uint8_t pointer. If pointers confuse you, you're not alone!
    //I don't want to go into detail about pointers here, I'll do another example with casting and pointers, for now, this is the syntax
    //to write a String into a text file.
    file.write((uint8_t *)content.c_str(), content.length() + 2);
    file.close();
    return true;
  }
}

String fileRead(String name) {
  //read file from SPIFFS and store it as a String variable
  String contents;
  File file = SPIFFS.open(name.c_str(), "r");
  if (!file) {
    String errorMessage = "Can't open '" + name + "' !\r\n";
    Serial.println(errorMessage);
    return "FILE ERROR";
  }
  else {

    // this is going to get the number of bytes in the file and give us the value in an integer
    int fileSize = file.size();
    int chunkSize = 1024;
    //This is a character array to store a chunk of the file.
    //We'll store 1024 characters at a time
    char buf[chunkSize];
    int numberOfChunks = (fileSize / chunkSize) + 1;

    int count = 0;
    int remainingChunks = fileSize;
    for (int i = 1; i <= numberOfChunks; i++) {
      if (remainingChunks - chunkSize < 0) {
        chunkSize = remainingChunks;
      }
      file.read((uint8_t *)buf, chunkSize - 1);
      remainingChunks = remainingChunks - chunkSize;
      contents += String(buf);
    }
    file.close();
    return contents;
  }
}


boolean fileRemove(String name) {
  //read file from SPIFFS and store it as a String variable
  SPIFFS.remove(name.c_str());
  return true;
}


void init_config() {
  //Turn on SPIFFS and mount the file system:
  Serial.println("starting SPIFFS....");
  SPIFFS.begin();

  String confnbr = fileRead("/sealnbr.txt");
  if (confnbr == "FILE ERROR") {
    Serial.println("awww CRUD. file read failed");
  } else {
    Serial.println("OH YEAH, here's the contents of your file:");
    Serial.println("-----------------------------");
    Serial.println(confnbr);
  }
  confnbr.trim();
  Serial.println(confnbr);

  if ( confnbr == sealnbr ) {
    // Seal Number was already stored -> Seal is broken!
    Serial.println("Seal is broken!");
    conf_void = true;
    return;
  }

  if ( conf_void == false ) {
    // actual seal number is not stored -> write to FS
    //Write to a file in SPIFFS.
    Serial.println("Writing to a file");
    boolean successfulWrite = fileWrite("/sealnbr.txt", sealnbr);
    if (successfulWrite) {
      Serial.println("file write success!");
    } else {
      Serial.println("awww CRUD. file write failed");
    }

  }

}

